/*
 * vim:expandtab:shiftwidth=8:tabstop=8:
 *
 * Copyright CEA/DAM/DIF  (2008)
 * contributeur : Philippe DENIEL   philippe.deniel@cea.fr
 *                Thomas LEIBOVICI  thomas.leibovici@cea.fr
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * -------------------N--------------------
 */

/**
 * \file    nfs41_op_layoutget.c
 * \author  $Author: deniel $
 * \date    $Date: 2005/11/28 17:02:50 $
 * \version $Revision: 1.8 $
 * \brief   Routines used for managing the NFS4 COMPOUND functions.
 *
 * nfs41_op_lock.c : Routines used for managing the NFS4 COMPOUND functions.
 *
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef _SOLARIS
#include "solaris_port.h"
#endif

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/file.h>           /* for having FNDELAY */
#include "HashData.h"
#include "HashTable.h"
#include "rpc.h"
#include "log.h"
#include "stuff_alloc.h"
#include "nfs23.h"
#include "nfs4.h"
#include "mount.h"
#include "nfs_core.h"
#include "cache_inode.h"
#include "cache_content.h"
#include "nfs_exports.h"
#include "nfs_creds.h"
#include "nfs_proto_functions.h"
#include "nfs_file_handle.h"
#include "nfs_tools.h"
#include "sal_data.h"
#include "sal_functions.h"

#include "pnfs.h"

/**
 * 
 * nfs41_op_layoutget: The NFS4_OP_LAYOUTGET operation. 
 *
 * This function implements the NFS4_OP_LAYOUTGET operation.
 *
 * @param op    [IN]    pointer to nfs4_op arguments
 * @param data  [INOUT] Pointer to the compound request's data
 * @param resp  [IN]    Pointer to nfs4_op results
 * 
 * @return NFS4_OK if successfull, other values show an error. 
 *
 * @see all the nfs41_op_<*> function
 * @see nfs4_Compound
 *
 */

#define arg_LAYOUTGET4 op->nfs_argop4_u.oplayoutget
#define res_LAYOUTGET4 resp->nfs_resop4_u.oplayoutget

int nfs41_op_layoutget(struct nfs_argop4 *op, compound_data_t * data,
                       struct nfs_resop4 *resp)
{
  char __attribute__ ((__unused__)) funcname[] = "nfs41_op_layoutget";

  resp->resop = NFS4_OP_LAYOUTGET;

#ifndef _USE_PNFS
  resp->resop = NFS4_OP_LAYOUTGET;
  res_LAYOUTGET4.logr_status = NFS4ERR_NOTSUPP;
  return res_LAYOUTGET4.logr_status;
#else
  /* Lock are not supported */
  resp->resop = NFS4_OP_LAYOUTGET;

  /* If there is no FH */
  if(nfs4_Is_Fh_Empty(&(data->currentFH)))
    {
      res_LAYOUTGET4.logr_status = NFS4ERR_NOFILEHANDLE;
      return res_LAYOUTGET4.logr_status;
    }

  /* If the filehandle is invalid */
  if(nfs4_Is_Fh_Invalid(&(data->currentFH)))
    {
      res_LAYOUTGET4.logr_status = NFS4ERR_BADHANDLE;
      return res_LAYOUTGET4.logr_status;
    }

  /* Tests if the Filehandle is expired (for volatile filehandle) */
  if(nfs4_Is_Fh_Expired(&(data->currentFH)))
    {
      res_LAYOUTGET4.logr_status = NFS4ERR_FHEXPIRED;
      return res_LAYOUTGET4.logr_status;
    }

  /* Commit is done only on a file */
  if(data->current_filetype != REGULAR_FILE)
    {
      /* Type of the entry is not correct */
      switch (data->current_filetype)
        {
        case DIRECTORY:
          res_LAYOUTGET4.logr_status = NFS4ERR_ISDIR;
          break;
        default:
          res_LAYOUTGET4.logr_status = NFS4ERR_INVAL;
          break;
        }

      return res_LAYOUTGET4.logr_status;
    }

  /* Call underlying function */
  return pnfs_layoutget( &arg_LAYOUTGET4, data, &res_LAYOUTGET4 ) ;
#endif                          /* _USE_PNFS */
}                               /* nfs41_op_layoutget */

/**
 * nfs41_op_layoutget_Free: frees what was allocared to handle nfs41_op_layoutget.
 * 
 * Frees what was allocared to handle nfs41_op_layoutget.
 *
 * @param resp  [INOUT]    Pointer to nfs4_op results
 *
 * @return nothing (void function )
 * 
 */
void nfs41_op_layoutget_Free(LAYOUTGET4res * resp)
{
#ifdef _USE_PNFS
   pnfs_layoutget_Free( resp ) ;
#endif
   return ;
}                               /* nfs41_op_layoutget_Free */
