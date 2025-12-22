#include "InputManager.h"
#include <gl/GL.h>
#include <math.h>
#include "Robot.h"
#include "Animator.h"
#include "leg.h"
#include "arm.h"
#include "Weapon.h"

// External game state variables (these should be moved to a GameState class later)
extern int camSwitch;
extern GLfloat diffuseLightPosition[];

InputManager::InputManager(Robot* robotObj)
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
	, robot(robotObj)
{
	// Initialize key states
	for (int i = 0; i < 256; i++)
	{
		keys[i] = false;
	}
}

void InputManager::SetRobot(Robot* robotObj)
{
	robot = robotObj;
}

InputManager::~InputManager()
{
}

InputMode InputManager::currentMode = CAMMOVEMENT_MODE;

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
	// Windows Input, have delay when hold
	switch (wParam)
	{
	case VK_TAB:
		currentMode = static_cast<InputMode>((currentMode + 1) % 3);
		break;
	case 'P':
		if (currentMode == CAMMOVEMENT_MODE) camSwitch *= -1;
		break;
	case 'F':
		if (currentMode == ANIMATION_MODE) robot->StartSpecialAnimation();
		break;
	case 'Q':
		if (currentMode == ANIMATION_MODE) robot->StartSwingKnife();
		break;
	case VK_SPACE:
		if (currentMode == ROBOTMOVEMENT_MODE) robot->ResetRotations();
		if (currentMode == ANIMATION_MODE) robot->StartJump();
		break;
	case '1':
		if (robot && robot->GetWeapon())
			robot->GetWeapon()->SetSkin(SKIN_STEEL);
		break;

	case '2':
		if (robot && robot->GetWeapon())
			robot->GetWeapon()->SetSkin(SKIN_CRIMSON);
		break;

	case '3':
		if (robot && robot->GetWeapon())
			robot->GetWeapon()->SetSkin(SKIN_SLAUGHTER);
		break;
	case '4':
		if (currentMode == ANIMATION_MODE || currentMode == ROBOTMOVEMENT_MODE) robot->ShowHat();
		break;
	case VK_ESCAPE:
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

// Camera And Light Movement
void InputManager::UpdateCamLightMovement()
{
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

	if (IsKeyPressed('Q'))
	{
		camY += moveSpeed;
	}

	if (IsKeyPressed('E'))
	{
		camY -= moveSpeed;
	}

	if (IsKeyPressed('I'))
	{
		diffuseLightPosition[1] += lightMoveSpeed;
		lightY = diffuseLightPosition[1];
	}
	if (IsKeyPressed('K'))
	{
		diffuseLightPosition[1] -= lightMoveSpeed;
		lightY = diffuseLightPosition[1];
	}
	if (IsKeyPressed('J'))
	{
		diffuseLightPosition[0] -= lightMoveSpeed;
		lightX = diffuseLightPosition[0];
	}
	if (IsKeyPressed('L'))
	{
		diffuseLightPosition[0] += lightMoveSpeed;
		lightX = diffuseLightPosition[0];
	}
	if (IsKeyPressed('U'))
	{
		diffuseLightPosition[2] += lightMoveSpeed;
		lightZ = diffuseLightPosition[2];
	}
	if (IsKeyPressed('O'))
	{
		diffuseLightPosition[2] -= lightMoveSpeed;
		lightZ = diffuseLightPosition[2];
	}
}

// Robot Movement and Rotation
void InputManager::UpdateRobotMovement()
{
	if (robot) {
		if (IsKeyPressed('1')) { robot->RotateHeadY(-0.05f); }
		if (IsKeyPressed('2')) { robot->RotateHeadY(0.05f); }
		if (IsKeyPressed('3')) { robot->RotateHeadZ(0.05f); }
		if (IsKeyPressed('4')) { robot->RotateHeadZ(-0.05f); }

		if (IsKeyPressed('5')) { robot->RotateTorsoY(-0.05f); }
		if (IsKeyPressed('6')) { robot->RotateTorsoY(0.05f); }
		if (IsKeyPressed('7')) { robot->RotateTorsoZ(0.05f); }
		if (IsKeyPressed('8')) { robot->RotateTorsoZ(-0.05f); }
	}

	if (IsKeyPressed(VK_UP))
	{
		kneeRotation += 0.1f;
		if (kneeRotation >= 120.0f) {
			kneeRotation = 120.0f;
		}
	}
	if (IsKeyPressed(VK_DOWN))
	{
		kneeRotation -= 0.1f;
		if (kneeRotation <= 0.0f) {
			kneeRotation = 0.0f;
		}
	}
	if (IsKeyPressed(VK_LEFT))
	{
		hipRotation += 0.1f;
		if (hipRotation >= 45.0f) {
			hipRotation = 45.0f;
		}
	}
	if (IsKeyPressed(VK_RIGHT))
	{
		hipRotation -= 0.1f;
		if (hipRotation <= -45.0f) {
			hipRotation = -45.0f;
		}
	}

	// Arm Rotation
	if (IsKeyPressed('A'))
	{
		robot->RotateLeftShoulder(-0.1f);
	}
	if (IsKeyPressed('Z'))
	{
		robot->RotateLeftShoulder(0.1f);
	}
	if (IsKeyPressed('S'))
	{
		robot->RotateRightShoulder(-0.1f);
	}
	if (IsKeyPressed('X'))
	{
		robot->RotateRightShoulder(0.1f);
	}
	if (IsKeyPressed('D'))
	{
		robot->RotateLeftElbow(-0.1f);
	}
	if (IsKeyPressed('C'))
	{
		robot->RotateLeftElbow(0.1f);
	}
	if (IsKeyPressed('F'))
	{
		robot->RotateRightElbow(-0.1f);
	}
	if (IsKeyPressed('V'))
	{
		robot->RotateRightElbow(0.1f);
	}
	if (IsKeyPressed('G'))
	{
		robot->RotateLeftWrist(0.1f);
	}
	if (IsKeyPressed('B'))
	{
		robot->RotateLeftWrist(-0.1f);
	}
	if(IsKeyPressed('H'))
	{
		robot->RotateLeftFingers(-0.1f, 0);
	}
	if (IsKeyPressed('N'))
	{
		robot->RotateLeftFingers(0.1f, 0);
	}
	if (IsKeyPressed('J'))
	{
		robot->RotateLeftFingers(-0.1f, 1);
	}
	if (IsKeyPressed('M'))
	{
		robot->RotateLeftFingers(0.1f, 1);
	}
	if (IsKeyPressed('K'))
	{
		robot->RotateLeftFingers(-0.1f, 2);
	}
	if (IsKeyPressed('L'))
	{
		robot->RotateLeftFingers(0.1f, 2);
	}
	if (IsKeyPressed('U'))
	{
		robot->RotateLeftFingers(-0.1f, 3);
	}
	if (IsKeyPressed('I'))
	{
		robot->RotateLeftFingers(0.1f, 3);
	}
	if (IsKeyPressed('O'))
	{
		robot->RotateLeftThumb(-0.1f);
	}
	if (IsKeyPressed('P'))
	{
		robot->RotateLeftThumb(0.1f);
	}
	if (IsKeyPressed('Q')) 
	{
		robot->RotateRightWrist(0.1f);
	}
	if (IsKeyPressed('W'))
	{
		robot->RotateRightWrist(-0.1f);
	}
	if (IsKeyPressed('E'))
	{
		robot->RotateRightFingers(-0.1f, 0);
	}
	if (IsKeyPressed('R'))
	{
		robot->RotateRightFingers(0.1f, 0);
	}
	if (IsKeyPressed('T'))
	{
		robot->RotateRightFingers(-0.1f, 1);
	}
	if (IsKeyPressed('Y'))
	{
		robot->RotateRightFingers(0.1f, 1);
	}
	if (IsKeyPressed('9'))
	{
		robot->RotateRightFingers(-0.1f, 2);
	}
	if (IsKeyPressed('0'))
	{
		robot->RotateRightFingers(0.1f, 2);
	}
	if (IsKeyPressed(VK_OEM_MINUS))
	{
		robot->RotateRightFingers(-0.1f, 3);
	}
	if (IsKeyPressed(VK_OEM_PLUS))
	{
		robot->RotateRightFingers(0.1f, 3);
	}
	if (IsKeyPressed(VK_OEM_4)) // [
	{
		robot->RotateRightThumb(-0.1f);
	}
	if (IsKeyPressed(VK_OEM_6)) // ]
	{
		robot->RotateRightThumb(0.1f);
	}

}

// Animation
void InputManager::UpdateAnimation(float deltaTime)
{
	bool isWalking = false;
	float step = 2.0f * deltaTime;

	if (IsKeyPressed('W'))
	{
		isWalking = true;
		robot->MoveRobot(0.0005f);
	}

	if (IsKeyPressed('S'))
	{
		isWalking = true;
		robot->MoveRobot(-0.0005f);
	}

	if (IsKeyPressed('A'))
	{
		robot->RotateRobot(-0.05f);
	}

	if (IsKeyPressed('D'))
	{
		robot->RotateRobot(0.05f);
	}

	if (isWalking) {
		animator.RobotWalk();
	}
	else {
		if(animator.GetState() == WALK_ANIM) animator.Stop();
	}
}

void InputManager::Update(float deltaTime)
{
	// Handle continuous key input
	yawRad = camYaw * (3.14159f / 180.0f);

	if (currentMode == CAMMOVEMENT_MODE) 
	{
		UpdateCamLightMovement();
	}
	else if (currentMode == ROBOTMOVEMENT_MODE)
	{
		UpdateRobotMovement();
	}
	else 
	{
		UpdateAnimation(deltaTime);
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