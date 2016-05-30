#include "EmulationPlatform.h"

void User::ConnectToController(){
	int socketfd, portno, n;
    struct socketaddr_in ctrl_addr;
    struct hostent *controller;
    // TODO
    // how to get host and portno??
    char *host;

    char buffer[256];
   
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) error("socket error");
    controller = gethostbyname(host);

    ctrl_addr.sin_family = AF_INET;

    bcopy((char *)controller->h_addr, 
         (char *)&ctrl_addr.sin_addr.s_addr,
         controller->h_length);

    ctrl_addr.sin_port = htons(portno);
    connect(socketfd, (struct sockaddr *) &ctrl_addr, sizeof(ctrl_addr)); 
    fgets(buffer,255,stdin);
    n = write(socketfd, buffer, strlen(buffer));

    if (n < 0) error("writing error");

    bzero(buffer,256);

    // TODO
    GetDecision();

    close(socketfd);
    return 0;
};
    
void User::GetDecision(){

};

void User::Routine(){

	while(true){
		// TODO
		// listen to EmulationPlatform


		// connect to controller and update quality
		ConnectToController();

	}
}

