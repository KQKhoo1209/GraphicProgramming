#pragma once
class Weapon;

void DrawHand(const float* fingerAngles, float thumbAngle);
void DrawArm(float shoulderSwing, float shoulderRaise, float elbow, float wrist, const float* fingerAngles, float thumbAngle, Weapon* weaponE = nullptr,bool drawWeapon = false);

extern float shoulderAngle;
extern float elbowAngle;
extern float fingerAngle;
extern float wristAngle;
extern float thumbAngle;
