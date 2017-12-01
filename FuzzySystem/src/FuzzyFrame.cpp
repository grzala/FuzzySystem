#include "FuzzyFrame.h"

using namespace fsm;

FuzzyFrame::FuzzyFrame(wxWindow* parent)
: MainFrame(parent)
{
    //init fuzzy system
    fm = new FuzzySystem();

}

FuzzyFrame::~FuzzyFrame()
{
    delete fm;
}


void FuzzyFrame::run_thread()
{
    if (running_thread)
    {
        stop_thread = true;
        free(running_thread);
    }
    stop_thread = false;
    std::thread t( [this] { this->run(); } );
    running_thread = &t;
    running_thread->detach();
}

void FuzzyFrame::run()
{
    while(true)
    {
        float val1, val2;
        try {
            val1 = stof(std::string(Input1->GetValue().mb_str()));
        } catch(std::exception& e) {
            val1 = 0;
            Input1->SetValue(wxString("0"));
        }
        try {
            val2 = stof(std::string(Input2->GetValue().mb_str()));
        } catch (std::exception& e) {
            val2 = 0;
            Input2->SetValue(wxString("0"));
        }

        try {
            fm->run(std::vector<float>{val1, val2});
            float result = fm->getResults();
            setResults(result);
        } catch (const exception& e) {
            cout << e.what() << endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (stop_thread) break;
    }
}

void FuzzyFrame::StartButtonClick( wxCommandEvent& event )
{
    run_thread();
}

void FuzzyFrame::setResults(string r)
{
    string cur_str = string(Output->GetValue().mb_str());
    cur_str.append("\n");
    cur_str.append(r);

    //prevent very long strings
    if (cur_str.size() > max_output_chars)
    {
        int to_erase = cur_str.size() - max_output_chars;
        cur_str.erase(cur_str.begin(), cur_str.begin()+to_erase);

        while (cur_str.at(0) != '\n' && cur_str.size() > 0)
        {
            cur_str.erase(cur_str.begin(), cur_str.begin()+1);
        }
        if (cur_str.at(0)  == '\n') cur_str.erase(cur_str.begin(), cur_str.begin()+1);
    }

    Output->SetValue(wxString(cur_str));
    Output->ShowPosition(Output->GetLastPosition()); //scroll to bottom
}


void FuzzyFrame::StopBtnClick( wxCommandEvent& event )
{
    stop_thread = true;
}


void FuzzyFrame::InputSpin1DownClick( wxSpinEvent& event )
{
    float val = stof(std::string(Input1->GetValue().mb_str()));
    val -= 1;
    Input1->SetValue(wxString(to_string(val)));
}

void FuzzyFrame::InputSpin1UpClick( wxSpinEvent& event )
{
    float val = stof(std::string(Input1->GetValue().mb_str()));
    val += 1;
    Input1->SetValue(wxString(to_string(val)));
}

void FuzzyFrame::InputSpin2DownClick( wxSpinEvent& event )
{
    float val = stof(std::string(Input2->GetValue().mb_str()));
    val -= 1;
    Input2->SetValue(wxString(to_string(val)));
}

void FuzzyFrame::InputSpin2UpClick( wxSpinEvent& event )
{
    float val = stof(std::string(Input2->GetValue().mb_str()));
    val += 1;
    Input2->SetValue(wxString(to_string(val)));
}

void FuzzyFrame::selectFile(wxCommandEvent& event)
{
    std::cout << "SELECtiNG File";
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
		_("Text files (*.txt)|*.txt|C++ Source Files (*.cpp, *.cxx)|*.cpp;*.cxx|C Source files (*.c)|*.c|C header files (*.h)|*.h"),
		wxFD_OPEN, wxDefaultPosition);

	// Creates a "open file" dialog with 4 file types
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		wxString path = OpenDialog->GetPath();

        fm->initSettingsFromFile(path);

        auto names = fm->getFuzzyInNames();

        InputName1->SetLabelText(wxString(names[0]));
        InputName2->SetLabelText(wxString(names[1]));
        OutputName->SetLabelText(wxString(fm->getFuzzyOutName()));

        //init with values loaded from file (or 0 0);
        auto curVals = fm->getCurrentValues();
        Input1->SetValue(wxString(to_string(curVals[0])));
        Input2->SetValue(wxString(to_string(curVals[1])));
	}

	// Clean up after ourselves
	OpenDialog->Destroy();
}

void FuzzyFrame::OnClose(wxCloseEvent& event)
{
    stop_thread  = true;

    wxThread::This()->Sleep(10);

    delete fm;
}
