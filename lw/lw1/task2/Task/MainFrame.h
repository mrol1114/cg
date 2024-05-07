#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/listbook.h>

#include "./Canvas.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const std::string& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(nullptr, wxID_ANY, title, pos, size)
	{
		auto tabs = new wxListbook(this, wxID_ANY, wxDefaultPosition, this->FromDIP(wxSize(640, 480)), wxNB_TOP);
		tabs->SetInternalBorder(0);

		wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(tabs, 1, wxEXPAND);

		wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

		wxPanel* drawingPaneWithButtons = new wxPanel(tabs);
		auto buttonPanel = CreateButtonPanel(drawingPaneWithButtons);
		auto canvas = new Canvas(drawingPaneWithButtons, wxID_ANY, wxDefaultPosition, wxDefaultSize);

		sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 0);
		sizer->Add(canvas, 1, wxEXPAND | wxALL, 0);
	}

private:
	wxPanel* CreateButtonPanel(wxWindow* parent)
	{
		wxPanel* panel = new wxPanel(parent);
		wxButton* addRectButton = new wxButton(panel, wxID_ANY, "Draw");

		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(addRectButton, 0, wxEXPAND | wxALL, 3);

		panel->SetSizer(sizer);

		addRectButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClick, this);

		return panel;
	}

	void OnAddButtonClick(wxCommandEvent& event)
	{
		m_canvas->AddHouse();
	}

	Canvas* m_canvas;
};