#include <stdlib.h>
#include <stdio.h>
#include <stdnoreturn.h>

extern unsigned debug_level;

#include "pcbtool_errors.h"

noreturn void error_exit()
{
 puts("Usage : pcbtool -<m,M,S> <number1/point> <number2> <number3> ...");
 puts("\tOptions :");
 puts("\t\t -m : millimeter to mil.");
 puts("\t\t -M : mil to millimeter.");
 puts("\t\t -S : create a solder mask pattern for irregular patterns");
 DBG(1,"Program Exit.");
 exit(EXIT_FAILURE);
}
noreturn void syntax_error_exit(char opt)
{
  if(opt == 'S' || opt == 's'){

 puts("Point ""\033[0;31m""syntax error.""\033[0m");
 puts("\tUsage : pcbtool -S <x>,<y>");
 DBG(1,"Program Exit.");
 exit(EXIT_FAILURE);

 }else if(opt == 'P' || opt == 'p'){

 puts("Pin diameter ""\033[0;31m""syntax error.""\033[0m");
 puts("\tUsage : pcbtool -P <number(in mm),2 width>");
 DBG(1,"Program Exit.");
 exit(EXIT_FAILURE);

 }else
 {
 DBG(1,"Program Exit.");
 exit(EXIT_FAILURE);
 }

}
noreturn void input_syntax_error_exit()
{
 puts("Input ""\033[0;31m""syntax error.""\033[0m");
 puts("Usage : ix <displacement> / iy <displacement>");
 DBG(1,"Program Exit.");
 exit(EXIT_FAILURE);
}