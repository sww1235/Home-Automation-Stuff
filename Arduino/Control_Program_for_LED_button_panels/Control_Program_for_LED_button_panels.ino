

#include <Wire.h>

#include <CShiftPWM.h>
#include <pins_arduino_compile_time.h>
#include <ShiftPWM.h>


#include <SPI.h>
#include <Ethernet.h>
//code based on arduino web client tutorial
//using static ip address



//each button press should send an http get request to the
//appropriate relay or device


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
IPAddress server9( , , , ); //static ip address of device to be controlled by button 9  (external)
IPAddress server0( , , , ); //static ip address of device to be controlled by button 10 (external)

EthernetClient client;
//EthernetServer server(port); //if we want a server

byte inputsA = 0;
byte inputsB = 0;

void setup() {
  //reset ethernet shield by pulling pin low
  Ethernet.begin(mac, ip); //initilize ethernet shield
  delay(1000);
  Wire.begin(); //wake up I2C bus




}

void loop()
{
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x20); //begin transmission on wire bus to address of mux, which is 0x20
  Wire.write(0x12); //set MCP23017 memory pointer to GPIOA address
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1); // read one byte of data from GPIOA. Status will be represented as a bianary nbr.
  inputsA = Wire.read();
  Wire.beginTransmission(0x20);
  Wire.write(0x13);
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1);
  inputsB = Wire.read();
  if (inputsA > 0 || inputsB > 0) //if a button was pressed
  {
    if (inputsA > 0)
    {
      switch (inputsA)
      {
        case 00000001: //button 1 pressed
          //statements
          break;
        case 00000010: //button 2 pressed
          //statements
          break;
        case 00000100: //button 3 pressed
          //statements
          break;
        case 00001000: //button 4 pressed
          //statements
          break;
        case 00010000: //button 5 pressed
          //statements
          break;
        case 00100000: //button 6 pressed
          //statements
          break;
        case 01000000: //button 7 pressed
          //statements
          break;
        case 10000000: //button 8 pressed
          //statements
          break;
        case 00000011: //buttons 1 and 2 pressed
          //statements
          break;
        case 00000110: //button 2 and 3 pressed
          //statements
          break;
        case 00001100: //button 3 and 4 pressed
          //statements
          break;
        case 00000000: //button 4 and 5 pressed
          //statements
          break;

        default:
          //statements

      }

    }
    if (inputsB > 0)
    {
      switch (inputsB)
      {


      }
    }

  }

  //monitor button inputs
  //if button # pressed then connect to proper server
  client.connect(server, 80);
  client.println("GET /search?q=arduino HTTP/1.1");

}
