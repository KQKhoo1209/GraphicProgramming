#pragma once
void DrawHand(const float* fingerAngles, float thumbAngle);
void DrawArm(float shoulder, float elbow, float wrist, const float* fingerAngles, float thumbAngle);

extern float shoulderAngle;
extern float elbowAngle;
extern float fingerAngle;
extern float wristAngle;
extern float thumbAngle;
