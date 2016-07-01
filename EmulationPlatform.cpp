#include "EmulationPlatform.h"

int main(int argc, char *argv[])
{
	int portno = atoi(argv[2]);
	char *host = argv[1];

	printf("%s %d\n",host,portno );
	EmulationScheduler *Scheduler = new EmulationScheduler();
	char *t = argv[3];
	Scheduler->Init(t);

	

	Scheduler->Routine(portno,host);


	return 0;

}