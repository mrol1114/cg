#pragma once

#include <memory>
#include <list>

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "./IGraphicObject.h"
#include "./HouseGraphicObject.h"

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
				object->Draw(gc);
			}

			delete gc;
		}
	}

	void OnMouseDown(wxMouseEvent& event)
	{
		auto clickedObjectIter = std::find_if(m_graphicObjects.rbegin(), m_graphicObjects.rend(), 
			[event](std::shared_ptr<IGraphicObject>& obj)
			{
				return obj->GetFrame().Contains(event.GetPosition());
			}
		);

		if (clickedObjectIter != m_graphicObjects.rend())
		{
			m_draggedObj = clickedObjectIter->get();
			m_lastDragOrigin = event.GetPosition();
		}
	}

	void OnMouseMove(wxMouseEvent& event)
	{
		if (m_draggedObj)
		{
			auto dragVector = event.GetPosition() - m_lastDragOrigin;

			m_draggedObj->SetFrame({
				dragVector.m_x + m_draggedObj->GetFrame().m_x,
				dragVector.m_y + m_draggedObj->GetFrame().m_y,
				m_draggedObj->GetFrame().m_width,
				m_draggedObj->GetFrame().m_height
			});

			m_lastDragOrigin = event.GetPosition();
			Refresh();
		}
	}

	void OnMouseUp(wxMouseEvent& event)
	{
		FinishDrag();
	}

	void OnMouseLeave(wxMouseEvent& event)
	{
		FinishDrag();
	}

	void FinishDrag()
	{
		m_draggedObj = nullptr;
	}

	std::list<std::shared_ptr<IGraphicObject>> m_graphicObjects = {};
	IGraphicObject* m_draggedObj;
	wxPoint2DDouble m_lastDragOrigin;
};