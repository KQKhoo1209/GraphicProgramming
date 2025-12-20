#include "texture.h"
#include <gl/GLU.h>

GLuint blueSteelTexture = 0;
GLuint steelTexture = 0;
GLuint darkSteelTexture = 0;
GLuint redSteelTexture = 0;
GLuint carbonTexture = 0;
GLuint darkBlueTexture = 0;
GLuint whiteMetalTexture = 0;
GLuint knifeTipTexture = 0;

static BITMAP BMP;
static HBITMAP hBMP = NULL;

void LoadTexture()
{
	// blueSteel Texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/blueSteel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &blueSteelTexture); // Apply name to the texture
	glBindTexture(GL_TEXTURE_2D, blueSteelTexture); // Work for this texture now

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture

	// steel Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/steel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &steelTexture);
	glBindTexture(GL_TEXTURE_2D, steelTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// darkSteel Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/darkSteel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &darkSteelTexture);
	glBindTexture(GL_TEXTURE_2D, darkSteelTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// redSteel Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/redSteel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &redSteelTexture);
	glBindTexture(GL_TEXTURE_2D, redSteelTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	
	// Carbon Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/carbon.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BITMAP), &BMP);

	glGenTextures(1, &carbonTexture);
	glBindTexture(GL_TEXTURE_2D, carbonTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	
	// Dark Blue Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/darkBlue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BITMAP), &BMP);

	glGenTextures(1, &darkBlueTexture);
	glBindTexture(GL_TEXTURE_2D, darkBlueTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// White Metal Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/whiteMetal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BITMAP), &BMP);

	glGenTextures(1, &whiteMetalTexture);
	glBindTexture(GL_TEXTURE_2D, whiteMetalTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// Knife Tip Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/knifeTip.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BITMAP), &BMP);

	glGenTextures(1, &knifeTipTexture);
	glBindTexture(GL_TEXTURE_2D, knifeTipTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
}

void ReleaseTexture()
{
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &darkSteelTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &redSteelTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &steelTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &blueSteelTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &carbonTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &darkBlueTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &whiteMetalTexture);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &knifeTipTexture);
}