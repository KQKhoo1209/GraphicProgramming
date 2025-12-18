#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>
#include <gl/GL.h>

extern GLuint blueSteelTexture;
extern GLuint steelTexture;
extern GLuint darkSteelTexture;
extern GLuint redSteelTexture;

void LoadTexture();
void ReleaseTexture();

#endif
