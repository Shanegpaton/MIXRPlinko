#include "Ball.hpp"

IMPLEMENT_SUBCLASS(Ball, "Ball")
EMPTY_SLOTTABLE(Ball, "Ball")
EMPTY_COPYDATA(Ball)
EMPTY_DELETEDATA(Ball)

BEGIN_EVENT_HANDLER(Ball)
ON_EVENT(3001, drop)
ON_EVENT(3002, changeColor);
ON_EVENT(3005, moveLeft)
ON_EVENT(3006, moveRight)
END_EVENT_HANDLER()

Ball::Ball()
{
    STANDARD_CONSTRUCTOR()
    setRadius(.9);
    setSlices(32);
}

bool Ball::changeColor() {
    mixr::base::Color* newColor = new mixr::base::Color();
    if (color == 0)
    {
        newColor->setRed(0.95);
        newColor->setGreen(0.61);
        newColor->setBlue(.73);  // Pastel magenta
        color = 1;
    }
    else if (color == 1)
    {
        newColor->setRed(1.0);
        newColor->setGreen(0.0);
        newColor->setBlue(0.0); // Red
        color = 2;
    }
    else if (color == 2) {
        newColor->setRed(0.5);
        newColor->setGreen(0.0);
        newColor->setBlue(0.5);
        color = 0;
    }

    setColor(newColor);
    delete newColor;
    return true;
}

bool Ball::moveLeft() {
    lcTranslate(-.2, 0);
    posX -= .2;
    return true;
}

bool Ball::moveRight() {
    lcTranslate(.2, 0);
    posX += .2;
    return true;
}

bool Ball::drop()
{
    setDropped(true);
    return true;
}



double Ball::getX() {
    return posX;
}

double Ball::getY() {
    return posY;
}

double Ball::getDx() {
    return dx;
}

double Ball::getDy() {
    return dy;
}

bool Ball::getDropped()
{
    return dropped;
}

void Ball::setX(double num)
{
    posX = num;
}

void Ball::setDropped(bool flag)
{
    dropped = flag;
}

void Ball::setY(double num)
{
    posY = num;
}

void Ball::setDx(double num)
{
    dx = num;
}

void Ball::setDy(double num)
{
    dy = num;
}
