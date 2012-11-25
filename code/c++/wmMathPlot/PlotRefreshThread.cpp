#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

#include "PlotRefreshThread.h"

PlotRefreshThread::PlotRefreshThread(vector<double> *datax, vector<double> *datay, mpWindow *plot, mpFXYVector *dataLayer, wxMutex *mutex)
 : wxThread(wxTHREAD_JOINABLE) {
	_datax = datax;
	_datay = datay;
	_plot = plot;
	_dataLayer = dataLayer;
	_mutex = mutex;
	_run = true;
	srand(time(NULL));
	fps = 0;
}

wxThread::ExitCode PlotRefreshThread::Entry() {

	struct timespec time;
	while( _run ) {
		_mutex->Lock();
		_dataLayer->SetData(*_datax, *_datay);
		_mutex->Unlock();

		_plot->Fit();
		_plot->UpdateAll();
		fps++;
		clock_gettime(CLOCK_REALTIME,&time);
//		if ( fps == 100 ){
//			//cout << "LALA:" << (float)100/(time.tv_sec - timePast.tv_sec) << endl;
//			cout << "now" << time.tv_sec << endl;
//			cout << "past" << timePast.tv_sec << endl;	
//		}
		if( time.tv_sec != timePast.tv_sec ) {
			cout << "FPS: " << fps << endl;
			fps = 0;
		}
		timePast = time;
	}

	return 0;
}

void PlotRefreshThread::cancel() {
	_run = false;
}
