#include "EmulationPlatform.h"

void EmulationScheduler::Init()
{
	pattern = new Pattern();
	pattern->Init();
};
	
void EmulationScheduler::Routine()
{
	for (std::vector<User>::iterator user = 
    	pattern->UserList.begin();user != pattern->UserList.end();++user)
    {
    	for (std::vector<float>::iterator t = user->Timestamps.begin();
    		t != user->Timestamps.end();++t)
    	{
    		user->CurTime = *t;
    		user->ConnectToController();
    	}
        
    }

};
	
// void RequestDecision(std::string User_ID, float Timestamp,UserFeature* Features,
//                          std::vector<Decision> Potential_Decision_Vector)
// {

// };
    
// void ReceiveDecision(std::string User_ID, float Timestamp, Decision *Decision)
// {
	
// };
