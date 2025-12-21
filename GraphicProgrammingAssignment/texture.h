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

void LoadTexture();
void ReleaseTexture();

#endif
