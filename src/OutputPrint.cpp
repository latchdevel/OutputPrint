/*
  OutputPrint class provides print() and println() methods 
  and String class from Wiring / Arduino library.

  OutputPrint class can use any file descriptor as output, 
  by default "stdout" if defined, and add a dummy "Serial" 
  instance to emulate Arduino Serial.print() function.

  Copyright (c) 2021 Jorge Rivera. All right reserved.

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
*/

#include "OutputPrint.h"

OutputPrint::OutputPrint(FILE* _output){
  output = _output;
}

int OutputPrint::flush(){
  return fflush(output);
}

size_t OutputPrint::write(uint8_t byte){
  return (size_t)putc(byte, output);
}

#ifdef stdout
OutputPrint Serial(stdout);
#endif