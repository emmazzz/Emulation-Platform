#include "EmulationPlatform.h"

int main(){


	// start listening to EmulationScheduler
    User *u = new User();
	int socketfd, connfd, portno;
    struct sockaddr_in user_addr, sched_addr;
    int n;

    char buffer[256];

    int MAX_QUEUE_SIZE = 5;
    
    

	// TODO: how to get portno??
    portno = 80; 
    user_addr.sin_family = AF_INET;  
    user_addr.sin_addr.s_addr = INADDR_ANY;  
    user_addr.sin_port = htons(portno);

    // bind the socket to IP address on portno
    bind(socketfd, (struct sockaddr *)&user_addr,sizeof(user_addr));

    printf("%d\n", socketfd);
    
    // u->ConnectToController();


    while(true){

    	// listen to scheduler
    	// create a socket
    	socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    	
    	listen(socketfd,MAX_QUEUE_SIZE);

    	socklen_t schedlen = sizeof(sched_addr);

    	connfd = accept(socketfd, (struct sockaddr *) &sched_addr, &schedlen);
    	if (connfd < 0){
        	printf("%s\n","acception error");
            return 1;
        }

    	printf("User: connection from %s port %d\n",
          	inet_ntoa(sched_addr.sin_addr), ntohs(sched_addr.sin_port));
    	
    	n = read(connfd,buffer,255);
    	
    	if (n < 0) {
            printf("%s\n","can't read from scheduler");
            return 1;
        }

    	// connect to controller and update quality
		// u->ConnectToController();


    	close(connfd);
    }
  
    
    close(socketfd);
    return 0; 
}