#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unitd.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

float TIMEPERIOD = 1.0;

class Decision{

};

class Quality{

};

class UserFeature{
	string User_ID;
	float Timestamp;
	string CDN;
	string Device;
	string Site;
};

class SystemEvent{
    float time;
    int event;
};

class Controller{
    Quality UpdateQuality(string User_ID, 
    	                  float Timestamp, 
    	                  UserFeature* Features,
    	                  Decision *Decision,
    	                  std::vector<Quality> QualityVector);
    void RequestDecision(string User_ID, float Timestamp,UserFeature* Features,
                         std::vector<Decision> Potential_Decision_Vector);
    void ReceiveDecision(string User_ID, float Timestamp, Decision *Decision);
    void Init();
    int ListenToUser(string User_ID);
};


class Pattern{
	std::vector<User> UserList;
	std::vector<UserFeature> RequestList;
	std::vector<SystemEvent> EventList;
	void GetUserRequests();
	void GetSystemEvents();
	void Init();
	bool GetUserByID(string User_ID, User *user);
};

class User{
	string User_ID;
	float Timestamp;
	float TimePeriod;
	Decision *Decision;
    void ConnectToController();
    void GetDecision();
};

class QualityEvaluator{
    Quality EvaluateQuality(string User_ID, float Timestamp,
    	                   std::vector<UserFeature> Client_Feature_Vector,
    	                   Decision *Decision);
};
class EmulationScheduler{

};

class EmulationPlatform{
	Controller *Controller;
	Pattern *Pattern;
	QualityEvaluator *Evaluator;
	EmulationScheduler *Scheduler;
};

