#pragma once
#ifndef HELPERFUNCTION_H
#define HELPERFUNCTION_H

void QuadNormal(float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4);
void TriNormal(float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3);
void DrawCube(float size);
void DrawCustomBox(
    float v0x, float v0y, float v0z,
    float v1x, float v1y, float v1z,
    float v2x, float v2y, float v2z,
    float v3x, float v3y, float v3z,
    float v4x, float v4y, float v4z,
    float v5x, float v5y, float v5z,
    float v6x, float v6y, float v6z,
    float v7x, float v7y, float v7z);

#endif