#include <vector>

#include <mathplot.h>

using namespace std;

class PlotRefreshThread : public wxThread {

	private:
	bool _run;
	vector<double> *_datax;
	vector<double> *_datay;
	mpWindow       *_plot;
	mpFXYVector    *_dataLayer;
	wxMutex        *_mutex;
	struct timespec timePast;
	long int fps;

	public:
	PlotRefreshThread(vector<double> *datax, vector<double> *datay, mpWindow *plot, mpFXYVector *dataLayer, wxMutex *mutex);
	wxThread::ExitCode Entry();
	void cancel();

};
