#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define PORT 4242
#define ADDRESS "localhost"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int socket_send(char buffer[]) {
    
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(ADDRESS);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(PORT);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    bzero(buffer,256);
    
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    close(sockfd);
    return 0;
    
}

int socket_send_js(int axis[], char buttons[])
{

    char buffer[256];
    
    for(int i = 0; i < 4; i++) {
        
        buffer[i] = axis[i];
        
    }
    
    for(int i = 0; i < 9; i++) {
        
        buffer[i+4] = buttons[i];
        
    }
    
    return socket_send(buffer);

}