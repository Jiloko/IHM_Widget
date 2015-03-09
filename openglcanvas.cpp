#include "wx/wx.h"
#include <wx/glcanvas.h>
#include "openglcanvas.h"
#include "GL/gl.h"
#include "mainframe.h"
#include "triangle.h"
#include "dialogs.h"

BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
    EVT_PAINT(OpenGLCanvas::OnPaint)
    EVT_SIZE(OpenGLCanvas::OnSize)
    EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
    EVT_MOTION(OpenGLCanvas::OnMouseMove)
    EVT_LEFT_DOWN(OpenGLCanvas::OnLeftDown)
    EVT_LEFT_UP(OpenGLCanvas::OnLeftUp)
    EVT_RIGHT_DOWN(OpenGLCanvas::OnRightDown)
    EVT_MENU(POPUP_PROP, OpenGLCanvas::OnProp)
    EVT_MENU(POPUP_DELETE, OpenGLCanvas::OnDelete)
END_EVENT_TABLE()

OpenGLCanvas::OpenGLCanvas(CMainFrame *parent, wxWindowID id, 
    const wxPoint& pos, const wxSize& size, long style,const wxString& name)
    :wxGLCanvas(parent, id, pos, size, style, name) 
{
    p = parent;
    state = 0;
    selected_triangle = -1;
}

void OpenGLCanvas::OnPaint( wxPaintEvent& event ) 
{
  wxPaintDC dc(this);
  SetCurrent();
  Draw();
  SwapBuffers();
}

void OpenGLCanvas::Draw() 
{
    int w, h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GetClientSize(&w, &h);
    glOrtho(-w/2., w/2., -h/2., h/2., -1., 3.);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClearColor( .3f, .4f, .6f, 1 );
    glClear( GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < p->nbtriangle; ++i)
    {
        Triangle triangle = p->tab_triangle[i];
        glBegin(GL_TRIANGLES);

        glColor3d((double)triangle.color.Red(), 
            (double)triangle.color.Green(), 
            (double)triangle.color.Blue());
        glVertex2i(triangle.p1.x, triangle.p1.y);
        glVertex2i(triangle.p2.x, triangle.p2.y);
        glVertex2i(triangle.p3.x, triangle.p3.y);
        glEnd();

        glLineWidth(triangle.thickness);
        glBegin(GL_LINE_LOOP);

        glColor3d(0,0,0);
        glVertex2i(triangle.p1.x,triangle.p1.y);
        glVertex2i(triangle.p2.x,triangle.p2.y);
        glVertex2i(triangle.p3.x,triangle.p3.y);
        glEnd();
        SwapBuffers();
    }

    glFlush();
}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{
    wxGLCanvas::OnSize(event);
    int w, h;
    GetClientSize(&w, &h);
}

void OpenGLCanvas::OnEraseBackground(wxEraseEvent& event) 
{

}

void OpenGLCanvas::OnMouseMove(wxMouseEvent& event)
{
    if(p->is_drawing) 
    {
        Draw();
        int w, h;
        GetClientSize(&w, &h);

        if(state == 1) 
        { 
            glLineWidth(p->thick);
            glBegin(GL_LINES);
            glColor3i(0,0,0);
            glVertex2i(triangle.p1.x,triangle.p1.y);
            glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
            glEnd();
        }
        else if(state == 2) 
        { 
            glLineWidth(p->thick);
            glBegin(GL_TRIANGLES);
            glColor3d((double)p->color->Red(),
                (double)p->color->Green(),
                (double)p->color->Blue());
            glVertex2i(triangle.p1.x,triangle.p1.y);
            glVertex2i(triangle.p2.x,triangle.p2.y);
            glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
            glEnd();

            glLineWidth(p->thick);
            glBegin(GL_LINE_LOOP);
            glColor3i(0,0,0);
            glVertex2i(triangle.p1.x,triangle.p1.y);
            glVertex2i(triangle.p2.x,triangle.p2.y);
            glVertex2i(event.GetX()-w/2,-event.GetY()+h/2);
            glEnd();
        }
        glFlush();
        SwapBuffers();
    }
}

