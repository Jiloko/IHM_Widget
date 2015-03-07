#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <fstream>
#include "mainframe.h"
#include "dialogs.h"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
    EVT_MENU(MENU_NEW, CMainFrame::OnNew)
    EVT_MENU(MENU_OPEN, CMainFrame::OnOpen)
    EVT_MENU(MENU_SAVE, CMainFrame::OnSave)
    EVT_MENU(MENU_QUIT, CMainFrame::OnQuit)
    EVT_MENU(MENU_THICKNESS, CMainFrame::OnSize)
    EVT_MENU(MENU_COLOR, CMainFrame::OnColor)
    EVT_MENU(MENU_TRIANGLE, CMainFrame::OnTriangle)
    EVT_MENU(MENU_VERSION, CMainFrame::OnVersion)
    EVT_MENU(MENU_HELP, CMainFrame::OnHelp)
    EVT_MENU(MENU_TOOLBAR, CMainFrame::OnToolbar)
    EVT_MENU(MENU_DRAW, CMainFrame::OnDraw)
END_EVENT_TABLE()

CMainFrame::CMainFrame(const wxString& title, const wxPoint& pos, 
    const wxSize& size):wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    thick = 5;
    color = new wxColour(wxT("red"));
    is_drawing = FALSE;
    nbtriangle = 0;
}



void CMainFrame::CreateMyToolbar()
{
    m_toolbar=CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL, TOOLBAR_TOOLS);

    wxBitmap toolBarBitmaps[4];
    toolBarBitmaps[0] = wxBitmap(wxT("new.bmp"),wxBITMAP_TYPE_BMP);
    toolBarBitmaps[1] = wxBitmap(wxT("open.bmp"),wxBITMAP_TYPE_BMP);
    toolBarBitmaps[2] = wxBitmap(wxT("save.bmp"),wxBITMAP_TYPE_BMP);
    toolBarBitmaps[3] = wxBitmap(wxT("draw.bmp"),wxBITMAP_TYPE_BMP);

    m_toolbar->SetToolBitmapSize(wxSize(toolBarBitmaps[0].GetWidth(), 
        toolBarBitmaps[0].GetHeight()));
    m_toolbar->AddTool(MENU_NEW, wxT("New"), toolBarBitmaps[0]);
    m_toolbar->AddTool(MENU_OPEN, wxT("Open"), toolBarBitmaps[1]);
    m_toolbar->AddTool(MENU_SAVE, wxT("Save"), toolBarBitmaps[2]);
    m_toolbar->AddSeparator();
    m_toolbar->AddCheckTool(MENU_DRAW, wxT("Draw"), toolBarBitmaps[3]);

    m_toolbar->Realize();
    SetToolBar(m_toolbar);

    canvas = new OpenGLCanvas(this, CANVAS, wxDefaultPosition, 
        wxDefaultSize, 0, wxT("GLCanvas"));
}



void CMainFrame::OnNew(wxCommandEvent& event)
{
    nbtriangle = 0;
    wxMenuBar* menu_bar = this->GetMenuBar();
    menu_bar->Enable(MENU_TRIANGLE,false);
    canvas->Draw();
}

/*---------------------Open/Save File---------------------*/

void CMainFrame::OnOpen(wxCommandEvent& event)
{
    FileDialog dialog(this, wxT("Select a file"), wxT(""), 
        wxT("mytriangles.tri"), wxT("*.tri"), wxOPEN);
    dialog.ShowModal();
    std::ifstream file(dialog.GetPath().fn_str(), std::ios::in);

    if (!file) 
    {
        wxString error_text, caption_text;
        error_text.Printf(wxT("Unable to open file"));
        error_text.Append(dialog.GetPath());
        caption_text.Printf(wxT("Error"));
        wxMessageDialog message(this, error_text, caption_text,
            wxOK | wxCENTRE | wxICON_ERROR);
        message.ShowModal();
        return;
    }
    file >> nbtriangle;

    for (int i = 0; i < nbtriangle; ++i)
    {
        Triangle triangle;

        std::string name;
        file >> name;
        triangle.name = replaceSpaceFromFile(name);
        file >> triangle.p1.x >> triangle.p1.y >> triangle.p2.x >> 
            triangle.p2.y >> triangle.p3.x >> triangle.p3.y;

        int r, g, b;
        file >> r >> g >> b;
        triangle.color = wxColour(r, g, b);

        file >> triangle.thickness;

        tab_triangle[i] = triangle;
    }

    if (nbtriangle > 0) 
    {
        wxMenuBar* menu_bar = this->GetMenuBar();
        menu_bar->Enable(MENU_TRIANGLE,true);
    }

    canvas->Draw();
}



