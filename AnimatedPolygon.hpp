#ifndef __AnimatedPolygon_H__
#define __AnimatedPolygon_H__

#include "mixr/graphics/Polygon.hpp"


class AnimatedPolygon final : public  mixr::graphics::Polygon
{
	DECLARE_SUBCLASS(AnimatedPolygon, mixr::graphics::Polygon)

public:
	AnimatedPolygon();
	void reset() final;
	void updateData(const double dt);
private:
	bool setSlotPath(mixr::base::String* pathName);

	bool setSlotStartTexture(mixr::base::Number* tex);

	bool setSlotTotalFrames(mixr::base::Number* num);

	bool setSlotStartFrame(mixr::base::Number* num);

	bool setSlotSpeed(mixr::base::Number* num);


	void setPath(mixr::base::String* path);
	void setFrame(mixr::base::Number* num);
	void setTotalFrames(mixr::base::Number* num);
	void setStartFrames(mixr::base::Number* num);
	int totalFrames{};
	int startFrame{};
	int frame{1};
	std::string path{};
	double speed = 1;
	bool initTex{};
	int startTexture{};
	bool startTexInit{};
	
};

#endif
