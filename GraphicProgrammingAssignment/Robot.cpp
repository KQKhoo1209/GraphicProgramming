#include <Windows.h>
#include "Robot.h"
#include "Animator.h"

extern GLfloat whiteColor[];

Robot::Robot()
    : robotTorso(nullptr)
    , robotHead(nullptr)
    , weapon(nullptr)
    , robotPosZ(0.0f)
    , robotRotY(0.0f)
    , torsoRotY(0.0f), torsoRotZ(0.0f)
    , headRotY(0.0f), headRotZ(0.0f)
{
}

Robot::~Robot()
{
    if (robotTorso) delete robotTorso;
    if (robotHead) delete robotHead;
    if (weapon) delete weapon;
}

void Robot::InitializeRobotQuadratics()
{
    // Create and initialize body parts
    robotTorso = new torso();
    robotTorso->InitializeTorsoQuadratics();

    robotHead = new head();
    robotHead->InitializeHeadQuadratics();

    weapon = new Weapon();
    weapon->InitializeWeaponQuadratics();
}

void Robot::MoveRobot(float delta)
{
    float angleRad = (robotRotY * 3.14) / 180;

    float dx = sin(angleRad) * delta;
    float dz = cos(angleRad) * delta;

    robotPosX += dx;
    robotPosZ += dz;
}

void Robot::RotateRobot(float delta)
{
    robotRotY += delta;
    // Keep within 0-360 range
    if (robotRotY > 360.0f) robotRotY -= 360.0f;
    if (robotRotY < 0.0f) robotRotY += 360.0f;
}

void Robot::RotateTorsoY(float delta)
{
    torsoRotY += delta;
    // Limit if needed
    if (torsoRotY > 45.0f) torsoRotY = 45.0f;
    else if (torsoRotY < -45.0f) torsoRotY = -45.0f;
}

void Robot::RotateTorsoZ(float delta)
{
    torsoRotZ += delta;
    // Limit if needed
    if (torsoRotZ > 30.0f) torsoRotZ = 30.0f;
    else if (torsoRotZ < 0.0f) torsoRotZ = 0.0f;
}

void Robot::RotateHeadY(float delta)
{
    headRotY += delta;
    // Limit to ±30 degrees
    if (headRotY > 30.0f)
        headRotY = 30.0f;
    else if (headRotY < -30.0f)
        headRotY = -30.0f;
}

void Robot::RotateHeadZ(float delta)
{
    headRotZ += delta;
    // Limit to ±30 degrees
    if (headRotZ > 30.0f)
        headRotZ = 30.0f;
    else if (headRotZ < -30.0f)
        headRotZ = -30.0f;
}

void Robot::ResetRotations()
{
    robotPosX = 0.0f;
    robotPosZ = 0.0f;
    robotRotY = 0.0f;
    torsoRotY = 0.0f;
    torsoRotZ = 0.0f;
    headRotY = 0.0f;
    headRotZ = 0.0f;
}

void Robot::DrawRobot()
{
    glPushMatrix();
    glTranslatef(robotPosX, 0.0f, robotPosZ);
    glRotatef(robotRotY, 0.0f, 1.0f, 0.0f);

        glPushMatrix();
        glTranslatef(0.0f, -0.75f, 0.0f);
        glScalef(0.8f, 1.1f, 0.8f);
        drawRobotLegs();
        glPopMatrix();

        glPushMatrix();
        glRotatef(torsoRotY, 0.0f, 1.0f, 0.0f);
        glRotatef(torsoRotZ, 1.0f, 0.0f, 0.0f);
        robotTorso->DrawTorso();

            glPushMatrix();
            glTranslatef(0.0f, 1.225f, 0.0f);
            glRotatef(headRotY, 0.0f, 1.0f, 0.0f);
            glRotatef(headRotZ, 1.0f, 0.0f, 0.0f);
            robotHead->DrawHead();
            glPopMatrix();

            // Left Arm
            glPushMatrix();
            glTranslatef(-0.85f, 0.4f, 0.0f);
            glScalef(-1.0f, 1.0f, 1.0f);
            glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
            glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
            DrawArm();
            glPopMatrix();

            // Right Arm
            glPushMatrix();
            glTranslatef(0.85f, 0.4f, 0.0f);
            glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
            glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
            DrawArm();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    //glRotatef(headRotY, 0.0f, 1.0f, 0.0f);
    //glRotatef(headRotZ, 0.0f, 0.0f, 1.0f);
    weapon->DrawWeapon();
    glPopMatrix();
}