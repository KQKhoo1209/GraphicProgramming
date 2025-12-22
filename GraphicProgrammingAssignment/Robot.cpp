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
    , leftSwing(0.0f), rightSwing(0.0f)
    , leftRaise(0.0f), rightRaise(-90.0f)
    , leftElbow(0.0f), rightElbow(0.0f)
	, leftWristAngle(0.0f), rightWristAngle(0.0f)
	, leftThumbAngle(0.0f), rightThumbAngle(0.0f)
{
    leftFingerAngles[0] = 0.0f;
    leftFingerAngles[1] = 0.0f;
    leftFingerAngles[2] = 0.0f;
    leftFingerAngles[3] = 0.0f;
	rightFingerAngles[0] = 0.0f;
    rightFingerAngles[1] = 0.0f;
    rightFingerAngles[2] = 0.0f;
	rightFingerAngles[3] = 0.0f;
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

    if (robotRotY > 360.0f) robotRotY -= 360.0f;
    if (robotRotY < 0.0f) robotRotY += 360.0f;
}

void Robot::RotateTorsoY(float delta)
{
    torsoRotY += delta;

    if (torsoRotY > 45.0f) torsoRotY = 45.0f;
    else if (torsoRotY < -45.0f) torsoRotY = -45.0f;
}

void Robot::RotateTorsoZ(float delta)
{
    torsoRotZ += delta;

    if (torsoRotZ > 30.0f) torsoRotZ = 30.0f;
    else if (torsoRotZ < 0.0f) torsoRotZ = 0.0f;
}

void Robot::RotateHeadY(float delta)
{
    headRotY += delta;

    if (headRotY > 30.0f)
        headRotY = 30.0f;
    else if (headRotY < -30.0f)
        headRotY = -30.0f;
}

void Robot::RotateHeadZ(float delta)
{
    headRotZ += delta;

    if (headRotZ > 30.0f)
        headRotZ = 30.0f;
    else if (headRotZ < -30.0f)
        headRotZ = -30.0f;
}

void Robot::RotateLeftShoulder(float delta)
{
    leftSwing += delta;
    if (leftSwing > 45.0f) leftSwing = 45.0f;
    else if (leftSwing < -90.0f) leftSwing = -90.0f;
}

void Robot::RotateRightShoulder(float delta)
{
    rightSwing += delta;
    if (rightSwing > 45.0f) rightSwing = 45.0f;
    else if (rightSwing < -90.0f) rightSwing = -90.0f;
}

void Robot::RotateLeftElbow(float delta)
{
    leftElbow += delta;
    if (leftElbow < -145.0f) leftElbow = -145.0f;
    else if (leftElbow > 0.0f) leftElbow = 0.0f;
}

void Robot::RotateRightElbow(float delta)
{
    rightElbow += delta;
    if (rightElbow < -145.0f) rightElbow = -145.0f;
    else if (rightElbow > 0.0f) rightElbow = 0.0f;
}

void Robot::RotateLeftWrist(float delta)
{
    leftWristAngle += delta;
    if (leftWristAngle > 60.0f) leftWristAngle = 60.0f;
    else if (leftWristAngle < -60.0f) leftWristAngle = -60.0f;
}

void Robot::RotateRightWrist(float delta)
{
    rightWristAngle += delta;
    if (rightWristAngle > 60.0f) rightWristAngle = 60.0f;
    else if (rightWristAngle < -60.0f) rightWristAngle = -60.0f;
}

void Robot::RotateLeftFingers(float delta, int fingerIndex)
{
    leftFingerAngles[fingerIndex] += delta;
    if (leftFingerAngles[fingerIndex] > 0.0f) leftFingerAngles[fingerIndex] = 0.0f;
    else if (leftFingerAngles[fingerIndex] < -100.0f) leftFingerAngles[fingerIndex] = -100.0f;
}

void Robot::RotateRightFingers(float delta, int fingerIndex)
{
    rightFingerAngles[fingerIndex] += delta;
    if (rightFingerAngles[fingerIndex] > 0.0f) rightFingerAngles[fingerIndex] = 0.0f;
    else if (rightFingerAngles[fingerIndex] < -100.0f) rightFingerAngles[fingerIndex] = -100.0f;
}

void Robot::RotateLeftThumb(float delta)
{
    leftThumbAngle += delta;
    if (leftThumbAngle > 0.0f) leftThumbAngle = 0.0f;
	else if (leftThumbAngle < -100.0f) leftThumbAngle = -100.0f;
}

