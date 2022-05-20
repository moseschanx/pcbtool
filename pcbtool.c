#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <setjmp.h>
#include <assert.h>
#include <ctype.h>
#include <stdnoreturn.h>


unsigned debug_level = DBG_LEVL; // Debug depth extend as number grow 

#include "pcbtool_errors.h"
#include "pcbtool_lib.h"


int main(int argc , char** argv)
{

  if(argc < 2) error_exit();
  
  double* resul = NULL;

  char* opt = argv[1];

  if(*opt++ == '-')
  {
    switch(*opt)
    {
      case 'm' :

      DBG(2,"Entering function milli_to_mil.")
      milli_to_mil(argc-2,argv+2);  // we perform add/substract for the reason the function only hanles desired (actual numer list) argument
      break;

      case 'M' :
      DBG(2,"Entering function mil_to_milli.");
      mil_to_milli(argc-2,argv+2);
      break;

      case 'S' :
      DBG(2,"Entering function soldermsk_gen.");
      soldermsk_gen(argv[2]);
      break;

      case 'P' :
      DBG(2,"Entering function padstack_gen.")
      padstack_gen(argv[2]);
      break;

      default :
        error_exit();

    }
  } else error_exit();

  puts("");  

  DBG(1 , "Program normal exit.");
  exit(EXIT_SUCCESS);

}

// input origin point 
// input displacements 
// get  back tot origin point 

// calculate all points 
// extends 0.1 mm to all points
// output soldermask shape path ( in allegro command line syntax )