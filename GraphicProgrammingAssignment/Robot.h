#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "torso.h"
#include "head.h"
#include "Weapon.h"
#include "leg.h"
#include "arm.h"

class Robot
{
private:
    torso* robotTorso;
    head* robotHead;
    Weapon* weapon;

    // Robot Position & Rotation
    float robotPosX, robotPosZ;
    float robotRotY;
    float torsoRotY, torsoRotZ;
    float headRotY, headRotZ;
    float shoulderAngle;
    float elbowAngle;
    float wristAngle;
    float fingerAngles[4];
    float thumbAngle;

    // For Knife Animation
    int knifeCount;
    float legAngle;
public:
    Robot();
    ~Robot();

    void InitializeRobotQuadratics();
    void DrawRobot();
    void MoveRobot(float delta);
    void RotateRobot(float delta);
    void RotateTorsoY(float delta);
    void RotateTorsoZ(float delta);
    void RotateHeadY(float delta);
    void RotateHeadZ(float delta);
    void RotateShoulder(float delta);
    void RotateElbow(float delta);
    void RotateWrist(float delta);
    void RotateFingers(float delta);
    void RotateThumb(float delta);
    void ResetRotations();

    head* GetHead() { return robotHead; }
    torso* GetTorso() { return robotTorso; }
    Weapon* GetWeapon() { return weapon; }

    float GetRobotPosX() const { return robotPosX; }
    float GetRobotPosZ() const { return robotPosZ; }
    float GetRobotRotationY() const { return robotRotY; }
    float GetHeadRotationY() const { return headRotY; }
    float GetHeadRotationZ() const { return headRotZ; }
    float GetTorsoRotationY() const { return torsoRotY; }
    float GetTorsoRotationZ() const { return torsoRotZ; }
    float GetShoulderAngle() const { return shoulderAngle; }
    float GetElbowAngle() const { return elbowAngle; }
    float GetWristAngle() const { return wristAngle; }
    float GetFingerAngles() const { return fingerAngle; }
    float GetThumbAngle() const { return thumbAngle; }

    // Animation
    void Update(float deltaTime);
    void StartJump();
    void StartSpecialAnimation();
};