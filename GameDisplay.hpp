#ifndef __GameDisplay_H__
#define __GameDisplay_H__

#include "mixr/ui/glut/GlutDisplay.hpp"
#include "mixr/graphics/Shapes.hpp"
#include "mixr/graphics/Polygon.hpp"
#include "Ball.hpp"
#include "Station.hpp"
#include "GameController.hpp"
#include <GL/glut.h>
#include "mixr/base/Pair.hpp"
#include "mixr/base/colors/Color.hpp"
#include "mixr/base/Pair.hpp"
#include <vector>


class GameDisplay final : public  mixr::glut::GlutDisplay
{
	DECLARE_SUBCLASS(GameDisplay, mixr::glut::GlutDisplay)

public:
	
	GameDisplay();
	bool event(const int event, mixr::base::Object* const obj = nullptr) final;
	void mouseEvent(const int button, const int state, const int x, const int y) final;
	void passiveMotionEvent(const int x, const int y) final;
	void mouseMotionEvent(const int x, const int y);
	void updateData(const double dt);
	void reset() final;
	bool changePage();
	int getBalls();
	std::vector<int> ballSet = {};
private: 
	bool dropped{1};
	int balls = 0;
	bool moveLeft();
	bool moveRight();
	void buttonEvent(const int num) override;
	int speedX{ 650 };
	int gravityX{ 650 };
	int startX{};         
	bool draggingG{};
	bool draggingS{};  
	std::string currentBall{};


	mixr::graphics::Circle* getBall();

};

#endif
