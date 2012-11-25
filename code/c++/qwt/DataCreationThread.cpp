#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "DataCreationThread.h"

DataCreationThread::DataCreationThread(vector<double> *datax, vector<double> *datay, QMutex *mutex)
 : QThread() {
	_datax = datax;
	_datay = datay;
	_mutex = mutex;
	_run = true;
	srand(time(NULL));
}

void DataCreationThread::run() {

	struct timespec time;
	float tmp;
	double value;

	sleep(1);
	while( _run ) {

		clock_gettime(CLOCK_REALTIME,&time);
		tmp  = time.tv_sec*1000 + ((float)time.tv_nsec)/1000000ULL;
		value = 100*cos(tmp*2*M_PI/2000);

		_mutex->lock();
		_datax->push_back(_datax->size() + 1);
		_datay->push_back( value );
		_mutex->unlock();

		usleep(1000);
	}

}

void DataCreationThread::cancel() {
	_run = false;
}
