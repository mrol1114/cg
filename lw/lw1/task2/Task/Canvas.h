#pragma once

#include <memory>
#include <list>

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "./IGraphicObject.h"
#include "./HouseGraphicObject.h"

class Canvas : public wxFrame
{
public:
	Canvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
		: wxFrame(parent, id, "", pos, size)
	{
		this->SetBackgroundStyle(wxBG_STYLE_PAINT);

		Bind(wxEVT_PAINT, &Canvas::OnPaint, this, wxID_ANY);
	}

	void AddHouse()
	{
		m_graphicObjects.push_back(std::make_shared<HouseGraphicObject>(
			wxRect2DDouble{ 200, 200, 200, 200 }
		));
		Refresh();
	}

private:
	void OnPaint(wxPaintEvent& evt)
	{
		wxAutoBufferedPaintDC dc(this);
		dc.Clear();

		wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

		if (gc)
		{
			for (const auto& object : m_graphicObjects)
			{
				gc->SetTransform(gc->CreateMatrix(object->GetMatrix()));
				object->Draw(gc);
			}

			delete gc;
		}
	}

	void OnMouseDown(wxMouseEvent& event)
	{
	}

	void OnMouseMove(wxMouseEvent& event)
	{

	}

	void OnMouseUp(wxMouseEvent& event)
	{
	}

	void OnMouseLeave(wxMouseEvent& event)
	{

	}

	void finishDrag()
	{

	}

	std::list<std::shared_ptr<IGraphicObject>> m_graphicObjects;
	std::shared_ptr<IGraphicObject> m_draggedObj;
	wxPoint2DDouble m_lastDragOrigin;
};