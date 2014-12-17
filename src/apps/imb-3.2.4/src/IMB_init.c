/*****************************************************************************
 *                                                                           *
 * Copyright (c) 2003-2012 Intel Corporation.                                *
 * All rights reserved.                                                      *
 *                                                                           *
 *****************************************************************************

This code is covered by the Community Source License (CPL), version
1.0 as published by IBM and reproduced in the file "license.txt" in the
"license" subdirectory. Redistribution in source and binary form, with
or without modification, is permitted ONLY within the regulations
contained in above mentioned license.

Use of the name and trademark "Intel(R) MPI Benchmarks" is allowed ONLY
within the regulations of the "License for Use of "Intel(R) MPI
Benchmarks" Name and Trademark" as reproduced in the file
"use-of-trademark-license.txt" in the "license" subdirectory. 

THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
solely responsible for determining the appropriateness of using and
distributing the Program and assumes all risks associated with its
exercise of rights under this Agreement, including but not limited to
the risks and costs of program errors, compliance with applicable
laws, damage to or loss of data, programs or equipment, and
unavailability or interruption of operations.

EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT NOR
ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING
WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OR
DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 

EXPORT LAWS: THIS LICENSE ADDS NO RESTRICTIONS TO THE EXPORT LAWS OF
YOUR JURISDICTION. It is licensee's responsibility to comply with any
export regulations applicable in licensee's jurisdiction. Under
CURRENT U.S. export regulations this software is eligible for export
from the U.S. and can be downloaded by or otherwise exported or
reexported worldwide EXCEPT to U.S. embargoed destinations which
include Cuba, Iraq, Libya, North Korea, Iran, Syria, Sudan,
Afghanistan and any other country to which the U.S. has embargoed
goods and services.

 ***************************************************************************

For more documentation than found here, see

[1] doc/ReadMe_IMB.txt 

[2] Intel (R) MPI Benchmarks
    Users Guide and Methodology Description
    In 
    doc/IMB_Users_Guide.pdf
    
 File: IMB_init.c 

 Modifications IMB_2.3 => IMB_3.0:
 Better argument checking and error messages
 Include -h flag for help
 2 new auxiliary functions:
 IMB_chk_arg_int
 IMB_chk_arg_file
 

 Implemented functions: 

 IMB_basic_input;
 IMB_chk_arg_int
 IMB_chk_arg_file
 IMB_chk_arg_thread_level
 IMB_get_rank_portion;
 IMB_init_communicator;
 IMB_set_communicator;
 IMB_valid;
 IMB_set_default;

 ***************************************************************************/





#include "IMB_declare.h"
#include "IMB_benchmark.h"

/* IMB 3.1 << */
#include "IMB_mem_info.h"
/* >> IMB 3.1  */

#include "IMB_prototypes.h"

#define MAX_INT_LOG (31)

struct Blist_item
{
    const char *bname;
    int   next_index;
};


static struct Blist_item* pool =NULL;
static int pool_size = 0;
static int curr_pos  = 0;


/**** static functions declarations*****/
static int IMB_chk_arg_int  (int* val, char ***argv, int *argc, int iarg);
static int IMB_chk_arg_file (FILE** fd, char ***argv, int *argc, int iarg);
#ifdef USE_MPI_INIT_THREAD
static int IMB_chk_arg_thread_level(int* val, char **argv, int argc, int iarg);
#endif /*USE_MPI_INIT_THREAD*/

static void IMB_init_Blist_item_pool();
static void IMB_free_Blist_item_pool();

static void IMB_add_to_list_tail(const char*, int*, int*);
static void IMB_print_list	(int list_head_index);
static void IMB_remove_invalid_items( int* p_list_head, int* p_list_tail, int* n_cases);
static void IMB_remove_item_from_list( const char* name, int* p_list_head, int* p_list_tail, int *n_cases);

/********************************************************************/
static int IMB_chk_arg_int(int* val, char ***argv, int *argc, int iarg)
{
    /* Checks command line argument for being nonnegative integer */
    int ok;

    ok=1;
    if( iarg < *argc )
    {
	int tst=IMB_str_atoi((*argv)[iarg]);

	if( tst>=0 ) 
	{
	    *val=tst;
	} else ok=0;
    }
    else ok=0;

    return ok;
}


static int IMB_chk_arg_file(FILE** fd, char ***argv, int *argc, int iarg)
{
    /* Checks command line argument for being a file */
    int ok;

    *fd=(FILE*)NULL;

    ok=1;
    if( iarg < *argc )
    {
	FILE* tst=(FILE*) fopen((*argv)[iarg],"r");

	if( tst ) 
	{
	    *fd=tst;
	} else ok=0;
    }
    else ok=0;

    return ok;
}

#ifdef USE_MPI_INIT_THREAD
#ifdef WIN_IMB
#define STRCASECMP(s1,s2) _stricmp((s1),(s2))
#else /*linux*/
#define STRCASECMP(s1,s2) strcasecmp((s1),(s2))
#endif
static int IMB_chk_arg_thread_level(int* val, char **argv, int argc, int iarg)
{
    /* Checks command line argument for being nonnegative integer */
    int ok;

    ok=1;
    if( iarg < argc )
    {
	if( !STRCASECMP(argv[iarg], "single"))
	{
	    *val = MPI_THREAD_SINGLE;
	} else if( !STRCASECMP(argv[iarg], "funneled"))
	{
	    *val = MPI_THREAD_FUNNELED;
	} else if( !STRCASECMP(argv[iarg], "serialized"))
	{
	    *val = MPI_THREAD_SERIALIZED;
	} else if( !STRCASECMP(argv[iarg], "multiple"))
	{
	    *val = MPI_THREAD_MULTIPLE;
	}else 
	    ok=0;
    }
    else 
	ok=0;

    return ok;
}
#endif /*#ifdef USE_MPI_INIT_THREAD*/

