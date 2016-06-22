#include "EmulationPlatform.h"

int main()
{
	EmulationScheduler *Scheduler = new EmulationScheduler();
	QualityEvaluator *Evaluator = new QualityEvaluator();
	Scheduler->Init();
	Scheduler->Routine();
	return 1;

}