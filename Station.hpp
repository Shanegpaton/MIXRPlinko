#ifndef __MyStation_H__
#define __MyStation_H__

#include "mixr/simulation/Station.hpp"
#include "mixr/ui/glut/GlutDisplay.hpp"
#include "GameDisplay.hpp"

class Station final : public mixr::simulation::Station
{
	DECLARE_SUBCLASS(Station, mixr::simulation::Station)

public:
	Station();
	void reset() final;

private:
	bool displayInit{};
};

#endif
