#include "Slider.hpp"
#include "mixr/ui/glut/GlutDisplay.hpp"
#include <GL/glut.h>

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Slider, "Slider")
EMPTY_COPYDATA(Slider)
EMPTY_DELETEDATA(Slider)


Slider::Slider()
{
    STANDARD_CONSTRUCTOR()
}


GameDisplay* Slider::getDisplay() {
    return dynamic_cast<GameDisplay*>(container());
}