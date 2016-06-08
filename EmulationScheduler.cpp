#include "EmulationPlatform.h"

void Init()
{
	Pattern->init();
};
	
void Routine()
{
	for (std::vector<User>::iterator user = 
    	Pattern->UserList.begin();feature != Pattern->UserList.end();++user)
    {
    	for (std::vector<float> t = user->Timestamps.begin();
    		t != user->Timestamps.end();++t)
    	{
    		user->CurTime = t;
    		user->ConnectToController();
    	}
        
    }

};
	
void RequestDecision(string User_ID, float Timestamp,UserFeature* Features,
                         std::vector<Decision> Potential_Decision_Vector)
{

};
    
void ReceiveDecision(string User_ID, float Timestamp, Decision *Decision)
{
	
};
