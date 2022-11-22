#include <Servo.h>
#define channumber 8 //How many channels have your radio???
#define filter 4 // Glitch Filter
#define MY_PERIOD 100


uint32_t tmr1;
int angleServo = 159;

Servo svp; // making servo object
int pinServo = 5; //  servo pin on arduino

int channel[channumber]; //read Channel values
int lastReadChannel[channumber]; //Last  values readed
int conta = 0; //counter
int PPMin = A3; // fs-A8S pin

void setup()
{
  svp.attach(pinServo);
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
  }

  servo_rotate(channel[1]);
  Serial.print(String(channel[1])+ "\t");
  }

  


void servo_rotate(int chan_value)
{
  Serial.println("Angleservo: " + String(angleServo));
  if (chan_value > 1100 && angleServo < 180)
  {
    angleServo++;
    svp.write(angleServo);
  }
  if (chan_value > 1300 && angleServo <180)
  {
    angleServo = angleServo + 2;
    svp.write(angleServo);
  }
  if (chan_value < 1000 && angleServo > 0)
  {
    angleServo--;
    svp.write(angleServo);
  }
  if (chan_value < 700 && angleServo >0)
  {
    angleServo = angleServo -2;
    svp.write(angleServo);
  }
  if (chan_value <= 1087 && chan_value >= 1081)
  {
    svp.write(angleServo);
  }
}
  




