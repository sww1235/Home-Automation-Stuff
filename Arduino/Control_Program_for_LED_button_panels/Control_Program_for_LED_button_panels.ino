//code based on arduino web client tutorial
//using static ip address



//each button press should send an http get request to the 
//appropriate relay or device

//includes
#include <SPI.h>
#include <Ethernet.h>

//Definitions
byte mac[] = { , , , , , }; //need to fill in with generated mac address (6 byte array)
IPAddress ip( , , , ); //static ip address of local device
IPAddress server1( , , , ); //static ip address of device to be controlled by button 1
IPAddress server2( , , , ); //static ip address of device to be controlled by button 2
IPAddress server3( , , , ); //static ip address of device to be controlled by button 3
IPAddress server4( , , , ); //static ip address of device to be controlled by button 4
IPAddress server5( , , , ); //static ip address of device to be controlled by button 5
IPAddress server6( , , , ); //static ip address of device to be controlled by button 6
IPAddress server7( , , , ); //static ip address of device to be controlled by button 7
IPAddress server8( , , , ); //static ip address of device to be controlled by button 8



EthernetClient client;
//EthernetServer server(port); //if we want a server

void setup() {
  //reset ethernet shield by pulling pin low
  Ethernet.begin(mac, ip); //initilize ethernet shield
  delay(1000);
  

}

void loop() {
  // put your main code here, to run repeatedly:
//monitor button inputs
//if button # pressed then connect to proper server
  client.connect(server, 80);
  client.println("GET /search?q=arduino HTTP/1.1");
  
}
