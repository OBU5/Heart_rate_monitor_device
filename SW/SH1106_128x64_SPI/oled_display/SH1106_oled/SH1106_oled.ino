/*

  HelloWorld.ino

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 17, /* reset=*/ 16);		//same as the NONAME variant, but maximizes setContrast() range


int hCenter = 32;                               // horizontal center of 64 / 2 = 32
int Radius = 30;                                // radius of circle
const float Pi = 3.14159265359;                 // Pi


void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB10_tr);	// choose a suitable font
  u8g2.drawStr(0,12,"MAX86150 DEMO");  // write something to the internal memory  
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font

  u8g2.drawStr(20,60,"Designed by OBU");  // write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(5000);  
  int index = 0;
  for(int j = 0; j < 10; j ++){
    u8g2.clearDisplay();                                      // clears display
    for (int i=0; i<120; i++){                                   // draws 120 pixels per loop
      index++;
      float Angle = index * 10;                                       // 120 X 3 = 360°
      int a = (hCenter + (sin(Angle * (Pi / 180)) * Radius));    // Pi/180 converts degrees to radians
      int b = (hCenter + (cos(Angle * (Pi / 180)) * Radius));    // Pi/180 converts degrees to radians
  
      u8g2.drawPixel(i,a);                              // draws each pixel for Sine wave
      u8g2.sendBuffer();    

      delay(50);
    } 
  }
}
