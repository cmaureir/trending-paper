#include <QtGui>
#include <QtCore>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include "DataCreationThread.h"
#include "MyCurve.h"
#include "MyPlot.h"
#include "PlotRefreshThread.h"

int main( int argc, char **argv )
{

	vector<double> *x = new vector<double>();
	vector<double> *y = new vector<double>();

	QApplication a(argc, argv);
	
	MyPlot *myPlot = new MyPlot();
	myPlot->setMinimumSize(1000,580);
	MyCurve *myCurve = new MyCurve("Curve 1");
	myCurve->attach(myPlot);
	myPlot->show();

	QMutex *mutex = new QMutex();
	QThread *dataCreationThread = new DataCreationThread(x, y, mutex);
	QThread *plotRefreshThread = new PlotRefreshThread(x, y, myPlot, myCurve, mutex);
	dataCreationThread->start();
	plotRefreshThread->start();

	QObject::connect(plotRefreshThread, SIGNAL(setData(double *, double *, int)), myCurve, SLOT(setDataSLOT(double *, double *, int)));
	QObject::connect(plotRefreshThread, SIGNAL(replot()), myPlot, SLOT(replotSLOT()));
	
	return a.exec();
}
