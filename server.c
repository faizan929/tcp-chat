#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for close()
#include <sys/socket.h> // for socket, bind, list 
#include <netinet/in.h>  // for sockaddr_in, htons

#define PORT 9002

int main(){
    int server_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1){ 
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // clear the server memory and set the server_addr = 0
    memset(&server_addr, 0, sizeof(server_addr));

    // set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to this address

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind Failed");
        exit(EXIT_FAILURE);

    }
                                         
 

    if(listen(server_fd, 5) < 0){
        perror("Listen Failed");
        exit(EXIT_FAILURE);

    }

    printf("Server is listening on port %d...\n", PORT);

    return 0;
}