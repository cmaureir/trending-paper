#include <vector>

#include <wx/thread.h>

using namespace std;

class DataCreationThread : public wxThread {

	private:
	bool _run;
	vector<double> *_datax;
	vector<double> *_datay;
	wxMutex *_mutex;

	public:
	DataCreationThread(vector<double> *datax, vector<double> *datay, wxMutex *mutex);
	wxThread::ExitCode Entry();
	void cancel();

};
