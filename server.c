#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

void error(char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    bzero(buffer, 256);

    char *letter;
    int i=0;

// recieve one by one letter

    while (1) {
    n = read(newsockfd, letter, 1);
        if (n < 0) {
            error("ERROR reading from socket");
        }
    buffer[i] = *letter;
        if (*letter == '\n'){
            break;
        }
    i++;
    printf("Letter: %c \n", *letter);
    printf("Current name: %s \n", buffer);


    }

    printf("Here is the message: %s\n", buffer);

// .................


    //n = write(newsockfd, "I got your message", 18);
    char buffer2 [256] = "dhqhj";
    n = write(newsockfd,buffer2 , 18);

    if (n < 0) {
        error("ERROR writing to socket");
    }

    bzero(buffer, 256);
    while (1) {
        n = read(newsockfd, letter, 1);
        if (n < 0) {
            error("ERROR reading from socket");
        }
        buffer[i] = *letter;
        if (*letter == '\n'){
            break;
        }
        i++;
        printf("Letter: %c \n", *letter);
    }
    return 0;
}