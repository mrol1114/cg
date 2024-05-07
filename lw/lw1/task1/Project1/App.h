#pragma once

#include <wx/wx.h>
#include "./MainFrame.h"

class App : public wxApp {
public:
    bool OnInit() {
        MainFrame* mainFrame = new MainFrame("Graphics", wxDefaultPosition, wxSize(660, 590));

        mainFrame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);