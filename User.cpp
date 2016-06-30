#include "EmulationPlatform.h"

// void User::CompactInfo(char *buffer)
// {
//     snprintf(buffer, sizeof(buffer), "%s %f", User_ID, CurTime);

// };

bool User::ConnectToController(char *host, int portno, char *buffer){
	int socketfd, n,ctrllen;
    struct sockaddr_in ctrl_addr;
    struct hostent *controller;

    // char buffer[256];
    memset(&ctrl_addr,0,sizeof(ctrl_addr));
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) {
        perror("socket error");
        exit(0);
    }

    controller = gethostbyname(host);
    if (controller == NULL){
        perror("wrong host!");
        exit(0);
    }

    bzero((char *)&ctrl_addr, sizeof(ctrl_addr));

    ctrl_addr.sin_family = AF_INET;

    bcopy((char *)controller->h_addr, 
         (char *)&ctrl_addr.sin_addr.s_addr,
         controller->h_length);

    ctrl_addr.sin_port = htons(portno);


    if (connect(socketfd, (struct sockaddr *) &ctrl_addr, sizeof(ctrl_addr)) < 0){
        perror("error connecting");
        exit(0);
    }

    printf("%s\n", "Connected!");


    n = write(socketfd, buffer, strlen(buffer));

    if (n < 0) {
        printf("cannot write\n");
    }

    printf("Message '%s' sent\n", buffer);

    bzero(buffer,256);

    n = read(socketfd,buffer,255);


    printf("Received : %s\n", buffer);

    close(socketfd);
    return true;
}
    



