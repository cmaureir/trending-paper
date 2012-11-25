#include <iostream>
#include "MyCurve.h"

using namespace std;

MyCurve::MyCurve(const char *name) : QwtPlotCurve(name) { }

void MyCurve::setDataSLOT(double *x, double *y, int size) {
	setData(x, y, size);
}
