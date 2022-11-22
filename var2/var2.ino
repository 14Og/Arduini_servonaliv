#include <ServoSmooth.h>
#define channumber 8 //How many channels have your radio???


int angleServo = 160;

ServoSmooth svp; // making servo object
int pinServo = 5; //  servo pin on arduino

int channel[channumber]; //read Channel values
int lastReadChannel[channumber]; //Last  values readed

int PPMin = A3; // fs-A8S pin

void setup()
{
  svp.attach(pinServo);
  svp.setSpeed(90);
  svp.setAccel(0.1);
  Serial.begin(9600); //Serial Begin
  pinMode(PPMin, INPUT); //PPMin as input
}


void loop()
{

  if (pulseIn(PPMin, HIGH) > 3000) //If pulse > 3000 useconds, continues
  {
    for (int i = 0; i <= channumber - 1; i++) //Read the pulses of the channels
    {
      channel[i] = pulseIn(PPMin, HIGH);
    }
    for (int i = 0; i <= channumber - 1; i++) //Average the pulses
    {
      if ((channel[i] > 2000) || (channel[i] < 100)) //If channel > max range, chage the value to the last pulse
      {
        lastReadChannel[i] = channel[i];
      }
      else
      {
        channel[i] = (lastReadChannel[i] + channel[i]) / 2; //Average the last pulse eith the current pulse
      }
    }
      if (channel[5]>500)
    {
        servo_rotate(channel[1]); // calls the function 
    }
  }
}

void servo_rotate(int chan_value)
{
  Serial.print("Angleservo: " + String(angleServo) + "\t" + "CH: " + chan_value + "\n");
  
  
  if (chan_value > 550 && angleServo < 180)
  {
    angleServo++;
    svp.write(angleServo);
  }
  if (chan_value > 700 && angleServo <180)
  {
    angleServo = angleServo + 3;
    svp.write(angleServo);
  }
  if (chan_value < 530 && angleServo > 0)
  {
    angleServo--;
    svp.write(angleServo);
  }
  if (chan_value < 300 && angleServo >0)
  {
    angleServo = angleServo -3;
    svp.write(angleServo);
  }
  if (chan_value <= 548 && chan_value >= 544)
  {
    svp.write(angleServo);
  }
}