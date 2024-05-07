#pragma once

#include <vector>
#include <optional>

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "./Path.h"

class Canvas : public wxPanel
{
public:
	Canvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
		: wxPanel(parent, id, pos, size)
	{
		this->SetBackgroundStyle(wxBG_STYLE_PAINT);

		Bind(wxEVT_PAINT, &Canvas::OnPaint, this, id);
		Bind(wxEVT_LEFT_DOWN, &Canvas::OnMouseDown, this, id);
		Bind(wxEVT_MOTION, &Canvas::OnMouseMove, this, id);
		Bind(wxEVT_LEFT_UP, &Canvas::OnMouseUp, this, id);
		Bind(wxEVT_LEAVE_WINDOW, &Canvas::OnMouseLeave, this, id);
	}

	void SetImage(const wxBitmap& bitmap)
	{
		m_image = bitmap;
		auto imageSize = m_image.value().GetSize();

		wxBitmap::Rescale(m_image.value(), { 
			m_image.value().GetSize().GetWidth() * m_image.value().GetSize().GetWidth() / GetSize().GetWidth(),
			m_image.value().GetSize().GetHeight() * m_image.value().GetSize().GetHeight() / GetSize().GetHeight()
		});
		m_currentPath.points = {};
		m_isNewImage = true;
		Refresh();
	}

	void SetColor(wxColor color)
	{
		m_currentPath.color = color;
	}

	void InitNewImage()
	{
		m_image = wxBitmap(GetSize() * GetContentScaleFactor());
		m_currentPath.points = {};
		m_isNewImage = true;
		Refresh();
	}

	const std::optional<wxBitmap>& GetImage()
	{
		return m_image;
	}

private:
	void OnPaint(wxPaintEvent& evt)
	{
		if (!m_image.has_value())
			return;

		wxAutoBufferedPaintDC dc(this);
		dc.SelectObject(m_image.value());
		if (m_isNewImage)
		{
			dc.Clear();
			dc.SetBackground(*wxTRANSPARENT_BRUSH);
			m_isNewImage = false;
		}

		wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
		if (gc)
		{
			DrawOnContext(gc);
			delete gc;
		}
	}

	void OnMouseDown(wxMouseEvent& event)
	{
		if (!m_image.has_value())
			return;

		m_currentPath.points = {};
		m_isDrawing = true;
	}

	void OnMouseMove(wxMouseEvent& event)
	{
		if (m_isDrawing)
		{
			auto point = event.GetPosition();

			m_currentPath.points.push_back(point);
			Refresh();
		}
	}

	void OnMouseUp(wxMouseEvent& event)
	{
		m_isDrawing = false;
		m_currentPath.points = {};
	}

	void OnMouseLeave(wxMouseEvent& event)
	{
		m_isDrawing = false;
		m_currentPath.points = {};
	}

	void DrawOnContext(wxGraphicsContext* gc)
	{
		auto& pointsVector = m_currentPath.points;
		if (pointsVector.size() > 1)
		{
			gc->SetPen(wxPen(
				m_currentPath.color,
				3));
			gc->StrokeLines(pointsVector.size(), pointsVector.data());
		}
	}

	std::optional<wxBitmap> m_image;
	bool m_isDrawing = false;
	bool m_isNewImage = false;
	Path m_currentPath = { {}, *wxBLACK };
};