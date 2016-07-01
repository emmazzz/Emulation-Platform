#include "EmulationPlatform.h"

void Pattern::GetUserRequests(char *t)
{	
	// parse user requests to RequestList from command line arguments?
	// UserFeature *r1 = new UserFeature();
	// r1->User_ID = "Emma";
	// r1->Timestamp = 0;
	// r1->CDN = "Akamai";
	// this->RequestList.push_back(*r1);

	float timestamp;

	FILE *trace = fopen(t,"r");
	printf("hey\n");
	if (trace == NULL) {
		fprintf(stderr,"wrong file!\n");
		exit(0);
	}
    char *ID = (char *)malloc(sizeof(char));
    char *CDN = (char *)malloc(sizeof(char));

	while (fscanf(trace, " %s %f %s", ID,&timestamp, CDN) > 0){
		UserFeature *r1 = new UserFeature();
		printf("Feature: %s %f %s\n",ID, timestamp,CDN);
		r1->User_ID = ID;
		r1->Timestamp = timestamp;
		r1->CDN = CDN;
		this->RequestList.push_back(*r1);
	}

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
    // printf("yay\n");
    for (std::vector<UserFeature>::iterator feature = 
    	RequestList.begin();feature != RequestList.end();++feature)
    {
    	User *user = new User();
    	if (!GetUserByID(feature->User_ID,feature->Timestamp)){
        	user->User_ID = feature->User_ID;
        	// printf("Feature time %f\n",(feature->Timestamp) );
        	user->Timestamps.push_back(feature->Timestamp);
        	user->TimePeriod = 0.1;
        	user->CDN = feature->CDN;
        	UserList.push_back(*user);
    	} 
        
    }

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