void OpenGLCanvas::OnLeftUp(wxMouseEvent& event) 
{
    if(p->is_drawing) 
    {
        state++;

        int w, h;
        GetClientSize(&w, &h);

        if(state == 1) 
        {
            triangle.p1.x = event.GetX()-w/2;
            triangle.p1.y =- event.GetY()+h/2;
            triangle.thickness = p->thick;
            triangle.color= wxColour((int)p->color->Red(),
                (int)p->color->Green(),
                (int)p->color->Blue(),wxALPHA_OPAQUE);
        }
        else if(state == 2) 
        {
            triangle.p2.x = event.GetX()-w/2;
            triangle.p2.y =- event.GetY()+h/2;
        }
        else if(state == 3) 
        {
            triangle.p3.x=event.GetX()-w/2;
            triangle.p3.y=-event.GetY()+h/2;

            if(p->nbtriangle < MAX_TRI) 
            {
                wxString name;
                name << p->nbtriangle+1;
                p->tab_triangle[p->nbtriangle].name = wxT("T " + name);
                p->tab_triangle[p->nbtriangle].p1 = triangle.p1;
                p->tab_triangle[p->nbtriangle].p2 = triangle.p2;
                p->tab_triangle[p->nbtriangle].p3 = triangle.p3;
                p->tab_triangle[p->nbtriangle].color = triangle.color;
                p->tab_triangle[p->nbtriangle].thickness = triangle.thickness;
                p-> nbtriangle++;

                if(p->nbtriangle>0) 
                {    
                    wxMenuBar* menu_bar = p->GetMenuBar();
                    menu_bar->Enable(MENU_TRIANGLE,true);
                }
                this->Draw();
            }
            else 
                std::cout << "Cannot save any more triangle" << std::endl;
            
            state=0;
        }
    }
}

void OpenGLCanvas::OnLeftDown(wxMouseEvent& event) 
{
}

void OpenGLCanvas::OnRightDown(wxMouseEvent& event) 
{
    int w, h;
    GetClientSize(&w, &h);
    int x = event.GetX()-w/2;
    int y =- event.GetY()+h/2;
    selected_triangle = InTriangle(x, y);
    if(selected_triangle > -1) 
    {
        wxMenu popupMenu;

        popupMenu.Append(POPUP_PROP, wxT("Propriety triangle"));
        popupMenu.Append(POPUP_DELETE, wxT("Delete triangle"));

        PopupMenu(&popupMenu, event.GetX(), event.GetY());
    } 
    else 
    {
        wxMenu popupMenu;

        popupMenu.Append(MENU_OPEN, wxT("Open file"));
        popupMenu.Append(MENU_SAVE, wxT("Save file"));

        popupMenu.AppendSeparator();

        popupMenu.Append(MENU_COLOR, wxT("Current color"));
        popupMenu.Append(MENU_THICKNESS, wxT("Current thickness"));

        popupMenu.AppendSeparator();

        popupMenu.Append(MENU_TRIANGLE, wxT("Manage triangles"));

        PopupMenu( &popupMenu, event.GetX(), event.GetY() );
    }
}

int OpenGLCanvas::InTriangle(int x, int y) 
{
    for (int i = 0; i < p->nbtriangle; ++i) 
    {
        Triangle triangle = p->tab_triangle[i];
        if(triangle.IsPointInTriangle(x, y))
            return i;
    }
    return -1;
}

void OpenGLCanvas::OnDelete(wxCommandEvent& event)
{
    if (selected_triangle > -1) 
    {
        p->DeleteTriangle(selected_triangle);
        p->canvas->Draw();
    }
}

void OpenGLCanvas::OnProp(wxCommandEvent& event)
{
    if(selected_triangle > -1) 
    {
        PropDialog dialog(this, -1, wxT("Properties"), selected_triangle, 
            p->tab_triangle[selected_triangle]);
        dialog.ShowModal();
        Triangle triangle = p->tab_triangle[selected_triangle];
        triangle.name = dialog.prop_name->GetValue();
        triangle.thickness = dialog.prop_spin->GetValue();
        wxString t = dialog.prop_radio->GetStringSelection();
        triangle.color = wxColour(t);
        p->tab_triangle[selected_triangle] = triangle;
        p->canvas->Draw();
    }
}
