#include "EmulationPlatform.h"

void Pattern::GetUserRequests()
{	
	// TODO
	// parse user requests to RequestList from command line arguments?
	User *user1 = new User();
	this->UserList.push_back(*user1);
	// RequestList = {};
}
	
void Pattern::GetSystemEvents()
{
	// TODO
	// parse system events to SystemEvents from command line arguments?
	// EventList = {};
}

void Pattern::Init()
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
        	user->TimePeriod = TIMEPERIOD;
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

int main(){
	Pattern *p = new Pattern();
	p->Init();
	std::cout << "Hello" << "World!\n";
	return 0;
}














