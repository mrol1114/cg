#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const std::string& title, const wxPoint& pos, const wxSize& size)
		: wxFrame(nullptr, wxID_ANY, title, pos, size)
	{
		this->SetBackgroundStyle(wxBG_STYLE_PAINT);

		Bind(wxEVT_PAINT, &MainFrame::OnPaint, this, wxID_ANY);
	}

	void Run()
	{
		while (true)
		{
			m_sign = m_MAXIMUM_DIF < m_dy ? -1 : m_sign;
			m_sign = m_MAXIMUM_DIF < 0 ? 1 : m_sign;
			m_dy += m_sign;
			Refresh();
		}
	}

private:
	void OnPaint(wxPaintEvent& evt)
	{
		wxAutoBufferedPaintDC dc(this);
		dc.Clear();

		wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

        if (gc)
        {
			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			gc->SetPen(wxPen(wxColor(0, 0, 0), 10));
            gc->DrawEllipse(80, 80, 40, 50); // b

			gc->SetBrush(*wxBLACK_BRUSH);
			gc->SetPen(*wxTRANSPARENT_PEN);
            gc->DrawRectangle(70, 50, 10, 80);
            gc->DrawRectangle(70, 50, 50, 10);

			gc->SetBrush(*wxTRANSPARENT_BRUSH);
			gc->SetPen(wxPen(wxColor(0, 0, 0), 10));
            gc->DrawEllipse(140, 50, 50, 80); // o

			gc->SetBrush(*wxBLACK_BRUSH);
			gc->SetPen(*wxTRANSPARENT_PEN);
            gc->DrawRectangle(210, 50, 10, 80); // H
            gc->DrawRectangle(220, 85, 30, 10);
            gc->DrawRectangle(250, 50, 10, 80);

			// use unique pointer
            delete gc;
        }
	}

	int const m_MAXIMUM_DIF = 50;

	int m_sign = 1;
	int m_dy = 0;
};