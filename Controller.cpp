#include "EmulationPlatform.h"
#define MAX_QUEUE_SIZE 200

Quality Controller::UpdateQuality(char *User_ID, 
    	                  float Timestamp, 
    	                  UserFeature* Features,
    	                  Decision *Decision,
    	                  std::vector<Quality> QualityVector)
{

};
    
int Controller::ListenToUser(){

	// start listening to user
	int socketfd, connfd, portno;
    socklen_t userlen;
    struct sockaddr_in ctrl_addr, user_addr;
    int n;

    char buffer[256];
    
    

	// TODO: how to get portno??
    int portno; 
    ctrl_addr.sin_family = AF_INET;  
    ctrl_addr.sin_addr.s_addr = INADDR_ANY;  
    ctrl_addr.sin_port = htons(portno);

    // bind the socket to IP address on portno
    bind(socketfd, &ctrl_addr,sizeof(ctrl_addr));

    while(true){

    	// listen to user

    	// create a socket
    	socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    	
    	listen(socketfd,MAX_QUEUE_SIZE);

    	userlen = sizeof(user_addr);

    	connfd = accept(socketfd, (struct sockaddr *) &user_addr, &userlen);

    	// printf("Controller: connection from %s port %d\n",inet_ntoa(user_addr.sin_addr), ntohs(user_addr.sin_port));
    	if (connfd < 0) 
        	error("acception error");

    	printf("Controller: connection from %s port %d\n",
          	inet_ntoa(user_addr.sin_addr), ntohs(user_addr.sin_port));
    	
    	n = read(connfd,buffer,255);
    	
    	if (n < 0) error("can't read from user");

    	// TODO
    	info = ParseInfo(buffer);
    	
    	UpdateQuality();
    	
    	// clear buffer    	
    	bzero(buffer,256);

    	// TODO
    	// send dicision
    	send(connfd, decision);

    	close(connfd);
    }
  
    
    close(sockfd);
    return 0; 
};
