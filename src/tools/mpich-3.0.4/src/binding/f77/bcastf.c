/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by buildiface 
 * DO NOT EDIT
 */
#include "mpi_fortimpl.h"


/* Begin MPI profiling block */
#if defined(USE_WEAK_SYMBOLS) && !defined(USE_ONLY_MPI_NAMES) 
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_BCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_BCAST = PMPI_BCAST
#pragma weak mpi_bcast__ = PMPI_BCAST
#pragma weak mpi_bcast_ = PMPI_BCAST
#pragma weak mpi_bcast = PMPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_BCAST = pmpi_bcast__
#pragma weak mpi_bcast__ = pmpi_bcast__
#pragma weak mpi_bcast_ = pmpi_bcast__
#pragma weak mpi_bcast = pmpi_bcast__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_BCAST = pmpi_bcast_
#pragma weak mpi_bcast__ = pmpi_bcast_
#pragma weak mpi_bcast_ = pmpi_bcast_
#pragma weak mpi_bcast = pmpi_bcast_
#else
#pragma weak MPI_BCAST = pmpi_bcast
#pragma weak mpi_bcast__ = pmpi_bcast
#pragma weak mpi_bcast_ = pmpi_bcast
#pragma weak mpi_bcast = pmpi_bcast
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_BCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_BCAST = PMPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_bcast__ = pmpi_bcast__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_bcast = pmpi_bcast
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_bcast_ = pmpi_bcast_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_BCAST  MPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_bcast__  mpi_bcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_bcast  mpi_bcast
#else
#pragma _HP_SECONDARY_DEF pmpi_bcast_  mpi_bcast_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_BCAST as PMPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_bcast__ as pmpi_bcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_bcast as pmpi_bcast
#else
#pragma _CRI duplicate mpi_bcast_ as pmpi_bcast_
#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(HAVE_MULTIPLE_PRAGMA_WEAK) && \
    defined(USE_ONLY_MPI_NAMES)
extern FORT_DLL_SPEC void FORT_CALL MPI_BCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_bcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_bcast__ = MPI_BCAST
#pragma weak mpi_bcast_ = MPI_BCAST
#pragma weak mpi_bcast = MPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_BCAST = mpi_bcast__
#pragma weak mpi_bcast_ = mpi_bcast__
#pragma weak mpi_bcast = mpi_bcast__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_BCAST = mpi_bcast_
#pragma weak mpi_bcast__ = mpi_bcast_
#pragma weak mpi_bcast = mpi_bcast_
#else
#pragma weak MPI_BCAST = mpi_bcast
#pragma weak mpi_bcast__ = mpi_bcast
#pragma weak mpi_bcast_ = mpi_bcast
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS) && defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_BCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_bcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_bcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_bcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_bcast__ = PMPI_BCAST
#pragma weak pmpi_bcast_ = PMPI_BCAST
#pragma weak pmpi_bcast = PMPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_BCAST = pmpi_bcast__
#pragma weak pmpi_bcast_ = pmpi_bcast__
#pragma weak pmpi_bcast = pmpi_bcast__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_BCAST = pmpi_bcast_
#pragma weak pmpi_bcast__ = pmpi_bcast_
#pragma weak pmpi_bcast = pmpi_bcast_
#else
#pragma weak PMPI_BCAST = pmpi_bcast
#pragma weak pmpi_bcast__ = pmpi_bcast
#pragma weak pmpi_bcast_ = pmpi_bcast
#endif /* Test on name mapping */
#endif /* Use multiple pragma weak */

#ifdef F77_NAME_UPPER
#define mpi_bcast_ PMPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_bcast_ pmpi_bcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_bcast_ pmpi_bcast
#else
#define mpi_bcast_ pmpi_bcast_
#endif /* Test on name mapping */

/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Bcast
#define MPI_Bcast PMPI_Bcast 

#else

#ifdef F77_NAME_UPPER
#define mpi_bcast_ MPI_BCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_bcast_ mpi_bcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_bcast_ mpi_bcast
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_bcast_ ( void*v1, MPI_Fint *v2, MPI_Fint *v3, MPI_Fint *v4, MPI_Fint *v5, MPI_Fint *ierr ){
    *ierr = MPI_Bcast( v1, (int)*v2, (MPI_Datatype)(*v3), (int)*v4, (MPI_Comm)(*v5) );
}
