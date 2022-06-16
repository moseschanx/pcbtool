
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern unsigned debug_level;
#include "pcbtool_errors.h"
#include "pcbtool_lib.h"

void  mil_to_milli(int sz , char** args)
{
  double* resul = (double*)malloc(sizeof(double)*sz);

  for(int i = 0;i<sz;++i)
  {
    resul[i] = ((atof(args[i]))*25.4 / 1000); 
    printf("%.4f\t",resul[i]); 
    
  }


}
void milli_to_mil(int sz , char** args) // sz : numer of the desired argument int argument list , args : actually pointer to the argument array
{
  double* resul = (double*)malloc(sizeof(double)*sz);

  for(int i = 0;i<sz;++i)
  {
    resul[i] = ((atof(args[i]))/25.4 * 1000) ; PRINTF(resul[i]);

  }

}

void soldermsk_gen(char* pt)
{
      Point pt_start;
      Point pt_itmd; // Intermediate processing point
      Point pt_array[256];
      int sign;

      pt_start.x = pt_start.y = 0;

      //extract start point from commandline argument 
        if(*pt == '-')
        {
          DBG(3,"x in Origin : negative sign detected.")
          sign = -1;
          ++pt;
        }
        else
        {
          DBG(3,"x in Origin : negative sign not detected.")
          sign = 1;
        }
        while(isdigit(*(pt)))
        {
          DBG(3,"Digit Detected.");
          pt_start.x = sign * (pt_start.x * 10 + (*pt) - '0');
          DBG(3,"pt_startx now is  : %.2f",pt_start.x);
          ++pt;
        }
        if(*pt++ == ',')
        {
        DBG(3," , Detected.");

        if(*pt == '-')
        {
          DBG(3,"y in Origin : negative sign detected.")
          sign = -1;
          ++pt;
        }
        else
        {
          DBG(3,"y in Origin : negative sign not detected.")
          sign = 1;
        }
        while(isdigit(*(pt)))
        {
          DBG(3,"Digit Detected.");
          pt_start.y = sign * (pt_start.y * 10 + (*pt) - '0');
          DBG(3,"pt_starty now is  : %.2f",pt_start.y);
          ++pt;
        }
        }else syntax_error_exit('S');

    pt_itmd.x = pt_start.x , pt_itmd.y = pt_start.y;

    DBG(3,"Your origin point now is (%.2f,%.2f)",(pt_itmd.x),(pt_itmd.y));


    puts("Please enter a set of displacement of your pattern :");
    char c; unsigned i = 0 ,i_x =0 , i_y = 0; // Indexes for generating new point 
    while((c=fgetc(stdin))!='\n')
    {
      ungetc(c,stdin);
      if((c=fgetc(stdin)) == 'i')
      {
        switch(fgetc(stdin))
        {
          case 'x' :
           while(isspace(c=fgetc(stdin)));
           ungetc(c,stdin);

            scanf("%f", &pt_itmd.x);
            ++i_x;
            break;

          case 'y' :
           while(isspace(c=fgetc(stdin)));
           ungetc(c,stdin);

            scanf("%f", &pt_itmd.y);
            ++i_y;

            break;
          default : 
            input_syntax_error_exit();
        }
      }
      if(i_x == i_y)
      {
        pt_array[i].x = pt_itmd.x;
        pt_array[i].y = pt_itmd.y;
        pt_itmd.x = pt_itmd.y = 0;
        ++i;
      }
      
/*
        if((c=fgetc(stdin)) == 'x')
        {
          while(isspace(c=fgetc(stdin)));
          ungetc(c,stdin);

          ++i_x;
          scanf("%f", &pt_itmd.x);

        }
        else if((c=fgetc(stdin)) == 'y')
        {
          while(isspace(c=fgetc(stdin)));
          ungetc(c,stdin);

          ++i_y;
          scanf("%f", &pt_itmd.y);

        }else ungetc(c,stdin);
        if(i_x == i_y)
        {
        pt_array[i].x = pt_itmd.x;
        pt_array[i].y = pt_itmd.y;
        pt_itmd.x = pt_itmd.y = 0;
        ++i;
        }else;
      }else input_syntax_error_exit();

*/
          
    }

}

void padstack_gen(char* ptr)
{

  int sign = 1;
  float pin_diam;
  float drill_diam;
  float pad_diam;
  float solder_diam;
  char padstack_name[12] = 
  {
    'T' , 'H' , 'C' , '\0' , 'R' , '\0' , '0' ,
                'D' , '\0' , 'R' , '\0' , '0'
  };

  if(*ptr == '-')
  {
    DBG(3,"Negative sign detected.");
    sign = -1;
    ++ptr;
  }
  if(isdigit(*ptr))
  {
    DBG(3,"Digit detected.");
    pin_diam = sign * atof(ptr);
    DBG(3,"pin_diam now is %.3f",pin_diam);


  }else syntax_error_exit('P');

calculate:
  if(pin_diam<0.8)
  {
    DBG(3,"In branch pin_diam < 0.8");
    drill_diam = pin_diam+0.2;
    pad_diam = drill_diam+0.3;
    solder_diam = pad_diam+0.075;
    DBG(3,"drill_diam now is : %.3f",drill_diam);
    DBG(3,"pad_diam now is : %.3f",pad_diam);
    DBG(3,"solder_diam now is : %.3f",solder_diam);

  }else
  {

    DBG(3,"In branch pin_diam >= 0.8");
    drill_diam = pin_diam+0.3;
    pad_diam = drill_diam+0.5;
    solder_diam = pad_diam+0.075;
    DBG(3,"drill_diam now is : %.3f",drill_diam);
    DBG(3,"pad_diam now is : %.3f",pad_diam);
    DBG(3,"solder_diam now is : %.3f",solder_diam);

  }
  padstack_name[3] = (int) pad_diam + '0';
  padstack_name[5] = (int) (pad_diam*10)%10 + '0';
  padstack_name[6] = (int) ((int)(pad_diam*100)%100)%10 + '0';

  padstack_name[8] = (int) drill_diam + '0';
  padstack_name[10] = (int) (drill_diam*10)%10 + '0';
  padstack_name[11] = (int) ((int)(drill_diam*100)%100)%10 + '0';
  DBG(3,"padstack_name now is : %s",padstack_name);

  printf("Your padstack name is : ""\033[0;32m""%s ""\033[0;0m""\n",padstack_name);
  printf("\tDrill finished diameter \t:\t\t %.3f\n",drill_diam);
  printf("\tDrill figure diameter \t\t:\t\t %.3f\n",drill_diam-0.2);
  printf("\tDesign layer - Pad diameter \t:\t\t ""\033[0;35m""%.3f""\033[0;0m""\n",pad_diam);
  printf("\tMask layer - Pad diameter \t:\t\t %.3f\n",solder_diam);

}

// Adhere to IPC-2222 standards fro minimum hole sizes
/*
  Once your component density classification has been determined , you should
  use the following equations to comply with the IPC-2222 Standard for minimum hole size.

    Level A Minimum Hole Size = maximum lead diameter + 0.25mm
    Level B Minimum Hole Size = maximum lead diameter + 0.20mm
    Level C Minimum Hole Size = maximum lead diameter + 0.25mm

*/

// Determine the pad sizes based on IPC-2221
/*
  After determining minumum hole size. Eqs.(444-6) from the IPC-2221 Standard should be used 
  to determine pad diameter.

    Level A Pad Diameter = minumum hole size + 0.1mm + 0.60mm
    Level B Pad Diameter = minimum hole size + 0.1mm + 0.50mm
    Level C Pad Diameter = minimum hole size + 0.1mm + 0.4mm

*/