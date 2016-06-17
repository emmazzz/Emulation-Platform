#include "EmulationPlatform.h"

// void User::CompactInfo(char *buffer)
// {
//     snprintf(buffer, sizeof(buffer), "%s %f", User_ID, CurTime);

// };

bool User::ConnectToController(){
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

    std::size_t length = User_ID.copy(buffer,0,User_ID.length());
    buffer[length]='\0';
    // CompactInfo(buffer);

    n = write(socketfd, buffer, strlen(buffer));

    if (n < 0) return false;

    bzero(buffer,256);

    n = read(newsockfd,buffer,255);

    if (n < 0) return false;

    close(socketfd);
    return true;
}
    

int main(){


	// start listening to EmulationScheduler
	int socketfd, connfd, portno;
    socklen_t userlen;
    struct sockaddr_in user_addr, sched_addr;
    int n;

    char buffer[256];
    
    

	// TODO: how to get portno??
    int portno; 
    user_addr.sin_family = AF_INET;  
    user_addr.sin_addr.s_addr = INADDR_ANY;  
    user_addr.sin_port = htons(portno);

    // bind the socket to IP address on portno
    bind(socketfd, &user_addr,sizeof(user_addr));

    while(true){

    	// listen to scheduler

    	// create a socket
    	socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    	
    	listen(socketfd,MAX_QUEUE_SIZE);

    	schedlen = sizeof(sched_addr);

    	connfd = accept(socketfd, (struct sockaddr *) &sched_addr, &schedlen);

    	if (connfd < 0) 
        	error("acception error");

    	printf("User: connection from %s port %d\n",
          	inet_ntoa(sched_addr.sin_addr), ntohs(sched_addr.sin_port));
    	
    	n = read(connfd,buffer,255);
    	
    	if (n < 0) error("can't read from scheduler");

    	// connect to controller and update quality
		ConnectToController();


    	close(connfd);
    }
  
    
    close(sockfd);
    return 0; 
}

