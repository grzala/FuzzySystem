///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/spinbutt.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* InputName1;
		wxTextCtrl* Input1;
		wxSpinButton* InputSpin1;
		wxStaticText* InputName2;
		wxTextCtrl* Input2;
		wxSpinButton* InputSpin2;
		wxButton* StartBtn;
		wxButton* StopBtn;
		wxStaticText* OutputName;
		wxTextCtrl* Output;
		wxMenuBar* menubar;
		wxMenu* m_menu1;

		// Virtual event handlers, overide them in your derived class
		virtual void InputSpin1DownClick( wxSpinEvent& event ) { event.Skip(); }
		virtual void InputSpin1UpClick( wxSpinEvent& event ) { event.Skip(); }
		virtual void InputSpin2DownClick( wxSpinEvent& event ) { event.Skip(); }
		virtual void InputSpin2UpClick( wxSpinEvent& event ) { event.Skip(); }
		virtual void StartButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void StopBtnClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void selectFile( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxString int_validator2;
		wxString int_validator1;

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Fuzzy"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,300 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );

		~MainFrame();

};

#endif //__MAINFRAME_H__
