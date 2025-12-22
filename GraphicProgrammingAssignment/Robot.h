#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "torso.h"
#include "head.h"
#include "Weapon.h"
#include "leg.h"
#include "arm.h"
#include "hat.h"

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
    float leftSwing, rightSwing;
    float leftRaise, rightRaise;
    float leftElbow, rightElbow;
    float leftWristAngle, rightWristAngle;
    float leftFingerAngles[4] = { 0 }, rightFingerAngles[4] = { 0 };
    float leftThumbAngle, rightThumbAngle;
    bool hasHat;

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
    void RotateLeftShoulder(float delta);
    void RotateRightShoulder(float delta);
    void RotateLeftElbow(float delta);
    void RotateRightElbow(float delta);
    void RotateLeftWrist(float delta);
    void RotateRightWrist(float delta);
    void RotateLeftFingers(float delta, int fingerIndex);
    void RotateRightFingers(float delta, int fingerIndex);
    void RotateLeftThumb(float delta);
    void RotateRightThumb(float delta);
    void ResetRotations();
    void ShowHat();

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
    float GetLeftShoulderAngle() const { return leftSwing; }
    float GetLeftElbowAngle() const { return leftElbow; }
    float GetLeftWristAngle() const { return leftWristAngle; }
    float GetLeftThumbAngle() const { return leftThumbAngle; }
    float GetLeftFingerAngle(int index) const { return leftFingerAngles[index];}
    float GetRightShoulderAngle() const { return rightSwing; }
    float GetRightElbowAngle() const { return rightElbow; }
    float GetRightWristAngle() const { return rightWristAngle; }
    float GetRightThumbAngle() const { return rightThumbAngle; }
    float GetRightFingerAngle(int index) const { return rightFingerAngles[index]; }

    // Animation
    void Update(float deltaTime);
    void StartJump();
    void StartSpecialAnimation();
    void StartSwingKnife();
};