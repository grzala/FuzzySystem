/***************************************************************
 * Name:      wxtestApp.cpp
 * Purpose:   Code for Application Class
 * Author:    a ()
 * Created:   2017-10-20
 * Copyright: a ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <Log.h>
#include "main.h"

IMPLEMENT_APP(wxtestApp);

bool wxtestApp::OnInit()
{
    //set_log_level(log_level::BUILD);

    FuzzyFrame* frame = new FuzzyFrame(nullptr);

    frame->Show();

    return true;
}
