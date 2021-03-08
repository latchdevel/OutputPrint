/*
  hello_world.cpp

  OutputPrint class provides print() and println() methods 
  and String class from Wiring / Arduino library.

  OutputPrint class can use any file descriptor as output, 
  by default "stdout" if defined, and add a dummy "Serial" 
  instance to emulate Arduino Serial.print() function.

  Copyright (c) 2021 Jorge Rivera. All right reserved.
  License GNU Lesser General Public License v3.0.
*/

#include "src/OutputPrint.h"

/* By default constructor set output to "sdtout" */
/* file descriptor is defined by POSIX <stdio.h> */

OutputPrint Out;    

/* "stderr" stream for standard error output      */
/* file descriptor is defined by POSIX <stdio.h>  */

OutputPrint Error(stderr);  

String hello_string = "Hello World!";

int main(){

    Out.println(hello_string);

    Error.print("- Example write to standard error: ");
    Error.println(-1,DEC);

    Serial.println("- Wiring/Arduino Serial.print() outout");

    return 0;
}




