#pragma once

#include <Windows.h>

// Forward declarations
class Camera;
class Robot;

enum InputMode
{
	CAMMOVEMENT_MODE,
	ROBOTMOVEMENT_MODE,
	ANIMATION_MODE
};

class InputManager
{
private:
	HWND hWnd;
	int windowWidth;
	int windowHeight;

	// Camera state
	float camX, camY, camZ;
	float camYaw, camPitch;
	float yawRad;

	// Light position
	float lightX, lightY, lightZ;

	// Input settings
	float moveSpeed;
	float mouseSensitivity;
	float lightMoveSpeed;

	// Mouse state
	int lastMouseX, lastMouseY;
	bool firstMouse;

	// Key states (for continuous input)
	bool keys[256];

	// Handle keyboard input
	void HandleKeyDown(WPARAM wParam);
	void HandleKeyUp(WPARAM wParam);

	// Handle mouse input
	void HandleMouseMove(HWND hWnd, LPARAM lParam);
	void CenterMouseCursor(HWND hWnd);

	void UpdateCamLightMovement();
	void UpdateRobotMovement();
	void UpdateAnimation(float deltaTime);

	Robot* robot;

public:
	InputManager(Robot* robotObj);
	~InputManager();

	static InputMode currentMode;

	// Initialize input manager with window handle and dimensions
	void Initialize(HWND hWnd, int windowWidth, int windowHeight);

	// Handle Windows messages for input
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Update function (called each frame for continuous input)
	void Update(float deltaTime);

	// Getters for camera movement
	float GetMoveSpeed() const { return moveSpeed; }
	float GetMouseSensitivity() const { return mouseSensitivity; }

	// Setters
	void SetMoveSpeed(float speed) { moveSpeed = speed; }
	void SetMouseSensitivity(float sensitivity) { mouseSensitivity = sensitivity; }
	void SetWindowDimensions(int width, int height);

	// Window dimension getters
	int GetWindowWidth() const { return windowWidth; }
	int GetWindowHeight() const { return windowHeight; }

	// Camera movement flags (for continuous movement)
	bool IsKeyPressed(int key) const;

	// Camera rotation
	float GetCameraYaw() const { return camYaw; }
	float GetCameraPitch() const { return camPitch; }
	void SetCameraYaw(float yaw) { camYaw = yaw; }
	void SetCameraPitch(float pitch) { camPitch = pitch; }

	// Camera position (for movement calculations)
	float GetCameraX() const { return camX; }
	float GetCameraY() const { return camY; }
	float GetCameraZ() const { return camZ; }
	void SetCameraPosition(float x, float y, float z) { camX = x; camY = y; camZ = z; }
	void UpdateCameraPosition(float deltaX, float deltaY, float deltaZ);

	// Light position
	float GetLightX() const { return lightX; }
	float GetLightY() const { return lightY; }
	float GetLightZ() const { return lightZ; }
	void SetLightPosition(float x, float y, float z);
	void SetLightPositionPointer(float x, float y, float z) { lightX = x; lightY = y; lightZ = z; }
	void UpdateLightPosition(float deltaX, float deltaY, float deltaZ);
	float GetLightMoveSpeed() const { return lightMoveSpeed; }
	void SetLightMoveSpeed(float speed) { lightMoveSpeed = speed; }

	void SetRobot(Robot* robotObj);
};

