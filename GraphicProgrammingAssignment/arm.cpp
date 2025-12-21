#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "arm.h"
#include "texture.h"
#include "helperFunction.h"
#include <math.h>
#include "Robot.h"

void CalculateNormalVector(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    //V1 = P2 - P1
    float V1x = x2 - x1;
    float V1y = y2 - y1;
    float V1z = z2 - z1;

    //V2 = P3 - P1
    float V2x = x3 - x1;
    float V2y = y3 - y1;
    float V2z = z3 - z1;

    //P1P2 x P1P3 = V1 x V2 = N	
    glNormal3f(
        (V1y * V2z) - (V1z * V2y),  //Nx
        (V1z * V2x) - (V1x * V2z),  //Ny
        (V1x * V2y) - (V1y * V2x)   //Nz
    );
}

void DrawCube()
{
    glBegin(GL_QUADS);
    // Front face
    CalculateNormalVector(-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Back face
    CalculateNormalVector(0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

    // Left face
    CalculateNormalVector(-0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Right face
    CalculateNormalVector(0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // Top face
    CalculateNormalVector(-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Bottom face
    CalculateNormalVector(-0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}

void DrawArmRing(int sides, float radius)
{
    float angleStep = 360.0f / sides;
    int halfSides = sides / 2;   // <-- THIS makes it half

    for (int i = 0; i < halfSides; i++)
    {
        glPushMatrix();

        glRotatef(i * angleStep, 0.0f, 1.0f, 0.0f);
        glTranslatef(-radius, 0.0f, 0.0f);

        DrawCustomBox(
            -0.025f, -0.15f, 0.1f,
            0.025f, -0.15f, 0.0825f,
            0.025f, 0.15f, 0.0825f,
            -0.025f, 0.15f, 0.1f,

            -0.025f, -0.15f, -0.1f,
            0.025f, -0.15f, -0.0825f,
            0.025f, 0.15f, -0.0825f,
            -0.025f, 0.15f, -0.1f
        );

        glPopMatrix();
    }
}

void DrawHand(const float* fingerAngles, float thumbAngle)
{
    glPushMatrix();

    // ===== Palm=====
    glPushMatrix();
    glTranslatef(0.15f, 0.0f, 0.0f);
    glScalef(0.30f, 0.08f, 0.16f);
    DrawCube();
    glPopMatrix();

    // ===== Fingers =====
    float fingerZ[4] = { 0.06f, 0.02f, -0.02f, -0.06f };
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
		glTranslatef(0.3f, 0.035f, fingerZ[i]); // position of each finger
        glRotatef(fingerAngles[i], 0, 0, 1);

        glPushMatrix();
        glTranslatef(0.04f, 0, 0);
        glScalef(0.08f, 0.025f, 0.025f);
        DrawCube();
        glPopMatrix();

        glTranslatef(0.08f, 0, 0);
        glRotatef(fingerAngles[i] * 0.6f, 0, 0, 1);
        glPushMatrix();
        glTranslatef(0.03f, 0, 0);
        glScalef(0.06f, 0.022f, 0.022f);
        DrawCube();
        glPopMatrix();

        glPopMatrix();
    }

    // ===== Thumb =====
    glPushMatrix();
    glTranslatef(0.2f, 0.0f, 0.05f);
    glRotatef(-40.0f, 0, 1, 0);
    glRotatef(thumbAngle, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.05f, 0, 0);
    glScalef(0.08f, 0.03f, 0.03f);
    DrawCube();
    glPopMatrix();

    glTranslatef(0.08f, 0, 0);
    glRotatef(thumbAngle * 0.6f, 0, 0, 1);
    glPushMatrix();
    glTranslatef(0.03f, 0, 0);
    glScalef(0.06f, 0.028f, 0.028f);
    DrawCube();
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
}

void DrawArmSegment(float length, float thicknessY, float thicknessZ)
{
    glPushMatrix();
    glTranslatef(length * 0.5f, 0.0f, 0.0f);
    glScalef(length, thicknessY, thicknessZ);
    DrawCube();
    glPopMatrix();
}

void DrawHandCover()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, carbonTexture);
    DrawCustomBox(
        -0.15f, -0.025f, 0.075f,
        0.15f, -0.025f, 0.075f,
        0.15f, 0.025f, 0.075f,
        -0.15f, 0.025f, 0.075f,

        -0.15f, -0.025f, -0.075f,
        0.15f, -0.025f, -0.075f,
        0.15f, 0.025f, -0.075f,
        -0.15f, 0.025f, -0.075f
    );
    glPopMatrix();
}

void DrawArm(float shoulderSwing, float shoulderRaise, float elbow, float wrist, const float* fingerAngles, float thumbAngle)
{
    GLUquadric* joint = gluNewQuadric();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    // ===== Shoulder =====
    glTranslatef(-0.3f, 0.0f, 0.0f);
    glRotatef(shoulderSwing, 1.0f, 0.0f, 0.0f);
    glRotatef(shoulderRaise, 0.0f, 0.0f, 1.0f);
    glScalef(1.25f, 1.0f, 1.25f);

    glBindTexture(GL_TEXTURE_2D, carbonTexture);
    glPushMatrix();
    glTranslatef(0.15f, -0.1f, 0.0f);
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    glRotatef(-60, 0.0f, 1.0f, 0.0f);
    DrawArmRing(8, 0.21f);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);
    // Shoulder joint
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);
    gluSphere(joint, 0.4, 16, 16);
    glPopMatrix();

    // Upper arm
    DrawArmSegment(0.55f, 0.12f, 0.10f);
    glTranslatef(0.55f, 0, 0);

    // ===== Elbow =====
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);
    gluSphere(joint, 0.4, 16, 16);
    glPopMatrix();

    glRotatef(elbow, 0.0f, 1.0f, 0.0f);

    // Forearm
    DrawArmSegment(0.45f, 0.11f, 0.09f);
    glTranslatef(0.45f, 0, 0);

    glPushMatrix();
    glRotatef(wrist, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.175f, 0.075f, 0.0f);
    DrawHandCover();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, steelTexture);
    // ===== Wrist =====
    glPushMatrix();
    glScalef(0.05f, 0.05f, 0.05f);
    gluSphere(joint, 0.3, 16, 16);
    glPopMatrix();

    glRotatef(wrist, 0.0f, 0.0f, 1.0f);

    // Hand
    DrawHand(fingerAngles, thumbAngle);

    gluDeleteQuadric(joint);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
