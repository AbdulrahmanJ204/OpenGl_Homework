#include "Walking_Circle.h"
#include <Window.h>




WalkingCircle* WalkingCircle::instancePtr = nullptr;






WalkingCircle::WalkingCircle()
	:
	Scene()
{
	float x = (float)Window::getWidth() / 3;
	Window::changeWindowSize(1200, 800);
	m_Proj = (glm::ortho(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight(), -100.0f, 100.0f));
	m_Ground = MyRectangle((float)Window::getWidth(), (float)Window::getHeight() / 3, "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "assets/textures/ground.png");
	m_Box = Square((float)Window::getWidth() / 9, "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "assets/textures/container.jpg");
	m_Circle = Square((float)Window::getWidth() / 9, "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "assets/textures/awesomeface.png");
	instancePtr = this;
	positions[0] = glm::vec3(Window::getWidth() / 2, (float)Window::getHeight() / 4, 0.0f);
	positions[1] = glm::vec3(Window::getWidth() / 2, (float)Window::getHeight() / 4 + (float)Window::getHeight() / 6, 0.0f);
	positions[2] = glm::vec3(Window::getWidth() / 2 - Window::getWidth() / 9, (float)Window::getHeight() / 4, 0.0f);
	circlePosition = glm::vec3(0.0f, (float)Window::getHeight() / 4, 0.0f);
	//m_Grid.SetProj(m_Proj);
	//m_X.SetProj(m_Proj);
	//m_O.SetProj(m_Proj);
	m_Ground.SetProj(m_Proj);
	m_Box.SetProj(m_Proj);
	m_Circle.SetProj(m_Proj);

}
WalkingCircle::~WalkingCircle()
{
}
void WalkingCircle::render() {
	GLCall(glClearColor(0.0f, 1.0f, 1.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	m_Ground.draw();

	for (int i = 0; i < 3; i++)
	{
		m_Box.Translate(positions[i]);
		m_Box.draw();
	}
	m_Circle.Translate(circlePosition);
	m_Circle.draw();

}



void WalkingCircle::processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime)
{

	if (action == GLFW_REPEAT) {
		return;
	}
	Window::changeWindowSize(1200, 800);
	m_Proj = (glm::ortho(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight(), -100.0f, 100.0f));

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(Window::instancePtr->getWindow(), true);
	}
	else if (action == GLFW_PRESS) {


		if (key == GLFW_KEY_CAPS_LOCK) {
			int mode = glfwGetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR);
			glfwSetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR, mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}
	}

}

void WalkingCircle::processContinuousInput(float& deltaTime)
{
	GLFWwindow* window = Window::instancePtr->getWindow();
	float movement = deltaTime * speed;
	glm::vec3 curPos = circlePosition;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

		glm::vec3 trans(0.0f, movement, 0.0f);
		if (curPos.y + m_Circle.getLength() + movement <= Window::getHeight())
			circlePosition = circlePosition + trans;

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		glm::vec3 trans(0.0f, -movement, 0.0f);
		bool can = true;
		float len = m_Box.getLength();
		for (int i = 0; i < 3; i++)
		{
		
			if (curPos.x + len < positions[i].x|| curPos.x > positions[i].x + len) continue;
			if (curPos.y >= positions[i].y + len)
				can &= (curPos.y - movement > positions[i].y + len);
		}
		//std::cout << " Cur y = " << curPos.y << " " << can << std::endl;
		if (curPos.y - movement >= Window::getHeight() / 4 && can)
			circlePosition = circlePosition + trans;


	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		glm::vec3 trans(-movement, 0.0f, 0.0f);
		bool can = true;
		for (int i = 0; i < 3; i++)
		{
			if (curPos.x <= positions[i].x) continue;
			if ((curPos.y >= positions[i].y && curPos.y <= positions[i].y + m_Box.getLength())) {
				can &= (curPos.x - movement > positions[i].x + m_Box.getLength());
			}
			if (curPos.y + m_Box.getLength() >= positions[i].y && curPos.y + m_Box.getLength() <= positions[i].y) {
				can &= (curPos.x - movement > positions[i].x + m_Box.getLength());
			}
		}

		if (curPos.x - movement >= 0 && can)
			circlePosition = circlePosition + trans;

	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		glm::vec3 trans(movement, 0.0f, 0.0f);
		bool can = true;
		for (int i = 0; i < 3; i++)
		{
			if (curPos.x >= positions[i].x) continue;

			if ((curPos.y >= positions[i].y && curPos.y <= positions[i].y + m_Box.getLength()) ||
				(curPos.y + m_Box.getLength() >= positions[i].y && curPos.y + m_Box.getLength() <= positions[i].y))
				can &= (curPos.x + m_Circle.getLength() + movement < positions[i].x);
		}
		if (curPos.x + m_Circle.getLength() + movement <= Window::getWidth() && can)
			circlePosition = circlePosition + trans;

	}

}
