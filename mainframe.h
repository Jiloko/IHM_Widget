
#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "wx/wx.h"

enum { MENU_NEW, MENU_OPEN, MENU_SAVE, MENU_EXIT, MENU_SIZE, MENU_COLOR,
       MENU_MANAGE, MENU_VERSION, MENU_TOOLBAR, MENU_DRAW, TOOLBAR_TOOLS};



class CMainFrame: public wxFrame
{
public:
	CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void CreateMyToolbar();
private:
    wxToolBar *m_toolbar;
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnSize(wxCommandEvent& event);
    void OnColor(wxCommandEvent& event);
    void OnManage(wxCommandEvent& event);
    void OnVersion(wxCommandEvent& event);
    void OnToolbar(wxCommandEvent& event);
    void OnDraw(wxCommandEvent& event);
    void OnTools(wxCommandEvent& event);

	DECLARE_EVENT_TABLE();


}; //MyFrame

#endif
