#include "GameDisplay.hpp"

IMPLEMENT_SUBCLASS(GameDisplay, "GameDisplay")
EMPTY_DELETEDATA(GameDisplay)
EMPTY_SLOTTABLE(GameDisplay);

BEGIN_EVENT_HANDLER(GameDisplay)
ON_EVENT(LEFT_ARROW_KEY, moveLeft)
ON_EVENT(RIGHT_ARROW_KEY, moveRight)
END_EVENT_HANDLER()

GameDisplay::GameDisplay() {
	STANDARD_CONSTRUCTOR();
	
}

int GameDisplay::getBalls() {
	return balls;
}

void GameDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
	BaseClass::mouseEvent(button, state, x, y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) { draggingG = false; draggingS = false; }
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !draggingG && x >= 650 && x <= 950 && y >= 10 && y <= 50) { draggingG = true; }
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !draggingG && x >= 650 && x <= 950 && y >= 60 && y <= 100) { draggingS = true; }
}

void GameDisplay::passiveMotionEvent(const int x, const int y)
{
	BaseClass::passiveMotionEvent(x, y);
	if (!draggingG || !draggingS) {
		startX = x;
	}
}

void GameDisplay::mouseMotionEvent(const int x, const int y)
{
	//handle gravity slider
	if (draggingG) {
		if (x <= 650) {
			gravityX = 650;
		}
		else if (x >= 950) {
			gravityX = 950;
		}
		else {
			mixr::graphics::Polygon* slider = dynamic_cast<mixr::graphics::Polygon*>(subpage()->findByName("gravitySlider")->object());
			slider->lcTranslate((x - gravityX) / 50.0, 0);
			gravityX = x;
			Station* station = dynamic_cast<Station*>(container());
			SendData sliderSD;
			station->send("controller", 3007, gravityX, sliderSD);
			
		}
	}

	if (draggingS) {
		if (x <= 650) {
			speedX = 650;
		}
		else if (x >= 950) {
			speedX = 950;
		}
		else {
			mixr::graphics::Polygon* slider = dynamic_cast<mixr::graphics::Polygon*>(subpage()->findByName("speedSlider")->object());
			slider->lcTranslate((x - speedX) / 50.0, 0);
			speedX = x;
			Station* station = dynamic_cast<Station*>(container());
			SendData sliderSD;
			station->send("controller", 3008, speedX, sliderSD);
		}
	}
}





void GameDisplay::updateData(const double dt)
{
	BaseClass::updateData(dt);

}
void GameDisplay::reset()
{
	BaseClass::reset();
	
	//if (getBall() != nullptr) {
	//	mixr::base::Color* newColor = new mixr::base::Color();
	//	newColor->setRed(0.95);
	//	newColor->setGreen(0.61);
	//	newColor->setBlue(.73); // Pastel magenta
	//	color = 1;
	//	getBall()->setColor(newColor);
	//	delete newColor;
	//}
}
void GameDisplay::copyData(const GameDisplay & org, const bool) {
	BaseClass::copyData(org);
}

bool GameDisplay::moveLeft() {
	if (!dropped) subpage()->send(currentBall.c_str(), 3005);
	return true;
}

bool GameDisplay::moveRight() {
	if (!dropped) subpage()->send(currentBall.c_str(), 3006);
	return true;
}

void GameDisplay::buttonEvent(const int b)
{
	switch (b) {
	case 3000: {
		newSubpage("p2", nullptr);
		break;
	}
	case 3001: {
		if (!dropped) {
			subpage()->send(currentBall.c_str(), 3001);
			dropped = true;
			ballSet.push_back(balls - 1);
		}
		break;
	}
	case 3002: {
		subpage()->send(currentBall.c_str(), 3002);
		break;
	}
	case 3003: {
		Station* station = dynamic_cast<Station*>(container());
		station->event(mixr::base::Component::RESET_EVENT);
		break;
		
	}
	case 3004: {
		if (dropped) {

			double radious = (std::rand() % 50) / 100.0 + .5;
			mixr::base::Color* newColor = new mixr::base::Color();
			newColor->setRed(0.95);
			newColor->setGreen(0.61);
			newColor->setBlue(.73);  // Pastel magenta
			Ball* ball = new Ball();
			ball->setFilled(true);
			ball->lcTranslate(0, 7);
			ball->setDropped(false);
			ball->setColor(newColor);
			ball->setRadius(radious);
			std::string name = "ball" + std::to_string(balls);
			currentBall = name;
			mixr::base::Pair* pair = new mixr::base::Pair(name.c_str(), ball);
			balls++;
			dropped = false;
			subpage()->addComponent(pair);
			break;
		}
	}
	}
}
