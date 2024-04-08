# NetSpectre
NetSpectre is a networking tool that can (for now) capture traffic on the given device.

## How to compile
1. Download necessary libraries
2. Run `make` in the project root folder
3. Done!

## Libraries used
* libpcap

## Future ideas
* Add a format option for packet capture so the user can choose what information shows and in what way.
* Network discovery tool that can find devices on the network based on IP and subnet, the user can also give a range of IP addresses to search.
* Port scanner
* Compare lists of known dangerous IPs and Domains and warn when capturing
* Send information to an server that can show saved scans and captures. 
* Save captured traffic to a pcap file
* Generate traffic (random data) to a specific IP/Domain
