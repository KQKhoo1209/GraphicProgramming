#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include "InputManager.h"
#include "Animator.h"
#include "Robot.h"
#include "torso.h"
#include "leg.h"
#include "arm.h"
#include "texture.h"
#include "Timer.h"

#pragma comment (lib, "OpenGL32.lib") // A shortcut. Only works with windows platform
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

HWND hWnd;
int windowWidth = 1280;
int windowHeight = 720;

int questionToDisplay = 0;
int change = 1;
float speed = 0.01f;

float angle = 0.0f;
float scaling = 1.0f;

Timer timer;
InputManager* inputManager = nullptr;
Robot* robot = nullptr;

// Camera direction vectors (calculated from yaw/pitch)
float yawRad;
float pitchRad;
float dirX;
float dirY;
float dirZ;
int camSwitch = 1;

float bridgeRot = 0.0f;

int spherePoint = 8;

GLUquadricObj* var = gluNewQuadric();
GLUquadricObj* tower = gluNewQuadric();

// Lightning
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f };
GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f };
GLfloat diffuseLightPosition[] = { 0.0f, 1.0f, 0.0f }; // Where the light located at

GLfloat redColor[] = { 1.0f, 0.0f, 0.0f };
GLfloat darkRedColor[] = { 0.75f, 0.0f, 0.0f };
GLfloat greenColor[] = { 0.0f, 1.0f, 0.0f };
GLfloat blueColor[] = { 0.0f, 0.0f, 1.0f };
GLfloat magentaColor[] = { 1.0f, 0.0f, 1.0f };
GLfloat yellowColor[] = { 1.0f, 1.0f, 0.0f };
GLfloat lightYellowColor[] = { 1.0f, 1.0f, 0.77f };
GLfloat cyanColor[] = { 0.0f, 1.0f, 1.0f };
GLfloat brownColor[] = { 0.7f, 0.5f, 0.3f };
GLfloat lightBrownColor[] = { 0.8f, 0.6f, 0.4f };
GLfloat mintColor[] = { 0.6f, 1.0f, 0.6f };
GLfloat vanillaColor[] = { 0.82f, 0.75f, 0.66f };
GLfloat strawberryColor[] = { 0.9f, 0.53f, 0.54f };
GLfloat chocoColor[] = { 0.94f, 0.8f, 0.64f };
GLfloat chocoStickColor[] = { 0.48f, 0.25f, 0.0f };
GLfloat grayColor[] = { 0.25f, 0.25f, 0.25f };
GLfloat yellowishBrownColor[] = { 0.72f, 0.58f, 0.0f };
GLfloat whiteColor[] = { 1.0f, 1.0f, 1.0f };
GLfloat blackColor[] = { 0.0f, 0.0f, 0.0f };

