/* ext2.c
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* implementation of the ext2 (revision 0) file system.
 * A description of data structures in the ext2 file system can be found at:
 * http://www.nongnu.org/ext2-doc/ext2.html
 *
 * This implementation is simplified. Main limitations are:
 * - double/triple indirection not supported
 * - symbolic links not supported (always handled as regular files)
 * - maximum number of block groups in the partition (CONFIG_EXT2_MAX_BLKGRP)
 * - no update of superblock data (mount count...)
 * - no support for behaviour control flags (compression, append only,
 *   indexed dir...)
 */

#include "config.h"
#include "disk.h"
#include "panic.h"
#include "direntry.h"
#include "ext2.h"
#include "inode.h"
#include "stat.h"
#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

/* constants */
#define EXT2_SUPER_MAGIC 0xef53

/* superblock */
struct superblk_t {
    uint32_t s_inodes_count;      /* # inodes */
    uint32_t s_blocks_count;      /* # blocks */
    uint32_t s_r_blocks_count;    /* # reserved blocks (for super user) */
    uint32_t s_free_blocks_count; /* # free blocks */
    uint32_t s_free_inodes_count; /* # free inodes */
    uint32_t s_first_data_block;  /* block containing the superblock */
    uint32_t s_log_block_size;    /* block size */
    uint32_t s_log_frag_size;     /* fragment size */
    uint32_t s_blocks_per_group;  /* # blocks per group */
    uint32_t s_frags_per_group;   /* # fragments per group */
    uint32_t s_inodes_per_group;  /* # inodes per group */
    uint32_t s_mtime;             /* last mount time */
    uint32_t s_wtime;             /* last write access time */
    uint16_t s_mnt_count;         /* current mount count without check */
    uint16_t s_max_mnt_count;     /* max mount count without check */
    uint16_t s_magic;             /* magic ext2 signature */
    uint16_t s_state;             /* FS state */
    uint16_t s_errors;            /* behaviour in case of error */
    uint16_t s_minor_rev_level;   /* minor revision level */
    uint32_t s_lastcheck;         /* time of last check */
    uint32_t s_checkinterval;     /* maximum time between checks */
    uint32_t s_creator_os;        /* OS which created the FS */
    uint32_t s_rev_level;         /* revision level */
    uint16_t s_def_resuid;        /* default uid for reserved blocks */
    uint16_t s_def_resgid;        /* default gid for reserved blocks */
    uint32_t s_padding [235];     /* padding to the end of the block */
};
struct superblk_t superblk;

/* block group descriptor and table */
struct group_desc_t {
    uint32_t bg_block_bitmap;      /* "block bitmap" block */
    uint32_t bg_inode_bitmap;      /* "inode bitmap" block */
    uint32_t bg_inode_table;       /* first "inode table" block */
    uint16_t bg_free_blocks_count; /* # free blocks */
    uint16_t bg_free_inodes_count; /* # free indodes */
    uint16_t bg_used_dirs_count;   /* # directories */
    uint16_t bg_pad;               /* padding */
    uint32_t bg_reserved [3];      /* reserved. used for padding */
};
#define __sizeof_group_desc (sizeof (struct group_desc_t))
struct group_desc_t grp_tbl [CONFIG_EXT2_MAX_BLKGRP];

/* inode */
struct inode_t {
    uint16_t i_mode;        /* file mode */
    uint16_t i_uid;         /* owner uid */
    uint32_t i_size;        /* file size (bytes) */
    uint32_t i_atime;       /* time of last access */
    uint32_t i_ctime;       /* time of creation */
    uint32_t i_mtime;       /* time of last modification */
    uint32_t i_dtime;       /* time of deletion */
    uint16_t i_gid;         /* group gid */
    uint16_t i_links_count; /* # hard links */
    uint32_t i_blocks;      /* # blocks */
    uint32_t i_flags;       /* implementation behaviour */
    uint32_t i_osd1;        /* OS dependent */
    uint32_t i_block [15];  /* pointers to blocks */
    uint32_t i_generation;  /* file version */
    uint32_t i_file_acl;    /* file access control list */
    uint32_t i_dir_acl;     /* directory access control list */
    uint32_t i_faddr;       /* fragment location */
    uint32_t i_osd2 [3];    /* OS dependent */
};
#define __sizeof_inode (sizeof (struct inode_t))

/* directory entry (without file name) */
struct direntry_t {
    uint32_t inode;    /* inode number */
    uint16_t rec_len;  /* displacement to the next direntry */
    uint16_t name_len; /* name length */
};
#define __sizeof_direntry (sizeof (struct direntry_t))

