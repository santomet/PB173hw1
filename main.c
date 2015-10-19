#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include "libmareceka.h"
#include "libmarecekb.h"


/**
 * @brief main
 *
 * According to stdin options it loads certain library (libmareceka or libmarecekb)
 */

int main(int argc, char *argv[])
{
   void *lib_handle;
   double (*fn)();
   int aflag, bflag;
   char *error;
   char usedLib[] = "libmareceka.so";
   char mOpt;


   while ((mOpt = getopt (argc, argv, "ab")) != -1)
      switch (mOpt)
        {
        case 'a':
          aflag = 1;
          break;
        case 'b':
          bflag = 1;
          usedLib[10] = 'b';
          break;
        case '?':
          if (bflag == aflag)
            fprintf (stderr, "Wrong arguments, choose a or b only.\n");
          return 1;
        default:
          abort ();
        }



   lib_handle = dlopen(usedLib, RTLD_LAZY);
   if (!lib_handle)
   {
      fprintf(stderr, "%s\n", dlerror());
      exit(1);
   }

   fn = dlsym(lib_handle, "writesomething");
   if ((error = dlerror()) != NULL)
   {
      fprintf(stderr, "%s\n", error);
      exit(1);
   }

   (*fn)();

   dlclose(lib_handle);
   return 0;
}

