#pragma once

#include <wx/graphics.h>

class IGraphicObject
{
public:
	virtual void Draw(wxGraphicsContext* gc) = 0;
	virtual void Move() = 0;

	virtual wxAffineMatrix2D& GetMatrix() = 0;
	virtual wxRect2DDouble& GetBoundaries() = 0;
};