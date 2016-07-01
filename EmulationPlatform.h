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

// float TIMEPERIOD = 1.0;

class Decision{
public:

	char *CDN;
	int bitRate;
	float Timestamp;
};

class Quality{
public:

	int score;
};

class UserFeature{
public:
	std::string User_ID;
	std::string CDN;
	std::string Device;
	std::string Site;
	float Timestamp;
	int bitRate;
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
   
    void ListenToUser(int portno);
};

class User{
public:
	std::string User_ID;
	std::string CDN;
	std::vector<float> Timestamps;
	float CurTime;
	float TimePeriod;
	Decision *Decision;
    bool ConnectToController(char *host, int portno, char *buffer);
};

class Pattern{
public:

	std::vector<User> UserList;
	std::vector<UserFeature> RequestList;
	std::vector<SystemEvent> EventList;
	void GetUserRequests(char *t);
	void GetSystemEvents();
	void InitPattern(char *t);
	bool GetUserByID(std::string User_ID, float t);
};



class QualityEvaluator{
public:

    Quality *EvaluateQuality(UserFeature *Decision);
};

class EmulationScheduler{
public:
	Controller *controller;
	Pattern *pattern;
	Decision *Default;
	std::vector<UserFeature> DecisionList;
	QualityEvaluator *Evaluator;
	void Init(char *t);
	void Routine(int portno, char *host);
	void RequestDecision(User *user,int portno, char *host);
};

class EmulationPlatform{
public:

	
};

