#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>
#include <gl/GL.h>

extern GLuint blueSteelTexture;
extern GLuint steelTexture;
extern GLuint darkSteelTexture;
extern GLuint redSteelTexture;
extern GLuint carbonTexture;
extern GLuint darkBlueTexture;
extern GLuint whiteMetalTexture;
extern GLuint knifeTipTexture;
extern GLuint crimsonWebTexture;
extern GLuint slaughterTexture;
extern GLuint hatRedTexture;
extern GLuint hatWhiteTexture;
extern GLuint monitorTexture;
extern GLuint energyTexture;

void LoadTexture();
void ReleaseTexture();

#endif
