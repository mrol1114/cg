#pragma once

#include <wx/graphics.h>

#include "./IGraphicObject.h"

class HouseGraphicObject : public IGraphicObject
{
public:
	HouseGraphicObject(wxRect2DDouble frame)
		: m_frame(frame)
	{
	}

private:
	void Draw(wxGraphicsContext* gc) override
	{
		gc->SetBrush(*wxBLACK_BRUSH);
		gc->DrawRectangle(m_frame.m_x + 40, m_frame.m_y + 40,
			m_frame.m_width - 40, m_frame.m_height - 120
		);
		gc->DrawRectangle(m_frame.m_x + 120, m_frame.m_y + 10,
			20, 50
		);
		DrawTriangle(gc,
			{ m_frame.m_x + m_frame.m_width / 4, m_frame.m_y + m_frame.m_height / 4 },
			{ m_frame.m_x + m_frame.m_width / 2, m_frame.m_y },
			{ m_frame.m_x + m_frame.m_width / 4 * 3, m_frame.m_y + m_frame.m_height / 4 }
		);

		gc->SetBrush(*wxWHITE_BRUSH);
		gc->DrawRectangle(m_frame.m_x + 60, m_frame.m_y + 70,
			30, m_frame.m_height - 150
		);
		gc->DrawRectangle(m_frame.m_x + 120, m_frame.m_y + 70,
			30, 30
		);

		gc->SetBrush(*wxBLACK_BRUSH);
		DrawFence(gc);
	}

	void DrawFence(wxGraphicsContext* gc)
	{
		double leftBorderOffset = 0;
		while (leftBorderOffset < m_frame.m_width)
		{
			gc->DrawRectangle(m_frame.m_x + leftBorderOffset, m_frame.m_y + 130,
				m_FENCE_WIDTH, m_frame.m_height - 130
			);
			leftBorderOffset += m_FENCE_WIDTH + m_FENCE_GAP;
		}
	}

	void DrawTriangle(wxGraphicsContext* gc, wxPoint2DDouble p1, wxPoint2DDouble p2, wxPoint2DDouble p3)
	{
		auto path = gc->CreatePath();

		wxPoint2DDouble points[3] = { p1, p2, p3 };

		gc->DrawLines(3, points);
	}

	wxRect2DDouble GetFrame() const override
	{
		return m_frame;
	}

	virtual void SetFrame(wxRect2DDouble frame) override
	{
		m_frame = frame;
	}

	static inline const double m_FENCE_WIDTH = 30;
	static inline const double m_FENCE_GAP = 5;
	wxRect2DDouble m_frame;
};