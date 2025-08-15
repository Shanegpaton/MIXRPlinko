#include "AnimatedPolygon.hpp"
#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/String.hpp"
#include "mixr/graphics/BmpTexture.hpp"

IMPLEMENT_SUBCLASS(AnimatedPolygon, "AnimatedPolygon")
EMPTY_DELETEDATA(AnimatedPolygon)
EMPTY_COPYDATA(AnimatedPolygon)


BEGIN_SLOTTABLE(AnimatedPolygon)
"path",
//"startTexture",
"totalFrames",
"startFrame",
"speed",
END_SLOTTABLE(AnimatedPolygon)

BEGIN_SLOT_MAP(AnimatedPolygon)
	ON_SLOT(1, setSlotPath , mixr::base::String)
	//ON_SLOT(2, setSlotStartTexture, mixr::base::Number)
	ON_SLOT(2, setSlotTotalFrames, mixr::base::Number);
	ON_SLOT(3, setSlotStartFrame, mixr::base::Number);
	ON_SLOT(4, setSlotSpeed, mixr::base::Number);
END_SLOT_MAP()


AnimatedPolygon::AnimatedPolygon()
{
	STANDARD_CONSTRUCTOR();
	
}

void AnimatedPolygon::reset()
{
	BaseClass::reset();
	if (!initTex) {
		for (int i = startFrame; i < totalFrames + startFrame; i++) {
			mixr::graphics::BmpTexture* tex = new mixr::graphics::BmpTexture;
			std::string fileName = "frame" + std::to_string(i) + ".bmp";
			tex->setTexturePath(path.c_str());
			tex->setTextureFileName(fileName.c_str());
			tex->loadTexture();
			if (!startTexInit) {
				startTexture = tex->getTexture();
				startTexInit = true;
			}
		}
		initTex = true;
	}
	
}

bool AnimatedPolygon::setSlotPath(mixr::base::String* pathName) {
	path = pathName->getString();
	return true;
}

bool AnimatedPolygon::setSlotStartTexture(mixr::base::Number* tex) {
	startTexture = tex->getInt();
	return true;
}

bool AnimatedPolygon::setSlotTotalFrames(mixr::base::Number* num) {
	totalFrames = num->getInt();
	return true;
}

bool AnimatedPolygon::setSlotStartFrame(mixr::base::Number* num) {
	startFrame = num->getInt();
	return true;
}

bool AnimatedPolygon::setSlotSpeed(mixr::base::Number* num) {
	speed = num->getInt();
	return true;
}


void AnimatedPolygon::updateData(const double dt) {

	BaseClass::updateData(dt);
	setTexture((int)frame + startTexture - 1);

	frame++;
	if (frame > totalFrames)
	{
		frame -= totalFrames;
	}

}
