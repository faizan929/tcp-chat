#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // close()
#include <sys/socket.h> // socket(), bind(), listen(), accept() 
#include <netinet/in.h>  // sockaddr_in, htons

#define PORT 9002

int main(){
    // CREATE A SERVER FILE DESCRIPTOR
    int server_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1){ 
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // CLEAR THE MEMORY
    memset(&server_addr, 0, sizeof(server_addr));

    // SET UP THE SERVER ADDRESS
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // BIND THE SOCKET TO THIS ADDRESS
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind Failed");
        exit(EXIT_FAILURE);

    }
                                         
    // LISTEN
    if (listen(server_fd, 5) < 0){
        perror("Listen Failed");
        exit(EXIT_FAILURE);

    }

    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    //CLIENT FILE DESCRIPTOR
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("Accept Failed");
        exit(EXIT_FAILURE);

    }

    printf("Client connected\n");


    char buffer[1024] = {0};
    while(1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exited\n");
            break;
        }
        printf("Client says:\n%s", buffer);

        printf("Server reply:\n");
        fgets(buffer, sizeof(buffer), stdin);
        //SEND NOW TO CLIENT FILE DESCRIPTOR
        send(client_fd, buffer, strlen(buffer), 0); 
        
        if (strncmp(buffer, "exit", 4) == 0){
            printf("Server is exiting...");
            break;
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

