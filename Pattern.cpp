#include "EmulationPlatform.h"

void Pattern::GetUserRequests()
{	
	// TODO
	// parse user requests to RequestList from command line arguments?
	UserFeature *r1 = new UserFeature();
	r1->User_ID = "Emma";
	r1->Timestamp = 0;
	r1->CDN = "Akamai";
	this->RequestList.push_back(*r1);
	printf("User requests received\n");
}
	
void Pattern::GetSystemEvents()
{
	// TODO
	// parse system events to SystemEvents from command line arguments?
	// EventList = {};
}

void Pattern::InitPattern()
{
	// get request and events first

	GetSystemEvents();
	GetUserRequests();

	// use request list to initilize all the users
    
    for (std::vector<UserFeature>::iterator feature = 
    	RequestList.begin();feature != RequestList.end();++feature)
    {
    	User *user = new User();
    	if (!GetUserByID(feature->User_ID,user)){
        	user->User_ID = feature->User_ID;
        	user->Timestamps.push_back(feature->Timestamp);
        	user->TimePeriod = 0.1;
        	user->CDN = feature->CDN;
        	UserList.push_back(*user);
    	} else{
    		user->Timestamps.push_back(feature->Timestamp);
    	}
        
    }

}
	
bool Pattern::GetUserByID(std::string User_ID, User *user)
{
	// iterate through user list to find user

	for (std::vector<User>::iterator u = UserList.begin();
		u != UserList.end();++u)
	{
		if (!User_ID.compare(u->User_ID)){
			*user = *u;
			return true;
		}
	}

	// didn't find it 

	return false;
}















