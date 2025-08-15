#ifndef __Ball_H__
#define __Ball_H__

#include "mixr/graphics/Shapes.hpp"
#include "mixr/base/colors/Color.hpp"

class Ball final : public mixr::graphics::Circle
{
	DECLARE_SUBCLASS(Ball, mixr::graphics::Circle);

public:
	Ball();
	bool event(const int event, mixr::base::Object* const obj = nullptr);
	double getX();
	double getY();
	double getDx();
	double getDy();
	bool getDropped();
	void setDropped(bool flag);
	void setX(double num);
	void setY(double num);
	void setDx(double num);
	void setDy(double num);

private:
	bool moveLeft();
	bool moveRight();
	int color{1};
	bool changeColor();
	bool drop();
	double posX{ 0 }, posY{ 7 };
	double dx{0}, dy{0};
	bool dropped{};
};
#endif