#ifndef plotrefreshthread_h
#define plotrefreshthread_h

#include <QMutex>
#include <QThread>
#include <vector>

#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include "MyCurve.h"

using namespace std;

class PlotRefreshThread : public QThread {

	Q_OBJECT

	private:
	bool _run;
	::std::vector<double> *_datax;
	::std::vector<double> *_datay;
	QwtPlot        *_plot;
	MyCurve        *_curve;
	QMutex         *_mutex;
	struct timespec timePast;
	long int fps;

	public:
	PlotRefreshThread(::std::vector<double> *datax, ::std::vector<double> *datay, QwtPlot *plot, MyCurve *_curve, QMutex *mutex);
	void run();
	void cancel();

	signals:
	void setData(double *x, double *y, int size);
	void replot();

};

#endif /* end of include guard: plotrefreshthread_h */
