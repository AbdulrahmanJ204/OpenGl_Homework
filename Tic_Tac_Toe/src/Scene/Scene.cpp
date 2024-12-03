#include "Scene.h"
#include "Application.h"

Scene::Scene() :
	m_Proj(glm::ortho(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight(), -100.0f, 100.0f))
{}


Scene::~Scene()
{
}