static ino_t ext2_root_ino = EXT2_ROOT_INO; /* root directory inode */

/* block size in bytes */
#define __BLK_SIZE ((unsigned int)(512 << superblk.s_log_block_size))

/* cache for disk I/O (used to store one block: max block size = 4096) */
#define __LOG_MAX_BLK_SIZE 2
unsigned char cache [512 << __LOG_MAX_BLK_SIZE];

/* convert a block number into an offset on the disk */
#define blk2off(block) ((block) << (10 + superblk.s_log_block_size))

/* inode number to block group and index of the inode table entry */
#define ino2grp(ino) (((ino)-1) / superblk.s_inodes_per_group)
#define ino2idx(ino) (((ino)-1) % superblk.s_inodes_per_group)

/* offset in a file to block unit and offset in this block */
#define offset2blk_n(offset) ((offset) >> (10 + superblk.s_log_block_size))
#define offset2blk_n_off(offset) ((offset) & (__BLK_SIZE - 1))

/* fill an inode structure.
 * return -EIO in case of low-level I/O error, 0 otherwise */
static int fill_inode (uint32_t ino, struct inode_t *inode) {
    /* find the disk offset of the inode table entry */
    uint32_t ino_tbl_blk = grp_tbl[ino2grp (ino)].bg_inode_table;
    uint32_t ino_idx = ino2idx (ino);
    uint64_t ino_off = blk2off (ino_tbl_blk) + (ino_idx * __sizeof_inode);
    /* read the inode entry */
    if (!disk_read (ino_off, inode, __sizeof_inode)) return -EIO;
    return 0;
}

/* store an inode structure.
 * return -EIO in case of low-level I/O error, 0 otherwise */
static int update_inode (uint32_t ino, struct inode_t *inode) {
  /* find the disk offset of the inode table entry */
  uint32_t ino_tbl_blk = grp_tbl[ino2grp (ino)].bg_inode_table;
  uint32_t ino_idx = ino2idx (ino);
  uint64_t ino_off = blk2off (ino_tbl_blk) + (ino_idx * __sizeof_inode);
  /* write the inode entry */
  if (!disk_write (ino_off, inode, __sizeof_inode)) return -EIO;
  return 0;
}

/* copy the n-th block of a file into the cache.
 * return __GET_FILE_BLK_OK if no error
 * return __GET_FILE_BLK_EOF if blk above the end of the file
 * return -EIO in case of I/O error
 * return -EFBIG if the file is too big for this implementation */
#define __GET_FILE_BLK_OK 0
#define __GET_FILE_BLK_EOF 1
#define __disk_blk_to_cache(blk)				      \
({  if ((blk) == 0) return __GET_FILE_BLK_EOF;                      \
  if (!disk_read (blk2off (blk), cache, __BLK_SIZE)) return -EIO;   \
})

int ext2_find_free_blk (uint32_t ino){

  int retval;
  // check grp_tbl for free blocks
  // -- first check inode's group
  uint32_t blkgrp_count;
  uint32_t group = ino2grp(ino);
  bool group_found = 0;
  blkgrp_count = ((superblk.s_blocks_count-1) / superblk.s_blocks_per_group) + 1;
  if (grp_tbl[group].bg_free_blocks_count <= 0){
    // if group is full find a group that isn't
    for (group = 0; group < blkgrp_count; group++){
      if (grp_tbl[group].bg_free_blocks_count > 0) {
        group_found = 1;
        break;
      }
    }
    if (!group_found) return -EFBIG;
  }

  // find nearest free block
  // -- load in block bitmap
  uint32_t tbl_blk_bit = grp_tbl[group].bg_block_bitmap;
  unsigned char *blk_bitmap;
  uint32_t free_blk;
  bool block_found = 0;
  uint32_t map_index;
  uint32_t bit_index;
  unsigned char bits[8];
  blk_bitmap = malloc(__BLK_SIZE);
  if (!disk_read (blk2off (tbl_blk_bit), blk_bitmap, __BLK_SIZE)) return -EIO;

  for (int i = 0; i < __BLK_SIZE; i++){
    // if full skip
    if((ssize_t)blk_bitmap[i] == 255) continue;
    else {
      //printf("%d\n", blk_bitmap[i]);
      for (int j = 0; j < 8; j++){
        bits[j] = (blk_bitmap[i] >> j) & 1;
        if((!block_found) && (bits[j] == 0)){
          map_index = i;
          bit_index = j;
          free_blk = (i*8)+j;
          block_found = 1;
        }
      }
      //printf("%d%d%d%d%d%d%d%d\n", bits[7], bits[6], bits[5], bits[4], bits[3], bits[2], bits[1], bits[0]);
      if (block_found) break;
    }
  }

  if (!block_found) return -EFBIG;

  uint32_t block = group*superblk.s_blocks_per_group + free_blk + 1;
  //printf("block: %d\n", block);

  // mark block as used
  bits[bit_index] = 1;
  //printf("%d%d%d%d%d%d%d%d\n", bits[7], bits[6], bits[5], bits[4], bits[3], bits[2], bits[1], bits[0]);
  unsigned int val = 0;
  for (int i = 0; i < 8; i++){
    val |= bits[i] << i;
  }
  blk_bitmap[map_index] = val;
  if (!disk_write (blk2off (tbl_blk_bit), blk_bitmap, __BLK_SIZE)) return -EIO;

  // update block group and superblock free and used block counts
  superblk.s_free_blocks_count--;
  grp_tbl[group].bg_free_blocks_count--;

  return block;

}

