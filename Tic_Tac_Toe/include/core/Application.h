#pragma once
#include "core.h"
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
#include "Tic_Tac_Toe.h"
#include "Walking_Circle.h"
enum class Scenes {
	TICTACTOE,
	WALKINGCIRCLE,
	MOD
};
class Application {
public:


	Application();
	~Application();

	void run();
	void onCursorPositionEvent(double x, double y);
	void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode);
	void processContinuousInput();

	Window& getWindow() { return window; };

	static Application& instance() { return *instancePtr; };

	static Application* instancePtr;
private:
	
	Window window;
	TicTacToe ticTacScene;
	WalkingCircle walkingCircleScene;
	myImGuiManager myImGui;
	float deltaTime, lastFrame;
	Scenes curScene = Scenes::TICTACTOE;
	void LoadImGui();
	void SetupBasics();
	void Clear();
	void UpdateDeltaTime();
	float getRandom();
};