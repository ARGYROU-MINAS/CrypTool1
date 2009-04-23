//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgFortschritt.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <time.h>

#include "CrypToolApp.h"
#include "DlgShowProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowProgress 


CDlgShowProgress::CDlgShowProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowProgress::IDD, pParent)
{
#ifdef debugprogress
	debug = 0;
#endif
	m_canceled=0;
	m_displayed=0;
	// old interface
	m_pos=-1;
	// new MV interface
	m_model = 0;

	//{{AFX_DATA_INIT(CDlgShowProgress)
	//}}AFX_DATA_INIT
}


void CDlgShowProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowProgress)
	DDX_Control(pDX, IDC_TEXT, m_text_ctl);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowProgress, CDialog)
	//{{AFX_MSG_MAP(CDlgShowProgress)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgShowProgress 

void CDlgShowProgress::setModel(CProgressModel *model) { 
	m_model = model; 
}
void CDlgShowProgress::setModelTitleFormat(CProgressModel *model,UINT title, UINT format)
{
	setTitle(title);
	setFormat(format);
	setModel(model);
}

void CDlgShowProgress::setModelTitleFormat(CProgressModel *model,UINT title, LPCTSTR format)
{
	setTitle(title);
	setFormat(format);
	setModel(model);
}

void CDlgShowProgress::setModelTitleFormat(CProgressModel *model,LPCTSTR title, UINT format)
{
	setTitle(title);
	setFormat(format);
	setModel(model);
}

void CDlgShowProgress::setModelTitleFormat(CProgressModel *model,LPCTSTR title, LPCTSTR format)
{
	setTitle(title);
	setFormat(format);
	setModel(model);
}
void CDlgShowProgress::startClock()
{
#ifdef debugprogress
	if (debug)
		fclose(debug);
	debug = fopen("c:\\temp\\progress.log","w");
#endif
	m_clock0 = GetTickCount(); //clock();
	QueryPerformanceFrequency((LARGE_INTEGER *)&m_hres_cps);
	QueryPerformanceCounter((LARGE_INTEGER *)&m_hres_clock0);
}


int CDlgShowProgress::Set(int pos)
{
	int t;
	m_model = 0; // we are using the old non MV interface
/*	if(m_pos==-1) {
		return -1;
	}*/
	t = m_pos;
	m_pos = pos;
	return t;
}

int CDlgShowProgress::Set(int pos, CString format)
{
	m_format = format;
	return Set(pos);
}

BOOL CDlgShowProgress::OnInitDialog() 
{
	Lock.Lock();
	CDialog::OnInitDialog();
	m_days.LoadString(IDS_STRING_DAYS);
	m_years.LoadString(IDS_STRING_YEARS);
	m_Progress.SetRange(0,100);
	SetWindowText(m_title);
	m_text_ctl.SetWindowText("");
	m_pos = 0;
	m_old_pos=-1;
	m_displayed=1;
	m_canceled = 0;
	SetTimer(43,250,NULL);
	Lock.Unlock();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgShowProgress::OnCancel() 
{
#ifdef debugprogress
	if (debug)
		fclose(debug);
	debug = 0;
#endif
	Lock.Lock();
	KillTimer(43);
	m_pos=-1;	
	m_canceled=1;
	CDialog::OnCancel();
	DestroyWindow();
	m_displayed=0;
	Lock.Unlock();
}


int CDlgShowProgress::Set(int pos, CString caption, CString format)
{
	m_title=caption;
	m_canceled = 0;
	return Set(pos, format);
}

CString CDlgShowProgress::duration(double progress) const
{
	//double sofar = (clock() - m_start_clock) / (double)CLOCKS_PER_SEC; // clock seems to be process time, not wall time
	double sofar; // time since start of calculation [s]
	if (m_hres_cps) {
		LONGLONG now;
		QueryPerformanceCounter((LARGE_INTEGER *)&now);
		sofar = (now - m_hres_clock0);
		sofar /= m_hres_cps;
	} else
		sofar = (GetTickCount() - m_clock0) / 1000.0;
	
	if (progress == 0.0 || sofar < 0.01)
		return "?";
	//double rest = sofar * (1.0 - progress) / progress; // numerisch instabil: 1.0-progress == 0.0 falls suchraumbits > double mantissenbits
	double rest = sofar / progress - sofar; 
	CString d;
#ifdef debugprogress
	CString raw;
	raw.Format("\nsofar\t%10.10g\nprogr\t%10.10g\ntotal\t%10.10g\n",sofar,progress,sofar/progress);
	if (debug)
		fprintf(debug,"%10.10g\t%10.10g\n",sofar,progress);
#endif
	if (rest < 3600.0*24.0) {
		double error = 0.01 / progress; // assuming 10ms time resolution
		int s = rest + 0.5;
		if (error < 1.0)
			d.Format("%02d:%02d:%02d",s/3600, (s / 60) % 60, s % 60);
		else if (error < 60.0)
			d.Format("%02d:%02d",s/3600, (s / 60) % 60);
		else 
			d.Format("%02d h",s/3600);
	} else if (rest < 3600.0*24.0*365.0) {
		//double logerror = log10((double)CLOCKS_PER_SEC*progress*(3600.0*24.0));
		d.Format("%.1f %s",rest/(3600.0*24.0),m_days);
	} else {
		//double logerror = log10((double)CLOCKS_PER_SEC*progress*(3600.0*24.0*365.0));
		d.Format("%.2g %s",rest/(3600.0*24.0*365.0),m_years);
	}
#ifdef debugprogress
	return raw + d;
#else
	return d;
#endif
}

void CDlgShowProgress::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent != 43) {
		CDialog::OnTimer(nIDEvent);
		return;
	}
	if(!m_displayed) 
		return;
	if (m_model) { // new MV interface
		CString text;
		double progress = m_model->getProgress();
		int percent = 100.0*progress+0.5;
		text.Format(m_format,percent,duration(progress));
		m_text_ctl.SetWindowText(text);
		m_Progress.SetPos(percent);
	} else {
		char line[256];
		Lock.Lock();
		if((m_pos==-1) || (m_old_pos == m_pos)) {
			Lock.Unlock();
			return;
		}
		m_old_pos = m_pos;
		m_Progress.SetPos(m_pos);
		SHOW_HOUR_GLASS
		sprintf(line, m_format, m_pos);
		m_text_ctl.SetWindowText(line);
		//HIDE_HOUR_GLASS
		Lock.Unlock();
	}
}

void CDlgShowProgress::cancel()
{
	if(m_displayed)
		PostMessage(WM_COMMAND,IDCANCEL,NULL);
}

void CDlgShowProgress::Display(const char * title)
{
	Set((int)0,title,"");
	Display();
} 

void CDlgShowProgress::Display()
{
	while(m_displayed) Sleep(10);
	theApp.m_MainWnd->PostMessage(WM_TIMER,44,NULL); /* oeffnet das Fenster modal im Hauptthread */
	while(!m_displayed) Sleep(10); /* wartet bis das Fenster existiert */
	startClock();

} 