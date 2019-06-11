#include <Adafruit_TMP006.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_TMP006 tmp006;
int MotionSensor=9;
int MircoPhone=8;
int Buzzer=10;
int SmokeSensor=A0;
int COSensor=A1;
int HeatSensor=A4;
int HighCo;
int MedCo;
int LowCo;
int SmokeLevel=0;
int CoLevel=0;
int CriticalSmokeLevel=30;
int FireState=0;
int MotionState=0;
char HumanProb;
int IOToutput[7];
char IOTinputChar[3];
int IOTinput[3];
char IOToutputChar[7]="0";
unsigned long LastSampleTime = 0;
int j;

char mystr[5]="Hello";

void setup() {
 //Heat Sensor Initiliztion  
    if (! tmp006.begin()) {
    //Serial.println("No sensor found");
    while (1);
  }
  
    //Initilzating Inputs and Outputs
  pinMode(MotionSensor,INPUT);
  pinMode(MircoPhone,INPUT);
  pinMode(SmokeSensor,INPUT);
  pinMode(COSensor,INPUT);
  pinMode(Buzzer,OUTPUT);
  
Serial.begin(115200);
  delay(1000);

}

void loop() 
{
  //const long SamplingTime = 5*1000;
  //long Timer= millis();

  //if ((Timer-LastSampleTime)>= SamplingTime)
 // {
  //  LastSampleTime+= SamplingTime;

//    if (Serial.available() >0)
//    {
//      Serial.readBytes(IOTinputChar, 3);
//    
//      delay(250);
//      for (j=0;j<3;j++)
//      {
//        IOTinput[j]=IOTinputChar[j]-'0';
//      }
//    }
    //Reading Smoke sensor analog values and printing them
//   SmokeLevel=analogRead(SmokeSensor);
//   Serial.println("Smoke Level:");Serial.println(SmokeLevel);
    
//    Reading CO sensor analog values and printing them
    CoLevel=analogRead(COSensor);
    //Serial.println("Co level is:");Serial.println(CoLevel);
    
    //Reading Heat sensor values and printing them
    int A=tmp006.readObjTempC();
    IOToutput[2]=A/10;
    IOToutput[3]=A-(IOToutput[2]*10);
    //Serial.print("Object Temperature: "); Serial.print(IOToutput[2]);Serial.print(IOToutput[3]); Serial.println("*C");
    
    float diet = tmp006.readDieTempC();
    //Serial.print("Die Temperature: "); Serial.print(diet); Serial.println("*C");

    if ((SmokeLevel>CriticalSmokeLevel) || (IOTinput[0]==1))
    { 
    
    //Evaluting if temperature if high enough for a fire
      if ((IOToutput[2] >50) | (IOTinput[0]==1) )
      {

      //Buzzer is activated
        digitalWrite(Buzzer,HIGH);
        IOToutput[0]=1;
     //Reading the state of motion sensor     
        if(digitalRead(MotionSensor)==HIGH)
        {
          IOToutput[4]=1;
        }
     
     //Reading the state of mircophone
        if(digitalRead(MircoPhone)==HIGH)
        {
          IOToutput[5]=1;
        }
      }
    }
    else if (SmokeLevel<CriticalSmokeLevel)
    {
      IOToutput[0]=0;
      IOToutput[4]=0;
      IOToutput[5]=0;
      digitalWrite(Buzzer,LOW);
    }

    if (CoLevel<300)
    {
      IOToutput[1]=0;
      
    }
    if (CoLevel>300)
    {
      IOToutput[1]=1;
      
    }
    if (digitalRead(Buzzer)==HIGH)
    {
      IOToutput[6]=1;
    }
    if (digitalRead(Buzzer)==LOW)
    {
      IOToutput[6]=0;
    }
    for(int i=0; i<7; i++)
    {
     IOToutputChar[i] = IOToutput[i] + '0';
     //Serial.println(IOToutputChar[i]);
    }
  
 delay(5000);

      // Send Data
    Serial.write(IOToutputChar,7);
    delay(1000);
  // Serial.flush();
//**************Receive Data***************

}

