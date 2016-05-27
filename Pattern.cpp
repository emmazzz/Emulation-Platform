#include "EmulationPlatform.h"

void Pattern::GetUserRequests()
{	
	// TODO
	// parse user requests to RequestList from command line arguments?
};
	
void Pattern::GetSystemEvents()
{
	// TODO
	// parse system events to SystemEvents from command line arguments?

};

void Pattern::Init()
{
	// get request and events first

	GetSystemEvents();
	GetUserRequests();

	// use request list to initilize all the users
    
    for (std::vector<UserFeature>::iterator feature = 
    	RequestList.begin();feature != RequestList.end();++feature)
    {
    	if (!GetUserByID(feature->User_ID)){
    		User *user = new User();
        	user->User_ID = feature->User_ID;
        	user->Timestamp = feature->Timestamp;
        	user->TimePeriod = TIMEPERIOD;
        	UserList.push_back(user);
    	} else{
    		// TODO
    		// update timestamp??
    	}
        
    }

};
	
bool Pattern::GetUserByID(string User_ID, User *user)
{
	// iterate through user list to find user

	for (std::vector<User>::iterator u = UserList.begin();
		u != UserList.end();++u;)
	{
		if (!User_ID.compare(u->User_ID)){
			*user = *u;
			return true;
		}
	}

	// didn't find it 

	return false;
};














