#pragma once
#include "Scene.h"

enum class status {
	EMPTY, CIRCLE, CROSS
};



class TicTacToe : Scene
{
public :
	TicTacToe();
	~TicTacToe();
	void render();
	bool checkWin(status x);
	bool checkRow(int i, status x) const;
	bool checkCol(int i, status x) const;
	void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime);
	void onCursorPositionEvent(double x, double y) {};
	void processContinuousInput(float& deltaTime) {};

	
	static TicTacToe* instancePtr;
private:
	status clicked[10];
	glm::vec3 positions[10];
	int cnt = 0;
	Square m_Grid, m_X, m_O;
	bool xWin = false, oWin = false;
};