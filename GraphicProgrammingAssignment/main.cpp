#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include "InputManager.h"

#pragma comment (lib, "OpenGL32.lib") // A shortcut. Only works with windows platform
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

int questionToDisplay = 0;
int change = 1;
float speed = 0.01f;

float angle = 0.0f;
float scaling = 1.0f;

// Input Manager
InputManager* inputManager = nullptr;

// Camera direction vectors (calculated from yaw/pitch)
float yawRad;
float pitchRad;
float dirX;
float dirY;
float dirZ;

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

GLuint woodTexture = 0;
GLuint brickTexture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

void LoadTexture()
{
	// Wood Texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Box.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &woodTexture); // Apply name to the texture
	glBindTexture(GL_TEXTURE_2D, woodTexture); // Work for this texture now

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture

	// Brick Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"YellowBrick.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &brickTexture); // Apply name to the texture
	glBindTexture(GL_TEXTURE_2D, brickTexture); // Work for this texture now

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture
}

void ReleaseTexture()
{
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &woodTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &brickTexture);
}

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

void Cube()
{
	// Front Quad
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, woodTexture);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);*/
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();

	// Back Quad
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	glPopMatrix();

	// Left Quad
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();

	// Right Quad
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();
	glPopMatrix();

	// Up Quad
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.65f, 0.0f); // Orange
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();
	glPopMatrix();

	// Down Quad
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();
	glPopMatrix();
}

void Background()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cyanColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyanColor);

	glPushMatrix();
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f, -0.81f, -2.0f);
	glVertex3f(-2.0f, -0.81f, 2.0f);
	glVertex3f(2.0f, -0.81f, 2.0f);
	glVertex3f(2.0f, -0.81f, -2.0f);
	glEnd();
	glPopMatrix();
}

void TowerFace()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-0.1f, 0.5f, 0.0f);
	glVertex3f(-0.1f, -0.5f, 0.0f);
	glVertex3f(0.1f, -0.5f, 0.0f);
	glVertex3f(0.1f, 0.5f, 0.0f);
	glEnd();
	glPopMatrix();
}

void TowerCube()
{
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.1f);
	TowerFace();
	glPopMatrix();

	glPushMatrix();
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 0.0f, -0.1f);
	TowerFace();
	glPopMatrix();

	// Left Face
	glPushMatrix();
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTranslatef(-0.1f, 0.1f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	TowerFace();
	glPopMatrix();

	// Right Face
	glPushMatrix();
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.1f, 0.1f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	TowerFace();
	glPopMatrix();
}

void TowerCylinder()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColor);
	glBindTexture(GL_TEXTURE_2D, brickTexture);
	gluQuadricTexture(tower, GL_TRUE);
	gluQuadricDrawStyle(tower, GLU_FILL);
	gluCylinder(tower, 0.05f, 0.05f, 1.0f, 8, 1);
	glPopMatrix();
}

void TowerCornerRoof()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, brownColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brownColor);
	gluQuadricDrawStyle(tower, GLU_FILL);
	gluCylinder(tower, 0.075f, 0.0f, 0.2f, 8, 1);
	glPopMatrix();
}

void TowerCorner()
{
	glPushMatrix();
	glTranslatef(-0.1f, 0.5f, -0.1f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	TowerCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1f, 0.5f, 0.1f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	TowerCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.5f, 0.1f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	TowerCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.5f, -0.1f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	TowerCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1f, 0.5f, -0.1f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	TowerCornerRoof();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.1f, 0.5f, 0.1f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	TowerCornerRoof();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.5f, 0.1f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	TowerCornerRoof();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, 0.5f, -0.1f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	TowerCornerRoof();
	glPopMatrix();
}

void TowerMiddle()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightYellowColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightYellowColor);
	glTranslatef(0.0f, 0.7f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	TowerCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.55f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.5f, 1.5f, 1.5f);
	TowerCornerRoof();
	glPopMatrix();
}

void TowerBottomUpDown()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-0.2f, 0.0f, -0.2f);
	glVertex3f(-0.2f, 0.0f, 0.2f);
	glVertex3f(0.2f, 0.0f, 0.2f);
	glVertex3f(0.2f, 0.0f, -0.2f);
	glEnd();
	glPopMatrix();
}

void TowerBottomSide()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-0.2f, 0.15f, 0.0f);
	glVertex3f(-0.2f, -0.15f, 0.f);
	glVertex3f(0.2f, -0.15f, 0.f);
	glVertex3f(0.2f, 0.15f, 0.0f);
	glEnd();
	glPopMatrix();
}

