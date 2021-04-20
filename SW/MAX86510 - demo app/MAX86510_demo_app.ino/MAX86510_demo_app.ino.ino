#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "max86150.h"


//max86150
#define debug Serial //Uncomment this line if you're using an Uno or ESP
MAX86150 max86150Sensor;
uint16_t ppgunsigned16;
uint16_t oledDot;

//OLED
U8G2_SH1106_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 17, /* reset=*/ 16);    //same as the NONAME variant, but maximizes setContrast() range
int hCenter = 32;                               // horizontal center of 64 / 2 = 32
int Radius = 30;                                // radius of circle
const float Pi = 3.14159265359;                 // Pi
int currentTime = 0;

void setup()
{  
    u8g2.begin();

    debug.begin(115200);
    debug.println("MAX86150 PPG Streaming Example");

    // Initialize sensor
    if (max86150Sensor.begin(Wire, 100000) == false)
    {
        debug.println("MAX86150 was not found. Please check wiring/power. ");
        while (1);
    }

    debug.println(max86150Sensor.readPartID());

    max86150Sensor.setup(); //Configure sensor. Use 6.4mA for LED drive
    
    
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
    u8g2.drawStr(0,12,"MAX86150 DEMO");  // write something to the internal memory  
    u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  
    u8g2.drawStr(20,60,"Designed by OBU");  // write something to the internal memory
    u8g2.sendBuffer();          // transfer internal memory to the display
    delay(5000);  
    u8g2.clearDisplay();                                      // clears display

}

void loop()
{
    if(max86150Sensor.check()>0)
    {
        ppgunsigned16 = (uint16_t) (max86150Sensor.getFIFORed()>>2);
        oledDot = (uint16_t) (ppgunsigned16 - 54000)/100;
        if(oledDot <=1){
          oledDot = 0;
        }else if(oledDot >= 63){
          oledDot = 63;
        }
        debug.println(ppgunsigned16);
        currentTime++;
        u8g2.drawPixel(currentTime,oledDot);                              // draws each pixel for Sine wave
        u8g2.sendBuffer();    
        delay(10);
      
        if (currentTime > 120){
          currentTime = 0;
          
            u8g2.clearDisplay();                                      // clears display
        }
    }
  /*
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
  u8g2.drawStr(0,12,"MAX86150 DEMO");  // write something to the internal memory  
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font

  u8g2.drawStr(20,60,"Designed by OBU");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
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
  }*/
}
