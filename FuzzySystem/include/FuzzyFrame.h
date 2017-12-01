#ifndef FUZZYFRAME_H
#define FUZZYFRAME_H

#include <iostream>
#include <thread>
#include <chrono>

#include <wx/thread.h>
#include <wx/filedlg.h>

#include "MainFrame.h"

#include "FuzzySystem.h"

using namespace fsm;

class FuzzyFrame: public MainFrame
{
    public:
        FuzzyFrame(wxWindow* parent);
        ~FuzzyFrame();

    private:

		void StartButtonClick( wxCommandEvent& event ) override;
		void StopBtnClick( wxCommandEvent& event ) override;
		void InputSpin1DownClick( wxSpinEvent& event ) override;
		void InputSpin1UpClick( wxSpinEvent& event ) override;
		void InputSpin2DownClick( wxSpinEvent& event ) override;
		void InputSpin2UpClick( wxSpinEvent& event ) override;
		void selectFile( wxCommandEvent& event ) override;

		void OnClose(wxCloseEvent& event);

		FuzzySystem* fm;

		void setResults(string r);
		void setResults(float r) {setResults(to_string(r));}

		void run();
		void run_thread();
		std::thread* running_thread;
		bool stop_thread = true;

		const unsigned int max_output_chars = 600;

};

#endif // FUZZYFRAME_H
