#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include <wx/spinctrl.h>
#include "triangle.h"
#include "mainframe.h"

enum {  
    VERSION_TEXT=1337,
    THICKNESS_TEXT,
    THICKNESS_SLIDER,
    COLOR_TEXT,
    COLOR_RADIO,
    TRIANGLE_LIST,
    BUTTON_PROP,
    BUTTON_DELETE,
    ID_PROP_TEXT,
    THICKNESS_PROP_TEXT,
    PROP_CTRL,
    PROP_SPIN
};

/*---------------------Version Dialog---------------------*/

class VersionDialog: public wxDialog 
{
    public:
        VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);
  
    private:
        DECLARE_EVENT_TABLE();
};

/*---------------------Thickness Dialog---------------------*/

class ThicknessDialog: public wxDialog 
{
    public:
        ThicknessDialog(CMainFrame *parent, wxWindowID id, 
            const wxString &title);
        wxSlider *thick_slider;

    private:
        DECLARE_EVENT_TABLE();
};

/*---------------------Color Dialog---------------------*/

class ColorDialog: public wxDialog 
{
    public:
        ColorDialog(CMainFrame *parent, wxWindowID id, const wxString &title);
        wxColour* getColor();
    
    private:
        DECLARE_EVENT_TABLE();
        wxRadioBox *color_radio;
};

/*---------------------Triangle Dialog---------------------*/

class TriangleDialog: public wxDialog 
{
    public:
        TriangleDialog(CMainFrame *parent, wxWindowID id, 
            const wxString &title);
        wxListBox * getListBox();

    private:
        DECLARE_EVENT_TABLE();
        CMainFrame *p;
        wxListBox *triangle_list;
        void OnProp(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
};

/*---------------------Properties Dialog---------------------*/

class PropDialog: public wxDialog 
{
    public:
        wxSpinCtrl *prop_spin;
        wxRadioBox *prop_radio;
        wxTextCtrl *prop_name;
        PropDialog(wxWindow *parent, wxWindowID id, const wxString &title,
            int id_tri, Triangle triangle);
  
    private:
        DECLARE_EVENT_TABLE();
};

/*---------------------File Dialog---------------------*/

class FileDialog: public wxFileDialog 
{
    public:
        FileDialog(wxWindow* parent, const wxString& message,
            const wxString& default_Dir, const wxString& default_File,
            const wxString& wildcard, long style);
  
};

#endif