void TowerBottom()
{
	// Upper Face
	glPushMatrix();
	glNormal3f(0.0f, 1.0f, 0.0f);
	TowerBottomUpDown();
	glPopMatrix();

	// Bottom Face
	glPushMatrix();
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTranslatef(0.0f, -0.3f, 0.0f);
	TowerBottomUpDown();
	glPopMatrix();

	// Front Face
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.15f, 0.2f);
	TowerBottomSide();
	glPopMatrix();

	// Back Face
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, -0.15f, -0.2f);
	TowerBottomSide();
	glPopMatrix();

	// Right Face
	glPushMatrix();
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.2f, -0.15f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	TowerBottomSide();
	glPopMatrix();

	// Left Face
	glPushMatrix();
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTranslatef(-0.2f, -0.15f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	TowerBottomSide();
	glPopMatrix();
}

void Tower()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightYellowColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightYellowColor);
	TowerCube();
	TowerCorner();
	TowerMiddle();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightBrownColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightBrownColor);
	glTranslatef(0.0f, -0.5f, 0.0f);
	TowerBottom();
	glPopMatrix();
}

void PillarSide()
{
	// Front Face
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.04f);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.04f, 0.0f);
	glVertex3f(-0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, 0.04f, 0.0f);
	glEnd();
	glPopMatrix();

	// Back Face
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 0.0f, -0.04f);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.04f, 0.0f);
	glVertex3f(-0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, 0.04f, 0.0f);
	glEnd();
	glPopMatrix();

	// Upper Face
	glPushMatrix();
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.04f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.04f, 0.0f);
	glVertex3f(-0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, 0.04f, 0.0f);
	glEnd();
	glPopMatrix();

	// Lower Face
	glPushMatrix();
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTranslatef(0.0f, -0.04f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.04f, 0.0f);
	glVertex3f(-0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, -0.04f, 0.0f);
	glVertex3f(0.5f, 0.04f, 0.0f);
	glEnd();
	glPopMatrix();
}

void UpperPillar()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightYellowColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightYellowColor);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.1f);
	PillarSide();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.1f);
	PillarSide();
	glPopMatrix();
}

void TwinTower()
{
	glPushMatrix();
	glTranslatef(-0.6f, 0.0f, 0.0f);
	Tower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6f, 0.0f, 0.0f);
	Tower();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0f);
	UpperPillar();
	glPopMatrix();
}

void BridgeUpDown()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.0f, -0.15f);
	glVertex3f(-0.5f, 0.0f, 0.15f);
	glVertex3f(0.5f, 0.0f, 0.15f);
	glVertex3f(0.5f, 0.0f, -0.15f);
	glEnd();
	glPopMatrix();
}

void BridgeFrontBack()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.5f, -0.05f, 0.0f);
	glVertex3f(0.5f, -0.05f, 0.0f);
	glVertex3f(0.5f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
}

void BridgeMiddle()
{
	glPushMatrix();
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.05f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, 0.0f, -0.01f);
	glVertex3f(-0.5f, 0.0f, 0.01f);
	glVertex3f(0.5f, 0.0f, 0.01f);
	glVertex3f(0.5f, 0.0f, -0.01f);
	glEnd();
	glPopMatrix();
}

void BridgeBody()
{
	// Upper Face
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grayColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grayColor);

	glPushMatrix();
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.05f, 0.0f);
	BridgeUpDown();
	glPopMatrix();

	// Bottom Face
	glPushMatrix();
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTranslatef(0.0f, -0.05f, 0.0f);
	BridgeUpDown();
	glPopMatrix();

	// Front Face
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.1f);
	BridgeFrontBack();
	glPopMatrix();

	// Back Face
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 0.0f, -0.1f);
	BridgeFrontBack();
	glPopMatrix();

	// Middle Line
	glPushMatrix();
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.001f, 0.0f);
	BridgeMiddle();
	glPopMatrix();
}

void RotateBridge()
{
	glPushMatrix();
	glTranslatef(-0.45f, 0.0f, 0.0f);
	glRotatef(bridgeRot, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.25f, 0.0f, 0.0f);
	glScalef(0.4f, 1.0f, 1.0f);
	BridgeBody();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.45f, 0.0f, 0.0f);
	glRotatef(bridgeRot * -1, 0.0f, 0.0f, 1.0f);
	glTranslatef(-0.25f, 0.0f, 0.0f);
	glScalef(0.4f, 1.0f, 1.0f);
	BridgeBody();
	glPopMatrix();
}

void Line()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);

	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	gluQuadricDrawStyle(tower, GLU_FILL);
	gluCylinder(tower, 0.0025f, 0.0025f, 0.5f, 8, 1);
	glPopMatrix();
}

void Lines()
{
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, 0.0f);
	Line();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2f, -0.1f, 0.0f);
	glScalef(1.0f, 0.8f, 1.0f);
	Line();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3f, -0.2f, 0.0f);
	glScalef(1.0f, 0.6f, 1.0f);
	Line();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4f, -0.3f, 0.0f);
	glScalef(1.0f, 0.4f, 1.0f);
	Line();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.4f, 0.0f);
	glScalef(1.0f, 0.2f, 1.0f);
	Line();
	glPopMatrix();
}

