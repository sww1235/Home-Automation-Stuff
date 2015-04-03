//#include <Dhcp.h>
//#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
//#include <EthernetServer.h>
//#include <EthernetUdp.h>
#include <Wire.h>
#include <CShiftPWM.h>
#include <pins_arduino_compile_time.h>
#include <ShiftPWM.h>
#include <SPI.h>
#include <avr/pgmspace.h>

//code based on arduino web client tutorial
//using static ip address

//Designed for use with Arduino Nano

/*
each button press should send an http get request to the
appropriate relay or device. Receiving Device should report to command and control server using similar mechanism.


Basically the idea is to have devices that control things (the servers that are connected to
the physical devices) and clients which are the push button panels and other human interfaces

Each server has an IP address and can have multiple controlled devices. Query strings will be customized
for specific controlled devices.

This code is a template that will be automagically filled in for a specific device by the
command and control server.


This code is for the RGB LED button panel clients.

Remember that there are 8 buttons on the device plus an additional 2 external buttons.
*/
//Definitions
const int ShiftPWM_latchPin = 8;
const int resetEthernetPin = 4;
const int rxSense 3;
//make sure to move all string constants to progmem to save space, especially the query strings.
const byte mac[] = { , , , , , }; //need to fill in with generated mac address (6 byte array)
const IPAddress ip( , , , ); //static ip address of local device (client)
//Duplicate Server IP address if it is accessed by more than one button.
const IPAddress server1( , , , ); //static ip address of device to be controlled by button 1
const IPAddress server2( , , , ); //static ip address of device to be controlled by button 2
const IPAddress server3( , , , ); //static ip address of device to be controlled by button 3
const IPAddress server4( , , , ); //static ip address of device to be controlled by button 4
const IPAddress server5( , , , ); //static ip address of device to be controlled by button 5
const IPAddress server6( , , , ); //static ip address of device to be controlled by button 6
const IPAddress server7( , , , ); //static ip address of device to be controlled by button 7
const IPAddress server8( , , , ); //static ip address of device to be controlled by button 8
const IPAddress server9( , , , ); //static ip address of device to be controlled by button 9  (external switch)
const IPAddress server0( , , , ); //static ip address of device to be controlled by button 10 (external switch)
const IPAddress ccServer( , , , );//static ip address of command and control server
//Will always have 10 queries, even if they are duplicates. (example string = "GET /?message HTTP/1.0")
const PROGMEM char query1[] = "";
const PROGMEM char query2[] = "";
const PROGMEM char query3[] = "";
const PROGMEM char query4[] = "";
const PROGMEM char query5[] = "";
const PROGMEM char query6[] = "";
const PROGMEM char query7[] = "";
const PROGMEM char query8[] = "";
const PROGMEM char query9[] = "";
const PROGMEM char query0[] = "";
const PROGMEM char ccQuerry[] = ""; //querry to get data back from command and control server
EthernetClient client; //main web client

//EthernetServer server(port); //if we want a server

byte GPIOA, GPIOB;
boolean button1, button2, button3, button4, button5, button6, button7, button8, button9, button0;
char incString[100]; // length of response from server (only requesting data from command and control server will use this, shrink if needed.
void(* resetFunc) (void) = 0; //declare reset function @ address 0

//need const for the char array because it is a pass by reference so it could be potentially modified by the function if const is not specififed.
void connectToServer(IPAddress address, const char request[]) {
  if (client.connect(address, 80))
  {
    client.println(PSTR(request)); //the client does not actually need to get anything back from the server.
    client.println(PSTR("Connection: close"));
    client.println();
    delay(500);
    client.flush();
    client.stop();
  }


}
void connectToServerAndRetrieveData(IPAddress address, const char request[]) {
  incString=""; //clear incString
  if (client.connect(address, 80))
  {
    client.println(PSTR(request)); 
    client.println(PSTR("Connection: close"));
    client.println();
    delay(500);
    if (client.available)
    {
      int ii = 0;
      while ((c = client.read()) != "\n")
      {
        incString[ii++] = c;

      }

    }


    client.flush();
    client.stop();
  }


}

void ethernetReset() {
  bool rxState;
  int cnt = 10, retryCount = 10, result;

  pinMode(resetEthernetPin, INPUT); //reset pin for ethernet shield
  pinMode(rxSense, INPUT); //sense pin for rx led on ethernet shield


  while (retryCount-- > 0) {
    digitalWrite(resetEthernetPin, HIGH); //enable internal pullup resistor on resetEthernetPin
    pinMode(resetEthernetPin, OUTPUT); //change pin mode to output
    digitalWrite(resetEthernetPin, LOW);//pull ehternet board reset pin low to reset
    delay(1000);
    digitalWrite(resetEthernetPin, HIGH);
    delay(2000);
    // after reset, check rx pin for constant on

    cnt = 10;
    result = 0;
    while (cnt-- != 0) { // simply count the number of times the light is on in the loop
      result += digitalRead(rxSense);
      delay(50);
    }
    if (result >= 6)     // experimentation gave me this number YMMV: confirm this number
      return;
    delay(50);

  }
  // OK, I tried 10 times to make it work, just start over.
  resetFunc();


}

void setup() {
  ethernetReset();
  Ethernet.begin(mac, ip); //initilize ethernet shield
  delay(1000);
  Wire.begin(); //wake up I2C bus




}


void loop()
{
  // put your main code here, to run repeatedly:
  connectToServerAndRetrieveData(ccServer, PSTR(ccQuery)); //this sets incString[] to a string value recieved from the command and control server that encodes the status of the leds
  //implement stuff to look at value of incString and change led values based on it.
  Wire.beginTransmission(0x20); //begin transmission on wire bus to address of mux, which is 0x20
  Wire.write(0x12); //set MCP23017 memory pointer to GPIOA address
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1); // read one byte of data from GPIOA. Status will be represented as a bianary nbr.
  GPIOA = Wire.read();
  Wire.beginTransmission(0x20);
  Wire.write(0x13);
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1);
  GPIOB = Wire.read();
  if (GPIOA > 0 || GPIOB > 0) //if a button was pressed
  {
    if (GPIOA > 0)
    {
      button1 = (boolean) GPIOA & B00000001; //set all other bits to zero except first which gives us true/false
      button2 = (boolean) GPIOA & B00000010;
      button3 = (boolean) GPIOA & B00000100;
      button4 = (boolean) GPIOA & B00001000;
      button5 = (boolean) GPIOA & B00010000;
      button6 = (boolean) GPIOA & B00100000;
      button7 = (boolean) GPIOA & B01000000;
      button8 = (boolean) GPIOA & B10000000;

      if (button1 == true)
      {
        connectToServer(server1, query1);
      }
      if (button2 == true)
      {
        connectToServer(server2, query2);
      }
      if (button3 == true)
      {
        connectToServer(server3, query3);
      }
      if (button4 == true)
      {
        connectToServer(server4, query4);
      }
      if (button5 == true)
      {
        connectToServer(server5, query5);
      }
      if (button6 == true)
      {
        connectToServer(server6, query6);
      }
      if (button7 == true)
      {
        connectToServer(server7, query7);
      }
      if (button8 == true)
      {
        connectToServer(server8, query8);
      }

    }
    if (GPIOB > 0)
    {
      button9 = (boolean) GPIOB & B00000001;
      button0 = (boolean) GPIOB & B00000010;
      if (button9 == true)
      {
        connectToServer(server9, query9);
      }
      if (button0 == true)
      {
        connectToServer(server0, query0);
      }

    }

  }



}
