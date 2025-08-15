#ifndef __Slider_H__
#define __Slider_H__

#include "mixr/graphics/Page.hpp"
#include "mixr/instruments/buttons/Button.hpp"
#include "GameDisplay.hpp"

class Slider final : public mixr::instruments::Button
{
	DECLARE_SUBCLASS(Slider, mixr::instruments::Button)

public:
	Slider();

 
	GameDisplay* getDisplay();
private:
	
	int startX{};         // startX of our last mouse position
	int startY{};         // startY of our last mouse position
	bool dragging{};      // are we dragging the map?
	int range{};          // range of our map
	SendData rangeSD;
};

#endif
