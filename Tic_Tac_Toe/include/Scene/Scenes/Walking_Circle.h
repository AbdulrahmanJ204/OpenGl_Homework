#pragma once
#include "Scene.h"
#include "MyRectangle.h"



class WalkingCircle : Scene
{
public :
	WalkingCircle();
	~WalkingCircle();
	void render();
	void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime);
	void onCursorPositionEvent(double x, double y) {};
	void processContinuousInput(float& deltaTime) ;

	
	static WalkingCircle* instancePtr;
private:
	MyRectangle m_Ground;
	Square m_Box;
	Square m_Circle;
	float speed = 250.0f;
	glm::vec3 positions[3] , circlePosition;
};