#define N_baseinfo 15
/* IMB 3.1 << */
#define N_base_f_info 3  /* for float data */
/* >> IMB 3.1  */

/* IMB 3.1 << */
/*
   new "ITERATIONS" object for repetition count scheduling 
 
   major changes in interpreting the command line
*/

int IMB_basic_input(struct comm_info* c_info, struct Bench** P_BList, 
                    struct iter_schedule* ITERATIONS,
                    int *argc, char ***argv, int* NP_min)
/* >> IMB 3.1  */
/*



Input variables: 

-argc                 (type int *)                      
                      Number of command line arguments
                      

-argv                 (type char ***)                      
                      List of command line arguments
                      


Output variables: 

-NP_min               (type int*)                      
                      Minimum number of processes to run (-npmin command line argument)
                      

-P_BList              (type struct Bench**)                      
                      (For explanation of struct Bench type:
                      describes all aspects of modes of a benchmark;
                      see [1] for more information)
                      
                      Address of list of benchmarks to run;
                      list is set up.
                      

-c_info               (type struct comm_info*)                      
                      Collection of all base data for MPI;
                      see [1] for more information
                      


*/
{
    int i,n_cases,n_lens,iarg,iarg_msg;
    int deflt;
    int * ALL_INFO;
    //char** DEFC, **CMT;
/* IMB 3.1 << */
    float ALL_F_INFO[N_base_f_info];
/* >> IMB 3.1  */
    int ok;
/* IMB_3.0 */
    int help_only;

    int Blist_head, Blist_incl_head, Blist_excl_head;
    int Blist_tail, Blist_incl_tail, Blist_excl_tail;
    int n_cases_incl, n_cases_excl;
    enum {
	CONSTRUCT_BLIST,
	INCL_BLIST,
	EXCL_BLIST
    } blist_ind;

    help_only=0;

    *P_BList 	= (struct Bench *)NULL;

/* IMB 3.1 << */
    ITERATIONS->n_sample=0;
    ITERATIONS->off_cache=0;
    ITERATIONS->cache_size=-1;
    ITERATIONS->s_offs = ITERATIONS->r_offs = 0;
    ITERATIONS->s_cache_iter = ITERATIONS->r_cache_iter = 1;
    ITERATIONS->msgspersample=MSGSPERSAMPLE;
    ITERATIONS->msgs_nonaggr=MSGS_NONAGGR;
    ITERATIONS->overall_vol=OVERALL_VOL;
/* IMB_3.2: run time control as default */
    ITERATIONS->secs=SECS_PER_SAMPLE;
    ITERATIONS->iter_dyn=1;
    ITERATIONS->numiters=(int*)NULL;
/* >> IMB 3.1  */

    MPI_Comm_rank(MPI_COMM_WORLD,&c_info->w_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&c_info->w_num_procs);

    unit = stdout; 

    if( c_info->w_rank == 0 && strlen(OUTPUT_FILENAME) > 0 )
    unit = fopen(OUTPUT_FILENAME,"w"); 

    deflt = 0;
    ok = 0;
    iarg_msg=-1;

    c_info->group_mode = -1;
#ifdef MPIIO
    *NP_min=1;
#else
    *NP_min=2;
#endif

    if( c_info->w_rank == 0 )
    {
	/* Interpret command line */
	n_lens = 0;
	n_cases   = n_cases_incl = n_cases_excl = 0;

	IMB_init_Blist_item_pool(); 
	Blist_head = Blist_incl_head = Blist_excl_head =
	Blist_tail = Blist_incl_tail = Blist_excl_tail = -1;

	if( *argc <= 1 )
	{
	    /* Take default */
	    deflt = 1;
	}
	else
	{

	    blist_ind = CONSTRUCT_BLIST;

	    iarg = 1;
       
	    while( iarg <= *argc-1 )
	    {

		if(!strcmp((*argv)[iarg],"-h") || !strcmp((*argv)[iarg],"-help"))
		{

		    help_only=1;
		    break;

		} else if(!strcmp((*argv)[iarg],"-npmin"))
		{
		    /* IMB_3.0: Better arg checking for following cases */
		    if( !IMB_chk_arg_int(NP_min,argv,argc,iarg+1) || (*NP_min<=0) )
		    {
			ok=-1;
			fprintf(stderr,"Invalid argument after \"npmin\"\n");
			break;
		    }

		    iarg++;

		    blist_ind = CONSTRUCT_BLIST;

		} else if(!strcmp((*argv)[iarg],"-multi"))
		{

		    int tst;
		    if( !IMB_chk_arg_int(&tst,argv,argc,iarg+1) )
		    {
			ok=-1;
		    }
		    else if( tst==0 || tst==1 )
		    {
			c_info->group_mode=tst;
		    }
		    else
		    {
			ok=-1;
		    }

		    if( ok==-1 ) 
		    {
			 fprintf(stderr,"Invalid argument after \"multi\"\n");
			 break;
		    }

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-off_cache"))
		{
		    int ierr, cls;
		    float cs;
		    if( iarg+1>=*argc ) 
		    {
			fprintf(stderr,"Missing argument after \"off_cache\"\n");
			ok=-1;
			break;
		    }

		    ierr=sscanf((*argv)[iarg+1],"%f,%d",&cs,&cls);
		    if( ierr==1 ) 
		    {
			if( cs<0. ) cs=CACHE_SIZE;
			cls=CACHE_LINE_SIZE;
		    }
		    else if( ierr!=2 )
		    {
			fprintf(stderr,"Invalid off_cache selection\n");
			ok = -1;
			break;
		    } 

		    ITERATIONS->cache_size = cs;
		    ITERATIONS->cache_line_size = cls;
		    ITERATIONS->off_cache=1;

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-iter"))
		{

		    int ierr, msgs, overall_vol, msgs_nonaggr;
		    if( iarg+1>=*argc ) 
		    {
			fprintf(stderr,"Missing argument after \"iter\"\n");
			ok=-1;
			break;
		    }

		    ierr=sscanf((*argv)[iarg+1],"%d,%d,%d",&msgs,&overall_vol,&msgs_nonaggr);
		    if( ierr<1 || ierr>3 )
		    {
			fprintf(stderr,"Invalid iter selection\n");
			ok = -1;
			break;
		    } 

		    if(ierr>=1) 
		    {
			ITERATIONS->msgspersample=msgs;
		    }
		    if(ierr>=2)
		    {
			ITERATIONS->overall_vol=1024*1024*overall_vol;
		    }

		    if(ierr==3)
		    {
			ITERATIONS->msgs_nonaggr=msgs_nonaggr;
		    }

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-time"))
		{
		    int ierr; 
		    float secs;

		    if( iarg+1>=*argc ) 
		    {
			fprintf(stderr,"Missing argument after \"iter\"\n");
			ok=-1;
			break;
		    }

		    ierr=sscanf((*argv)[iarg+1],"%f",&secs);
		    if( ierr!=1 )
		    {
			fprintf(stderr,"Invalid -time selection\n");
			ok = -1;
			break;
		    } 

		    ITERATIONS->iter_dyn=1;
		    ITERATIONS->secs=secs;

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-mem"))
		{

		    int ierr; 
		    float GB;

		    if( iarg+1>=*argc ) 
		    {
			fprintf(stderr,"Missing argument after \"-mem\"\n");
			ok=-1;
			break;
		    }

		    ierr=sscanf((*argv)[iarg+1],"%f",&GB);
		    if( ierr!=1 )
		    {
			fprintf(stderr,"Invalid -time selection\n");
			ok = -1;
			break;
		    } 

		    c_info->max_mem=GB;
		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-map"))
		{
		    int ierr;
		    if( iarg+1>=*argc ) 
		    {
			fprintf(stderr,"Missing argument after \"map\"\n");
			ok=-1;
			break;
		    }

		    ierr=sscanf((*argv)[iarg+1],"%d%c%d",&c_info->px,(char*) &i,&c_info->py);
		    if(ierr<3 || c_info->px*c_info->py < c_info->w_num_procs)
		    {
			fprintf(stderr,"Invalid map selection\n");
			ok = -1;
			break;
		    } 

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-msglen"))
		{
		    FILE*t;
		    if( !IMB_chk_arg_file(&t,argv,argc,iarg+1) )
		    {
			ok=-1; 
			fprintf(stderr,"Filename after \"msglen\" flag invalid\n");
			break;
		    }

		    iarg_msg=iarg+1;
		    blist_ind = CONSTRUCT_BLIST;

		    if( t )
		    {
			char inp_line[72];

			while(fgets(inp_line,72,t))
			{
			    if( inp_line[0] != '#' && strlen(inp_line)>1 )
				n_lens++;
			}
			fclose(t);
		    }

		    if ( n_lens==0 )
		    {
			fprintf(stderr,"Sizes file %s invalid or doesnt exist\n",(*argv)[iarg_msg]);
			ok = -1;
		    }
		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-input"))
		{
		    FILE*t;
		    if( !IMB_chk_arg_file(&t,argv,argc,iarg+1) )
		    {
			ok=-1; 
			fprintf(stderr,"Filename after \"input\" flag invalid\n");
			break;
		    }

		    blist_ind = CONSTRUCT_BLIST;

		    if( t )
		    {
			char inp_line[72], nam[32];

			while(fgets(inp_line,72,t))
			{
			    if( inp_line[0] != '#' && strlen(inp_line)-1 )
			    {
				sscanf(inp_line,"%s",nam);

				n_cases++;
				IMB_add_to_list_tail( nam, &Blist_head, &Blist_tail);
			    }
			}
			fclose(t);
		    }
		    else fprintf(unit,"Input file %s doesnt exist\n",(*argv)[iarg+1]);

		    iarg++;

		} else if(!strcmp((*argv)[iarg],"-include"))                
		{                                                    
		    if( (iarg+1>=*argc) || ((*argv)[iarg+1][0] == '-')) 
		    {
			fprintf(stderr,"Missing argument after \"include\"\n");
			fflush(stderr);
			ok=-1;
			break;
		    }

		    blist_ind = INCL_BLIST;
	
		} else if(!strcmp((*argv)[iarg],"-exclude"))
		{
		    if( (iarg+1>=*argc) || ((*argv)[iarg+1][0] == '-')) 
		    {
			fprintf(stderr,"Missing argument after \"exclude\"\n");
			fflush(stderr);
			ok=-1;
			break;
		    }

		    blist_ind = EXCL_BLIST;

		} 
		/* IMB 3.2.3 << */
		else if(!strcmp((*argv)[iarg],"-msglog"))
		{

		    int ierr, max_log, min_log;
		    if( iarg+1>=*argc ) 
		    {
			fprintf(stderr,"Missing argument after \"-msglog\"\n");
			ok=-1;
			break;
		    }

		    ierr=sscanf((*argv)[iarg+1],"%d:%d",&min_log, &max_log);

		    if(ierr==2)
		    {
			
			if( (min_log>=0) &&
			    (max_log>0) &&
			    (min_log<MAX_INT_LOG) &&
			    (max_log<MAX_INT_LOG) &&
			    (max_log>min_log))

			{
			    c_info->min_msg_log = min_log;
			    c_info->max_msg_log = max_log;
			} else
			{
			    ok= -1;
			    break;
			}
		    } else if( ierr==1)
		    {
			 if( min_log>0)
			 {
			     c_info->max_msg_log = min_log;
			 } else
			 {
			     ok= -1;
			     break;
			 }

		    } if( ierr==0)
		    {
			ok = -1;
		    } 

		    if( ok == -1)
		    {
			fprintf(stderr,"Invalid -msglog argument, must be <num1>:<num2>\n");
			fprintf(stderr,"where num1 and num2 are positive integer numbers, and num2>num1\n");
			break;
		    }

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;
		} 
#ifdef USE_MPI_INIT_THREAD
		else if(!strcmp((*argv)[iarg],"-thread_level"))
		{
		    int thread_level;
		    if( !IMB_chk_arg_thread_level(&thread_level, *argv, *argc, iarg+1) )
		    {
			ok=-1; 
			fprintf(stderr,"Invalid -thread_level argument, must be single/funneled/serialized/multiple\n");
			break;
		    }

		    mpi_thread_desired = thread_level;

		    blist_ind = CONSTRUCT_BLIST;
		    iarg++;

		}
#endif
		/* >> IMB 3.2.3  */
		else
		{
		    /*It must be the name of one of benchmark*/
		    if( blist_ind == CONSTRUCT_BLIST)
		    {
			n_cases++;
			IMB_add_to_list_tail((*argv)[iarg], &Blist_head, &Blist_tail);
		    }
		    else if( blist_ind == INCL_BLIST)
		    {
			n_cases_incl++;
			IMB_add_to_list_tail((*argv)[iarg], &Blist_incl_head, &Blist_incl_tail);
		    } else if( blist_ind == EXCL_BLIST)
		    {
			n_cases_excl++;
			IMB_add_to_list_tail((*argv)[iarg], &Blist_excl_head, &Blist_excl_tail);
		    }
		}

		iarg++;
	    } /*while( iarg <= *argc-1 )*/
	} /* else if( *argc > 1 )*/

/* IMB_3.0 */
	if( help_only || ok<0 ) 
	{

	    /* Set flag "not ok" => help mode in main */
	    n_cases=0;
	    IMB_i_alloc(int,ALL_INFO,N_baseinfo,"Basic_Input");
	    ok=-3;

	}
	else
	{

	    /* remove wrong items*/
	    if( n_cases > 0)
	    {
		IMB_remove_invalid_items( &Blist_head, &Blist_tail, &n_cases);
	    }

	    if( n_cases_excl > 0) 
	    {
		IMB_remove_invalid_items( &Blist_excl_head, &Blist_excl_tail, &n_cases_excl);
	    }

	    if( n_cases_incl > 0)
	    {
		IMB_remove_invalid_items( &Blist_incl_head, &Blist_incl_tail, &n_cases_incl);
	    }

	    if (n_cases==0 && n_cases_excl==0 && n_cases_incl==0) 
	    {
		deflt = 1;
	    }
		
            if( deflt)
	    {
		IMB_construct_blist_default(P_BList);
	    } else
	    {

		if( n_cases==0 )
		{
		    char** def_cases, **General_cmt;
		    int i;

		    n_cases = IMB_get_def_cases(&def_cases, &General_cmt);

		    for( i=0; i<n_cases; i++)
			IMB_add_to_list_tail( def_cases[i], &Blist_head, &Blist_tail);
		}

		/* Add benchmarks specified by option -include*/
		if( n_cases_incl > 0)
		{
		    struct Blist_item* include_tail = &pool[Blist_incl_tail];

		    include_tail->next_index = Blist_head;
		    Blist_head = Blist_incl_head;

		    n_cases += n_cases_incl;
		}

		/* Remove benchmarks specified by option -exclude*/
		if( n_cases_excl > 0) 
		{
		    int curr_index = Blist_excl_head;
                    struct Blist_item*  curr_item;

		    while( curr_index != -1)
		    {
			curr_item  = &pool[curr_index];

			IMB_remove_item_from_list( curr_item->bname, &Blist_head, &Blist_tail, &n_cases);

			curr_index = curr_item->next_index;
		    }

		}

		printf(" benchmarks to run ") ;
		IMB_print_list(Blist_head);
		printf("\n") ;

		if( n_cases > 0)
		{
		    int i=0;
		    int curr_index = Blist_head;
		    struct Blist_item* blist_item;


		    *P_BList = (struct Bench*)	IMB_v_alloc((1+n_cases)*sizeof(struct Bench), "Construct_Blist 2");

		    while( curr_index != -1)
		    {
			blist_item = &pool[curr_index];

			IMB_construct_blist( &(*P_BList)[i], blist_item->bname);

			curr_index = blist_item->next_index;
			i++;
		    }
		    (*P_BList)[n_cases].name = NULL;
                    
		} else
		{
		    ok = -1;
		    *P_BList = (struct Bench*)	IMB_v_alloc(sizeof(struct Bench), "Construct_Blist 2");
		    (*P_BList)[0].name = NULL;
		}

	    }

	    

	    IMB_free_Blist_item_pool();

	    if( iarg_msg>=0 )
	    {
		FILE*t = fopen((*argv)[iarg_msg],"r");
		c_info->n_lens=n_lens;

		if( t && n_lens>0 )
		{
		    char inp_line[72], S[32];
		    int sz, isz;

		    IMB_i_alloc(int, c_info->msglen,n_lens,"Basic_Input");

		    isz=-1;

		    while(fgets(inp_line,72,t))
		    {
			S[0]='\0';
			if( inp_line[0] != '#' && strlen(inp_line)-1 )
			{
			    int ierr;
			    sz=0;

			    ierr=sscanf(&inp_line[0],"%d%s",&sz,&S[0]);
			    if( ierr<=0 || ierr==EOF || sz<0 )
			    {
				ierr=-1;
			    }
			    else if(ierr==2) 
			    {
				if      (S[0]=='k' ||  S[0]=='K') {sz=sz*1024;}
				else if (S[0]=='m' ||  S[0]=='M') {sz=sz*1024*1024;}
				else 
				{ 
				    ierr=-1; 
				} 
			    } /*else if(ierr==2) */

			    if( ierr>0 ) 
			    {
				isz++;
				c_info->msglen[isz]=sz;
			    }
			    else
			    {
				fprintf(stderr,"Invalid line in file %s\n",(*argv)[iarg_msg]);
			    }
			} /*if( inp_line[0] != '#' && strlen(inp_line)-1 )*/
		    } /*while(fgets(inp_line,72,t))*/

		    n_lens=c_info->n_lens=isz+1;
		    fclose(t);

		    if ( n_lens==0 )
		    {
			fprintf(stderr,"Sizes File %s invalid or doesnt exist\n",(*argv)[iarg_msg]);
			ok = -1;
		    }
		} /*if( t && n_lens>0 )*/
	    } /*if( iarg_msg>=0 )*/

	    IMB_i_alloc(int, ALL_INFO,N_baseinfo+n_cases,"Basic_Input");

	    if( !deflt )
	    {
		i=0;
		n_cases = 0;

		while( (*P_BList)[i].name )
		{
		    int index;
		    index = IMB_get_bmark_index((*P_BList)[i].name);
		    //IMB_get_def_index(&index,(*P_BList)[i].name );
  
/* IMB_3.0
		    if( index >= 0 )
*/
		    /*if( index  != LIST_END )*/
		    ALL_INFO[N_baseinfo+n_cases++] = index;

		    i++;
		} /*while( (*P_BList)[i].name )*/

	    } /*if( !deflt )*/

/* IMB_3.0 end "!help_only" */
	} /* else if !( help_only || ok<0 ) */


/* IMB 3.1 << */
	ALL_INFO[0]  = *NP_min;
	ALL_INFO[1]  = c_info->group_mode;
	ALL_INFO[2]  = deflt;
	ALL_INFO[3]  = ITERATIONS->cache_line_size;
	ALL_INFO[4]  = ITERATIONS->msgspersample;
	ALL_INFO[5]  = ITERATIONS->overall_vol;
	ALL_INFO[6]  = ITERATIONS->msgs_nonaggr;
	ALL_INFO[7]  = ITERATIONS->iter_dyn;
	ALL_INFO[8]  = n_cases;
	ALL_INFO[9]  = c_info->n_lens;
	ALL_INFO[10] = c_info->px;
	ALL_INFO[11] = c_info->py;
	ALL_INFO[12] = c_info->min_msg_log;
	ALL_INFO[13] = c_info->max_msg_log;
	ALL_INFO[14] = ok;

	ALL_F_INFO[0] = ITERATIONS->cache_size;
	ALL_F_INFO[1] = ITERATIONS->secs;
	ALL_F_INFO[2] = c_info->max_mem;

	MPI_Bcast(ALL_F_INFO,N_base_f_info,MPI_FLOAT,0,MPI_COMM_WORLD);
/* >> IMB 3.1  */
	MPI_Bcast(ALL_INFO,N_baseinfo,MPI_INT,0,MPI_COMM_WORLD);

	if( ok<0 ) return ok;

	if( n_cases > 0 && !deflt)
	    MPI_Bcast(ALL_INFO+N_baseinfo,n_cases,MPI_INT,0,MPI_COMM_WORLD);

	if( n_lens  > 0 )
/* IMB 3.1 << */
	{
	    MPI_Bcast(c_info->msglen,n_lens,MPI_INT,0,MPI_COMM_WORLD);

	    if( ITERATIONS->iter_dyn )
	    {
		IMB_i_alloc(int, ITERATIONS->numiters,n_lens,"Basic_Input");
	    }
/* >> IMB 3.1  */
	}

	IMB_v_free((void**)&ALL_INFO);

    } else  /* w_rank > 0 */
/* Receive input arguments */
    {
	int TMP[N_baseinfo];

/* IMB 3.1 << */
	MPI_Bcast(ALL_F_INFO,N_base_f_info,MPI_FLOAT,0,MPI_COMM_WORLD);
/* >> IMB 3.1  */
	MPI_Bcast(TMP,N_baseinfo,MPI_INT,0,MPI_COMM_WORLD);

	*NP_min = TMP[0];
	c_info->group_mode = TMP[1];
	deflt = TMP[2];
/* IMB 3.1 << */
	ITERATIONS->cache_size	= ALL_F_INFO[0];

	if(ITERATIONS->cache_size<0.) ITERATIONS->off_cache=0;
	else                          ITERATIONS->off_cache=1;

	ITERATIONS->cache_line_size	= TMP[3];
	ITERATIONS->msgspersample	= TMP[4];
	ITERATIONS->overall_vol		= TMP[5];
	ITERATIONS->msgs_nonaggr	= TMP[6];
	ITERATIONS->iter_dyn		= TMP[7];
	ITERATIONS->secs		= ALL_F_INFO[1];

	c_info->max_mem		= ALL_F_INFO[2];
	n_cases 		= TMP[8];
	n_lens 			= TMP[9];
	c_info->px 		= TMP[10];
	c_info->py 		= TMP[11];
	c_info->min_msg_log	= TMP[12];
	c_info->max_msg_log	= TMP[13];
	ok 			= TMP[14];
/* >> IMB 3.1  */

	if( ok<0 ) return ok;

	if( deflt )
	{
	    IMB_construct_blist_default(P_BList);
	}
	else if( n_cases>0 )
	{
	    char** ALLC;

	    IMB_i_alloc(int, ALL_INFO,n_cases,"Basic_Input");
	    MPI_Bcast(ALL_INFO,n_cases,MPI_INT,0,MPI_COMM_WORLD);

	    //IMB_get_def_cases(&DEFC,&CMT);
	    IMB_get_all_cases(&ALLC);

	    *P_BList = (struct Bench*)	IMB_v_alloc((1+n_cases)*sizeof(struct Bench), "Construct_Blist 1");

	    for( i = 0; i<n_cases; i++ )
		/* IMB_3.0 */
	    {
		IMB_construct_blist(&(*P_BList)[i], ALLC[ALL_INFO[i]]);
	    }

	    (*P_BList)[n_cases].name = NULL;

	    IMB_v_free((void**)&ALL_INFO);
	}

	if( n_lens>0 ) 
	{
	    c_info->n_lens = n_lens;

	    IMB_i_alloc(int, c_info->msglen,n_lens,"Basic_Input");
	    MPI_Bcast(c_info->msglen,n_lens,MPI_INT,0,MPI_COMM_WORLD);

/* IMB 3.1 << */
	    if( ITERATIONS->iter_dyn )
	    {
		IMB_i_alloc(int,ITERATIONS->numiters,n_lens,"Basic_Input");
	    }
/* >> IMB 3.1  */
	} /*if( n_lens>0 ) */
    }

#ifdef DEBUG
    {
	int i;

	if( n_lens>0 )
	{
	    fprintf(dbg_file,"Got msglen:\n");

	    for(i=0; i<n_lens; i++) fprintf(stderr,"%d ",c_info->msglen[i]);
	}

	fprintf(dbg_file,"\n\n");
	fprintf(dbg_file,"px py = %d %d\n",c_info->px,c_info->py);
	fprintf(dbg_file,"\n\n");
    }
#endif /*DEBUG*/
 
#ifndef EXT
    if( do_nonblocking )
	IMB_cpu_exploit(TARGET_CPU_SECS, 1);
#endif

    return 0;
}


void IMB_get_rank_portion(int rank, int NP, size_t size, 
                          size_t unit_size, size_t* pos1, size_t* pos2)
/*

                      
                      Splits <size> into even contiguous pieces among processes
                      


Input variables: 

-rank                 (type int)                      
                      Process' rank
                      

-NP                   (type int)                      
                      Number of processes
                      

-size                 (type int)                      
                      Portion to split
                      

-unit_size            (type int)                      
                      Base unit for splitting
                      


Output variables: 

-pos1                 (type int*)
-pos2                 (type int*)                      
                      Process' portion is from unit pos1 to pos2
                      


*/
{
    size_t ne, baslen;
    int    mod;

    ne = (size+unit_size-1)/unit_size;
    baslen = ne/NP;
    mod    = (int) ne%NP;

    if( rank < mod )
    {
	*pos1 = rank*(baslen+1)*unit_size;
	*pos2 = *pos1-1+(baslen+1)*unit_size;
    }
    else
    {
	*pos1 = (rank*baslen + mod)*unit_size;
	*pos2 = *pos1-1 + baslen*unit_size;
    }

    *pos2 = min(*pos2,size-1);

}

/********************************************************************/


int IMB_init_communicator(struct comm_info* c_info, int NP)
/*



Input variables: 

-NP                   (type int)                      
                      Number of all started processes
                      


In/out variables: 

-c_info               (type struct comm_info*)                      
                      Collection of all base data for MPI;
                      see [1] for more information
                      
                      Communicator of active processes gets initialized;
                      grouping of processes (in the 'multi' case) in communicators
                      


Return value          (type int)                      
                      Non currently used error exit (value is always 0)
                      


*/
{
    int i,snd,cnt,proc,*aux_ptr;

    MPI_Group group, w_group;
    MPI_Status stat;

    c_info->NP=NP;                     	/* NUMBER OF OVERALL PROCESSES    */          
    IMB_set_communicator( c_info );     /* GROUP MANAGEMENT               */

    /* INITIALIZATION  WITHIN THE ACTUAL COMMUNICATOR */
    if( c_info->communicator != MPI_COMM_NULL )
    {
	MPI_Comm_size(c_info->communicator,&(c_info ->num_procs));
	MPI_Comm_rank(c_info->communicator,&(c_info ->rank));
    
	c_info->pair0 = 0;
	c_info->pair1 = c_info ->num_procs-1;
    
	c_info->select_tag = 0;
	/*c_info->select_source = 0;*/
    }
    else
    {
	c_info -> rank = -1;
    }

    if( c_info->communicator == MPI_COMM_WORLD ) 
    {
	c_info->n_groups = 1;
	c_info->g_sizes[0] = c_info->w_num_procs;

	for(i=0; i<c_info->w_num_procs; i++) c_info->g_ranks[i]=i;
    }
    else
    {
	/* Collect global group information */
	if( c_info->rank == 0 )
	{
	    /* group leaders provide group ranks */
	    MPI_Comm_group(MPI_COMM_WORLD,&w_group);
	    MPI_Comm_group(c_info->communicator,&group);

	    for (i=0; i<c_info->num_procs; i++) c_info->g_sizes[i] = i;

	    /* TRANSLATION OF RANKS */
	    MPI_Group_translate_ranks( group, c_info->num_procs, 
				       c_info->g_sizes,w_group,
				       c_info->g_ranks );
	    snd = c_info->num_procs;
	}
	else
	{
	    *c_info->g_ranks = -1;
	    snd = 1;
	}

	/* w_rank 0 collects in g_ranks ranks of single groups */
	if( c_info->w_rank == 0 ) 
	{
	    if( c_info->rank == 0 )
	    {
		c_info->n_groups = 1;
		c_info->g_sizes[c_info->n_groups-1] = c_info->num_procs;
		aux_ptr = c_info->g_ranks+c_info->num_procs;
	    }
	    else
	    {
		c_info->n_groups = 0;
		aux_ptr=c_info->g_ranks;
	    }

	    for( proc=1; proc<c_info->w_num_procs; proc++ )
	    {
		/* Recv group ranks or -1  */
		cnt = (int)(c_info->g_ranks+c_info->w_num_procs-aux_ptr);
		/* July 2002 fix V2.2.1 (wrong logistics), next 23 lines */

		if( cnt <= 0 )
		    /* all leaders have sent, recv dummies (-1) from others! */
		{
		    cnt=1;
		    MPI_Recv(&i,cnt,MPI_INT,proc,1000,MPI_COMM_WORLD,&stat);
		}
		else
		{

		    MPI_Recv(aux_ptr,cnt,MPI_INT,proc,1000,MPI_COMM_WORLD,&stat);
	    
		    if( *aux_ptr >= 0 ) 
		    {
			/* Message was from a group leader  */
			c_info->n_groups ++;
			MPI_Get_count( &stat, MPI_INT,
				       &c_info->g_sizes[c_info->n_groups-1]);
			aux_ptr += c_info->g_sizes[c_info->n_groups-1];
		    }

		}
		/* end fix V2.2.1 */
	    } /*for( proc=1; proc<c_info->w_num_procs; proc++ )*/
	}
	else  /* w_rank != 0 */
	{
	    MPI_Send(c_info->g_ranks,snd,MPI_INT,0,1000,MPI_COMM_WORLD);
	}
    }
    /* End collection of group information */   

    IMB_set_errhand(c_info);

    return 0;
}


/**********************************************************************/

void IMB_set_communicator(struct comm_info *c_info )
/*

                      
                      Performs the actual communicator splitting
                      


In/out variables: 

-c_info               (type struct comm_info *)                      
                      Collection of all base data for MPI;
                      see [1] for more information
                      
                      Application communicator gets initialized
                      


*/
{
    int color,key,i,j,ii;
    int* map;
  
  /* insert choice for communicator here;
     NOTE   :  globally more than one communicator is allowed   
     Example: grouping of pairs of processes: 
     0 0 1 1 2 2  .. (if even),  UNDEF 0 0 1 1 2 2  .. (if odd) 
     */

    if( c_info->communicator != MPI_COMM_NULL &&  
	c_info->communicator != MPI_COMM_SELF &&
	c_info->communicator != MPI_COMM_WORLD)
    {
	i=MPI_Comm_free(&c_info->communicator);
	IMB_err_hand(1,i);
    }

    IMB_i_alloc( int, map, c_info->w_num_procs, "IMB_init");
    ii=0;

    if( c_info->px>1 && c_info->py>1 )
    {
	for( i=0; i<c_info->px; i++ )
	    for( j=0; j<c_info->py; j++ )
	    {
		if(i+j*c_info->px<c_info->w_num_procs)
		    map[i+j*c_info->px] = ii++;
	    }
    }
    else
    {
	for( i=0; i<c_info->w_num_procs; i++ ) map[i]=i;
    }

    if(c_info->group_mode >= 0)
    {
	i=map[c_info->w_rank];
	color = i/c_info->NP;
	c_info->group_no = color;
	key = i;
	if(color >= c_info->w_num_procs/c_info->NP) color=MPI_UNDEFINED;
	MPI_Comm_split(MPI_COMM_WORLD, color, key, &c_info->communicator);
    }
  /* Default choice and Group definition.  */
    else
    {
	if(map[c_info->w_rank] < c_info->NP) color=0;
	else color=MPI_UNDEFINED;   

	c_info->group_no = 0;
	key=map[c_info->w_rank];
	MPI_Comm_split(MPI_COMM_WORLD, color, key, &c_info->communicator); 
    }

    IMB_v_free((void**)&map);
}


int IMB_valid(struct comm_info * c_info, struct Bench* Bmark, int NP)
/*

                      
                      Validates an input Benchmark / NP setting
                      


Input variables: 

-c_info               (type struct comm_info *)                      
                      Collection of all base data for MPI;
                      see [1] for more information
                      

-Bmark                (type struct Bench*)                      
                      (For explanation of struct Bench type:
                      describes all aspects of modes of a benchmark;
                      see [1] for more information)
                      
                      User input benchmark setting
                      

-NP                   (type int)                      
                      Number of active processes
                      


Return value          (type int)                      
                      1/0 for valid / invalid input
                      


*/
{
/* Checks validity of Bmark for NP processes */
/* Erroneous cases: */
    int invalid, skip;

    invalid = 0; 
    skip = 0;

#ifndef MPIIO
    invalid = Bmark->RUN_MODES[0].type == SingleTransfer && NP <=1;
    skip    = Bmark->RUN_MODES[0].type == SingleTransfer && NP > 2;
#endif

    if ( invalid )
    {
	if( c_info->w_rank == 0 )
	{
	    //	if( NP == 1 )
	    // 	 fprintf(unit,"\n# !! Benchmark %s invalid for %d process   !! \n\n",Bmark->name,NP);
	    //	else
	    fprintf(unit,"\n# !! Benchmark %s invalid for %d processes !! \n\n",Bmark->name,NP);
	}
 
	return 0;
    }

    /* Cases to skip: */
    if ( skip ) return 0;

    return 1;
}

void IMB_set_default(struct comm_info* c_info)
/*

                      
                      Default initialization of comm_info
                      


Output variables: 

-c_info               (type struct comm_info*)                      
                      Collection of all base data for MPI;
                      see [1] for more information
                      


*/
{
    c_info->w_num_procs=0;          
    c_info->w_rank=-1;
    c_info->NP=0;                   
    c_info->px=0;                   
    c_info->py=0;                   
    c_info->communicator=MPI_COMM_NULL;    
    c_info->num_procs =0;
    c_info->rank = -1;
    c_info->s_data_type =  MPI_DATATYPE_NULL;
    c_info->r_data_type =  MPI_DATATYPE_NULL;
    c_info->red_data_type =  MPI_DATATYPE_NULL;
    c_info->op_type = MPI_OP_NULL;
    c_info->pair0 = c_info->pair1 = -2;
    c_info->select_tag = 0;
    c_info->select_source = 0;
    c_info->s_buffer = NULL;
    c_info->s_data = NULL;
    c_info->s_alloc = 0;
    c_info->r_buffer = NULL;
    c_info->r_data = NULL;
    c_info->r_alloc = 0;
/* IMB 3.1 << */
    c_info->max_mem = MAX_MEM_USAGE;
/* >> IMB 3.1  */
    c_info->n_lens = 0;
    c_info->msglen = NULL;
    c_info->group_mode = 0;
    c_info->n_groups = 0;
    c_info->group_no = -1;
    c_info->g_sizes = NULL;
    c_info->g_ranks = NULL;
    c_info->reccnt = NULL;
    c_info->rdispl = NULL;

/* IMB 3.2.3 << */
    c_info->max_msg_log = MAXMSGLOG;
    c_info->min_msg_log = MINMSGLOG;
/* >> IMB 3.2.3  */

    c_info->ERR=MPI_ERRHANDLER_NULL;
 
#ifdef MPIIO
/*   FILE INFORMATION     */
 
    c_info->filename=NULL;
    c_info->File_comm=MPI_COMM_NULL;
    c_info->File_num_procs=0;
    c_info->all_io_procs=0;
    c_info->File_rank=-1;

    c_info->fh=MPI_FILE_NULL;
    c_info->etype=MPI_DATATYPE_NULL;
    c_info->e_size=0;
    c_info->filetype=MPI_DATATYPE_NULL;

    c_info->split.Locsize=0;
    c_info->split.Offset=(MPI_Offset)0;
    c_info->split.Totalsize=0;
 
    c_info->amode=0;
    c_info->info=MPI_INFO_NULL;
 
/* View: */
    c_info->disp=(MPI_Offset)0;
    c_info->datarep=NULL;
    c_info->view=MPI_DATATYPE_NULL;
    c_info->ERRF=MPI_ERRHANDLER_NULL;
#endif /*MPIIO*/

#ifdef EXT
    c_info->WIN=MPI_WIN_NULL;
    c_info->info=MPI_INFO_NULL;
    c_info->ERRW=MPI_ERRHANDLER_NULL;
#endif /*EXT*/
 

}

static void IMB_init_Blist_item_pool()
{
   char** allc;
   pool_size = IMB_get_all_cases(&allc)  *3;
   curr_pos  = 0;

   pool = (struct Blist_item*) malloc( sizeof(struct Blist_item)*pool_size );
   IMB_Assert(pool != NULL);

}

static void IMB_free_Blist_item_pool()
{
    free(pool);
    pool = NULL;

    pool_size = 0;
    curr_pos  = 0;

}


static int IMB_get_Blist_item_index()
{
    int   ret;
    int   i, n;

    i = curr_pos;
    n = pool_size;


    if( i == n )
    {
	char** allc;
	n += IMB_get_all_cases(&allc);

	pool = realloc( pool, sizeof(struct Blist_item)*n );
	IMB_Assert(pool != NULL);
	pool_size = n;

    } else
	IMB_Assert(i<n);


    ret = i;
    i++;
    curr_pos = i;

    return ret;
}

static void IMB_add_to_list_tail(const char* Bname, int *list_head_index, int* list_tail_index)
{
    int head = *list_head_index;
    int new_item_index = IMB_get_Blist_item_index();
    struct Blist_item* blist_item = &pool[new_item_index];

    blist_item->bname	   = Bname;
    blist_item->next_index = -1;

    if( head == -1)
    /* empty list*/
    {
	IMB_Assert(*list_tail_index==-1);
	*list_head_index = new_item_index;
    } else
    {
	int tail = *list_tail_index;
	struct Blist_item* blist_tail_item = &pool[tail];

	blist_tail_item->next_index = new_item_index;

    }

    *list_tail_index = new_item_index;
}

static void IMB_print_list(int list_head_index)
{
    int index = list_head_index;
    struct Blist_item* blist_item;
     
    while( index != -1)
    {
	blist_item = &pool[index];
	index = blist_item->next_index;
	printf("%s ", blist_item->bname);
    }
    
}

static void IMB_remove_invalid_items( int* p_list_head, int* p_list_tail, int *n_cases)
{
    int    curr_item = *p_list_head;
    int    prev_item = -1;
    int    iret;
    struct Blist_item* blist_item;

    while(curr_item != -1)
    {
	 blist_item = &pool[curr_item];

	 iret = IMB_get_bmark_index((char*) blist_item->bname);

	 if( iret == LIST_INVALID)
	 {
	     int next_item = blist_item->next_index;

	     fprintf(stderr,"Invalid benchmark name %s\n", blist_item->bname);

	     (*n_cases)--;

	     if( prev_item != -1)
	     {
		 struct Blist_item* prev_blist_item = &pool[prev_item];

		 prev_blist_item->next_index = next_item;

		 if( next_item == -1) *p_list_tail = prev_item;

		 curr_item = next_item;

		 IMB_Assert( (*n_cases) > 0);

	     } else
	     {
		 curr_item = *p_list_head = next_item;

		 if( next_item == -1) 
		 {
		     *p_list_tail = -1;
		     IMB_Assert( (*n_cases) == 0);
		 } else
		     IMB_Assert( (*n_cases) > 0);

	     }

	 } else
	 {
	     prev_item = curr_item;
	     curr_item = blist_item->next_index;
	 }

    } /* while*/

}

static void IMB_remove_item_from_list( const char* name, int* p_list_head, int* p_list_tail, int *n_cases)
{
    int    curr_item = *p_list_head;
    int    prev_item = -1;
    int    iret;
    struct Blist_item* blist_item;

    while(curr_item != -1)
    {
	 blist_item = &pool[curr_item];

	 iret = IMB_strcasecmp(name, blist_item->bname);

	 if( iret == 0)
	 {
	     int next_item = blist_item->next_index;

	     (*n_cases)--;

	     if( prev_item != -1)
	     {
		 struct Blist_item* prev_blist_item = &pool[prev_item];

		 prev_blist_item->next_index = next_item;

		 if( next_item == -1) *p_list_tail = prev_item;

		 curr_item = next_item;

		 IMB_Assert( (*n_cases) > 0);

	     } else
	     {
		 curr_item = *p_list_head = next_item;

		 if( next_item == -1) 
		 {
		     *p_list_tail = -1;
		     IMB_Assert( (*n_cases) == 0);
		 } else
		     IMB_Assert( (*n_cases) > 0);

	     }

	 } else
	 {
	     prev_item = curr_item;
	     curr_item = blist_item->next_index;
	 }

    } /* while*/

}
/********************************************************************/


