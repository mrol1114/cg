#pragma once

class IDrawable
{
public:
	virtual void Draw() = 0;
	virtual void Init() = 0;

	virtual ~IDrawable() = default;
};