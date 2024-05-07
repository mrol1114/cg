#pragma once

#include <wx/graphics.h>

#include "./IGraphicObject.h"

class HouseGraphicObject : public IGraphicObject
{
public:
	HouseGraphicObject(wxRect2DDouble boundaries)
		: m_boundaries(boundaries)
	{
	}

	wxAffineMatrix2D& GetMatrix()
	{
		return m_matrix;
	}

private:
	void Draw(wxGraphicsContext* gc)override
	{
		wxColor homeColor(205, 133, 63);

		gc->SetBrush(*wxYELLOW_BRUSH);

		gc->DrawRectangle(m_boundaries.m_x + 40, m_boundaries.m_y + 40,
			m_boundaries.m_width - 40, m_boundaries.m_height - 120
		);
		DrawTriangle(gc,
			{ m_boundaries.m_x + m_boundaries.m_width / 4, m_boundaries.m_y + m_boundaries.m_height / 4 },
			{ m_boundaries.m_x + m_boundaries.m_width / 2, m_boundaries.m_y },
			{ m_boundaries.m_x + m_boundaries.m_width / 4 * 3, m_boundaries.m_y + m_boundaries.m_height / 4 }
		);
	}

	void Move()override
	{

	}

	void DrawTriangle(wxGraphicsContext* gc, wxPoint2DDouble p1, wxPoint2DDouble p2, wxPoint2DDouble p3)
	{
		auto path = gc->CreatePath();

		wxPoint2DDouble points[3] = { p1, p2, p3 };

		gc->DrawLines(3, points);
	}

	wxAffineMatrix2D m_matrix;
	wxRect2DDouble m_boundaries = { 0, 0 , 200, 200 };
};