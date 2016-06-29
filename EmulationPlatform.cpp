#include "EmulationPlatform.h"

int main(int argc, char *argv[])
{
	int portno = atoi(argv[2]);
	char *host = argv[1];

	printf("%s %d\n",host,portno );

	EmulationScheduler *Scheduler = new EmulationScheduler();

	QualityEvaluator *Evaluator = new QualityEvaluator();

	Scheduler->Init();

	Scheduler->Routine(portno,host);

	
	return 0;

}