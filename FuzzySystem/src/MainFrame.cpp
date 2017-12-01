///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* MainLayout;
	MainLayout = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* TopLayout;
	TopLayout = new wxBoxSizer( wxHORIZONTAL );


	TopLayout->Add( 30, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* InputLaout1;
	InputLaout1 = new wxBoxSizer( wxVERTICAL );

	InputName1 = new wxStaticText( this, wxID_ANY, wxT("Input1"), wxDefaultPosition, wxDefaultSize, 0 );
	InputName1->Wrap( -1 );
	InputLaout1->Add( InputName1, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* InputCtrlLaout1;
	InputCtrlLaout1 = new wxBoxSizer( wxHORIZONTAL );

	Input1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	Input1->SetMaxLength( 10000 );
	Input1->SetValidator( wxTextValidator( wxFILTER_NUMERIC, &int_validator2 ) );

	InputCtrlLaout1->Add( Input1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	InputSpin1 = new wxSpinButton( this, wxID_ANY, wxDefaultPosition, wxSize( 20,20 ), 0 );
	InputCtrlLaout1->Add( InputSpin1, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );


	InputLaout1->Add( InputCtrlLaout1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );


	TopLayout->Add( InputLaout1, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* InputLaout2;
	InputLaout2 = new wxBoxSizer( wxVERTICAL );

	InputName2 = new wxStaticText( this, wxID_ANY, wxT("Input2"), wxDefaultPosition, wxDefaultSize, 0 );
	InputName2->Wrap( -1 );
	InputLaout2->Add( InputName2, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* InputCtrlLaout2;
	InputCtrlLaout2 = new wxBoxSizer( wxHORIZONTAL );

	Input2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	Input2->SetMaxLength( 10000 );
	Input2->SetValidator( wxTextValidator( wxFILTER_NUMERIC, &int_validator1 ) );

	InputCtrlLaout2->Add( Input2, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	InputSpin2 = new wxSpinButton( this, wxID_ANY, wxDefaultPosition, wxSize( 20,20 ), 0 );
	InputCtrlLaout2->Add( InputSpin2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5 );


	InputLaout2->Add( InputCtrlLaout2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );


	TopLayout->Add( InputLaout2, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	MainLayout->Add( TopLayout, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	wxBoxSizer* ButtonBox;
	ButtonBox = new wxBoxSizer( wxVERTICAL );

	StartBtn = new wxButton( this, wxID_ANY, wxT("start"), wxDefaultPosition, wxSize( 200,25 ), 0 );
	ButtonBox->Add( StartBtn, 0, wxALL, 5 );

	StopBtn = new wxButton( this, wxID_ANY, wxT("stop"), wxDefaultPosition, wxSize( 200,25 ), 0 );
	ButtonBox->Add( StopBtn, 0, wxALL, 5 );


	MainLayout->Add( ButtonBox, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 10 );

	wxBoxSizer* BottomLayout;
	BottomLayout = new wxBoxSizer( wxVERTICAL );

	OutputName = new wxStaticText( this, wxID_ANY, wxT("Output"), wxDefaultPosition, wxDefaultSize, 0 );
	OutputName->Wrap( -1 );
	BottomLayout->Add( OutputName, 0, wxALL, 5 );

	Output = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CHARWRAP|wxTE_MULTILINE|wxTE_WORDWRAP );
	BottomLayout->Add( Output, 1, wxALL|wxEXPAND, 5 );


	MainLayout->Add( BottomLayout, 1, wxEXPAND, 5 );


	this->SetSizer( MainLayout );
	this->Layout();
	menubar = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_choosefile;
	m_choosefile = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Choose File") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_choosefile );

	menubar->Append( m_menu1, wxT("File") );

	this->SetMenuBar( menubar );


	this->Centre( wxBOTH );

	// Connect Events
	InputSpin1->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MainFrame::InputSpin1DownClick ), NULL, this );
	InputSpin1->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MainFrame::InputSpin1UpClick ), NULL, this );
	InputSpin2->Connect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MainFrame::InputSpin2DownClick ), NULL, this );
	InputSpin2->Connect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MainFrame::InputSpin2UpClick ), NULL, this );
	StartBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::StartButtonClick ), NULL, this );
	StopBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::StopBtnClick ), NULL, this );
	this->Connect( m_choosefile->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::selectFile ) );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	InputSpin1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MainFrame::InputSpin1DownClick ), NULL, this );
	InputSpin1->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MainFrame::InputSpin1UpClick ), NULL, this );
	InputSpin2->Disconnect( wxEVT_SCROLL_LINEDOWN, wxSpinEventHandler( MainFrame::InputSpin2DownClick ), NULL, this );
	InputSpin2->Disconnect( wxEVT_SCROLL_LINEUP, wxSpinEventHandler( MainFrame::InputSpin2UpClick ), NULL, this );
	StartBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::StartButtonClick ), NULL, this );
	StopBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::StopBtnClick ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::selectFile ) );

}
