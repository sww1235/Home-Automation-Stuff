package main

import (
	"fmt"
	"log"
	"os"
)

var serverList = make(map[IP]string)

var clientList = make(map[IP]string)

const port int = 80 //TODO decide on custom port or make part of config
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
//getters and setters for serverList and clientList from database

// returns a string? with all status info for servers.
func getNetworkStatus() string {
	var s string = "" //TODO determine status query string
	for IP, _ := range serverList {
		s += networkQuery(s, IP)
	}
	return s
}

//This encapsulates s into tcp packets, establishes a tcp session w/ ip,
//transmits the packets and recieves and returns the response as a string
//TODO decide on exact return value
func networkQuery(s string, ip [4]int) string {

}

// //provides some basic error handling for file io
// //TODO make sure this actually fits within go's language ideals
// func check(e error) {
// 	if e != nil {
//     //log.Panicln("")
// 		log.Panicln(e)
// 	}
// }

func createFileHandle(path string) *os.File {
	f, err := os.Open("")
	if err != nil {
		log.Panicf("Failed opening file %s", path)
		log.Panicln(e)
	}
	return f
}

func closeFileHandle(f *os.File) {
	log.Printf("Closing file %s", f.Name())
	f.Close()
}

func configGen(address IP) {
	//rootPath := ""

}
