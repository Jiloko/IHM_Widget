#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>

#include "dialogs.h"
#include "mainframe.h"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
	EVT_MENU(MENU_NEW,     CMainFrame::OnNew)
	EVT_MENU(MENU_OPEN,    CMainFrame::OnSave)
	EVT_MENU(MENU_SAVE,    CMainFrame::OnSave)
	EVT_MENU(MENU_EXIT,    CMainFrame::OnExit)
	EVT_MENU(MENU_SIZE,    CMainFrame::OnSize)
	EVT_MENU(MENU_COLOR,   CMainFrame::OnColor)
	EVT_MENU(MENU_MANAGE,  CMainFrame::OnManage)
	EVT_MENU(MENU_VERSION, CMainFrame::OnVersion)
	EVT_MENU(MENU_TOOLBAR, CMainFrame::OnToolbar)
	EVT_MENU(MENU_DRAW,    CMainFrame::OnDraw)
	EVT_MENU(TOOLBAR_TOOLS,   CMainFrame::OnTools)
END_EVENT_TABLE()



CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size) 
{
    nbtriangle = 0;
} //constructor

void CMainFrame::CreateMyToolbar()
{
    m_toolbar=CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL,TOOLBAR_TOOLS);
    wxBitmap toolBarBitmaps[4];
    toolBarBitmaps[0] = wxBitmap(wxT("new.bmp"),wxBITMAP_TYPE_BMP);
    toolBarBitmaps[1] = wxBitmap(wxT("open.bmp"),wxBITMAP_TYPE_BMP);
    toolBarBitmaps[2] = wxBitmap(wxT("save.bmp"),wxBITMAP_TYPE_BMP);
    toolBarBitmaps[3] = wxBitmap(wxT("draw.bmp"),wxBITMAP_TYPE_BMP);
    m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(),
                                 toolBarBitmaps[0].GetHeight()));
    m_toolbar->AddTool(MENU_NEW, wxT("Nouveau"), toolBarBitmaps[0]);
    m_toolbar->AddTool(MENU_OPEN, wxT("Ouvrir"), toolBarBitmaps[1]);
    m_toolbar->AddTool(MENU_SAVE, wxT("Sauvegarder"), toolBarBitmaps[2]);
    m_toolbar->AddSeparator();
    m_toolbar->AddCheckTool(MENU_DRAW, wxT("Dessiner"), toolBarBitmaps[3]);

    m_toolbar->Realize();
    SetToolBar(m_toolbar);
}

void CMainFrame::OnNew(wxCommandEvent& event)
{

}

void CMainFrame::OnOpen(wxCommandEvent& event)
{

}

void CMainFrame::OnSave(wxCommandEvent& event)
{

}

void CMainFrame::OnExit(wxCommandEvent& event)
{
    Close(TRUE);
}

void CMainFrame::OnSize(wxCommandEvent& event)
{
	ThicknessDialog thicknessdialog(this, -1, wxT("Epaisseur"));
	thicknessdialog.ShowModal();
}

void CMainFrame::OnColor(wxCommandEvent& event)
{
    ColorDialog colordialog(this, -1, wxT("Couleur"));
    colordialog.ShowModal();
}

void CMainFrame::OnManage(wxCommandEvent& event)
{
	TriangleDialog triangledialog(this, -1, wxT("Gestion des triangles"));

    wxListBox * list = triangledialog.getList();
    list->Clear();
    list->Append(wxT("tri4"));
    list->Append(wxT("tri5")); 
    list->SetSelection(1);
	triangledialog.ShowModal();
}

void CMainFrame::OnVersion(wxCommandEvent& event)
{
	VersionDialog versiondialog(this, -1, wxT("Version"));
	versiondialog.ShowModal();
}

void CMainFrame::OnToolbar(wxCommandEvent& event)
{
    if(m_toolbar->IsShownOnScreen())
        m_toolbar->Hide();
    else
        m_toolbar->Show();   
}

void CMainFrame::OnDraw(wxCommandEvent& event)
{
    std::cout << "pouet" << std::endl;
}

void CMainFrame::OnTools(wxCommandEvent& event)
{
	
}
