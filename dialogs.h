#ifndef DIALOGS_H
#define DIALOGS_H

#include "wx/wx.h"
#include "mainframe.h"

enum {ID_TEXT1 = 10000, ID_TEXT2 = 10001, ID_SLIDER1 = 10002, ID_PROP = 10003, ID_SUPPR = 10004, ID_TEXT3 = 10005,
	 ID_LISTBOX1 = 10006, ID_TEXT_CTRL1= 10007, ID_SPIN_CTRL1=10008, ID_RADIO1=10009};

/*****************Thickness Dialog************************/

class VersionDialog: public wxDialog
{
    public :
        VersionDialog(wxWindow *parent, wxWindowID id, const wxString &title);

    private :

    DECLARE_EVENT_TABLE();
};


/*****************Color Dialog************************/

class ColorDialog: public wxDialog
{
    public :
        ColorDialog(wxWindow *parent, wxWindowID id, const wxString &title);

    private :

    DECLARE_EVENT_TABLE();
};


/*****************TriangleDialog Dialog************************/

class ThicknessDialog: public wxDialog
{
    public :
        ThicknessDialog(wxWindow *parent, wxWindowID id, const wxString &title);

    private :

    DECLARE_EVENT_TABLE();
};


/*****************TriangleDialog Dialog************************/

class TriangleDialog: public wxDialog
{
    public :
        TriangleDialog(wxWindow *parent, wxWindowID id, const wxString &title);
        wxListBox * getList();
    private :
        wxListBox *listBox;
        void OnProperties(wxCommandEvent& event);

    DECLARE_EVENT_TABLE();
};

/*****************Properties Dialog************************/

class PropertiesDialog: public wxDialog
{
    public :
        PropertiesDialog(wxWindow *parent, wxWindowID id, const wxString &title);

    private :

    DECLARE_EVENT_TABLE();
};

#endif // DIALOGS_H


