#ifndef mycurve_h
#define mycurve_h

#include <QObject>
#include <qwt/qwt_plot_curve.h>

class MyCurve : public QObject, public QwtPlotCurve {

	Q_OBJECT

	public:
	MyCurve(const char* name);

	public slots:
	void setDataSLOT(double *x, double *y, int size);

};

#endif /* mycurve_h */
