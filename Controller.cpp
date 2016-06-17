#include "EmulationPlatform.h"
#define MAX_QUEUE_SIZE 200

void Controller::UpdateQuality(std::string User_ID, 
    	                  float Timestamp, 
    	                  UserFeature* Features,
    	                  Decision *Decision,
    	                  std::vector<Quality> QualityVector)
{

}
    
void Controller::ListenToUser(){

	// start listening to user
	int socketfd, connfd, portno;
    socklen_t userlen;
    struct sockaddr_in ctrl_addr, user_addr;
    // char *decision;
    int n;

    char buffer[256];
    
    

	// TODO: how to get portno??
    portno = 80; 
    ctrl_addr.sin_family = AF_INET;  
    ctrl_addr.sin_addr.s_addr = INADDR_ANY;  
    ctrl_addr.sin_port = htons(portno);

    // bind the socket to IP address on portno
    socketfd =  socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr *)&ctrl_addr,sizeof(ctrl_addr));

    while(true){

    	// listen to user

    	// create a socket
    	
    	listen(socketfd,MAX_QUEUE_SIZE);

    	userlen = sizeof(user_addr);

    	connfd = accept(socketfd, (struct sockaddr *) &user_addr, &userlen);

    	// printf("Controller: connection from %s port %d\n",inet_ntoa(user_addr.sin_addr), ntohs(user_addr.sin_port));
    	if (connfd < 0){
        	printf("%s\n", "acception error");
            break;
        }
    	printf("Controller: connection from %s port %d\n",
          	inet_ntoa(user_addr.sin_addr), ntohs(user_addr.sin_port));
    	
    	n = read(connfd,buffer,255);
    	
    	if (n < 0) {
            close(connfd);

            printf("%s\n","can't read from user");
            break;
        }

    	// TODO
    	// info = ParseInfo(buffer);
    	
    	// UpdateQuality();
    	
    	// clear buffer    	
    	bzero(buffer,256);

    	// TODO
    	// send dicision
    	// send(connfd, (void *)decision, sizeof(decision),portno);

    	close(connfd);
    }
  
    
    close(socketfd);
    // return 0; 
}

int main(){
    Controller *c = new Controller();
    c->ListenToUser();
    return 0;
}
