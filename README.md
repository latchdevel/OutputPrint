# OutputPrint

OutputPrint class provides **print()** and **println()** methods and **String** class from Wiring / Arduino library.

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

OutputPrint class can use any file descriptor as output, by default "stdout" if defined, and add a dummy "Serial" instance to emulate Arduino **Serial.print()** function.
Can run on any libc/libc++ compatible system, like MacOS, FreeBSD, Linux, even Windows.

For Serial.print() reference see: https://www.arduino.cc/reference/en/language/functions/communication/serial/print/

For String class reference see: https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/

Copyright (c) 2021 Jorge Rivera. All right reserved. 
License GNU Lesser General Public License v3.0.

## Hello World example
Example C++ standard source file "hello_world.cpp":
```cpp
/*
  hello_world.cpp

  OutputPrint class provides print() and println() methods 
  and String class from Wiring / Arduino library.

  OutputPrint class can use any file descriptor as output, 
  by default "stdout" if defined, and add a dummy "Serial" 
  instance to emulate Arduino Serial.print() function.

  Copyright (c) 2021 Jorge Rivera.  All right reserved.
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

    Serial.println("- Wiring/Arduino Serial.print() output");

    return 0;
}
```
### Build
```
$ git clone https://github.com/latchdevel/OutputPrint
$ cd OutputPrint
$ mkdir build
$ cd build
$ cmake .. 
$ make hello_world
```

### Execute
```
$ ./hello_world
Hello World!
- Example write to standard error: -1
- Wiring/Arduino Serial.print() output
```

# License
Copyright (c) 2021 Jorge Rivera. All right reserved.

License GNU Lesser General Public License v3.0.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License 
along with this library; if not, write to the Free Software Foundation, 
Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.

See the [LICENSE](LICENSE.md) file for license rights and limitations (lgpl-3.0).
