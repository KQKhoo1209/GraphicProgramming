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

    float robotPosX, robotPosZ;
    float robotRotY;
    float torsoRotY, torsoRotZ;
    float headRotY, headRotZ;

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
};