/* allocate a free block to an inode */
int ext2_blk_allocate (uint32_t ino, struct inode_t* inode, uint32_t blk_n) {

  int retval;

  // find free block
  uint32_t block;
  if ((block = ext2_find_free_blk(ino)) < 0) return block;
  
  // add block to inode array
  if (blk_n < 12){
    // direct
    inode->i_blocks++;
    inode->i_block[blk_n] = block;
    if ((retval = update_inode (ino, inode)) < 0) return retval;
  }
  else if (blk_n < 12 + (__BLK_SIZE >> 2)) {
    // indirect
    // -- check if indirect block has been assigned yet
    if ((blk_n == 12) && (inode->i_block[12] == 0)){
      // assign indirect block
      inode->i_block[blk_n] = block;
      // find new block to allocate data to
      if ((block = ext2_find_free_blk(ino)) < 0) return block;
      if ((retval = update_inode (ino, inode)) < 0) return retval;
    }
    __disk_blk_to_cache (inode->i_block [12]);
    cache [blk_n - 12] = block;
    if (!disk_read (blk2off (inode->i_block [12]), cache, __BLK_SIZE)) return -EIO;
  }
  
  return 1;
}

/* Find next block for file */
static int get_file_blk (struct inode_t* inode, uint32_t blk_n, uint32_t ino, int create) {
    if (blk_n < 12) { /* direct blocks */
        uint32_t disk_blk = inode->i_block [blk_n];
        // check if read or write
	if (!create){
	  __disk_blk_to_cache (disk_blk);
	} else {
	  //printf("disk_blk: %d\n", disk_blk);
	  if ((disk_blk) == 0){
	    //add block to inode
	    if(!ext2_blk_allocate(ino, inode, blk_n)) return -EFBIG;
	  }
	}
        return __GET_FILE_BLK_OK;
    }
    else if (blk_n < 12 + (__BLK_SIZE >> 2)) { /* simple indirection */
        uint32_t disk_blk, ind_blk = inode->i_block [12];
	__disk_blk_to_cache (ind_blk);
	disk_blk = ((uint32_t *) (cache)) [blk_n - 12];
        if (!create){
	  __disk_blk_to_cache (disk_blk);
	} else {
	  if ((disk_blk) == 0){
            //add block to inode
	    if(!ext2_blk_allocate(ino, inode, blk_n)) return -EFBIG;
          }
        }
        return __GET_FILE_BLK_OK;
    }
    return -EFBIG; /* double/triple indirection not supported yet */
}

