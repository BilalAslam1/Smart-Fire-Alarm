#include <ESP8266Wi-Fi.h>
#include <ThingerESP8266.h>

#define USERNAME "Sense"
#define DEVICE_ID "ESP8266"
#define DEVICE_CREDENTIAL "l%Yjg@IvUtgW"

#define SSID "Sammy"
#define SSID_PASSWORD "password1"

//Define global input and ouput arrays to communicate with Arduino
char mystr[7];
char sending[3] = {0};
int receiving_int[7] = {0};
int sending_int[3] = {0};
int x = 0, a, b;

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup()
{
  //set Baudrate for communication
  Serial.begin(115200);
 delay(100);

  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_Wi-Fi(SSID, SSID_PASSWORD);

  //*************Initialize Input/Ouput Resources********************************************
  //Output resources
  thing["MQ2"] >> [](pson & out)
  {
    if (receiving_int[0] == 0)
    {
      
      out = "No fire detected. The area is safe.";
    }
    else
    {
      out = "Fire Detected! Vacate the premises immedietely!";
    }
  };
  thing["MQ9"] >> [](pson & out)
  {
    if (receiving_int[1] == 0)
    {
      
      out = "CO levels are below threshold.";
    }
    else
    {
      out = "CO levels are at a hazardous level!";
    }
  };
  thing["Temp"] >> [](pson & out)
  {
    a= receiving_int[2];
    a=a*10;
    b = receiving_int[3];
    a = a+b;
    out = a;
  };
  thing["PIR"] >> [](pson & out)
  {
    if (receiving_int[4] == 0)
    {
      out = "No people detected in the vicinity.";
    }
    else
    {
      
      out = "People are within the vicinity.";
    }
  };
  thing["Microphone"] >> [](pson & out)
  {
    if (receiving_int[5] == 0)
    {
       out = "No human sound were detected.";
    }
    else
    {
     
      out = "Human sound was detected.";
    }
  };
  thing["Buzzer_State"] >> [](pson & out)
  {
    if (receiving_int[6] == 0)
    {
      out = "OFF.";
    }
    else
    {
      
      out = "ON.";
    }
  };

  //Input Resouces
  thing["Buzzer"] << [](pson& in){
    sending_int[0] = in;
};
//thing["Test"] << [](pson& in)
//{
//    sending_int[1] = in;
//};
thing["Reset"] << [](pson& in){
    sending_int[2] = in;
};
//thing["Test"] << [](pson& in){
//    if(in = LOW){
//        sending_int[1] = 0;
//        in  = HIGH;
//        Serial.println("0");
//    }
//    else{
//        sending_int[1] = 1;
//        in = LOW;
//        Serial.println("1");
//    }
//};

  //  //Input and Output Resource
  //  thing["Buzzer"] = [](pson& in, pson& out)
  //  {
  //  if ((in ==0) && (receiving_int ==0))
  //  {
  //    out =
  //  }
  //  };

  // resource output example (i.e. reading a sensor value)
  //thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop()
{
thing.handle();
//
  //stream resources
  thing.stream(thing["MQ2"]);
  thing.stream(thing["MQ9"]);
  thing.stream(thing["Buzzer_State"]);
  thing.stream(thing["Temp"]);
  thing.stream(thing["PIR"]);
  thing.stream(thing["Microphone"]);
  //thing.stream(thing["Test"]);
  //thing.stream(thing["Reset"]);
//Serial.println("Hello");
    //Receive Info
   // if (Serial.available() > 0)
    //{
    delay(1000);
    if (Serial.available()>6 )
    {
Serial.readBytes(mystr, 7);
    delay(2000);
      //Serial.println(receiving);
      for (x = 0; x < 7; x++)
      {
        receiving_int[x] = mystr[x] - '0';
      }
    }
    delay(1000);
    //Serial.println("ReceivingChar");
   // for (x=0;x<15;x++)
    //{
     // Serial.println(iron);
    //  Serial.println(receiving_int[x]);
 //   }
   //     Serial.println("Receiving INT");
    //for (x=0;x<15;x++)
    //{
     // Serial.println(receiving_int[x]);
   // }
  
//    //Output Info to arduino
//    for (x = 0; x < 3; x++)
//    {
//      sending_int[x] = sending[x] + '0';
//    }
//    Serial.write(sending, 3);
//char mystr[8]={0};
  
}
