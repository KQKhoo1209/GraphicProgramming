#ifndef LEG_H
#define LEG_H
#pragma once

extern float hipRotation;
extern float kneeRotation;

extern bool isWalking;
extern float walkPhase;

// Draw both legs
void drawRobotLegs();

void drawSingleLeg(float xOffset);

void drawCuboid(float w, float h, float d);

#endif
