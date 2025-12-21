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
    , knifeCount(5)
    , legAngle(60)
    , shoulderAngle(-90.0f), elbowAngle(0.0f), wristAngle(0.0f)
    , thumbAngle(0.0f)
{
    fingerAngles[0] = 0.0f;
    fingerAngles[1] = 0.0f;
    fingerAngles[2] = 0.0f;
    fingerAngles[3] = 0.0f;
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
    float angleRad = (robotRotY * 3.14159f) / 180.0f;

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

void Robot::RotateShoulder(float delta)
{
    shoulderAngle += delta;
    if (shoulderAngle > 90.0f) shoulderAngle = 90.0f;
    else if (shoulderAngle < -90.0f) shoulderAngle = -90.0f;
}

void Robot::RotateElbow(float delta)
{
    elbowAngle += delta;
    if (elbowAngle > 145.0f) elbowAngle = 145.0f;
    else if (elbowAngle < 0.0f) elbowAngle = 0.0f;
}

void Robot::RotateWrist(float delta)
{
    wristAngle += delta;
    if (wristAngle > 60.0f) wristAngle = 60.0f;
    else if (wristAngle < -60.0f) wristAngle = -60.0f;
}

void Robot::RotateFingers(float delta)
{
}

void Robot::RotateThumb(float delta)
{
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
    shoulderAngle = -90.0f;
    elbowAngle = 0.0f;
    wristAngle = 0.0f;
    fingerAngles[0, 1, 2, 3] = 0.0f;
    thumbAngle = 0.0f;
    hipRotation = 0.0f;
    kneeRotation = 0.0f;
}

void Robot::Update(float deltaTime)
{
    animator.AnimUpdate(deltaTime);
}

void Robot::StartJump()
{
    animator.RobotJump();
}

void Robot::StartSpecialAnimation()
{
    animator.KnifeAnimation();
}

void Robot::DrawRobot()
{
    bool isSpecialAnim = (animator.GetState() == KNIFE_SEP_ANIM);

    glPushMatrix();

    float jumpY = animator.GetJumpHeight();
    hipRotation = animator.GetJumpKneeAngle();

    glTranslatef(robotPosX, 0.0f + jumpY, robotPosZ);
    glRotatef(robotRotY, 0.0f, 1.0f, 0.0f);

        glPushMatrix();
        glTranslatef(0.0f, -0.75f, 0.0f);
        glScalef(0.8f, 1.1f, 0.8f);
        drawRobotLegs();
        glPopMatrix();

        glPushMatrix();
        float extraTorsoRot = animator.GetSpecialTorsoAngle();

        glRotatef(torsoRotY, 0.0f, 1.0f, 0.0f);
        glRotatef(torsoRotZ + extraTorsoRot, 1.0f, 0.0f, 0.0f);
        robotTorso->DrawTorso();

            glPushMatrix();
            float extraHeadRot = animator.GetSpecialHeadAngle();
            glTranslatef(0.0f, 1.225f, 0.0f);
            glRotatef(headRotY, 0.0f, 1.0f, 0.0f);
            glRotatef(headRotZ + extraHeadRot, 1.0f, 0.0f, 0.0f);
            robotHead->DrawHead();
            glPopMatrix();

            if (isSpecialAnim && animator.GetKnifeScale(0) > 0.0f)
            {
                glPushMatrix();
                glTranslatef(0.0f, 0.2f, 0.5f);
                glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

                float spacing = 0.3f; // Distance between knives
                float startSide = -((knifeCount - 1) * spacing) / 2.0f;

                for (int i = 0; i < knifeCount; i++)
                {
                    float scale = animator.GetKnifeScale(i);

                    if (scale <= 0.01f) continue;

                    float sidePos = startSide + (i * spacing);

                    glPushMatrix();
                    glTranslatef(0.5f, 0.0f, sidePos);
                    glScalef(scale * 0.5f, scale * 0.5f, scale * 0.5f);
                    weapon->DrawWeapon();
                    glPopMatrix();
                }
                glPopMatrix();
            }

            // === DRAW ARMS ===
            float shoulder = 0.0f;
            float elbow = 0.0f;

            if (animator.GetState() == KNIFE_SEP_ANIM)
            {
                shoulder = animator.GetSpecialShoulderAngle();
                elbow = animator.GetSpecialElbowAngle();
            }
            else
            {
                shoulder = shoulderAngle;
                elbow = elbowAngle;
            }

            // Left Arm
            glPushMatrix();
            glTranslatef(-1.15f, 0.75f, 0.0f);
            glScalef(-1.0f, 1.0f, 1.0f);
            DrawArm(shoulder, elbow, 0.0f, fingerAngles, thumbAngle);
            glPopMatrix();

            // Right Arm
            glPushMatrix();
            glTranslatef(1.15f, 0.75f, 0.0f);
            DrawArm(shoulder, elbow, 0.0f, fingerAngles, thumbAngle);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}