void Robot::RotateRightThumb(float delta)
{
    rightThumbAngle += delta;
    if (rightThumbAngle > 0.0f) rightThumbAngle = 0.0f;
    else if (rightThumbAngle < -100.0f) rightThumbAngle = -100.0f;
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
    leftSwing = 0.0f;
    rightSwing = 0.0f;
    leftRaise = -90.0f; 
    rightRaise = -90.0f;
    leftElbow = 0.0f;
    rightElbow = 0.0f;
    leftWristAngle = 0.0f;
	rightWristAngle = 0.0f;
    leftFingerAngles[0] = 0.0f;
	leftFingerAngles[1] = 0.0f;
	leftFingerAngles[2] = 0.0f;
	leftFingerAngles[3] = 0.0f;
	rightFingerAngles[0] = 0.0f;
	rightFingerAngles[1] = 0.0f;
	rightFingerAngles[2] = 0.0f;
	rightFingerAngles[3] = 0.0f;
    leftThumbAngle = 0.0f;
	rightThumbAngle = 0.0f;
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

void Robot::StartSwingKnife()
{
    animator.SwingKnives();
}

void Robot::ShowHat()
{
    hasHat = !hasHat;
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

			//Draw Hat
            if (hasHat)
            {
                glPushMatrix();
                glTranslatef(0.0f, 0.1f, 0.0f);
                glScalef(0.5f, 0.5f, 0.5f);
                glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
                DrawHat();
                glPopMatrix();
            }
            glPopMatrix();

            if (isSpecialAnim && animator.GetKnifeScale(0) > 0.0f)
            {
                glPushMatrix();
                glTranslatef(0.0f, 0.2f, 0.5f);
                glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

                float spacing = 0.5f;
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

            if (animator.GetState() != IDLE_ANIM)
            {
                leftSwing = animator.GetShoulderAngle(-1.0f);
                rightSwing = animator.GetShoulderAngle(1.0f);

                leftRaise = -90.0f;
                rightRaise = -90.0f;

                if (animator.GetState() == KNIFE_SEP_ANIM)
                {
                    leftSwing = 0.0f;
                    rightSwing = 0.0f;

                    leftRaise = animator.GetSpecialShoulderAngle(); // Use lift for knife trick
                    rightRaise = leftRaise;

                    leftElbow = animator.GetSpecialElbowAngle();
                    rightElbow = animator.GetSpecialElbowAngle();

                    leftWristAngle = 0.0f;
					rightWristAngle = 0.0f;
                }
            }
            else
            {
                leftRaise = -90.0f;
                rightRaise = -90.0f;
            }

            if (animator.GetState() == SWING_KNIFE_ANIM)
            {
                for (int i = 0; i < 4; i++) {
                    leftFingerAngles[i] = animator.GetSwingFingerAngle(-1.0f);
                    rightFingerAngles[i] = animator.GetSwingFingerAngle(1.0f);
                }

                // === DRAW LEFT ARM ===
                glPushMatrix();
                glTranslatef(-1.15f, 0.75f, 0.0f);
                glScalef(-1.0f, 1.0f, 1.0f);
                DrawArm(
                    animator.GetSwingShoulderAngle(1.0f),
                    -90.0f,
                    animator.GetSwingElbowAngle(1.0f),
                    animator.GetSwingWristAngle(1.0f),
                    leftFingerAngles,
                    animator.GetSwingThumbAngle(1.0f),
                    weapon,
                    true
                );
                glPopMatrix();

                // === DRAW RIGHT ARM ===
                glPushMatrix();
                glTranslatef(1.15f, 0.75f, 0.0f);
                DrawArm(
                    animator.GetSwingShoulderAngle(1.0f),
                    -90.0f,
                    animator.GetSwingElbowAngle(1.0f),
                    animator.GetSwingWristAngle(1.0f),
                    rightFingerAngles,
                    animator.GetSwingThumbAngle(1.0f),
                    weapon,
					true
                );
                glPopMatrix();
                for (int i = 0; i < 4; i++) {
                    leftFingerAngles[i] = 0.0f;
                    rightFingerAngles[i] = 0.0f;
                }
            }
            else
            {

                // === DRAW LEFT ARM ===
                glPushMatrix();
                glTranslatef(-1.15f, 0.75f, 0.0f);
                glScalef(-1.0f, 1.0f, 1.0f);
                DrawArm(leftSwing, leftRaise, leftElbow, leftWristAngle, leftFingerAngles, leftThumbAngle);
                glPopMatrix();

                // === DRAW RIGHT ARM ===
                glPushMatrix();
                glTranslatef(1.15f, 0.75f, 0.0f);
                DrawArm(rightSwing, rightRaise, rightElbow, rightWristAngle, rightFingerAngles, rightThumbAngle);
            }
            
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}