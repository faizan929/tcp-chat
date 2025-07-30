#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9002

int main(){
    int socket_fd; // fd : file description
    struct sockaddr_in server_addr;

    // CREATE THE SOCKET 

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);

    }

    // CLEAR THE MEMORY
    memset(&server_addr, 0, sizeof(server_addr));

    // DEFINE SERVER ADDRESS AND CONNECT TO IT
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);


    // CONNECT TO SERVER 
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 ) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");
    

  
    while(1) {
        char buffer[1024];
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);

        //EXIT CONDITION
        if(strncmp(buffer, "exit", 4) == 0){
            break;
        }

        send(socket_fd, buffer, strlen(buffer), 0);

    }


    close(socket_fd);

} 