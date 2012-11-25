// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <mathplot.h>

#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/intl.h>
#include <wx/print.h>
#include <wx/thread.h>

#include <math.h>

#include "DataCreationThread.h"
#include "PlotRefreshThread.h"

class MyFrame;
class MyApp;

// MyFrame

class MyFrame: public wxFrame
{
public:
    MyFrame();

    void OnAbout( wxCommandEvent &event );
    void OnQuit( wxCommandEvent &event );
    void OnFit( wxCommandEvent &event );

private:
    int axesPos[2];
    bool ticks;
    DECLARE_DYNAMIC_CLASS(MyFrame)
    DECLARE_EVENT_TABLE()
	mpWindow        *m_plot;
	DataCreationThread *m_dataThread;
	PlotRefreshThread  *m_plotThread;
	wxMutex *m_mutex;
};

// MyApp

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

// main program

IMPLEMENT_APP(MyApp)

// MyFrame

enum {
    ID_QUIT  = 108,
    ID_ABOUT,
    ID_PRINT,
    ID_PRINT_PREVIEW,
    ID_ALIGN_X_AXIS,
    ID_ALIGN_Y_AXIS,
    ID_TOGGLE_GRID
};

IMPLEMENT_DYNAMIC_CLASS( MyFrame, wxFrame )

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
  EVT_MENU(ID_ABOUT, MyFrame::OnAbout)
  EVT_MENU(ID_QUIT,  MyFrame::OnQuit)
  EVT_MENU(mpID_FIT, MyFrame::OnFit)
 END_EVENT_TABLE()

MyFrame::MyFrame()
       : wxFrame( (wxFrame *)NULL, -1, wxT("wxWindows mathplot sample #3 - 'mpMovableObject' objects"),
			wxDefaultPosition, wxSize(1000,580) )
{

	::std::vector<double> *datax = new vector<double>;
	::std::vector<double> *datay = new vector<double>;

	wxMenu *file_menu = new wxMenu();
	wxMenu *view_menu = new wxMenu();
	
	file_menu->Append( ID_ABOUT, wxT("&About..."));
	file_menu->Append( ID_QUIT,  wxT("E&xit\tAlt-X"));
	
	view_menu->Append( mpID_FIT,      wxT("&Fit bounding box"), wxT("Set plot view to show all items"));
	view_menu->Append( mpID_ZOOM_IN,  wxT("Zoom in"),           wxT("Zoom in plot view."));
	view_menu->Append( mpID_ZOOM_OUT, wxT("Zoom out"),          wxT("Zoom out plot view."));
	
	wxMenuBar *menu_bar = new wxMenuBar();
	menu_bar->Append(file_menu, wxT("&File"));
	menu_bar->Append(view_menu, wxT("&View"));
	
	SetMenuBar( menu_bar );
	CreateStatusBar(1);
	
	m_plot = new mpWindow( this, -1, wxPoint(0,0), wxSize(200,200), wxSUNKEN_BORDER );
	m_plot->SetMargins(0,0,50,70);
	mpScaleX* xaxis = new mpScaleX(wxT("x"), mpALIGN_BOTTOM, true);
	mpScaleY* yaxis = new mpScaleY(wxT("y"), mpALIGN_LEFT, true);
	xaxis->SetDrawOutsideMargins(false);
	yaxis->SetDrawOutsideMargins(false);
	m_plot->AddLayer(xaxis);
	m_plot->AddLayer(yaxis);

	mpFXYVector *lData;
	m_plot->AddLayer( lData = new mpFXYVector(wxT("data")) );
	lData->SetContinuity(true);

	wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );
	
	topsizer->Add( m_plot, 1, wxEXPAND );
	
	SetAutoLayout( TRUE );
	SetSizer( topsizer );
	axesPos[0] = 0;
	axesPos[1] = 0;
	ticks = true;

	m_plot->EnableDoubleBuffer(true);
	m_plot->LockAspect( false );
	m_plot->Fit();


	m_mutex = new wxMutex();

	m_dataThread = new DataCreationThread(datax, datay, m_mutex);
	m_dataThread->Create();
	m_dataThread->Run();

	m_plotThread = new PlotRefreshThread(datax, datay, m_plot, lData, m_mutex);
	m_plotThread->Create();
	m_plotThread->Run();

}

void MyFrame::OnQuit( wxCommandEvent &WXUNUSED(event) )
{
	m_dataThread->cancel();
	m_dataThread->Wait();

	m_plotThread->cancel();
	m_plotThread->Wait();

	Close( TRUE );
}

void MyFrame::OnFit( wxCommandEvent &WXUNUSED(event) )
{
    m_plot->Fit();
}

void MyFrame::OnAbout( wxCommandEvent &WXUNUSED(event) )
{
    wxMessageBox( wxT("wxWidgets mathplot sample #3\n(c) 2007 David Schalig, Davide Rondini, Jose Luis Blanco"));
}


//-----------------------------------------------------------------------------
// MyApp
//-----------------------------------------------------------------------------

bool MyApp::OnInit()
{
    wxFrame *frame = new MyFrame();
    frame->Show( TRUE );

    return TRUE;
}

