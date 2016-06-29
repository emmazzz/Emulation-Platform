#include "EmulationPlatform.h"

void Pattern::GetUserRequests()
{	
	// TODO
	// parse user requests to RequestList from command line arguments?
	UserFeature *r1 = new UserFeature();
	UserFeature *r2 = new UserFeature();
	r1->User_ID = "Emma";
	r1->Timestamp = 0.7;
	r2->User_ID = "Emma";
	r2->Timestamp = 1.3;
	this->RequestList.push_back(*r1);
	this->RequestList.push_back(*r2);
	printf("User requests received\n");
	// RequestList = {};
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
        	UserList.push_back(*user);
    	} else{
    		// TODO
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















