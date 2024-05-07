#pragma once

#include "./IGraphicObject.h"

class CircleGraphicObject : public IGraphicObject
{
public:

private:
	void Draw(wxGraphicsContext* gc)override
	{
		gc->CreatePath();

		gc->DrawRectangle();
	}

	wxRect2DDouble GetFrame()const override
	{

	}

	void SetFrame(wxRect2DDouble frame)override
	{

	}

};