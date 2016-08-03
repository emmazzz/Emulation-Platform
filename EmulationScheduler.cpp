#include "EmulationPlatform.h"
using namespace std; 

void EmulationScheduler::Init(char *t)
{
	pattern = new Pattern();
    trace = fopen(t,"r");
	// pattern->InitPattern(t);
	Evaluator = new QualityEvaluator();

};
	
void EmulationScheduler::Routine(int portno, char *host)
{
	// for (std::vector<User>::iterator user = 
 //    	pattern->UserList.begin();user != pattern->UserList.end();++user)
 //    {
 //    	for (std::vector<float>::iterator t = user->Timestamps.begin();
 //    		t != user->Timestamps.end();++t)
 //    	{
 //            user->CurTime = *t;
 //            // printf("user is %s\n",user->User_ID.c_str() );
 //    		RequestDecision(&(*user), portno,host);
 //    	}
        

 //    }
    int num = 0;


    char *feature1 = (char *)malloc(sizeof(char));
    char *feature2 = (char *)malloc(sizeof(char));
    char *feature3 = (char *)malloc(sizeof(char));
    char *decisionAndQuality = (char *)malloc(sizeof(char));
    char buffer[1000];
    char line [1000];
    char *b = (char *)malloc(sizeof(char));
    char *decision = (char *)malloc(sizeof(char));
    float quality;
    while(fgets(line,sizeof line,trace)!= NULL){
      num ++;

      sscanf(line,"%s %s %s",feature1,feature2,feature3);

      snprintf(buffer, sizeof(buffer),"%s %s %s", feature1,feature2,feature3);

      string buffers = buffer;
      buffers.append(" | ");
      decisionAndQuality = strstr(line,"|")+2;

      printf("Features are: %s %s %s\n", feature1,feature2,feature3);
      printf("Decisions are : %s\n", decisionAndQuality);
      
      std::string dqstring = decisionAndQuality;
      std::stringstream ss(dqstring);

      std::string dqpair;

      string d;
      string q;
      float quality;
      std::vector<Decision> DecisionList;
      while(getline(ss,dqpair,'\t')){
        if (strlen(dqpair.c_str()) < 3) continue;
        printf("dqpair %s len %lu \n",(char *)dqpair.c_str(),strlen(dqpair.c_str()));
        stringstream dqss(dqpair);
        getline(dqss,d,',');
        getline(dqss,q,',');
        buffers.append(d);
        buffers.append("\t");
        char *decision = (char *)d.c_str();
        sscanf((char *)q.c_str(),"%f",&quality);
        printf("decision %s\n",decision);
        printf("quality %f\n", quality);

        Decision *dec = new Decision();
        dec->quality = quality;
        dec->decision = decision;
        DecisionList.push_back(*dec);


      }
      b = (char *)buffers.c_str();
      printf("%s\n", b);
      printf("host is %s\n",host );
      RequestDecision(b, portno,host);

      printf("ENDLOOP\n\n\n\n\n\n");

      bzero(b,1000);

      // while (strlen(decisionAndQuality) > 0){
      //   // decisionAndQuality += n;
      //   // printf("%s\n",decisionAndQuality);
      //   b = strstr(decisionAndQuality,",")+1;

      //   // printf("decisionAndQuality+b: %s\n",b);
      //   sscanf(b,"%f",&quality);
      //   b -= 1;
      //   *b = '\0';
      //   char *buf = (char *)malloc(sizeof(char));
        
      //   int index = (unsigned long)b - (unsigned long)decisionAndQuality;

      //   std::string copy = decisionAndQuality;
      //   std::string a = decisionAndQuality;
      //   std::size_t index1 = copy.find(",");
      //   std::string decisionstring = a.substr(0,index1);
      //   decision = (char *)decisionstring.c_str();
      //   // std::size_t rest = copy.find(" ");

      //   int n = sprintf(buf,"%s,%f",decision,quality)-5;
      //   // decisionAndQuality = (char *)copy.substr(rest).c_str();

      //   decisionAndQuality += n;
      //   printf("dq %s\n", decisionAndQuality);
      //   printf("length of string %lu\n",strlen(decisionAndQuality));
      //   printf("decision is : %s and quality is %f \n\n\n\n",decision,quality );

      //   // 
      //   bzero(feature1,256);
      //   bzero(feature2,256);
      //   bzero(feature3,256);
      //   // bzero(decisionAndQuality,256);
      //   bzero(decision,256);
      // }
    }
    

};
	
void EmulationScheduler::RequestDecision(char *buffer, int portno, char *host)
{
	int socketfd, n,userlen;
    struct sockaddr_in user_addr;
    struct hostent *user;

    // char *User_ID = (char *)u->User_ID.c_str();
    // float Timestamp = u->CurTime;
    // char *CDN = (char *)u->CDN.c_str();
    // char buffer[256];
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

        // printf("%s\n", User_ID);

    if (connect(socketfd, (struct sockaddr *) &user_addr, sizeof(user_addr)) < 0){
        perror("error connecting");
        exit(0);
        return;
    }

    printf("%s\n", "Connected!");
    // bzero(buffer,256);
    // int length = snprintf(buffer, sizeof(buffer), "%s %f %s", User_ID, Timestamp, CDN);
    // buffer[length]='\0';

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

    // n=sscanf(buffer, "%f %s",&Timestamp,CDN);

    
    UserFeature *decision = new UserFeature();
    // decision->User_ID = User_ID;
    // decision->Timestamp = Timestamp;
    // decision->CDN = CDN;
    // DecisionList.push_back(*decision);

    // evaluate quality
    Quality *quality = Evaluator->EvaluateQuality(decision);
    int q = quality->score;


    sprintf(msg, "Quality score for decision \n");

    n = write(socketfd,msg,sizeof(msg)+1);

    printf("Message '%s' sent\n",msg );


    close(socketfd);
};
    
