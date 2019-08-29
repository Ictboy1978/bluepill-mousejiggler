#include <USBComposite.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define LED PC13

//Minimum and maximum moving time, it will be generated randomly between every NEWPERC time.
#define PERCMIN  18
#define PERCMAX  88

//Generate new percentage every NEWPERC sec.
#define NEWPERC  180

USBHID HID;
HIDMouse Mouse(HID);

//------------------------------------------------------
void setup(){
  pinMode(LED,OUTPUT);
  digitalWrite(LED,1);
  HID.begin(HID_MOUSE);
  delay(1500);
  randomSeed(100);
}
//------------------------------------------------------
void Ledflash()
{
  digitalWrite(LED,0);    
  delay(250);
  digitalWrite(LED,1);
}
//------------------------------------------------------
void GoDir(u8 dir, u8 spd)
{
  if(dir==0) Mouse.move(0,spd); 
  if(dir==1) Mouse.move(0,-spd); 
  if(dir==2) Mouse.move(spd,0); 
  if(dir==3) Mouse.move(-spd,0); 
  if(dir==4) Mouse.move(spd,spd); 
  if(dir==5) Mouse.move(spd,-spd); 
  if(dir==6) Mouse.move(-spd,spd); 
  if(dir==7) Mouse.move(-spd,-spd);
}
//------------------------------------------------------
void Jiggle(void)
{
      GoDir(4,1);
      delay(250);
      GoDir(7,1);
      Ledflash();
}
//------------------------------------------------------
void loop()
{
u16 x, per;
u32 timm;

    for(x=0;x<20;x++) GoDir(0,4);
    for(x=0;x<20;x++) GoDir(2,4);
    for(x=0;x<20;x++) GoDir(1,4);
    for(x=0;x<20;x++) GoDir(3,4);
  
    timm=millis();
    per=PERCMIN+random(PERCMAX-PERCMIN+1);
    
    while(1)
    {
      for(x=0;x<per;x++) Jiggle();
      for(x=0;x<(100-per);x++) delay(500);
      if((millis()-timm) > 1000*NEWPERC)
      {
              per=PERCMIN+random(PERCMAX-PERCMIN+1);
              timm=millis();
              Ledflash();
      }
    }
}
//------------------------------------------------------
