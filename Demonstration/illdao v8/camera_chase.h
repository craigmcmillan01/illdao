#pragma once

#include "camera.h"

using namespace irr::core;

class ChaseCamera : public Camera
{
private:
	vector3df followTargetPosition;
	vector3df followTargetRotation;
	vector3df positionOffset;
	vector3df targetOffset;
	vector3df relativeCameraRotation;
	float springiness;
public:
	ChaseCamera() { }
	~ChaseCamera() { }
	vector3df getFollowTargetPosition() const { return followTargetPosition; }
	void SetFollowTargetPosition(vector3df value) { followTargetPosition = value; }
	vector3df getFollowTargetRotation() const { return followTargetRotation; }
	void setFollowTargetRotation(vector3df value) {followTargetRotation = value; }
	vector3df getPositioniOffset() const { return positionOffset; }
	void setPositionOffset(vector3df value) { positionOffset = value; }
	vector3df getTargetOffset() const { return targetOffset; }
	void setTargetOffset(vector3df value) { targetOffset = value; }
	vector3df getRelativeCameraRotation() const { return relativeCameraRotation; }
	void setRelativeCameraRotation (vector3df value) {relativeCameraRotation = value; }
	float getSpringiness() const { return springiness; }
	float setSpringiness(float value) {springiness = value; }
	void initialise();
	void update(float deltaTime);
	void move(vector3df newFollowTargetPosition, vector3df newFollowTargetRotation);
	void rotate(vector3df deltaRotation);
};