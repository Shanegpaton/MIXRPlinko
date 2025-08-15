#include "GameController.hpp"
#include "Station.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/graphics/Page.hpp"
#include <cmath>
#include "mixr/graphics/readouts/NumericReadout.hpp"
#include "mixr/base/PairStream.hpp"

IMPLEMENT_SUBCLASS(GameController, "GameController")
EMPTY_DELETEDATA(GameController)
EMPTY_COPYDATA(GameController)

BEGIN_SLOTTABLE(GameController)
"pegs",
"gravity",
END_SLOTTABLE(GameController)

BEGIN_SLOT_MAP(GameController)
	ON_SLOT(1, setSlotPegs, mixr::base::List)
	ON_SLOT(2, setSlotGravity, mixr::base::Number)
END_SLOT_MAP()

BEGIN_EVENT_HANDLER(GameController)
ON_EVENT_OBJ(3007, setGravity, mixr::base::Number)
ON_EVENT_OBJ(3008, setSpeed, mixr::base::Number)
END_EVENT_HANDLER()

GameController::GameController() {
	STANDARD_CONSTRUCTOR();
}

bool GameController::setGravity(mixr::base::Number* num) {
	gravity = std::pow(num->getDouble() / 800, 4);
	return true;
}

bool GameController::setSpeed(mixr::base::Number* num) {
	speedMP = num->getDouble() / 800;
	return true;
}

mixr::graphics::Page* GameController::getPage() {
	auto* station = dynamic_cast<Station*>(container());
	mixr::base::Pair* pair = station->findByName("GameDisplay");
	GameDisplay* dis = dynamic_cast<GameDisplay*>(pair->object());
	return  dynamic_cast<mixr::graphics::Page*>(dis->findSubpageByName("p2")->object());
}
Ball* GameController::getBallI(int i) {
	mixr::graphics::Page* page = getPage();
	std::string ballName = "ball" + std::to_string(i);
	if (page->findByName(ballName.c_str()) != nullptr) {
		return  dynamic_cast<Ball*>(page->findByName(ballName.c_str())->object());
	}
	return nullptr;
}


mixr::graphics::Polygon* GameController::getBasket()
{	
	mixr::graphics::Page* page = getPage();
	return  dynamic_cast<mixr::graphics::Polygon*>(page->findByName("Basket")->object());
}

void GameController::reset()
{
	BaseClass::reset();
	//reset ball
	//auto* ball = getBall();
	if (!initValues) {
		//ball->lcTranslate(-posX - ball->getVertices()->x(), -posY);
	}
	else {
		
		//ball->lcTranslate(-posX, -posY + 7);

	 }
	posY = 0;
	posX = 0;
	dy = 0;
	dx = 0;
	initValues = false;
	mixr::base::Vec3d* newCords = new mixr::base::Vec3d();
	//newCords->y() = ball->getVertices()->y();
	//ball->setVertices(newCords, 2);
	// reset basket
	/*getBasket()->lcTranslate(-basketX, 0);
	basketX = 0;
	basketSpeed = 5;*/
}

void GameController::deleteBall(int i) {
	auto* station = dynamic_cast<Station*>(container());
	mixr::base::Pair* pair = station->findByName("GameDisplay");
	GameDisplay* dis = dynamic_cast<GameDisplay*>(pair->object());
	mixr::graphics::Page* page = dynamic_cast<mixr::graphics::Page*>(dis->findSubpageByName("p2")->object());;
	Ball* ball = getBallI(i);
	mixr::base::PairStream* pairStream = page->getComponents();
	std::string ballName = "ball" + std::to_string(i);
	int length = dis->ballSet.size();
	for (int j = 0; j < length; j++) {
		if (dis->ballSet.at(j) == i) {
			dis->ballSet.erase(dis->ballSet.begin() + j);
		}
		j = length;
	}
	auto* ballPair = dynamic_cast<mixr::base::Pair*>(page->findByName(ballName.c_str()));
	pairStream->remove(ballPair);
	//ball->unref();
}

