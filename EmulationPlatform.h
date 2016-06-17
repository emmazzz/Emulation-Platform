#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <netdb.h>
#include <algorithm>

float TIMEPERIOD = 1.0;

class Decision{
public:

	int bitRate;
};

class Quality{
public:

	int quality;
};

class UserFeature{
public:
	std::string User_ID;
	float Timestamp;
	std::string CDN;
	std::string Device;
	std::string Site;
};

class SystemEvent{
public:

    float time;
    int event;
};

class Controller{
public:

    void UpdateQuality(std::string User_ID, 
    	                  float Timestamp, 
    	                  UserFeature* Features,
    	                  Decision *Decision,
    	                  std::vector<Quality> QualityVector);
   
    void ListenToUser();
};

class User{
public:
	std::string User_ID;
	std::vector<float> Timestamps;
	float CurTime;
	float TimePeriod;
	Decision *Decision;
	// void CompactInfo(char *buffer);
    bool ConnectToController();
};

class Pattern{
public:

	std::vector<User> UserList;
	std::vector<UserFeature> RequestList;
	std::vector<SystemEvent> EventList;
	void GetUserRequests();
	void GetSystemEvents();
	void Init();
	bool GetUserByID(std::string User_ID, User *user);
};



// class QualityEvaluator{
// public:

//     Quality EvaluateQuality(std::string User_ID, float Timestamp,
//     	                   std::vector<UserFeature> Client_Feature_Vector,
//     	                   Decision *Decision);
// };
// class EmulationScheduler{
// public:

// 	Controller *Controller;
// 	Pattern *Pattern;
// 	Decision *Default;
// 	void Init();
// 	void Routine();
// 	void RequestDecision(std::string User_ID, float Timestamp,UserFeature* Features,
//                          std::vector<Decision> Potential_Decision_Vector);
//     void ReceiveDecision(std::string User_ID, float Timestamp, Decision *Decision);
// };

// class EmulationPlatform{
// public:

// 	QualityEvaluator *Evaluator;
// 	EmulationScheduler *Scheduler;
// };

