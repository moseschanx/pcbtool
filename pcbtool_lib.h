#ifndef PCB_TOOL_LIB_H
#define PCB_TOOL_LIB_H



// type definitions  
typedef struct {
  float x;
  float y;
}Point;




// function prototypes
void mil_to_milli(int sz , char** args);
void milli_to_mil(int sz , char** args); // sz : numer of the desired argument int argument list , args : actually pointer to the argument array
void soldermsk_gen(char* pt);
void padstack_gen(char* ptr);

#endif