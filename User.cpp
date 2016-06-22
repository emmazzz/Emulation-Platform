#include "EmulationPlatform.h"

// void User::CompactInfo(char *buffer)
// {
//     snprintf(buffer, sizeof(buffer), "%s %f", User_ID, CurTime);

// };

bool User::ConnectToController(){
	int socketfd, portno, n,ctrllen;
    struct sockaddr_in ctrl_addr;
    struct hostent *controller;
    // TODO
    // how to get host and portno??
    portno = 80;
    char *host = "localhost";

    char buffer[256];
    memset(&ctrl_addr,0,sizeof(ctrl_addr));
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // if (socketfd < 0) error("socket error");
    controller = gethostbyname(host);

    ctrl_addr.sin_family = AF_INET;

    bcopy((char *)controller->h_addr, 
         (char *)&ctrl_addr.sin_addr.s_addr,
         controller->h_length);

    ctrl_addr.sin_port = htons(portno);
    connect(socketfd, (struct sockaddr *) &ctrl_addr, sizeof(ctrl_addr)); 
    printf("%s\n", "connected");
    std::size_t length = User_ID.copy(buffer,0,User_ID.length());
    buffer[length]='\0';
    // CompactInfo(buffer);

    n = write(socketfd, buffer, strlen(buffer));

    if (n < 0) {
        printf("cannot write\n");
        // return false;
    }

    bzero(buffer,256);

    n = read(socketfd,buffer,255);

    // if (n < 0) return false;

    printf("received : %s\n", buffer);

    close(socketfd);
    return true;
}
    