void GameController::updateData(const double dt)
{
	BaseClass::updateData(dt);
	auto* station = dynamic_cast<Station*>(container());

	mixr::base::Pair* pair = station->findByName("GameDisplay");

	GameDisplay* dis = dynamic_cast<GameDisplay*>(pair->object());
	// move basket
	if (dis->subpage() == dynamic_cast<mixr::graphics::Page*>(dis->findSubpageByName("p2")->object())) {
		mixr::graphics::Polygon* basket = getBasket();
		basketX += basketSpeed * dt;
		if (basketX >= 8 || basketX <= -8) {
			basketSpeed = -basketSpeed;
		}
		basket->lcTranslate(basketSpeed * dt, 0);
	}
	//find all of the balls
	Ball* ball;
	int ballsLength = dis->ballSet.size();
	for (int i = 0; i < ballsLength; i++) {
		ball = getBallI(dis->ballSet.at(i));
		if (ball != nullptr) {
			//check if the given ball has dropped
			if (ball->getDropped()) {
				// add gravity to dy
				ball->setDy(ball->getDy() - gravity); //dy -= gravity;
				//loop through all pegs
				mixr::base::List::Item* peg = pegCords->getFirstItem();
				while (peg != nullptr) {
					//get the x and y cords of a peg
					mixr::graphics::Circle* circ = dynamic_cast<mixr::graphics::Circle*>(peg->getValue());
					const mixr::base::Vec3d* pc = dynamic_cast<const mixr::base::Vec3d*>(circ->getVertices());
					double pegX = pc->x();
					double pegY = pc->y();
					// check for collsion
					bool collision = checkCollision(pegX, pegY, ball->getX(), ball->getY(), ball->getRadius());
					if (collision) {
						// get collision angle
						double angle = getCollisionAngle(pegX, pegY, ball->getX(), ball->getY());
						// change dy and dx bassed on angle
						bool top = (ball->getY() >= pegY);
						changeVelocity(angle, top, ball);
					}
					peg = peg->getNext();
				}
				// loop through all the balls
				for (int j = i + 1; j < ballsLength; j++) {
					//get ball at j
					Ball* ball2 = getBallI(dis->ballSet.at(j));
					if (ball2 != nullptr) {
						// check if i is colliding with j
						bool collision = checkCollision(ball2->getX(), ball2->getY(), ball->getX(), ball->getY(), ball->getRadius(), ball2->getRadius());
						if (collision) {
							double angle = getCollisionAngle(ball2->getX(), ball2->getY(), ball->getX(), ball->getY());
							bool top = (ball->getY() >= ball2->getY());
							// TODO: handle ball collision for two balls
							ballCollision(angle, top, ball, ball2);
						}
					}
				}
				//check for wall collision
				if (ball->getX() + .9 >= 10) {
					ball->setDx(-ball->getDx());
				}
				else if (ball->getX() - .9 <= -10) {
					ball->setDx(-ball->getDx());
				}
				//checkWall();
				// update ball cords
				ball->lcTranslate(ball->getDx() * dt, ball->getDy() * dt);
				ball->setY(ball->getY() + ball->getDy() * dt);
				ball->setX(ball->getX() + ball->getDx() * dt);
			}
			if (std::abs(ball->getX() - basketX) < 2.5 && std::abs(ball->getY() + 8) < .5) {
				if (mixr::base::getComputerTime() - scoreTime > .2) {
					scoreTime = mixr::base::getComputerTime();
					score++;
					SendData ss;
					mixr::graphics::Page* page = dynamic_cast<mixr::graphics::Page*>(dis->findSubpageByName("p2")->object());
					page->send("score", UPDATE_VALUE, score, ss);
					deleteBall(dis->ballSet.at(i));
					ballsLength--;
				}


			}
			if (ball->getY() < -13) {  
				deleteBall(dis->ballSet.at(i));
				ballsLength--;
			}
		}
	}
}



