#include <stdio.h>
#include <stdlib.h>
#include <wx/wx.h>
#include <wx/accel.h>
#include <wx/spinctrl.h>

#include "dialogs.h"

BEGIN_EVENT_TABLE(VersionDialog, wxDialog)
END_EVENT_TABLE ()

VersionDialog::VersionDialog( wxWindow *parent, wxWindowID id,const wxString &title)
    :wxDialog( parent, id, title)
{
    wxBoxSizer *box1 = new wxBoxSizer( wxVERTICAL );
    wxStaticText *item1 = new wxStaticText( this, ID_TEXT1, wxT("Version 1.0"),
                                            wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    wxButton *item2 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

    box1->Add(item1, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item2, 0, wxALIGN_CENTRE|wxALL, 5);
    this->SetAutoLayout(TRUE);
    this->SetSizer(box1);
    box1->Fit(this);
    box1->SetSizeHints(this);

}
BEGIN_EVENT_TABLE(ThicknessDialog, wxDialog)
END_EVENT_TABLE ()

ThicknessDialog::ThicknessDialog( wxWindow *parent, wxWindowID id,const wxString &title)
    :wxDialog( parent, id, title)
{
    wxBoxSizer *box1 = new wxBoxSizer( wxVERTICAL );
    wxStaticText *item1 = new  wxStaticText( this, ID_TEXT2, wxT("Choisir l'épaisseur du trait"),
                                             wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    wxSlider *item2 = new wxSlider( this, ID_SLIDER1, 5, 0, 10, wxDefaultPosition, wxSize(200, 60), wxSL_LABELS);
    wxButton *item3 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

    box1->Add(item1, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item2, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item3, 0, wxALIGN_CENTRE|wxALL, 5);
    this->SetAutoLayout(TRUE);
    this->SetSizer(box1);
    box1->Fit(this);
    box1->SetSizeHints(this);

}


BEGIN_EVENT_TABLE(TriangleDialog, wxDialog)
END_EVENT_TABLE ()

TriangleDialog::TriangleDialog( wxWindow *parent, wxWindowID id,const wxString &title)
    :wxDialog( parent, id, title)
{
    wxBoxSizer *box1 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *box2 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *box3 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText *item1 = new  wxStaticText( this, ID_TEXT3, wxT("Liste des triangles"),
                                             wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );



    wxString choices [] = { wxT("tri1"),wxT("tri2"),wxT("tri3")};
    wxListBox *item2 = new wxListBox( this, ID_LISTBOX1, wxDefaultPosition, wxSize(100, 250), 3 , choices, 0); // 3 : size(choices)

    box1->Add(item1, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item2, 0, wxALIGN_CENTRE|wxALL, 5);

    wxButton *item3 = new wxButton( this, ID_PROP, wxT("Propriétés"), wxDefaultPosition);
    wxButton *item4 = new wxButton( this, ID_SUPPR, wxT("Supprimer"), wxDefaultPosition);
    wxButton *item5 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);

    box2->Add(item3, 0, wxALIGN_CENTRE|wxALL, 5);
    box2->Add(item4, 0, wxALIGN_CENTRE|wxALL, 5);
    box2->Add(item5, 0, wxALIGN_CENTRE|wxALL, 5);

     
    box3->Add(box1, 0, wxALIGN_LEFT|wxALL, 5);
    box3->Add(box2, 0, wxALIGN_RIGHT|wxALIGN_CENTER|wxALL, 5);

    this->SetAutoLayout(TRUE);
    this->SetSizer(box3);
    box3->Fit(this);
    box3->SetSizeHints(this);

}

BEGIN_EVENT_TABLE(PropertiesDialog, wxDialog)
END_EVENT_TABLE ()

PropertiesDialog::PropertiesDialog( wxWindow *parent, wxWindowID id,const wxString &title)
    :wxDialog( parent, id, title)
{
    wxBoxSizer *box1 = new wxBoxSizer( wxVERTICAL );
    wxBoxSizer *box2 = new wxBoxSizer( wxHORIZONTAL );
    wxBoxSizer *box3 = new wxBoxSizer( wxVERTICAL );

    wxStaticText *item1 = new wxStaticText( this, ID_TEXT1, wxT("Identifiant du triangle"),
                                             wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    wxTextCtrl   *item2 = new wxTextCtrl( this, ID_TEXT_CTRL1, wxEmptyString,  wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );

    wxStaticText *item3 = new wxStaticText( this, ID_TEXT2, wxT("Epaisseur du trait"),
                                             wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    wxSpinCtrl   *item4 = new wxSpinCtrl(this , ID_SPIN_CTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize);

    box1->Add(item1, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item2, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item3, 0, wxALIGN_CENTRE|wxALL, 5);
    box1->Add(item4, 0, wxALIGN_CENTRE|wxALL, 5);


    wxString choices[] = {wxT("Rouge"),wxT("Bleu"),wxT("Vert")};
    wxRadioBox   *item5 = new wxRadioBox(this, ID_RADIO1, wxT("Couleur"), wxDefaultPosition, wxDefaultSize, 3, choices);
    box2->Add(box1, 0, wxALIGN_LEFT|wxALL, 5);
    box2->Add(item5, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton     *item6 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition);
    box3->Add(box2 , 0, wxALIGN_CENTRE|wxALL, 5);
    box3->Add(item6, 0, wxALIGN_CENTRE|wxALL, 5);

    this->SetAutoLayout(TRUE); 
    this->SetSizer(box3); 
    box3->Fit(this); 
    box3->SetSizeHints(this); 

}