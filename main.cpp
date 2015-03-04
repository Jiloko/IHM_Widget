
#include "wx/wx.h" 
#include <wx/menu.h>

#include "mainframe.h"
#include "dialogs.h"

class MyApp: public wxApp 
{
    virtual bool OnInit();

	CMainFrame *m_MainFrame;

};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit() 
{
    //Main menu
	m_MainFrame = new CMainFrame( wxString("Fenêtre", wxConvUTF8), wxPoint(50,50), wxSize(450,340) );

    m_MainFrame->CreateMyToolbar();
    m_MainFrame->Show(TRUE);
    wxMenuBar *menu_bar = new wxMenuBar;
    wxMenu *file_menu = new wxMenu;
    wxMenu *display_menu = new wxMenu;
    wxMenu *options_menu = new wxMenu;
    wxMenu *help_menu = new wxMenu;

    menu_bar->Append(file_menu, wxT("Fichier"));
    menu_bar->Append(display_menu, wxT("Affichage"));
    menu_bar->Append(options_menu, wxT("Options"));
    menu_bar->Append(help_menu, wxT("Aide"));

    file_menu->Append(MENU_NEW, wxT("Nouveau\tCtrl-N"));
    file_menu->AppendSeparator();
    file_menu->Append(MENU_OPEN, wxT("Ouvrir\tCtrl-O"));
    file_menu->Append(MENU_SAVE, wxT("Sauvegarder\tCtrl-S"));
    file_menu->AppendSeparator();
    file_menu->Append(MENU_EXIT, wxT("Quitter\tCtrl-Q"));

    display_menu->AppendCheckItem(MENU_TOOLBAR, wxT("Barre d'outils\tCtrl-B")),

    options_menu->Append(MENU_SIZE, wxT("Taille\tCtrl-E"));
    options_menu->Append(MENU_COLOR, wxT("Couleur\tCtrl-R"));
    options_menu->Append(MENU_MANAGE, wxT("Gestion\tCtrl-G"));

    help_menu->Append(MENU_VERSION, wxT("Version"));

    display_menu->Check(MENU_TOOLBAR,TRUE);

    //menu_bar->Enable(MENU_MANAGE,false);

    m_MainFrame->SetMenuBar(menu_bar);

    
    
	return TRUE;
} 


