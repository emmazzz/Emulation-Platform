#include "EmulationPlatform.h"

void EmulationScheduler::Init()
{
	pattern = new Pattern();
	pattern->InitPattern();
};
	
void EmulationScheduler::Routine(int portno, char *host)
{
	for (std::vector<User>::iterator user = 
    	pattern->UserList.begin();user != pattern->UserList.end();++user)
    {
    	for (std::vector<float>::iterator t = user->Timestamps.begin();
    		t != user->Timestamps.end();++t)
    	{
    		RequestDecision(user->User_ID, user->CurTime, portno,host);

    	}
        
    }

};
	
void EmulationScheduler::RequestDecision(std::string User_ID, float Timestamp, int portno, char *host)
{
	int socketfd, n,userlen;
    struct sockaddr_in user_addr;
    struct hostent *user;

    char buffer[256];
    memset(&user_addr,0,sizeof(user_addr));
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) {
        perror("socket error");
        exit(0);
    }

    user = gethostbyname(host);
    if (user == NULL){
        perror("wrong host!");
        exit(0);
    }

    bzero((char *)&user_addr, sizeof(user_addr));

    user_addr.sin_family = AF_INET;

    bcopy((char *)user->h_addr, 
         (char *)&user_addr.sin_addr.s_addr,
         user->h_length);

    user_addr.sin_port = htons(portno);

        printf("%s\n", User_ID.c_str());

    if (connect(socketfd, (struct sockaddr *) &user_addr, sizeof(user_addr)) < 0){
        perror("error connecting");
        exit(0);
        return;
    }

    printf("%s\n", "Connected!");

    // std::size_t length = User_ID.copy(buffer,0,User_ID.length());
    int length = snprintf(buffer, sizeof(buffer), "%s %f", User_ID.c_str(), Timestamp);
    buffer[length]='\0';
    printf("%d\n", length);
    // CompactInfo(buffer);

    n = write(socketfd, buffer, strlen(buffer));

    if (n < 0) {
        printf("cannot write\n");
        // return false;
    }

    printf("Message '%s' sent\n", buffer);

    bzero(buffer,256);

    n = read(socketfd,buffer,255);

    // if (n < 0) return false;

    printf("Received : %s\n", buffer);

    close(socketfd);
};
    