void BridgeLine()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.1f);
	Lines();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.1f);
	Lines();
	glPopMatrix();
}

void PillarCylinder()
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blueColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blueColor);
	gluQuadricDrawStyle(tower, GLU_FILL);
	gluCylinder(tower, 0.01f, 0.01f, 1.0f, 8, 1);
	glPopMatrix();
}

void Pillar()
{
	glPushMatrix();
	glRotatef(-45, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	PillarCylinder();
	glPopMatrix();
}

void Pillars()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.2f, 0.1f);
	Pillar();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.2f, -0.1f);
	Pillar();
	glPopMatrix();
}

void Bridge()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grayColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grayColor);
	// Right Bridge
	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 0.0f);
	BridgeBody();
	glPopMatrix();

	// Left Bridge
	glPushMatrix();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	BridgeBody();
	glPopMatrix();

	glPushMatrix();
	RotateBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.8f, 0.55f, 0.0f);
	BridgeLine();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8f, 0.55f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	BridgeLine();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7f, 0.55f, 0.0f);
	Pillars();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.7f, 0.55f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	Pillars();
	glPopMatrix();
}

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

	// Camera View
	//glOrtho(-4, 4, -4, 4, 4, -4);
	//glFrustum(-0.1f, 0.1f, -0.1f, 0.1f, 0.2, 2);

	// Set up projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate aspect ratio dynamically from window size
	int windowWidth = inputManager ? inputManager->GetWindowWidth() : 1280;
	int windowHeight = inputManager ? inputManager->GetWindowHeight() : 720;
	float aspectRatio = (float)windowWidth / (float)windowHeight;
	if (windowHeight == 0) aspectRatio = 1.777f; // Prevent division by zero

	gluPerspective(50.6272, aspectRatio, 0.01f, 100.0f);

	// Set up modelview matrix and camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CameraMove();

	GLfloat matrix[16] = { diffuseLightPosition[1], 0,0,0,
						-diffuseLightPosition[0], 0, -diffuseLightPosition[2], -1,
						0, 0, diffuseLightPosition[1], 0,
						0, 0, 0, diffuseLightPosition[1] };

	switch (questionToDisplay)
	{
	case 0:
	{
		glPushMatrix();
		glTranslatef(diffuseLightPosition[0], diffuseLightPosition[1], diffuseLightPosition[2]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
		gluSphere(var, 0.05, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glBindTexture(GL_TEXTURE_2D, brickTexture);
		glPopMatrix();

		// Tower Bridge
		glPushMatrix();
		Background();
		glPushMatrix();
		TwinTower();
		glPushMatrix();
		glTranslatef(0.0f, -0.56f, 0.0f);
		Bridge();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		break;
	}
	case 1:
	{
		glPushMatrix();
		glTranslatef(diffuseLightPosition[0], diffuseLightPosition[1], diffuseLightPosition[2]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
		gluSphere(var, 0.05, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(1.0f, 5.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glPopMatrix();

		glPushMatrix();
		Cube();
		glPopMatrix();
		break;
	}
	case 2:
	{
		// Light
		glPushMatrix();
		glTranslatef(diffuseLightPosition[0], diffuseLightPosition[1], diffuseLightPosition[2]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
		gluSphere(var, 0.05, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
		glVertex3f(-2.5f, 0.0f, -2.5f);
		glVertex3f(-2.5f, 0.0f, 2.5f);
		glVertex3f(2.5f, 0.0f, 2.5f);
		glVertex3f(2.5f, 0.0f, -2.5f);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
		gluQuadricDrawStyle(var, GLU_FILL);
		gluSphere(var, 0.2f, 10, 10);
		glPopMatrix();

		// Draw the shadow
		glPushMatrix();
		glTranslatef(0.0f, 0.001f, 0.0f);
		glMultMatrixf(matrix);
		glTranslatef(0.0f, 0.5f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blackColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackColor);
		gluQuadricDrawStyle(var, GLU_FILL);
		gluSphere(var, 0.1f, 10, 10);
		glPopMatrix();
		break;
	}
	case 3:
	{
		break;
	}
	case 4:
	{

		break;
	}
	default:
		break;
	}
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void Release()
{
	gluDeleteQuadric(var);
	gluDeleteQuadric(tower);
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

	// Initialize Input Manager
	inputManager = new InputManager();
	int windowWidth = 1280;
	int windowHeight = 720;

	// Create windowed mode window
	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Input Manager with window handle
	inputManager->Initialize(hWnd, windowWidth, windowHeight);

	// Set pointer to diffuse light position array
	//inputManager->SetLightPositionPointer(diffuseLightPosition[]);

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

		// Update input manager (handles continuous key input)
		if (inputManager)
		{
			inputManager->Update();
		}

		Display();

		SwapBuffers(hdc);
	}

	Release();
	ReleaseTexture();

	// Clean up Input Manager
	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------