package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"path"
	"strconv"
	"time"
)

// func temp(){
// test := net.IPv4(3,5,7,8)
// }
//[key is string representation of ip address x.x.x.x]
//value is string representing name/location of device
var serverList = make(map[string]string)

var clientList = make(map[string]string)

const port int = 80 //TODO decide on custom port or make part of config
func main() {
	fmt.Printf("hello, world\n")

	//On load:
	//need to query database to update serverList and clientList
	//Send status command to all clients and servers and display them
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
		s += networkQuery(s, net.ParseIP(IP))
	}
	return s
}

//This encapsulates s into tcp packets, establishes a tcp session w/ ip,
//transmits the packets and recieves and returns the response as a string
//TODO decide on exact return value
func networkQuery(s string, ip net.IP) string {
	var response string = ""

	return response
}

func receiveFromClient(port int) {
	incoming, err := net.Listen("tcp", ":"+strconv.Itoa(port))
	if err != nil {
		// handle error
		log.Println(err)
	}
	for {
		conn, err := incoming.Accept()
		if err != nil {
			// handle error
		}
		//go handleConnection(conn)
	}
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
		log.Panicln(err)
	}
	return f
}

func closeFileHandle(f *os.File) {
	log.Printf("Closing file %s", f.Name())
	f.Close()
}

//have meta list of all query strings
//take config options passed in and generate source file
//return fullPath which is the path to the generated source file
func clientSourceGen(selfIP net.IP, rootPath string, deviceType string, queryStrings []string, IPAddresses []net.IP, C2_IP net.IP, C2_query net.IP, MAC net.HardwareAddr, port int, DNS net.IP, gateway net.IP, subnet net.IP) string {
	fullPath := path.Join(rootPath, serverList[net.IP.String(selfIP)], time.Now().Format(time.RFC822))
	inFile := createFileHandle(fullPath)
	defer closeFileHandle(inFile)
	outFile := createFileHandle(fullPath)
	defer closeFileHandle(outFile)
	switch deviceType {
	case "LED client":
		//needs array of 10 server ip addresses, array of 10 query strings,
		//C2 server ip, C2 server query, MAC, self IP,
		//port, dns, gateway, subnet,

	case "Other client":

		//needs array of n server ip addresses, array of n query strings,
		//C2 server ip, C2 server query, MAC, self IP,
		//port, dns, gateway, subnet,
	}
	return fullPath
}

//serverSourceGen takes config options passed in and generate source file.
//It returns fullPath which is the path to the generated source file
func serverSourceGen(selfIP net.IP, rootPath string, deviceType string, queryStrings []string, C2_IP net.IP, C2_query net.IP, MAC net.HardwareAddr, port int, DNS net.IP, gateway net.IP, subnet net.IP) string {
	fullPath := path.Join(rootPath, serverList[net.IP.String(selfIP)], time.Now().Format(time.RFC822))
	inFile := createFileHandle(fullPath)
	defer closeFileHandle(inFile)
	outFile := createFileHandle(fullPath)
	defer closeFileHandle(outFile)
	switch deviceType {
	//case "Other server":
	//needs array of query strings to respond to,
	//For other server, query string will be of aproximate form "'Port'-{ON:OFF}"
	//C2 server ip, C2 server query, MAC, self IP,
	//port, dns, gateway, subnet,

	case "Relay server":

		//needs array of query strings to respond to,
		//For relay server, query string will be of aproximate form "'Port'-{ON:OFF}"
		//C2 server ip, C2 server query, MAC, self IP,
		//port, dns, gateway, subnet,

	default:

	}
	return fullPath
}
