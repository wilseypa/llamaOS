/* Note that this file is not used as of GFortran 4.5, and exists here
   only for backwards compatibility.  */

#include "libgfortran.h"

/* The main Fortran program actually is a function, called MAIN__.
   We call it from the main() function in this file.  */
//void MAIN__ (void);
int main (int argc, char *argv[]);

/* Main procedure for fortran programs.  All we do is set up the environment
   for the Fortran program.  */
int
fortran_main (int argc, char *argv[])
{
  /* Set up the runtime environment.  */
//  set_args (argc, argv);

  /* Call the Fortran main program.  Internally this is a function
     called MAIN__ */
//  MAIN__ ();

main (argc, argv);

  /* Bye-bye!  */
  return 0;
}