void CMainFrame::OnSave(wxCommandEvent& event) 
{
    FileDialog dialog(this, wxT("Save file"), wxT("˜"), 
        wxT("mytriangles.tri"), wxT("*.tri"), wxSAVE|wxFD_OVERWRITE_PROMPT);
    dialog.ShowModal();
    std::ofstream file(dialog.GetPath().fn_str(), std::ios::out);

    if (!file) 
    {
        wxString error_text, caption_text;
        error_text.Printf(wxT("Unable to save file "));
        error_text.Append(dialog.GetPath());
        caption_text.Printf(wxT("Erreur"));
        wxMessageDialog message(this, error_text, caption_text,
            wxOK | wxCENTRE | wxICON_ERROR);
        message.ShowModal();
        return;
    }

    file << nbtriangle << std::endl << std::endl;
    for (int i = 0; i < nbtriangle; ++i)
    {
        Triangle triangle = tab_triangle[i];
        std::string name = replaceSpaceToFile(triangle.name);
        file << name << std::endl;
        file << triangle.p1.x << " " << triangle.p1.y << " " << triangle.p2.x 
            << " " << triangle.p2.y << " " << triangle.p3.x << " " 
            << triangle.p3.y << std::endl;
        file << (int)triangle.color.Red() << " " 
            << (int)triangle.color.Green() << " " 
            << (int)triangle.color.Blue() << std::endl;
        file << triangle.thickness << std::endl << std::endl;
    }
}

/*---------------------Dialogs management---------------------*/

void CMainFrame::OnQuit(wxCommandEvent& event)
{
  Close(TRUE);
}

void CMainFrame::OnSize(wxCommandEvent& event) 
{
    ThicknessDialog dialog(this, -1, wxT("Thickness"));
    dialog.ShowModal();
    this->thick = dialog.thick_slider->GetValue();
}

void CMainFrame::OnColor(wxCommandEvent& event) 
{
    ColorDialog dialog(this, -1, wxT("Color"));
    dialog.ShowModal();
    this->color = dialog.getColor();
}

void CMainFrame::OnTriangle(wxCommandEvent& event) 
{
    TriangleDialog dialog(this, -1, wxT("Triangle"));

    wxListBox * list = dialog.getListBox();

    list->Clear();

    for (int i = 0; i < nbtriangle; ++i) 
    {
        wxString chi;
        chi << i+1;
        list->Append(tab_triangle[i].name);
    }

    dialog.ShowModal();
}

void CMainFrame::OnVersion(wxCommandEvent& event) 
{
    VersionDialog dialog(this, -1, wxT("Version"));
    dialog.ShowModal();
}

void CMainFrame::OnHelp(wxCommandEvent& event) 
{
    help.DisplayContents();
}
void CMainFrame::OnToolbar(wxCommandEvent& event)
{
    if (m_toolbar->IsShownOnScreen())
        m_toolbar->Hide();
    else
        m_toolbar->Show();
}

void CMainFrame::OnDraw(wxCommandEvent& event)
{
    is_drawing = !is_drawing;
}

void CMainFrame::DeleteTriangle(int i) 
{
    std::copy(tab_triangle + i + 1, tab_triangle + nbtriangle, tab_triangle + i);
    nbtriangle--;
    if (nbtriangle == 0) 
    {
        wxMenuBar* menu_bar = this->GetMenuBar();
        menu_bar->Enable(MENU_TRIANGLE,false);
    }
}

/*---------------------Saving name with space function---------------------*/

std::string CMainFrame::replaceSpaceToFile(wxString arg)
{
    std::string str = std::string(arg.mb_str());
    for(std::string::iterator i = str.begin(); i != str.end(); ++i) 
    {
        if(*i == ' ') 
            *i = '|';
    }
    return str;
}

wxString CMainFrame::replaceSpaceFromFile(std::string str) 
{
    for(std::string::iterator i = str.begin(); i != str.end(); ++i) 
    {
        if(*i == '|')
          *i = ' ';
    }
    wxString std(str.c_str(), wxConvUTF8);
    return std;
}
