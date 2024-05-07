#pragma once

#include <map>

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/listbook.h>
#include <wx/filename.h>
#include <wx/colordlg.h>

#include "./Canvas.h"
// сохранять пропорции картинки
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
		wxButton* loadButton = new wxButton(panel, wxID_ANY, "Load");
		wxButton* newButton = new wxButton(panel, wxID_ANY, "New");
		wxButton* saveAsButton = new wxButton(panel, wxID_ANY, "Save As");
		wxButton* pickColorButton = new wxButton(panel, wxID_ANY, "Pick color");

		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(loadButton, 0, wxEXPAND | wxALL, 3);
		sizer->Add(newButton, 0, wxEXPAND | wxALL, 3);
		sizer->Add(saveAsButton, 0, wxEXPAND | wxALL, 3);
		sizer->Add(pickColorButton, 0, wxEXPAND | wxALL, 3);

		panel->SetSizer(sizer);

		loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadButtonClick, this);
		saveAsButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveAsButtonClick, this);
		newButton->Bind(wxEVT_BUTTON, &MainFrame::OnNewButtonClick, this);
		pickColorButton->Bind(wxEVT_BUTTON, &MainFrame::OnPickColorButtonClick, this);

		return panel;
	}

	void OnLoadButtonClick(wxCommandEvent& event)
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
			wxMessageBox("Invalid file extension, supports: png, jpeg, bmp");
			return;
		}

		wxBitmap bitmap(dialog.GetPath(), m_imageFileExtensions.at(fileName.GetExt()));

		if (!bitmap.IsOk())
		{
			wxMessageBox("Failed to load file");
			return;
		}

		m_canvas->SetImage(bitmap);
	}

	void OnSaveAsButtonClick(wxCommandEvent& event)
	{
		if (!m_canvas->GetImage().has_value())
		{
			wxMessageBox("Image is not open");
			return;
		}

		wxFileDialog saveFileDialog(this, _("Save drawing"), "", "",
			"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return;

		wxBitmap bitmap = m_canvas->GetImage().value();
		bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	}

	void OnPickColorButtonClick(wxCommandEvent& event)
	{
		wxColourDialog colorDialog(this);
		if (colorDialog.ShowModal() == wxID_CANCEL)
			return;

		m_canvas->SetColor(colorDialog.GetColourData().GetColour());
	}

	void OnNewButtonClick(wxCommandEvent& event)
	{
		m_canvas->InitNewImage();
	}

	inline const static std::unordered_map<wxString, wxBitmapType> m_imageFileExtensions = {
		{"png", wxBITMAP_TYPE_PNG},
		{"jpeg", wxBITMAP_TYPE_JPEG},
		{"bmp", wxBITMAP_TYPE_BMP},
	};
	Canvas* m_canvas;
};