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

    float robotPosX, robotPosY, robotPosZ;
    float robotRotY;
    float torsoRotY, torsoRotZ;
    float headRotY, headRotZ;

public:
    Robot();
    ~Robot();

    void InitializeRobotQuadratics();
    void DrawRobot();
    void SetPosition(float x, float y, float z);
    void RotateRobot(float delta);
    void RotateTorsoY(float delta);
    void RotateTorsoZ(float delta);
    void RotateHeadY(float delta);
    void RotateHeadZ(float delta);
    void ResetRotations();

    head* GetHead() { return robotHead; }
    torso* GetTorso() { return robotTorso; }
    Weapon* GetWeapon() { return weapon; }

    float GetHeadRotationY() const { return headRotY; }
    float GetHeadRotationZ() const { return headRotZ; }
    float GetTorsoRotationY() const { return torsoRotY; }
    float GetTorsoRotationZ() const { return torsoRotZ; }
};