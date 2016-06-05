#include "EmulationPlatform.h"

Quality QualityEvaluator::EvaluateQuality(string User_ID, float Timestamp,
    	                   std::vector<UserFeature> Client_Feature_Vector,
    	                   Decision *Decision)
{
	// TODO
	Quality Q = new Quality();
	Q.quality = 1;
	return Q
};