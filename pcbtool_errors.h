#ifndef PCB_TOOL_ERRORS_H
#define PCB_TOOL_ERRORS_H

#include <stdnoreturn.h>

#ifndef DBG_LEVL
  #error "please Specify Debug Level (DBG_LEVL) in your command line. -DDBG_LEVL=<1-3>"
#endif

#ifdef DEBUG
  #define COL_CLR "\033[0m"

        #define DBG(level , fmt , ...) \
        if(debug_level >= level){ \
        if(level == 1) \
        fprintf(stderr,"At file %s line %d : \t",__FILE__,__LINE__) ,fprintf(stderr ,"\033[0;32m"fmt"\n" COL_CLR , ##__VA_ARGS__ );\
        if(level == 2) \
        fprintf(stderr,"At file %s line %d : \t",__FILE__,__LINE__) ,fprintf(stderr ,"\033[0;33m"fmt"\n" COL_CLR , ##__VA_ARGS__ );\
        if(level == 3) \
        fprintf(stderr,"At file %s line %d : \t",__FILE__,__LINE__) ,fprintf(stderr ,"\033[0;31m"fmt"\n" COL_CLR , ##__VA_ARGS__ );\
        }
#else
    #define DBG(level , fmt , ...)
#endif

#define PRINTF(num) \
        if(num<0.001) \
          printf("%.6f\t\t",num); \
        else if(num<0.01) \
          printf("%.4f\t",num); \
        else \
          printf("%.2f\t",num);


// function prototypes
noreturn void error_exit();
noreturn void syntax_error_exit(char);
noreturn void input_syntax_error_exit();

#endif

