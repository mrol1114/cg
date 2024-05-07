#pragma once

#include "./IGraphicObject.h"

class ImageGraphicObject : public IGraphicObject
{
public:
	ImageGraphicObject(const wxBitmap& bitmap, wxRect2DDouble frame)
		: m_bitmap(bitmap)
		, m_frame(frame)
	{

	}

private:
	void Draw(wxGraphicsContext* gc)override
	{
		gc->DrawBitmap(m_bitmap, m_frame.m_x, m_frame.m_y, m_frame.m_width, m_frame.m_height);
	}

	wxRect2DDouble GetFrame()const override
	{
		return m_frame;
	}

	void SetFrame(wxRect2DDouble frame)override
	{
		m_frame = frame;
	}

	wxBitmap m_bitmap;
	wxRect2DDouble m_frame;
};