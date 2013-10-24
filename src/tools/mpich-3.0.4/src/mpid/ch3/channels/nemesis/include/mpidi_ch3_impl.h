/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#if !defined(MPICH_MPIDI_CH3_IMPL_H_INCLUDED)
#define MPICH_MPIDI_CH3_IMPL_H_INCLUDED

#include "mpidimpl.h"
#include "mpiu_os_wrappers.h"
#include "mpid_nem_generic_queue.h"

#if defined(HAVE_ASSERT_H)
#include <assert.h>
#endif

extern void *MPIDI_CH3_packet_buffer;
extern int MPIDI_CH3I_my_rank;

typedef GENERIC_Q_DECL(struct MPID_Request) MPIDI_CH3I_shm_sendq_t;
extern MPIDI_CH3I_shm_sendq_t MPIDI_CH3I_shm_sendq;
extern struct MPID_Request *MPIDI_CH3I_shm_active_send;

/* Send queue macros */
/* MT - not thread safe! */
#define MPIDI_CH3I_Sendq_empty(q) GENERIC_Q_EMPTY (q)
#define MPIDI_CH3I_Sendq_head(q) GENERIC_Q_HEAD (q)
#define MPIDI_CH3I_Sendq_enqueue(qp, ep) do {                                           \
        /* add refcount so req doesn't get freed before it's dequeued */                \
        MPIR_Request_add_ref(ep);                                                       \
        MPIU_DBG_MSG_FMT(CH3_CHANNEL, VERBOSE, (MPIU_DBG_FDEST,                         \
                          "MPIDI_CH3I_Sendq_enqueue req=%p (handle=%#x), queue=%p",     \
                          ep, (ep)->handle, qp));                                       \
        GENERIC_Q_ENQUEUE (qp, ep, dev.next);                                           \
    } while (0)
#define MPIDI_CH3I_Sendq_dequeue(qp, ep)  do {                                          \
        GENERIC_Q_DEQUEUE (qp, ep, dev.next);                                           \
        MPIU_DBG_MSG_FMT(CH3_CHANNEL, VERBOSE, (MPIU_DBG_FDEST,                         \
                          "MPIDI_CH3I_Sendq_dequeuereq=%p (handle=%#x), queue=%p",      \
                          *(ep), *(ep) ? (*(ep))->handle : -1, qp));                    \
        MPID_Request_release(*(ep));                                                    \
    } while (0)
#define MPIDI_CH3I_Sendq_enqueue_multiple_no_refcount(qp, ep0, ep1)             \
    /* used to move reqs from one queue to another, so we don't update */       \
    /* the refcounts */                                                         \
    GENERIC_Q_ENQUEUE_MULTIPLE(qp, ep0, ep1, dev.next)

int MPIDI_CH3I_Progress_init(void);
int MPIDI_CH3I_Progress_finalize(void);
int MPIDI_CH3I_Shm_send_progress(void);
int MPIDI_CH3I_Complete_sendq_with_error(MPIDI_VC_t * vc);

int MPIDI_CH3I_SendNoncontig( MPIDI_VC_t *vc, MPID_Request *sreq, void *header, MPIDI_msg_sz_t hdr_sz );

int MPID_nem_lmt_shm_initiate_lmt(MPIDI_VC_t *vc, MPIDI_CH3_Pkt_t *rts_pkt, MPID_Request *req);
int MPID_nem_lmt_shm_start_recv(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV s_cookie);
int MPID_nem_lmt_shm_start_send(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV r_cookie);
int MPID_nem_lmt_shm_handle_cookie(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV cookie);
int MPID_nem_lmt_shm_done_send(MPIDI_VC_t *vc, MPID_Request *req);
int MPID_nem_lmt_shm_done_recv(MPIDI_VC_t *vc, MPID_Request *req);
int MPID_nem_lmt_shm_vc_terminated(MPIDI_VC_t *vc);

