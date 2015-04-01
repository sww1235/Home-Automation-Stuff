//#include <Dhcp.h>
//#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
//#include <EthernetServer.h>
//#include <EthernetUdp.h>
#include <Wire.h>
#include <CShiftPWM.h>
#include <pins_arduino_compile_time.h>
//#include <ShiftPWM.h>
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

//make sure to move all constants to progmem to save space, especially the query strings.
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
const IPAddress server9( , , , ); //static ip address of device to be controlled by button 9  (external)
const IPAddress server0( , , , ); //static ip address of device to be controlled by button 10 (external)
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
EthernetClient client;
//EthernetServer server(port); //if we want a server

byte GPIOA, GPIOB;
boolean button1, button2, button3, button4, button5, button6, button7, button8, button9, button0;





void setup() {
  //reset ethernet shield by pulling pin low and wait for initilization
  Ethernet.begin(mac, ip); //initilize ethernet shield
  delay(1000);
  Wire.begin(); //wake up I2C bus




}
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

void loop()
{
  // put your main code here, to run repeatedly:
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
