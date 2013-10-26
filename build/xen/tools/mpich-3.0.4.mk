#
# Copyright (c) 2013, William Magato
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS
# ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of the copyright holder(s) or
# contributors.
#

# include common variables
include common-vars.mk
include common-flags.mk

MAKEFILE_SOURCES += tools/mpich-$(MPICH_VERSION).mk

CFLAGS += \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/binding/f77 \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpi/datatype \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpi/romio/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/utils/monitor \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/common/sched \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpl/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpl/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/openpa/src \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/openpa/src.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/util/wrappers \
  -I $(INCDIR) \
  -DUSE_DBG_LOGGING \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(SRCDIR)

C_SOURCES = \
  tools/mpich-$(MPICH_VERSION)/src/binding/f77/statusf2c.c \
  tools/mpich-$(MPICH_VERSION)/src/binding/f77.build/setbot.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/attr/attrutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/attr/comm_create_keyval.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/attr/comm_delete_attr.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/attr/comm_free_keyval.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/attr/comm_get_attr.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/attr/comm_set_attr.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/allgather.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/allgatherv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/allred_group.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/allreduce.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/alltoall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/alltoallv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/alltoallw.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/barrier.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/barrier_group.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/bcast.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/exscan.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/gather.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/gatherv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/helper_fns.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iallgather.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iallgatherv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iallreduce.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ialltoall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ialltoallv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ialltoallw.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ibarrier.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ibcast.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iexscan.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/igather.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/igatherv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ired_scat.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ired_scat_block.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/ireduce.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iscan.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iscatter.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/iscatterv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/nbcutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/op_commutative.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/op_create.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/op_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opband.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opbor.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opbxor.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opland.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/oplor.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/oplxor.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opmax.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opmaxloc.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opmin.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opminloc.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opno_op.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opprod.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opreplace.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/opsum.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/red_scat.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/red_scat_block.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/reduce.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/reduce_local.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/scan.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/scatter.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/coll/scatterv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/comm/comm_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/comm/comm_group.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/comm/comm_rank.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/comm/comm_size.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/comm/comm_split.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/comm/commutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/get_count.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/pack.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/pack_size.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_commit.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_contiguous.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_create_indexed_block.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_create_struct.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_get_envelope.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_get_extent.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_get_extent_x.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_get_true_extent.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_get_true_extent_x.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_hvector.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_indexed.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_struct.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/type_vector.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/typeutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/datatype/unpack.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/errhan/errutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/group/group_compare.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/group/group_difference.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/group/group_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/group/group_incl.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/group/group_translate_ranks.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/group/grouputil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_create.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_dup.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_get.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_getn.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_getnth.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_getvallen.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/info_set.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/info/infoutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/init/abort.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/init/async.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/init/finalize.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/init/init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/init/initthread.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/bsend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/bsend_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/bsendutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/bufattach.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/buffree.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/cancel.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/greq_complete.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/greq_start.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/ibsend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/improbe.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/imrecv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/iprobe.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/irecv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/irsend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/isend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/issend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/mpir_request.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/mprobe.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/mrecv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/probe.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/recv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/recv_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/request_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/request_get_status.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/rsend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/rsend_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/send.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/send_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/sendrecv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/sendrecv_rep.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/ssend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/ssend_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/start.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/startall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/status_set_cancelled.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/test.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/test_cancelled.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/testall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/testany.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/testsome.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/wait.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/waitall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/waitany.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/waitsome.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/rma/rmatypeutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/rma/winutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/timer/mpidtime.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/timer/wtick.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/timer/wtime.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/cart_rank.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/cart_shift.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/dist_gr_neighb.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/dist_gr_neighb_count.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/graph_nbr.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/graphnbrcnt.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/inhb_allgather.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/inhb_allgatherv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/inhb_alltoall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/inhb_alltoallv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/inhb_alltoallw.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/nhb_allgather.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/nhb_allgatherv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/nhb_alltoall.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/nhb_alltoallv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/nhb_alltoallw.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/topo/topoutil.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi_t/mpi_t_util.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi_t/mpit_init_thread.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/netmod/none/none.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_abort.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_finalize.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_isend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_isendv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_istartmsg.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_istartmsgv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_progress.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_rma_shm.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3_win_fns.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3i_comm.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/ch3i_eagernoncontig.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_alloc.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_barrier.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_ckpt.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_debug.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_finalize.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_lmt.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_lmt_shm.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_mpich.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_network.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src/mpid_nem_network_poll.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/src.build/mpid_nem_net_array.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_buffer.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_comm.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_comm_spawn_multiple.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_eager.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_eagersync.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_handle_connection.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_handle_recv_pkt.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_handle_recv_req.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_handle_send_req.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_port.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_recvq.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_request.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_rma_ops.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_rma_sync.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_rndv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/ch3u_win_fns.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_abort.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_cancel_recv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_cancel_send.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_finalize.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_get_universe_size.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_init.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_irecv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_isend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_issend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_port.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_probe.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_recv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_send.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_ssend.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpid_vc.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpidi_isend_self.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpidi_pg.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/src/mpidi_printf.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/darray_support.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create_blockindexed.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create_contig.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create_indexed.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create_pairtype.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create_struct.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/dataloop_create_vector.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/segment.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/segment_count.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/segment_flatten.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/segment_packunpack.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/subarray_support.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/dataloop/typesize_support.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_contents_support.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_datatype_contents.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_datatype_free.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_ext32_datatype.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_ext32_segment.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_segment.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_blockindexed.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_commit.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_contiguous.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_create_pairtype.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_create_resized.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_debug.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_dup.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_get_contents.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_get_envelope.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_indexed.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_struct.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_vector.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpid_type_zerolen.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpir_type_flatten.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype/mpir_type_get_contig_blocks.c \
  tools/mpich-$(MPICH_VERSION)/src/mpid/common/sched/mpid_sched.c \
  tools/mpich-$(MPICH_VERSION)/src/mpl/src/mplenv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpl/src/mplstr.c \
  tools/mpich-$(MPICH_VERSION)/src/util/dbg/dbg_printf.c \
  tools/mpich-$(MPICH_VERSION)/src/util/dbg/exit.c \
  tools/mpich-$(MPICH_VERSION)/src/util/mem/argstr.c \
  tools/mpich-$(MPICH_VERSION)/src/util/mem/handlemem.c \
  tools/mpich-$(MPICH_VERSION)/src/util/mem/safestr.c \
  tools/mpich-$(MPICH_VERSION)/src/util/mem/strerror.c \
  tools/mpich-$(MPICH_VERSION)/src/util/msgs/msgprint.c \
  tools/mpich-$(MPICH_VERSION)/src/util/other/assert.c \
  tools/mpich-$(MPICH_VERSION)/src/util/param/param_vals.c \
  tools/mpich-$(MPICH_VERSION)/src/util/procmap/local_proc.c

F77_SOURCES = \
  tools/mpich-$(MPICH_VERSION)/src/binding/f77.build/setbotf.f

HEADERS = \
  $(INCDIR)/mpi.h \
  $(INCDIR)/mpicxx.h \
  $(INCDIR)/mpif.h \
  $(INCDIR)/mpio.h

OBJECTS  = $(C_SOURCES:%.c=$(OBJDIR)/%.o)
OBJECTS += $(F77_SOURCES:%.f=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/tools/mpich.a $(HEADERS)

$(LIBDIR)/tools/mpich.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/include.build/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/binding/cxx.build/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/binding/f77.build/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpi/romio/include.build/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)