#define mount_error(format, ...)    \
({  kwarning (format, ##__VA_ARGS__); return false; })
bool ext2_mount () {
    uint32_t blkgrp_count;

    /* initialize the disk */
    if (!disk_initialize ()) return false;

    /* read superblock at offset 1024 from the beginning of the partition */
    if (!disk_read (1024, (void *)(&superblk), 1024))
        mount_error ("can't read partition superblock");

    /* check that this file system is supported */
    if (superblk.s_magic != EXT2_SUPER_MAGIC)
        mount_error ("file system is not ext2");
    if (superblk.s_rev_level != 0)
        mount_error ("revision %d of ext2 is not supported",
            superblk.s_rev_level);

    /* check that the block size is supported */
    if (superblk.s_log_block_size > __LOG_MAX_BLK_SIZE)
        mount_error ("block size too big: %u bytes", __BLK_SIZE);

    /* check the number of block groups */
    blkgrp_count =
        ((superblk.s_blocks_count-1) / superblk.s_blocks_per_group) + 1;
    //printf("blkgrp_count: %d\n", blkgrp_count);
    if (blkgrp_count > CONFIG_EXT2_MAX_BLKGRP)
        mount_error ("ext2 partition has %u block groups (max = %u)",
            blkgrp_count, CONFIG_EXT2_MAX_BLKGRP);

    /* read the block groups table */
    if (!disk_read (blk2off (superblk.s_first_data_block+1),
        (void *)(grp_tbl), blkgrp_count * __sizeof_group_desc))
        mount_error ("can't read block group table at block %u (%u blocks)",
            superblk.s_first_data_block+1, blkgrp_count);

    return true;
}

bool ext2_unmount () {
  
  uint32_t blkgrp_count = ((superblk.s_blocks_count-1) / superblk.s_blocks_per_group) + 1;
  // update block group info on disk
  if (!disk_write (blk2off (superblk.s_first_data_block+1),
		  (void *)(grp_tbl), blkgrp_count * __sizeof_group_desc))
    mount_error ("can't write block group table at block %u (%u blocks)",
		 superblk.s_first_data_block+1, blkgrp_count);
  // update superblock info on disk
  if (!disk_write (1024, (void *)(&superblk), 1024))
    mount_error ("can't write partition superblock");
  // finalize disk
  if (!disk_finalize ()) return false;

  return true;
}

int ext2_lookup (ino_t parent, const char *name, int name_len, ino_t *ino) {
    struct inode_t parent_inode;
    int retval, blk = 0;
    if (name_len > MAX_FILE_NAME_SIZE) return -ENAMETOOLONG;

    /* retrieve the parent inode and check that it is a directory */
    if ((retval = fill_inode (parent, &parent_inode)) < 0) return retval;
    if (!S_ISDIR (parent_inode.i_mode)) return -ENOTDIR;

    /* loop through the directory blocks */
    while ((retval = get_file_blk (&parent_inode, blk++, parent, 0)) !=
        __GET_FILE_BLK_EOF) {
        uint16_t offset = 0;
        /* loop through the directory entries in that block */
        while (offset < __BLK_SIZE) {
            struct direntry_t dir;
            memcpy (&dir, cache + offset, __sizeof_direntry);
            /* check that this entry is not corrupted */
            if (offset + dir.name_len > __BLK_SIZE) return -ENOENT;
            /* check if this entry has the file name we look for */
            if ((dir.name_len == (uint16_t)name_len) &&
                (strncmp ((char *)(cache + offset + __sizeof_direntry), name,
                    name_len) == 0)) {
                *ino = dir.inode; return 0;
            }
            offset += dir.rec_len;
        }
    }
    return (((retval < 0) && (retval != -EFBIG)) ? retval : -ENOENT);
}

int ext2_fill_stat (ino_t ino, struct stat *buf) {
    struct inode_t inode;
    int retval; if ((retval = fill_inode (ino, &inode)) < 0) return retval;
    buf->st_dev = 1; /* only one disk device is mounted */
    buf->st_ino = ino;
    buf->st_mode = inode.i_mode;
    buf->st_nlink = inode.i_links_count;
    buf->st_uid = inode.i_uid;
    buf->st_gid = inode.i_gid;
    buf->st_rdev = 0;
    buf->st_size = inode.i_size;
    buf->st_blksize = 1024 << superblk.s_log_block_size;
    buf->st_blocks = inode.i_blocks << (superblk.s_log_block_size+1);
    buf->st_atime = (time_t)(inode.i_atime);
    buf->st_mtime = (time_t)(inode.i_mtime);
    buf->st_ctime = (time_t)(inode.i_ctime);
    return 0;
}

ssize_t ext2_read (struct inode *node, void *buf, off_t offset, size_t count)
{
    struct inode_t inode;
    size_t filesize = node->st.st_size;
    size_t max_to_read = filesize - offset;
    uint32_t first_blk = offset2blk_n (offset);
    uint32_t last_blk = offset2blk_n (offset + count - 1);
    off_t first_blk_beg_off = offset2blk_n_off (offset);
    off_t last_blk_end_off = offset2blk_n_off (offset + count - 1) + 1;
    uint32_t blk = first_blk;
    int retval;
    size_t bytes_read = 0;

    if ((count == 0) || (offset < 0) || ((size_t)(offset) >= filesize))
        return 0;
    if ((retval = fill_inode (node->st.st_ino, &inode)) < 0) return retval;

    printf ("ext2_read offset: %d, len: %d\n", offset, count);

    /* loop through the file blocks */
    while ((retval = get_file_blk (&inode, blk, node->st.st_ino, 0)) != __GET_FILE_BLK_EOF) {
        /* begin/end offset to read for this block */
        off_t beg = (blk == first_blk) ? first_blk_beg_off : 0;
        off_t end = (blk == last_blk) ? last_blk_end_off : (off_t)__BLK_SIZE;
        size_t to_read = fmin ((size_t)(end - beg), max_to_read);

        /* read from the disk cache into the destination buffer */
        memcpy (((char *)buf) + bytes_read, cache + beg, to_read);
        bytes_read += to_read; max_to_read -= to_read;

        /* last block to read => exit */
        if ((blk++ >= last_blk) || (bytes_read >= count) ||
            (max_to_read == 0))
            break;
    }
    return ((retval < 0) ? retval : (ssize_t)(bytes_read));
}

ssize_t ext2_write (struct inode *node, const void *data_buf,
                    off_t offset, size_t len)
{
#if 0    
  struct inode_t inode;
  int retval;

  if ((retval = fill_inode (node->st.st_ino, &inode)) < 0) return retval;

  /* read the inode entry */
  if (!disk_write (blk2off (inode.i_block [0]), data_buf, len)) return -EIO;
  
#endif
  //#if 0
  struct inode_t inode;
  int retval;
  size_t to_write;
  size_t written = 0;

  // load inode
  if ((retval = fill_inode (node->st.st_ino, &inode)) < 0) return retval;

  // zero check
  if ((len == 0) || (offset < 0))
    return 0;

  printf ("ext2_write offset: %d, len: %d\n", offset, len);
  // perform lock to prevent other ops accessing inode
  //lock(node->st.st_lock); // (this is just a dummy function right now and won't be needed until parallel)

  // loop through blocks until all data is written
//  for (uint32_t blk = 0; written < len; blk++){
   while (written < len) {
    uint32_t blk = offset2blk_n (offset);

    printf ("   blk: %d\n", blk);

    to_write = len - written;

    if((len-written) > __BLK_SIZE){
      to_write = __BLK_SIZE;
    }
    
//    printf("to_write: %d len: %d written: %d blk_size: %d\n", to_write, len, written, __BLK_SIZE);
    
    // get block to write to 
    if((retval = get_file_blk (&inode, blk, node->st.st_ino, 1)) == __GET_FILE_BLK_OK){
      // write data to block
      //printf("writing block: %d at location: %d\n", blk, blk2off (inode.i_block [blk]));
      if (!disk_write (blk2off (inode.i_block [blk]) + (offset), data_buf, to_write)) return -EIO;
      written += to_write;

      offset += to_write;
      data_buf = (const char *)data_buf + to_write;
    } else {
      return -EFBIG;
    }
  }

  inode.i_size = (inode.i_size > (offset)) ? inode.i_size : (offset);
   update_inode (node->st.st_ino, &inode);
   //unlock inode
  //unlock(node->st.st_lock); // (this is just a dummy function right now and won't be needed until parallel)
  //#endif
  return ((retval < 0) ? retval : (ssize_t)(len));

}

ssize_t ext2_readdir (struct inode *dirnode, struct direntry *dir,
    off_t offset) {
    struct inode_t dir_inode;
    int retval = 0;
    int blk = offset2blk_n (offset);
    off_t off_in_blk = offset2blk_n_off (offset);
    struct direntry_t direntry;

    /* retrieve the directory inode */
    if ((retval = fill_inode (dirnode->st.st_ino, &dir_inode)) < 0)
        return retval;
    /* retrieve the directory block. if EOF, return 0 */
    if ((retval = get_file_blk (&dir_inode, blk, dirnode->st.st_ino, 0)) != __GET_FILE_BLK_OK)
        return (((retval < 0) && (retval != -EFBIG)) ? retval : 0);

    /* retrieve the current directory entry */
    memcpy (&direntry, cache + off_in_blk, __sizeof_direntry);
    /* check that the entry is not corrupted */
    if ((unsigned int)(off_in_blk) + direntry.name_len > __BLK_SIZE) return 0;
    /* copy the entry into the destination direntry  */
    dir->inode = direntry.inode;
    dir->name_len = direntry.name_len;
    memcpy (dir->name, cache + off_in_blk + __sizeof_direntry,
        direntry.name_len);
    dir->name [direntry.name_len] = 0;

    return direntry.rec_len;
}

