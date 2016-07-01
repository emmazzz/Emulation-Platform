#include "EmulationPlatform.h"
#define MAX_QUEUE_SIZE 200

// void Controller::UpdateQuality(std::string User_ID, 
//     	                  float Timestamp, 
//     	                  UserFeature* Features,
//     	                  Decision *Decision,
//     	                  std::vector<Quality> QualityVector)
// {

// }
    
void Controller::ListenToUser(int portno){

	// start listening to user
	int socketfd, connfd;
    socklen_t userlen;
    struct sockaddr_in ctrl_addr, user_addr;
    int n;

    char buffer[256];
    
    socketfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0){
        perror("socket error");
        exit(0);
    }

    memset(&ctrl_addr, 0, sizeof(struct sockaddr_in));

    ctrl_addr.sin_family = AF_INET;  
    ctrl_addr.sin_addr.s_addr = INADDR_ANY;  
    ctrl_addr.sin_port = htons(portno);

    // bind the socket to IP address on portno

    if (bind(socketfd, (struct sockaddr *)&ctrl_addr,sizeof(ctrl_addr)) < 0){
        perror("error binding");
        exit(0);
    }
    printf("%d\n", socketfd);
    while(true){

    	// listen to user
    	
    	listen(socketfd,MAX_QUEUE_SIZE);

    	userlen = sizeof(user_addr);

    	connfd = accept(socketfd, (struct sockaddr *) &user_addr, &userlen);

    	if (connfd < 0){
        	perror("acception error");
            exit(0);
        }
    	printf("Controller: connection from %s port %d\n",
          	inet_ntoa(user_addr.sin_addr), ntohs(user_addr.sin_port));
    	
        char msg[256];
    	n = read(connfd,msg,255);
    	
    	if (n < 0) {
            close(connfd);

            printf("%s\n","can't read from user");
            break;
        }
        msg[n] = 0;
        const char *q = "Quality";
        if (strncmp(q, msg, strlen(q)) == 0){
            bzero(buffer,256);
            bzero(msg,256);
            write(connfd,"Quality score received!\n",255);
            close(connfd);
            continue;
        }
        printf("Controller received: %s\n", msg);
    	bzero(buffer,256);
    	// UpdateQuality();
    	sprintf(buffer, "Decision CDN: %s", msg);

    	
    	// send dicision
        write(connfd,buffer,256);

        // clear buffer     
        bzero(buffer,256);
        bzero(msg,256);
     	close(connfd);
    }
  
    
    close(socketfd);
}

int main(int argc, char *argv[]){
    Controller *c = new Controller();
    int portno = atoi(argv[1]);
    c->ListenToUser(portno);
    return 0;
}
