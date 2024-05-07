#pragma once

#include <map>

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/listbook.h>
#include <wx/filename.h>

#include "./Canvas.h"
// при выходе мыши во время таскания не отвязываться от картинки
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
		wxButton* loadImageButton = new wxButton(panel, wxID_ANY, "Load Image");

		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(loadImageButton, 0, wxEXPAND | wxALL, 3);

		panel->SetSizer(sizer);

		loadImageButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpenButtonClick, this);

		return panel;
	}

	void OnOpenButtonClick(wxCommandEvent& event)
	{
		auto dialog = wxFileDialog(
			this, "Load...", "", "", 
			"All files (*.*)|*.*", 
			wxFD_OPEN | wxFD_FILE_MUST_EXIST
		);
		if (dialog.ShowModal() == wxID_CANCEL)
			return;

		wxFileName fileName(dialog.GetPath());
		if (!m_imageFileExtensions.contains(fileName.GetExt()))
		{
			wxMessageBox("Invalid file extension, supports: png, jpeg, bmp, gif");
			return;
		}

		wxBitmap bitmap(dialog.GetPath(), m_imageFileExtensions.at(fileName.GetExt()));

		if (!bitmap.IsOk())
		{
			wxMessageBox("Failed to load file");
			return;
		}

		m_canvas->AddImage(bitmap);
	}

	inline const static std::unordered_map<wxString, wxBitmapType> m_imageFileExtensions = {
		{"png", wxBITMAP_TYPE_PNG},
		{"jpeg", wxBITMAP_TYPE_JPEG},
		{"gif", wxBITMAP_TYPE_GIF},
		{"bmp", wxBITMAP_TYPE_BMP},
	};
	Canvas* m_canvas;
};