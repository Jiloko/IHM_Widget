#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/spinctrl.h>
#include <iterator>

#include "dialogs.h"
#include "triangle.h"

/*---------------------Version Dialog---------------------*/

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE ()

VersionDialog::VersionDialog(wxWindow *parent, 
    wxWindowID id, const wxString &title) :wxDialog(parent, id, title) 
{
    wxBoxSizer *box0 = new wxBoxSizer(wxVERTICAL);

    wxStaticText *version_text = new wxStaticText(this, VERSION_TEXT,
        wxT("Version 1.0.0"), wxDefaultPosition,
        wxDefaultSize, wxALIGN_CENTRE );

    wxButton *version_button = new wxButton(this, wxID_OK, wxT("OK"), 
        wxDefaultPosition);

    box0->Add(version_text, 0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add(version_button, 0, wxALIGN_CENTRE|wxALL, 5);

    this->SetAutoLayout(TRUE);
    this->SetSizer(box0);
    box0->Fit(this);
    box0->SetSizeHints(this);
}

/*---------------------Thickness Dialog---------------------*/


BEGIN_EVENT_TABLE(ThicknessDialog, wxDialog)
END_EVENT_TABLE ()

ThicknessDialog::ThicknessDialog(CMainFrame *parent, wxWindowID id, 
    const wxString &title) :wxDialog(parent, id, title) 
{
    wxBoxSizer *box0 = new wxBoxSizer(wxVERTICAL);

    wxStaticText *thick_text = new wxStaticText(this, THICKNESS_TEXT,
        wxT("Select thickness"), wxDefaultPosition, 
        wxDefaultSize, wxALIGN_CENTRE);

    thick_slider = new wxSlider(this, THICKNESS_SLIDER, 
        parent->thick, 1, 10, wxDefaultPosition, 
        wxSize(200, 50), wxSL_LABELS);

    wxButton *thick_button = new wxButton(this, wxID_OK, wxT("OK"), 
        wxDefaultPosition);

    box0->Add( thick_text, 0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add( thick_slider,  0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add( thick_button, 0, wxALIGN_CENTRE|wxALL, 5);

    this->SetAutoLayout(TRUE);
    this->SetSizer(box0);
    box0->Fit(this);
    box0->SetSizeHints(this);
}

/*---------------------Color Dialog---------------------*/

BEGIN_EVENT_TABLE(ColorDialog, wxDialog)
END_EVENT_TABLE ()

ColorDialog::ColorDialog(CMainFrame *parent, 
    wxWindowID id, const wxString &title) :wxDialog( parent, id, title) 
{
    wxBoxSizer *box0 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *color_text = new wxStaticText(this, COLOR_TEXT,
        wxT("Select color"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

    wxString colors[] = { wxT("Red"), wxT("Green"), wxT("Blue") };
    color_radio = new wxRadioBox(this, COLOR_RADIO, wxT("Color"), 
        wxDefaultPosition, wxDefaultSize, 3, colors);

    int choice = 0;

    if (parent->color->Red() == 255)
        choice = 0;
    else if (parent->color->Green() == 255)
        choice = 1;
    else // Blue == 255
        choice = 2;

    color_radio->SetSelection(choice);

    wxButton *color_button = new wxButton(this, wxID_OK,
        wxT("OK"), wxDefaultPosition);

    box0->Add(color_text, 0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add(color_radio, 0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add(color_button, 0, wxALIGN_CENTRE|wxALL, 5);

    this->SetAutoLayout(TRUE);
    this->SetSizer(box0);
    box0->Fit(this);
    box0->SetSizeHints(this);
}

wxColour* ColorDialog::getColor() 
{
    wxColour* c = new wxColour(color_radio->GetStringSelection());
    return c;
}

/*---------------------Triangle Dialog---------------------*/

BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
    EVT_BUTTON(BUTTON_PROP, TriangleDialog::OnProp)
    EVT_BUTTON(BUTTON_DELETE, TriangleDialog::OnDelete)
END_EVENT_TABLE ()

TriangleDialog::TriangleDialog(CMainFrame *parent, wxWindowID id, 
    const wxString &title) :wxDialog( parent, id, title)
{
    p = parent;

    wxBoxSizer *box0 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *box1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *box2 = new wxBoxSizer(wxVERTICAL);

    wxStaticText *triangle_text = new wxStaticText(this, COLOR_TEXT, 
        wxT("Triangles list"), wxDefaultPosition, 
        wxDefaultSize, wxALIGN_CENTRE);

    triangle_list = new wxListBox(this, TRIANGLE_LIST, 
        wxDefaultPosition, wxDefaultSize);
    triangle_list->SetSelection(0);

    box1->Add(triangle_text, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(triangle_list, 0, wxALIGN_CENTRE|wxALL, 5);

    wxButton *triangle_properties_b = new wxButton(this, BUTTON_PROP, 
        wxT("Properties"), wxDefaultPosition);
    wxButton *triangle_delete_b = new wxButton(this, BUTTON_DELETE,
        wxT("Delete"), wxDefaultPosition);
    wxButton *triangle_ok_b = new wxButton(this, wxID_OK, 
        wxT("OK"), wxDefaultPosition);

    box2->Add(triangle_properties_b, 0, wxALIGN_CENTRE|wxALL, 5);
    box2->Add(triangle_delete_b, 0, wxALIGN_CENTRE|wxALL, 5);
    box2->Add(triangle_ok_b, 0, wxALIGN_CENTRE|wxALL, 5);

    box0->Add(box1, 0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add(box2, 0, wxALIGN_CENTRE|wxALL, 5);

    this->SetAutoLayout(TRUE);
    this->SetSizer(box0);
    box0->Fit(this);
    box0->SetSizeHints(this);
}

wxListBox* TriangleDialog::getListBox()
{
    return this->triangle_list;
}

void TriangleDialog::OnProp(wxCommandEvent& event) 
{
    wxListBox* list = this->getListBox();
    int nb_color = list->GetSelection();
    if(nb_color >= 0) 
    {
        PropDialog dialog(this, -1, wxT("Properties"), 
            nb_color, p->tab_triangle[nb_color]);
        dialog.ShowModal();

        Triangle triangle = p->tab_triangle[nb_color];
        wxString color = dialog.prop_radio->GetStringSelection();

        triangle.thickness = dialog.prop_spin->GetValue();
        triangle.name = dialog.prop_name->GetValue();
        triangle.color = wxColour(color);

        p->tab_triangle[nb_color] = triangle;
        list->SetString(nb_color, triangle.name);
        p->canvas->Draw();
    }
}

void TriangleDialog::OnDelete(wxCommandEvent& event) 
{
    wxListBox* list = this->getListBox();
    int nb_color = list->GetSelection();
    if(nb_color >= 0) 
    {
        list->Delete(nb_color);
        p->DeleteTriangle(nb_color);
        p->canvas->Draw();
    }
}

/*---------------------Properties Dialog---------------------*/

BEGIN_EVENT_TABLE(PropDialog, wxDialog)
END_EVENT_TABLE ()

PropDialog::PropDialog(wxWindow *parent, wxWindowID id, const wxString &title, 
    int id_tri, Triangle triangle) :wxDialog( parent, id, title) 
{
    wxBoxSizer *box0 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *box1 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *box2 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *prop_text1 = new wxStaticText(this, ID_PROP_TEXT, 
    wxT("ID triangle [1-10 character]"), wxDefaultPosition, 
        wxDefaultSize, wxALIGN_CENTRE);

    prop_name = new wxTextCtrl(this, PROP_CTRL, triangle.name);
    prop_name->SetMaxLength(10);

    wxStaticText *prop_text2 = new wxStaticText(this, THICKNESS_PROP_TEXT,
        wxT("Thickness"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

    prop_spin = new wxSpinCtrl(this, PROP_SPIN, wxEmptyString, 
        wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
        1, 10, triangle.thickness);

    box1->Add(prop_text1, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(prop_name, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(prop_text2, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(prop_spin, 0, wxALIGN_CENTRE|wxALL, 5);

    wxString colors[] = { wxT("Red"), wxT("Green"), wxT("Blue") };

    int choice = 0;

    if (triangle.color == wxColour(wxT("red")))
        choice = 0;
    else if (triangle.color == wxColour(wxT("green")))
        choice = 1;
    else if (triangle.color == wxColour(wxT("blue")))
        choice = 2;

    prop_radio = new wxRadioBox(this, COLOR_RADIO, wxT("Color"), 
    wxDefaultPosition, wxDefaultSize, 3, colors);
    prop_radio->SetSelection(choice);

    box2->Add(box1, 0, wxALIGN_CENTRE|wxALL, 5);
    box2->Add(prop_radio, 0, wxALIGN_CENTRE|wxALL, 5);

    wxButton *prop_button = new wxButton(this, wxID_OK, wxT("OK"), 
        wxDefaultPosition);

    box0->Add(box2, 0, wxALIGN_CENTRE|wxALL, 5);
    box0->Add(prop_button, 0, wxALIGN_CENTRE|wxALL, 5);

    this->SetAutoLayout(TRUE);
    this->SetSizer(box0);
    box0->Fit(this);
    box0->SetSizeHints(this);
}

/*---------------------File Dialog---------------------*/

FileDialog::FileDialog(wxWindow* parent, const wxString& message,
    const wxString& defaultDir, const wxString& defaultFile, 
    const wxString& wildcard, long style) 
    :wxFileDialog(parent, message, defaultDir,
         defaultFile, wildcard, style)
{ }
