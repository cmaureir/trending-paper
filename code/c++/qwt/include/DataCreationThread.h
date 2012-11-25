#ifndef datacreationthread_h
#define datacreationthread_h

#include <QMutex>
#include <QThread>
#include <vector>

using namespace std;

class DataCreationThread : public QThread {

	private:
	bool _run;
	vector<double> *_datax;
	vector<double> *_datay;
	QMutex *_mutex;

	public:
	DataCreationThread(vector<double> *datax, vector<double> *datay, QMutex *mutex);
	void run();
	void cancel();

};

#endif /* end of include guard: datacreationthread_h */
