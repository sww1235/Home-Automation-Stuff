package main

import (
	"fmt"
	"net"
)

var serverList = make(map[IP]string)

func main() {
	fmt.Printf("hello, world\n")
}

//What exactly does this need to do
//List of functions
//Status
//add device
//update device
//prepare firmware
//compile firmware
//upload firmware to tftp server and send remote reset to arduino
//manage database connection
//Simulate arduino button presses
//send query string on network

//
func getNetworkStatus() {
	var s string = ""
	for IP, _ := range serverList {
		s += networkQuery(s, IP)
	}
}

//This encapsulates s into tcp packets, establishes a tcp session w/ ip,
//transmits the packets and recieves and returns the response as a string
//TODO decide on exact return value
func networkQuery(s string, ip [4]int) string {

}