void CameraMove()
{
	if (!inputManager) return;

	float camYaw = inputManager->GetCameraYaw();
	float camPitch = inputManager->GetCameraPitch();
	float camX = inputManager->GetCameraX();
	float camY = inputManager->GetCameraY();
	float camZ = inputManager->GetCameraZ();

	yawRad = camYaw * (3.14159f / 180.0f);
	pitchRad = camPitch * (3.14159f / 180.0f);

	dirX = cos(pitchRad) * sin(yawRad);
	dirY = sin(pitchRad);
	dirZ = -cos(pitchRad) * cos(yawRad);

	gluLookAt(
		camX, camY, camZ,                // camera position
		camX + dirX, camY + dirY, camZ + dirZ, // look target
		0.0f, 1.0f, 0.0f                 // fixed up vector (world Y-axis)
	);
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Let InputManager handle input messages
	if (inputManager)
	{
		LRESULT result = inputManager->HandleMessage(hWnd, msg, wParam, lParam);
		if (result == 0) // Message was handled
			return result;
	}

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool InitPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void Display() // Render
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Buffer

	// Lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, diffuseLightPosition);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	// Set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate aspect ratio dynamically from window size
	int windowWidth = inputManager ? inputManager->GetWindowWidth() : 1280;
	int windowHeight = inputManager ? inputManager->GetWindowHeight() : 720;
	float aspectRatio = (float)windowWidth / (float)windowHeight;
	if (windowHeight == 0) aspectRatio = 1.777f; // Prevent division by zero

	// Camera View
	if (camSwitch == 1) {
		gluPerspective(50.6272, aspectRatio, 0.01f, 100.0f);
	}
	else if(camSwitch == -1) {
		glOrtho(-5, 5, -5, 5, -5, 5);
	}
	//glFrustum(-0.1f, 0.1f, -0.1f, 0.1f, 0.2, 2);

	// Set up modelview matrix and camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CameraMove();

	GLfloat matrix[16] = { diffuseLightPosition[1], 0,0,0,
						-diffuseLightPosition[0], 0, -diffuseLightPosition[2], -1,
						0, 0, diffuseLightPosition[1], 0,
						0, 0, 0, diffuseLightPosition[1] };

	// Light indicator (reuse existing light code)
	glPushMatrix();
	glTranslatef(diffuseLightPosition[0], diffuseLightPosition[1] + 1.0f, diffuseLightPosition[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
	gluSphere(var, 0.05f, 10, 10);
	glPopMatrix();

	if (robot)
	{
		robot->DrawRobot();
	}

	//switch (questionToDisplay)
	//{
	//case 0:
	//{
	//	// Light indicator (reuse existing light code)
	//	glPushMatrix();
	//	glTranslatef(diffuseLightPosition[0], diffuseLightPosition[1], diffuseLightPosition[2]);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
	//	gluSphere(var, 0.05f, 10, 10);
	//	glPopMatrix();

	//	// ===== YOUR ROBOT LEGS =====
	//	glPushMatrix();
	//	glTranslatef(0.0f, 1.0f, 0.0f); // lift above ground
	//	drawRobotLegs();
	//	glPopMatrix();

	//	break;
	//	
	//	break;
	//}
	//case 1:
	//{
	//	
	//	break;
	//}
	//break;
	//case 2: 
	//{

	//	break;
	//}
	//case 3: // robot legs
	//{
	//	
	//}
	//case 4:
	//{

	//	// Light indicator (reuse existing light code)
	//	glPushMatrix();
	//	glTranslatef(diffuseLightPosition[0], diffuseLightPosition[1], diffuseLightPosition[2]);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
	//	gluSphere(var, 0.05f, 10, 10);
	//	glPopMatrix();

	//	// ===== YOUR ROBOT LEGS =====
	//	glPushMatrix();
	//	glTranslatef(0.0f, 1.0f, 0.0f); // lift above ground
	//	DrawArm();
	//	glPopMatrix();
	//	break;
	//}
	//default:
	//	break;
	//}
	
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------
void InitClass()
{
	robot = new Robot();
	robot->InitializeRobotQuadratics();

	inputManager = new InputManager(robot);
	inputManager->Initialize(hWnd, windowWidth, windowHeight);
}

void Release()
{
	gluDeleteQuadric(var);
	gluDeleteQuadric(tower);
}

void ReleaseClass()
{
	// Clean up Input Manager
	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}

	if (robot)
	{
		delete robot;
		robot = nullptr;
	}
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	// Create windowed mode window
	hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
		NULL, NULL, wc.hInstance, NULL);

	timer.Reset();

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	// HDC = Handle to Display Context
	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	InitPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	LoadTexture();
	InitClass();

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);
	SetFocus(hWnd); // Ensure window receives keyboard input
	SetForegroundWindow(hWnd); // Bring window to front

	// Message Loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		timer.Tick();
		float dt = timer.GetDeltaTime();

		// Update input manager (handles continuous key input)
		if (inputManager)
		{
			inputManager->Update(dt);
			animator.AnimUpdate(dt);
			
		}

		Display();
		SwapBuffers(hdc);
	}

	Release();
	ReleaseTexture();
	ReleaseClass();

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------