void GameController::ballCollision(double angle, bool top, Ball* ball1, Ball* ball2) {
	double m1 = ball1->getRadius();  
	double m2 = ball2->getRadius();

	// Velocities before collision
	double v1x = ball1->getDx();
	double v1y = ball1->getDy();
	double v2x = ball2->getDx();
	double v2y = ball2->getDy();

	// Vector from ball1 to ball2
	double nx = ball2->getX() - ball1->getX();
	double ny = ball2->getY() - ball1->getY();
	double dist = std::sqrt(nx * nx + ny * ny);
	// Normalizing the vector
	nx /= dist;
	ny /= dist;

	// Tangential vector
	double tx = -ny;
	double ty = nx;

	// Normal velocities
	double v1n = v1x * nx + v1y * ny;
	double v2n = v2x * nx + v2y * ny;

	// Tangential velocities (unchanged in elastic collision)
	double v1t = v1x * tx + v1y * ty;
	double v2t = v2x * tx + v2y * ty;

	// New normal velocities after collision
	double v1n_prime = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
	double v2n_prime = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

	// Convert the scalar normal and tangential velocities into vectors again
	double v1n_prime_x = v1n_prime * nx;
	double v1n_prime_y = v1n_prime * ny;
	double v2n_prime_x = v2n_prime * nx;
	double v2n_prime_y = v2n_prime * ny;

	double v1t_x = v1t * tx;
	double v1t_y = v1t * ty;
	double v2t_x = v2t * tx;
	double v2t_y = v2t * ty;

	// Final velocities by adding the normal and tangential components
	ball1->setDx(v1n_prime_x + v1t_x);
	ball1->setDy(v1n_prime_y + v1t_y);
	ball2->setDx(v2n_prime_x + v2t_x);
	ball2->setDy(v2n_prime_y + v2t_y);

	
}

void GameController::changeVelocity(double angle, bool top, Ball* ball) {
	dy = ball->getDy();
	dx = ball->getDx();
	double speed = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
	speed *= speedMP;
	if (speed > 15) {
		speed = 15;
	}
	// top right
	if (angle >= 0 && angle <= 3.141592 / 2 && top) {
		// Top right quadrant
		dy = sin(angle) * speed;
		dx = cos(angle) * speed;
	}
	// Top left  
	else if (angle < 0 && angle >= -3.141592 / 2 && top) {
		dy = -sin(angle) * speed;
		dx = -cos(angle) * speed;
	}
	// Bottom left  
	else if (angle > 0 && angle <= 3.141592 / 2 && !top) {

		dy = -sin(angle) * speed;
		dx = -cos(angle) * speed;
	}
	// Bottom right
	else if (angle >= -3.141592 / 2 && angle < 0 && !top) {
		dy = sin(angle) * speed;
		dx = cos(angle) * speed;
	}
	else {
		dy = sin(angle) * speed;
		dx = cos(angle) * speed + .1;
	}
	ball->setDy(dy);
	ball->setDx(dx);

}
double GameController::getCollisionAngle(double x1, double y1, double x2, double y2) 
{
		return atan((y2 - y1) / (x2 - x1));

}
bool GameController::checkCollision(double x1, double y1, double x2, double y2, double radius1, double radius2)
{
	// use euclidean disatnace formula to see how far the centers are apart
	double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
	// check if the distance between the points is greater than the sum both of the radii
	if (distance <= radius1 + radius2) {
		return true;
	}
	return false;
}

bool GameController::setSlotGravity(mixr::base::Number* num) {
	gravity = num->getInt();
	return true;
}

bool GameController::setSlotPegs(mixr::base::List* pegs) {
	
	pegCords = new mixr::base::List();
	mixr::base::List::Item * item = pegs->getFirstItem();
	while (item != nullptr) {
		mixr::base::Pair* pa = dynamic_cast<mixr::base::Pair*>(item->getValue());
		mixr::graphics::Circle* circ = dynamic_cast<mixr::graphics::Circle*>(pa->object());
		//mixr::base::List::Item* i = dynamic_cast<mixr::base::List::Item*>(circ);
		pegCords->put(circ);
		item = item->getNext();
	}
	return true;
}

bool GameController::setSlotBallCords(mixr::base::Vec3d* ball) {
	ballCords = ball;
	return true;
}

