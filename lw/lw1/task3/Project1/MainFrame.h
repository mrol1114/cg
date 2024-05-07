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
		wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

		auto buttonPanel = CreateButtonPanel(this);
		m_canvas = new Canvas(this, wxID_ANY, wxDefaultPosition, wxSize(640, 480));

		mainSizer->Add(buttonPanel, 0, wxALL, 10);
		mainSizer->Add(m_canvas, 0, wxALL, 10);
		this->SetSizerAndFit(mainSizer);
	}

private:
	wxPanel* CreateButtonPanel(wxWindow* parent)
	{
		wxPanel* panel = new wxPanel(parent);
		wxButton* drawPictureButton = new wxButton(panel, wxID_ANY, "DrawPicture");

		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(drawPictureButton, 0, wxEXPAND | wxALL, 3);

		panel->SetSizer(sizer);

		drawPictureButton->Bind(wxEVT_BUTTON, &MainFrame::OnDrawPictureClick, this);

		return panel;
	}

	void OnDrawPictureClick(wxCommandEvent& event)
	{
		m_canvas->AddHouse();
	}

	Canvas* m_canvas;
};