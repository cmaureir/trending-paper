#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

#include "PlotRefreshThread.h"

PlotRefreshThread::PlotRefreshThread(vector<double> *datax, vector<double> *datay, QwtPlot *plot, MyCurve *curve, QMutex *mutex)
 : QThread() {
	_datax = datax;
	_datay = datay;
	_plot  = plot;
	_curve = curve;
	_mutex = mutex;
	_run = true;
	srand(time(NULL));
	fps = 0;
}

void PlotRefreshThread::run() {

	struct timespec time;
	unsigned int i;
	long int start, end;
	double *x = NULL;
	double *y = NULL;

	sleep(1);
	clock_gettime(CLOCK_REALTIME,&time);
//	start = time.tv_sec * 1000000000 + time.tv_nsec;
	start = time.tv_nsec;
	while( _run ) {
		_mutex->lock();
		x = (double *)realloc(x, sizeof(double)*_datax->size());
		y = (double *)realloc(y, sizeof(double)*_datax->size());
		for (i = 0; i < _datax->size(); i++) {
			x[i] = (*_datax)[i];
			y[i] = (*_datay)[i];
		}
		emit setData(x, y, _datax->size());
		_mutex->unlock();

		emit replot();
		fps++;
		if( !(fps % 100) ) {
			clock_gettime(CLOCK_REALTIME,&time);
//			end = time.tv_sec * 1000000000 + time.tv_nsec;
			end = time.tv_nsec;
			cout << "FPS: " << ((float)100*1000000000)/(end - start) << endl;
			start = end;
		}

#if 0
		if( time.tv_sec != timePast.tv_sec ) {
			cout << "FPS: " << fps << endl;
			fps = 0;
		}
		timePast.tv_sec = time.tv_sec;
		timePast.tv_nsec = time.tv_nsec;
#endif
	}

}

void PlotRefreshThread::cancel() {
	_run = false;
}
