/*
Copyright (c) 2013, William Magato
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the copyright holder(s) or contributors.
*/

#include "mpid_nem_impl.h"


static int nm_llamaNET_init(MPIDI_PG_t *pg_p, int pg_rank,
                   char **bc_val_p, int *val_max_sz_p)
{
   printf ("nm_llamaNET_init\n");
   return MPI_SUCCESS;
}

static int nm_llamaNET_get_business_card(int my_rank, char **bc_val_p, int *val_max_sz_p)
{
   printf ("nm_llamaNET_get_business_card\n");
   MPIU_Assertp(0);
   return MPI_SUCCESS;
}

static int nm_llamaNET_connect_to_root(const char *business_card, MPIDI_VC_t *new_vc)
{
   printf ("nm_llamaNET_connect_to_root\n");
   MPIU_Assertp(0);
   return MPI_SUCCESS;
}

static int nm_llamaNET_vc_init(MPIDI_VC_t *vc)
{
   printf ("nm_llamaNET_vc_init\n");
   return MPI_SUCCESS;
}

static int nm_llamaNET_vc_destroy(MPIDI_VC_t *vc)
{
   printf ("nm_llamaNET_vc_destroy\n");
   return MPI_SUCCESS;
}

static int nm_llamaNET_vc_terminate(MPIDI_VC_t *vc)
{
   printf ("nm_llamaNET_vc_terminate\n");
   return MPIDI_CH3U_Handle_connection(vc, MPIDI_VC_EVENT_TERMINATED);
}

static int nm_llamaNET_poll(int in_blocking_poll)
{  
   printf ("nm_llamaNET_poll\n");
   return MPI_SUCCESS;
}

static int nm_llamaNET_ckpt_shutdown(void)
{
   printf ("nm_llamaNET_ckpt_shutdown\n");
   return MPI_SUCCESS;
}

static int nm_llamaNET_finalize(void)
{
   printf ("nm_llamaNET_finalize\n");
   return nm_llamaNET_ckpt_shutdown();    
}

MPID_nem_netmod_funcs_t MPIDI_nem_llamaNET_funcs = {
    nm_llamaNET_init,
    nm_llamaNET_finalize,
    nm_llamaNET_poll,
    nm_llamaNET_get_business_card,
    nm_llamaNET_connect_to_root,
    nm_llamaNET_vc_init,
    nm_llamaNET_vc_destroy,
    nm_llamaNET_vc_terminate,
    NULL /* anysource iprobe */
};
