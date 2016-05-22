#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

class Controller{

};

class UserRequest{
	char *user;
	float time;
	char *CDN;
	char *device;
	char *site;
};

class SystemEvent{
    float time;
    int event;
};
class Pattern{
	std::vector<UserRequest*> RequestList;
	std::std::vector<SystemEvent*> EventList;
	void GetUserRequests();
	void GetSystemEvents();
};

class User{

};

class QualityEvaluator{

};

class EmulationPlatform{

};

