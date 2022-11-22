#define channumber 8 //How many channels have your radio???
#define filter 10 // Glitch Filter

#define MIN_POS 700
#define MED_POS 1000
#define MAX_POS 1300


int channel[channumber]; //read Channel values
int lastReadChannel[channumber]; //Last  values readed
int conta = 0; //couter
int Led = 13;
int PPMin = A5;
int pyroCH1 = A1;
int pyroCH2 = A2;
int pyroCH3 = A3;
int pyroCH4 = A4;

void setup()
{
  Serial.begin(57600); //Serial Begin
  pinMode(PPMin, INPUT); //PPMin as input
  pinMode(Led, OUTPUT); // Led pin
  pinMode(pyroCH1, OUTPUT); // CH1 pin
  pinMode(pyroCH2, OUTPUT); // CH2 pin
  pinMode(pyroCH3, OUTPUT); // CH3 pin
  pinMode(pyroCH4, OUTPUT); // CH4 pin    
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
        channel[i] = lastReadChannel[i];
      }
      else
      {
        channel[i] = (lastReadChannel[i] + channel[i]) / 2; //Average the last pulse eith the current pulse
        conta++; //increment counter
      }
    }

  }

  if (conta > filter) //If counter is > than filter, then prints values
  {
    for (int i = 0; i <= channumber - 1; i++) //Cycle to print values
    {
      Serial.print(channel[i], DEC); //Channel value
      Serial.print("\t");

      lastReadChannel[i] = channel[i];
    }
  
    Serial.println();
    
    delay(100); //Delay
    conta = 0; //Restart counter.
  }
}
