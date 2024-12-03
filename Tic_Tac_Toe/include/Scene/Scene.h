#pragma once
#include "core.h"
#include "Texture.h"
#include "Square.h"

class Scene
{
public:

	Scene();
	~Scene();
	virtual void render()  = 0;
	virtual void onCursorPositionEvent(double x, double y) = 0;
	virtual void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime) = 0;
	virtual void processContinuousInput(float& deltaTime) = 0;


	glm::mat4 m_Proj;
private:
	//float m_Rotation = 0.0f, m_Scale = 10.0f;
	
};

