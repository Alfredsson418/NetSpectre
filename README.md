# NetSpectre
NetSpectre is a swiss army knife of network tools

## Tools
* [`Capture`](CAPTURE.md) - Capture and show incomming/outgoing traffic to terminal and/or pcap files

## How to compile
1. Download necessary libraries
2. Run `make` in the project root folder
3. Done!

## Libraries used
* libpcap
* argp

## Future ideas
* Network discovery tool that can find devices on the network based on IP and subnet, the user can also give a range of IP addresses to search.
* Port scanner
* Compare lists of known dangerous IPs and Domains and warn when capturing
* Send information to an server that can show saved scans and captures. 
* Save captured traffic to a pcap file
* Generate traffic (random data) to a specific IP/Domain
