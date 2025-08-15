#ifndef __GameController_H__
#define __GameController_H__
#include "mixr/base/List.hpp"
#include "Ball.hpp"
#include "mixr/base/Vectors.hpp"
#include "mixr/base/Component.hpp"
#include "mixr/base/numeric/Number.hpp"
#include "mixr/graphics/Shapes.hpp"
#include "mixr/base/util/system_utils.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "mixr/graphics/Page.hpp"

class GameController final : public  mixr::base::Component
{
	DECLARE_SUBCLASS(GameController, mixr::base::Component)

public:
	GameController();

	bool setGravity(mixr::base::Number* num);

	bool setSpeed(mixr::base::Number* num);

	

	void reset() final;
	void deleteBall(int i);
	bool event(const int event, mixr::base::Object* const obj = nullptr);

private:
	mixr::graphics::Page* getPage();
	Ball* getBallI(int i);
	double getCollisionAngle(double x1, double y1, double x2, double y2);
	void ballCollision(double angle, bool top, Ball* ball1, Ball* ball2);
	void changeVelocity(double angle, bool top, Ball* ball);
	mixr::base::List* pegCords;
	mixr::graphics::Polygon* getBasket();
	const mixr::base::Vec3d* ballCords{};
	void updateData(const double dt);
	bool checkCollision(double x1, double y1, double x2, double y2, double radius1, double radius2 = .4);
	bool initValues;
	bool setSlotGravity(mixr::base::Number* num);
	bool setSlotPegs(mixr::base::List* pegs);
	double gravity{ .438 };
	double speedMP{ 1 };
	bool setSlotBallCords(mixr::base::Vec3d* ball);
	double posX{  }, posY;
	int score{};
	int ballIndex;
	double dx, dy;
	double collisionTime{};
	double scoreTime{ mixr::base::getComputerTime() };
	double basketX{ 0 }, basketSpeed{ 5 };
};
#endif
