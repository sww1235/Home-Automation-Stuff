#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

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

*/
//Definitions
byte mac[] = { , , , , , }; //need to fill in with generated mac address (6 byte array)
IPAddress ip( , , , ); //static ip address of local device (server)

EthernetServer server(80);
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
