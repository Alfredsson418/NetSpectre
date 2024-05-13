/*
SOCK_STREAM to create a TCP socket instead.

After creating the socket, you need to set up a sockaddr_in structure for the target address.
This structure should have its sin_family field set to AF_INET, 
its sin_port field set to the port number you want to scan (converted to network byte order), 
and its sin_addr field set to the IP address of the target (converted to a struct in_addr).

Once the target address is set up, you can attempt to connect to it using the connect function. 
This function takes in the socket, a pointer to the target address, and the size of the address. 
If the connection is successful, the port is open. If not, the port is closed.

Don't forget to close the socket after you're done with it using the close function.

You'll want to repeat this process for each port you want to scan. This can be done in a loop, 
where the loop variable is the port number.
*/

#include "../../include/scan/tcp_scan.h"

void tcp_scan(char ip[IPV4_ADDR_STR_LEN], int port) {

    int sock = socket(AF_INET, SOCK_STREAM, 0);


    if (sock < 0) {
        ERR_PRINT("ERROR creating TCP socket!", NULL);
        return;
    }

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
        ERR_PRINT("Invalid address/ Address not supported \n", NULL);
        return;
    }

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        PRINT("PORT %d IS NOT OPEN\n", port);
    } else {
        PRINT("CONNECTED ON ADDR %s ON PORT %d\n", ip, port);
    }

    close(sock);

}