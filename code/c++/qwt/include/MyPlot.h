#ifndef myplot_h
#define myplot_h

#include <QObject>
#include <qwt/qwt_plot.h>

class MyPlot: public QwtPlot {

	Q_OBJECT

	public slots:
	void replotSLOT();

};

#endif /* end of include guard: myplot_h */

