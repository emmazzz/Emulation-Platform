#include "EmulationPlatform.h"

void doit()
{
	Scheduler = new EmulationScheduler();
	Evaluator = new QualityEvaluator();
	Scheduler->init();
	Scheduler->Controller->ListenToUser();
	Scheduler->Routine();
	

}