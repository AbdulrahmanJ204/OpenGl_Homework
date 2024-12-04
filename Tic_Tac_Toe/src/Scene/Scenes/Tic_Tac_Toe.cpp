#include "Tic_Tac_Toe.h"
#include <Window.h>




TicTacToe* TicTacToe::instancePtr = nullptr;






TicTacToe::TicTacToe()
	:Scene()
{
	
	Window::changeWindowSize(900, 900);
	m_Proj = (glm::ortho(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight(), -100.0f, 100.0f));
	float x = (float)Window::getWidth() / 3;
	instancePtr = this;
	m_Grid = Square((float)Window::getWidth(), "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "assets/textures/grid.png");
	m_X = Square((float)Window::getWidth() / 3, "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "assets/textures/X.png");
	m_O = Square((float)Window::getWidth() / 3, "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", "assets/textures/O.png");
	for (int i = 0; i < 10; i++) clicked[i] = status::EMPTY;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			positions[i + j * 3 + 1] = glm::vec3(x * i, x * j, 0);

	m_Grid.SetProj(m_Proj);
	m_X.SetProj(m_Proj);
	m_O.SetProj(m_Proj);


}
TicTacToe::~TicTacToe()
{
}
void TicTacToe::render() {
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	m_Grid.draw();
	oWin = checkWin(status::CIRCLE);
	xWin = checkWin(status::CROSS);
	for (int i = 1; i < 11; i++)
	{
		if (clicked[i] == status::CIRCLE)
		{
			m_O.Translate(positions[i]);
			m_O.draw();
		}
		else if (clicked[i] == status::CROSS)
		{
			m_X.Translate(positions[i]);
			m_X.draw();
		}
	}

}

bool TicTacToe::checkWin(status x)
{
	for (int i = 1; i <= 7; i += 3)
	{
		if (checkRow(i, x)) return true;
	}
	for (int i = 1; i < 4; i++)
	{
		if (checkCol(i, x)) return true;
	}
	if (clicked[1] == clicked[5] &&
		clicked[5] == clicked[9] &&
		clicked[9] == x) return true;
	if (clicked[3] == clicked[5] &&
		clicked[5] == clicked[7] &&
		clicked[7] == x) return true;
	return false;
}

bool TicTacToe::checkRow(int i, status x) const
{
	return clicked[i] == clicked[i + 1] &&
		clicked[i + 1] == clicked[i + 2] &&
		clicked[i + 2] == x;

}
bool TicTacToe::checkCol(int i, status x) const
{
	return clicked[i] == clicked[i + 3] &&
		clicked[i + 3] == clicked[i + 6] &&
		clicked[i + 6] == x;

}

void TicTacToe::processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime)
{

	if (action == GLFW_REPEAT) {
		return;
	}
	Window::changeWindowSize(900, 900);
	m_Proj = (glm::ortho(0.0f, (float)Window::getWidth(), 0.0f, (float)Window::getHeight(), -100.0f, 100.0f));

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(Window::instancePtr->getWindow(), true);
	}
	else if (action == GLFW_PRESS) {
		if (xWin || oWin) {
			//std::string winner = xWin ? "X" : "O";
			//std::string msg = "Player " + winner + " Won!";
			//spdlog::info(msg);
			return;
		}
		if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
			key -= GLFW_KEY_0;
			if (clicked[key] == status::EMPTY && cnt < 10) {

				if (cnt % 2) clicked[key] = status::CIRCLE, cnt++;
				else clicked[key] = status::CROSS, cnt++;
			}
		}
		else if (key >= GLFW_KEY_KP_1 && key <= GLFW_KEY_KP_9) {
			key -= GLFW_KEY_KP_0;
			if (clicked[key] == status::EMPTY && cnt < 10) {
				if (cnt % 2) clicked[key] = status::CIRCLE, cnt++;
				else clicked[key] = status::CROSS, cnt++;
			}
		}
		if (key == GLFW_KEY_CAPS_LOCK) {
			int mode = glfwGetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR);
			glfwSetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR, mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}
	}

}
