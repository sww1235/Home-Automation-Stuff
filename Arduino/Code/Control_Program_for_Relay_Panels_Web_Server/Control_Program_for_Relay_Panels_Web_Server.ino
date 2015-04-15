#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <avr/pgmspace.h>

//need to modify client.cpp and client.h with below code to allow for getting client ip address. may not be needed.

/*
//for client.cpp
Client::Client(uint8_t *ip, uint16_t port) {
 _ip = ip;
 _port = port;  
 _sock = 255;
}

//what you need to add starts here
void Client::IP_address(uint8_t * addr)
{
	getSn_DIPR(_sock, addr);

}

//for client.h


void stop();
void IP_address(uint8_t * addr);//Only add this line as the others already exist
uint8_t connected();

*/

//code based on arduino web server tutorial
//using static ip address

//Designed for use with Arduino Nano


/*
Basically the idea is to have devices that control things (the servers that are connected to
the physical devices) and clients which are the push button panels and other human interfaces

Each server has an IP address and can have multiple controlled devices. Query strings will be customized
for specific controlled devices.

This code is a template that will be automagically filled in for a specific device by the
command and control server.


this is code for an arduino board that controls something when it receives an
Http get request with a query string in the URL. the specific action to be taken
depends on the query string. It is running a local web server

it also reports its status to the command and control server

*/
//Definitions
byte mac[] = { , , , , , }; //need to fill in with generated mac address (6 byte array)
IPAddress ip( , , , ); //static ip address of local device (server)
// add list of query strings to respond to here
// will need two entries to turn something on and off.
const PROGMEM char query1[] = ""; 

EthernetServer server(80);
char incString[100]; //set max length of request string
void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip);
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available(); //listen for incoming clients
  while (client.connected())
  {
    if (client.available())
    {
      int ii = 0;
      while ((c = client.read()) != "\n") //read from client
      {
        incString[ii++] = c;

      }
      
      //incString now has querry string inside it.
      //do client.println(""); if you want to display html page 
      //write to client
      delay(1);
      //stopping client
      client.stop();
      //implement functions here that control outputs
      //define query strings at the top and then reference them in the if statements down here
      if (strcmp_PF(incString, PSTR(query1))==0)
      {
      //do what ever, like set output high or low to trigger a relay or whatever.
      }//repeat if statements for other triggers
      
      incString=""; //clear string for next useage
      
      


    }

  }

}
}
