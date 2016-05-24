#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
class Desision{

};

class Quality{

};

class UserFeature{
	char *User_ID;
	float Timestamp;
	char *CDN;
	char *Device;
	char *Site;
};

class SystemEvent{
    float time;
    int event;
};

class Controller{
    Quality UpdateQuality(char *User_ID, 
    	                  float Timestamp, 
    	                  UserFeature* Features,
    	                  Decision *Decision,
    	                  std::vector<Quality*> QualityVector);
    void RequestDecision(char *User_ID, float Timestamp,UserFeature* Features,
                         std::vector<Decision*> Potential_Decision_Vector);
    void ReceiveDecision(char *User_ID, float Timestamp, Decision *Decision);
};


class Pattern{
	std::vector<UserFeature*> RequestList;
	std::vector<SystemEvent*> EventList;
	void GetUserRequests();
	void GetSystemEvents();
};

class User{
	char *User_ID;
	float Timestamp;
	float TimePeriod;
	Decision *Decision;
    void ConnectToController();
    void GetDecision();
};

class QualityEvaluator{
    Quality EvaluatQuality(char *User_ID, float Timestamp,
    	                   std::vector<UserFeature*> Client_Feature_Vector,
    	                   Decision *Decision);
};

class EmulationPlatform{
	Controller *Controller;
	Pattern *Pattern;
	QualityEvaluator *Evaluator;
};

