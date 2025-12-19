#include "texture.h"
#include <gl/GLU.h>

GLuint blueSteelTexture = 0;
GLuint steelTexture = 0;
GLuint darkSteelTexture = 0;
GLuint redSteelTexture = 0;
GLuint carbonTexture = 0;

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

	glGenTextures(1, &steelTexture); // Apply name to the texture
	glBindTexture(GL_TEXTURE_2D, steelTexture); // Work for this texture now

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture

	// darkSteel Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/darkSteel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &darkSteelTexture); // Apply name to the texture
	glBindTexture(GL_TEXTURE_2D, darkSteelTexture); // Work for this texture now

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture

	// redSteel Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"Asset/redSteel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &redSteelTexture); // Apply name to the texture
	glBindTexture(GL_TEXTURE_2D, redSteelTexture); // Work for this texture now

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture
	
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
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // Grab BMP data and store in current active texture
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
}

void BindTexture(GLuint texID) 
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
}