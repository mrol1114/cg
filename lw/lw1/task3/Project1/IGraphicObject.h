#pragma once

#include <wx/graphics.h>

class IGraphicObject
{
public:
	virtual void Draw(wxGraphicsContext* gc) = 0;

	virtual wxRect2DDouble GetFrame() const = 0;
	virtual void SetFrame(wxRect2DDouble frame) = 0;
};