#include "EmulationPlatform.h"

void EmulationScheduler::Init(char *t)
{
	pattern = new Pattern();
	pattern->InitPattern(t);
	Evaluator = new QualityEvaluator();

};
	
void EmulationScheduler::Routine(int portno, char *host)
{
	for (std::vector<User>::iterator user = 
    	pattern->UserList.begin();user != pattern->UserList.end();++user)
    {
    	for (std::vector<float>::iterator t = user->Timestamps.begin();
    		t != user->Timestamps.end();++t)
    	{
            user->CurTime = *t;
            printf("user is %s\n",user->User_ID.c_str() );
    		RequestDecision(&(*user), portno,host);
    	}
        
    }

};
	
void EmulationScheduler::RequestDecision(User *u, int portno, char *host)
{
	int socketfd, n,userlen;
    struct sockaddr_in user_addr;
    struct hostent *user;

    char *User_ID = (char *)u->User_ID.c_str();
    float Timestamp = u->CurTime;
    char *CDN = (char *)u->CDN.c_str();
    char buffer[256];
    char msg[256];
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

        printf("%s\n", User_ID);

    if (connect(socketfd, (struct sockaddr *) &user_addr, sizeof(user_addr)) < 0){
        perror("error connecting");
        exit(0);
        return;
    }

    printf("%s\n", "Connected!");

    int length = snprintf(buffer, sizeof(buffer), "%s %f %s", User_ID, Timestamp, CDN);
    buffer[length]='\0';
    printf("%d\n", length);

    // write to user

    n = write(socketfd, buffer, strlen(buffer));

    if (n < 0) {
        printf("cannot write\n");
    }

    printf("Message '%s' sent\n", buffer);

    bzero(buffer,256);

    // read decision from user
    n = read(socketfd,buffer,255);

    printf("Received : %s\n", buffer);

    n=sscanf(buffer, "%f %s",&Timestamp,CDN);


    UserFeature *decision = new UserFeature();
    decision->User_ID = User_ID;
    decision->Timestamp = Timestamp;
    decision->CDN = CDN;
    DecisionList.push_back(*decision);

    // evaluate quality
    Quality *quality = Evaluator->EvaluateQuality(decision);
    int q = quality->score;


    sprintf(msg, "Quality score for decision '%s %f %s': %d\n", User_ID, Timestamp, CDN,q);

    n = write(socketfd,msg,sizeof(msg)+1);

    printf("Message '%s' sent\n",msg );


    close(socketfd);
};
    
