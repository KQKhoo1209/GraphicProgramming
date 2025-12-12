#include "InputManager.h"
#include <gl/GL.h>
#include <math.h>

// External game state variables (these should be moved to a GameState class later)
extern int questionToDisplay;
extern float bridgeRot;
extern int spherePoint;
extern GLfloat diffuseLightPosition[];

InputManager::InputManager()
	: hWnd(nullptr)
	, windowWidth(1280)
	, windowHeight(720)
	, camX(0.0f)
	, camY(0.5f)
	, camZ(3.0f)
	, camYaw(0.0f)
	, camPitch(0.0f)
	, yawRad(0.0f)
	, lightX(0.0f)
	, lightY(1.0f)
	, lightZ(0.0f)
	, moveSpeed(0.001f)
	, mouseSensitivity(0.05f)
	, lightMoveSpeed(0.001f)
	, lastMouseX(400)
	, lastMouseY(300)
	, firstMouse(true)
	, OnQuestionChange(nullptr)
	, OnBridgeRotate(nullptr)
	, OnQuit(nullptr)
{
	// Initialize key states
	for (int i = 0; i < 256; i++)
	{
		keys[i] = false;
	}
}

InputManager::~InputManager()
{
}

void InputManager::Initialize(HWND hWnd, int windowWidth, int windowHeight)
{
	this->hWnd = hWnd;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	ShowCursor(false);
}

void InputManager::SetWindowDimensions(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}

LRESULT InputManager::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		HandleKeyDown(wParam);
		keys[wParam] = true;
		break;

	case WM_KEYUP:
		HandleKeyUp(wParam);
		keys[wParam] = false;
		break;

	case WM_MOUSEMOVE:
		HandleMouseMove(hWnd, lParam);
		return 0;

		//case WM_SIZE:
		//	// Update window dimensions when window is resized
		//	SetWindowDimensions(LOWORD(lParam), HIWORD(lParam));
		//	break;

	default:
		return 1; // Message not handled
	}

	return 0; // Message handled
}

void InputManager::HandleKeyDown(WPARAM wParam)
{
	switch (wParam)
	{
	case '1':
		if (OnQuestionChange) OnQuestionChange(0);
		questionToDisplay = 0;
		break;
	case '2':
		if (OnQuestionChange) OnQuestionChange(1);
		questionToDisplay = 1;
		break;
	case '3':
		if (OnQuestionChange) OnQuestionChange(2);
		questionToDisplay = 2;
		break;
	case '4':
		if (OnQuestionChange) OnQuestionChange(3);
		questionToDisplay = 3;
		break;
	case '5':
		if (OnQuestionChange) OnQuestionChange(4);
		questionToDisplay = 4;
		break;
	case '6':
		if (OnQuestionChange) OnQuestionChange(5);
		questionToDisplay = 5;
		break;
	case '7':
		if (OnQuestionChange) OnQuestionChange(6);
		questionToDisplay = 6;
		break;
	case 'Q':
		bridgeRot += 1.0f;
		if (bridgeRot >= 45) {
			bridgeRot = 45;
		}
		if (OnBridgeRotate) OnBridgeRotate(bridgeRot);
		break;
	case 'E':
		bridgeRot -= 1.0f;
		if (bridgeRot <= 0) {
			bridgeRot = 0;
		}
		if (OnBridgeRotate) OnBridgeRotate(bridgeRot);
		break;
	case VK_SPACE:
		bridgeRot = 0.0f;
		if (OnBridgeRotate) OnBridgeRotate(bridgeRot);
		break;
	case VK_ESCAPE:
		if (OnQuit) OnQuit();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
}

void InputManager::HandleKeyUp(WPARAM wParam)
{
	// Handle key release if needed
}

void InputManager::HandleMouseMove(HWND hWnd, LPARAM lParam)
{
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	if (firstMouse)
	{
		// Center mouse cursor on first move
		CenterMouseCursor(hWnd);
		lastMouseX = windowWidth / 2;
		lastMouseY = windowHeight / 2;
		firstMouse = false;
		return;
	}

	// Calculate relative movement from center
	int centerX = windowWidth / 2;
	int centerY = windowHeight / 2;

	float dx = mouseX - centerX;
	float dy = mouseY - centerY;

	// Update camera angles based on relative movement
	camYaw += dx * mouseSensitivity;
	camPitch -= dy * mouseSensitivity;

	// Center mouse cursor again for next frame
	CenterMouseCursor(hWnd);

	// Update last position to center (since we just centered it)
	lastMouseX = centerX;
	lastMouseY = centerY;
}

void InputManager::CenterMouseCursor(HWND hWnd)
{
	POINT center;
	center.x = windowWidth / 2;
	center.y = windowHeight / 2;
	ClientToScreen(hWnd, &center);
	SetCursorPos(center.x, center.y);
}

void InputManager::Update()
{
	// Handle continuous key input for camera movement
	yawRad = camYaw * (3.14159f / 180.0f);

	if (IsKeyPressed('W'))
	{
		camX += sin(yawRad) * moveSpeed;
		camZ -= cos(yawRad) * moveSpeed;
	}
	if (IsKeyPressed('A'))
	{
		camX -= cos(yawRad) * moveSpeed;
		camZ -= sin(yawRad) * moveSpeed;
	}
	if (IsKeyPressed('S'))
	{
		camX -= sin(yawRad) * moveSpeed;
		camZ += cos(yawRad) * moveSpeed;
	}
	if (IsKeyPressed('D'))
	{
		camX += cos(yawRad) * moveSpeed;
		camZ += sin(yawRad) * moveSpeed;
	}

	if (IsKeyPressed('U'))
	{
		diffuseLightPosition[1] += lightMoveSpeed;
		lightY = diffuseLightPosition[1];
	}
	if (IsKeyPressed('J'))
	{
		diffuseLightPosition[1] -= lightMoveSpeed;
		lightY = diffuseLightPosition[1];
	}
	if (IsKeyPressed('H'))
	{
		diffuseLightPosition[0] -= lightMoveSpeed;
		lightX = diffuseLightPosition[0];
	}
	if (IsKeyPressed('K'))
	{
		diffuseLightPosition[0] += lightMoveSpeed;
		lightX = diffuseLightPosition[0];
	}
	if (IsKeyPressed('Y'))
	{
		diffuseLightPosition[2] += lightMoveSpeed;
		lightZ = diffuseLightPosition[2];
	}
	if (IsKeyPressed('I'))
	{
		diffuseLightPosition[2] -= lightMoveSpeed;
		lightZ = diffuseLightPosition[2];
	}
}

bool InputManager::IsKeyPressed(int key) const
{
	if (key >= 0 && key < 256)
	{
		return keys[key] || (GetAsyncKeyState(key) & 0x8000);
	}
	return false;
}

void InputManager::UpdateCameraPosition(float deltaX, float deltaY, float deltaZ)
{
	camX += deltaX;
	camY += deltaY;
	camZ += deltaZ;
}

void InputManager::SetLightPosition(float x, float y, float z)
{
	lightX = x;
	lightY = y;
	lightZ = z;
	// Also update the diffuseLightPosition array directly
	diffuseLightPosition[0] = x;
	diffuseLightPosition[1] = y;
	diffuseLightPosition[2] = z;
}

void InputManager::UpdateLightPosition(float deltaX, float deltaY, float deltaZ)
{
	lightX += deltaX;
	lightY += deltaY;
	lightZ += deltaZ;
}