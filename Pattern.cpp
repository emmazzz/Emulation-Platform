#include "EmulationPlatform.h"

void Pattern::GetUserRequests(char *t)
{	
	// parse user requests to RequestList from command line arguments?
	
	float timestamp;

	FILE *trace = fopen(t,"r");
	// printf("hey\n");
	if (trace == NULL) {
		fprintf(stderr,"wrong file!\n");
		exit(0);
	}

	char *feature1 = (char *)malloc(sizeof(char));
	char *feature2 = (char *)malloc(sizeof(char));
	char *feature3 = (char *)malloc(sizeof(char));
	char *decisionAndQuality = (char *)malloc(sizeof(char));
 //    char *ID = (char *)malloc(sizeof(char));
 //    char *CDN = (char *)malloc(sizeof(char));

	// while (fscanf(trace, " %s %f %s", ID,&timestamp, CDN) > 0){
	// 	UserFeature *r1 = new UserFeature();
	// 	// printf("Feature: %s %f %s\n",ID, timestamp,CDN);
	// 	r1->User_ID = ID;
	// 	r1->Timestamp = timestamp;
	// 	r1->CDN = CDN;
	// 	this->RequestList.push_back(*r1);
	// }
	char buffer[256];
	char line [1000];
	char *b = (char *)malloc(sizeof(char));
	char *decision = (char *)malloc(sizeof(char));
	float quality;
    while(fgets(line,sizeof line,trace)!= NULL){

      sscanf(line,"%s %s %s",feature1,feature2,feature3);

      snprintf(buffer, sizeof(buffer),"Features are: %s %s %s\n", feature1,feature2,feature3);

      decisionAndQuality = strstr(line,"|")+1;

      printf("Features are: %s %s %s\n", feature1,feature2,feature3);
	  printf("Decisions are : %s\n", decisionAndQuality);

	  while (sscanf(decisionAndQuality,"%s",decision) > 0){
	  	// decisionAndQuality += n;
	  	b = strstr(decision,",")+1;

	  	printf("decisionAndQuality+b: %s\n",b);
	  	sscanf(b,"%f",&quality);
	  	b -= 1;
	  	*b = '\0';
	    int n = sprintf(b,"%s,%f",decision,quality);

	  	decisionAndQuality += n;
	  	// printf("%s\n", decisionAndQuality);
	  	printf("decision is : %s and quality is %f \n",decision,quality );
	  }
    }

	// while (fscanf(trace,"%s %s %s | %s", feature1,feature2,feature3,decisionAndQuality) > 0){
		
	// }
	// free(feature1);
	// free(feature2);
	// free(feature3);
	// free(decisionAndQuality);
	fclose(trace);
	printf("User requests received\n");
}
	
void Pattern::GetSystemEvents()
{
	// TODO
	// parse system events to SystemEvents from command line arguments?
	// EventList = {};
}

void Pattern::InitPattern(char *t)
{
	// get request and events first

	GetSystemEvents();
	GetUserRequests(t);

	// use request list to initilize all the users
 //    printf("yay\n");
 //    for (std::vector<UserFeature>::iterator feature = 
 //    	RequestList.begin();feature != RequestList.end();++feature)
 //    {
 //    	User *user = new User();
 //    	if (!GetUserByID(feature->User_ID,feature->Timestamp)){
 //        	user->User_ID = feature->User_ID;
 //        	// printf("Feature time %f\n",(feature->Timestamp) );
 //        	user->Timestamps.push_back(feature->Timestamp);
 //        	user->TimePeriod = 0.1;
 //        	user->CDN = feature->CDN;
 //        	UserList.push_back(*user);
 //    	} 
        
 //    }

}
	
bool Pattern::GetUserByID(std::string User_ID, float t)
{
	// iterate through user list to find user

	for (std::vector<User>::iterator u = UserList.begin();
		u != UserList.end();++u)
	{
		if (!User_ID.compare(u->User_ID)){
			// *user = *u;
			u->Timestamps.push_back(t);
			return true;
		}
	}

	// didn't find it 

	return false;
}