int MPID_nem_lmt_dma_initiate_lmt(MPIDI_VC_t *vc, MPIDI_CH3_Pkt_t *rts_pkt, MPID_Request *req);
int MPID_nem_lmt_dma_start_recv(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV s_cookie);
int MPID_nem_lmt_dma_start_send(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV r_cookie);
int MPID_nem_lmt_dma_handle_cookie(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV cookie);
int MPID_nem_lmt_dma_done_send(MPIDI_VC_t *vc, MPID_Request *req);
int MPID_nem_lmt_dma_done_recv(MPIDI_VC_t *vc, MPID_Request *req);
int MPID_nem_lmt_dma_vc_terminated(MPIDI_VC_t *vc);

int MPID_nem_lmt_vmsplice_initiate_lmt(MPIDI_VC_t *vc, MPIDI_CH3_Pkt_t *rts_pkt, MPID_Request *req);
int MPID_nem_lmt_vmsplice_start_recv(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV s_cookie);
int MPID_nem_lmt_vmsplice_start_send(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV r_cookie);
int MPID_nem_lmt_vmsplice_handle_cookie(MPIDI_VC_t *vc, MPID_Request *req, MPID_IOV cookie);
int MPID_nem_lmt_vmsplice_done_send(MPIDI_VC_t *vc, MPID_Request *req);
int MPID_nem_lmt_vmsplice_done_recv(MPIDI_VC_t *vc, MPID_Request *req);
int MPID_nem_lmt_vmsplice_vc_terminated(MPIDI_VC_t *vc);

int MPID_nem_handle_pkt(MPIDI_VC_t *vc, char *buf, MPIDI_msg_sz_t buflen);

/* Nemesis-provided RMA implementation */
int MPIDI_CH3_SHM_Win_shared_query(MPID_Win *win_ptr, int target_rank, MPI_Aint *size, int *disp_unit, void *baseptr);
int MPIDI_CH3_SHM_Win_free(MPID_Win **win_ptr);

/* Shared memory window atomic/accumulate mutex implementation */

#define MPIDI_CH3I_SHM_MUTEX_LOCK(win_ptr)                                              \
    do {                                                                                \
        int pt_err = pthread_mutex_lock((win_ptr)->shm_mutex);                          \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_lock",        \
                             "**pthread_lock %s", strerror(pt_err));                    \
    } while (0)

#define MPIDI_CH3I_SHM_MUTEX_UNLOCK(win_ptr)                                            \
    do {                                                                                \
        int pt_err = pthread_mutex_unlock((win_ptr)->shm_mutex);                        \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_unlock",      \
                             "**pthread_unlock %s", strerror(pt_err));                  \
    } while (0)

#define MPIDI_CH3I_SHM_MUTEX_INIT(win_ptr)                                              \
    do {                                                                                \
        int pt_err;                                                                     \
        pthread_mutexattr_t attr;                                                       \
                                                                                        \
        pt_err = pthread_mutexattr_init(&attr);                                         \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_mutex",       \
                             "**pthread_mutex %s", strerror(pt_err));                   \
        pt_err = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);           \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_mutex",       \
                             "**pthread_mutex %s", strerror(pt_err));                   \
        pt_err = pthread_mutex_init((win_ptr)->shm_mutex, &attr);                       \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_mutex",       \
                             "**pthread_mutex %s", strerror(pt_err));                   \
        pt_err = pthread_mutexattr_destroy(&attr);                                      \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_mutex",       \
                             "**pthread_mutex %s", strerror(pt_err));                   \
    } while (0);

#define MPIDI_CH3I_SHM_MUTEX_DESTROY(win_ptr)                                           \
    do {                                                                                \
        int pt_err = pthread_mutex_destroy((win_ptr)->shm_mutex);                       \
        MPIU_ERR_CHKANDJUMP1(pt_err, mpi_errno, MPI_ERR_OTHER, "**pthread_mutex",       \
                             "**pthread_mutex %s", strerror(pt_err));                   \
    } while (0);

#endif /* !defined(MPICH_MPIDI_CH3_IMPL_H_INCLUDED) */
