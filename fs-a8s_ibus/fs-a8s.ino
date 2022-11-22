#include <string.h>

#define IBUS_BUFFSIZE 32    // Max iBus packet size (2 byte header, 14 channels x 2 bytes, 2 byte checksum)
#define IBUS_MAXCHANNELS 6 // My TX only has 10 channels, no point in polling the rest

static uint8_t ibusIndex = 0;
static uint8_t ibus[IBUS_BUFFSIZE] = {0};
static uint16_t rcValue[IBUS_MAXCHANNELS];

static boolean rxFrameDone;
int ch1;
int ch2;
int ch3;
int ch4;
void setup() 
{
  Serial.begin(115200); 
  Serial.println("setup done!");
}

void loop() 
{
  readRx();
}

void readRx()
{
  rxFrameDone = false;
  
  if (Serial.available())
  {
    uint8_t val = Serial.read();
    // Look for 0x2040 as start of packet
    if (ibusIndex == 0 && val != 0x20)
    {
      ibusIndex = 0;
      return;
    }
    if (ibusIndex == 1 && val != 0x40) 
    {
      ibusIndex = 0;
      return;
    }

    if (ibusIndex == IBUS_BUFFSIZE)
    {
      ibusIndex = 0;
      int high=3;
      int low=2;
      for(int i=0;i<IBUS_MAXCHANNELS; i++)
      {
        //left shift away the first 8 bits of the first byte and add the whole value of the previous one
        rcValue[i] = (ibus[high] << 8) + ibus[low];
        high += 2;
        low += 2;
      }
      ch1 = map(rcValue[2], 1000, 2000, 0, 255);
      Serial.print("ch3:");
      Serial.print(ch1);
      Serial.print("     ");
      ch2 = map(rcValue[3], 2000, 1000, 0, 255);
      Serial.print("ch4:");
      Serial.print(ch2);
      Serial.print("     ");
      ch3 = map(rcValue[1], 2000, 1000, 0, 255);
      Serial.print("ch2:");
      Serial.print(ch3);
      Serial.print("     ");
      ch4 = map(rcValue[7], 2000, 1000, 0, 255);
      Serial.print("ch1:");
      Serial.print(ch4);
      Serial.print("     ");
      Serial.println();
      rxFrameDone = true;
      return;
    }
    else
    {
      ibus[ibusIndex] = val;
      ibusIndex++;
    }
  }
}
