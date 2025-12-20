#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "arm.h"
#include "texture.h"
#include <math.h>

GLfloat rColor[] = { 1.0f, 0.0f, 0.0f };
GLfloat gColor[] = { 0.0f, 1.0f, 0.0f };
GLfloat bColor[] = { 0.0f, 0.0f, 1.0f };


float shoulderAngle = 0.0f;
float elbowAngle = 0.0f;
float wristAngle = 0.0f;
float fingerAngles[3] = { 0.0f, 0.0f, 0.0f };
float thumbAngle = 0.0f;


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

void DrawHand()
{
    glPushMatrix();

    // Palm
    glPushMatrix();
    glScalef(0.22f, 0.12f, 0.18f);
    DrawCube();
    glPopMatrix();

    // Finger
    float startY = 0.05f;
    for (int i = 0; i < 3; ++i)
    {
        glPushMatrix();
        glTranslatef(0.1f, startY - i * 0.05f, -0.05f);
        glRotatef(fingerAngles[i], 0.0f, 0.0f, 1.0f);
        glTranslatef(0.06f, 0.0f, 0.0f);
        glScalef(0.1f, 0.025f, 0.025f);
        DrawCube();
        glPopMatrix();
    }

    // Thumb
    glPushMatrix();
    glTranslatef(0.05f, -0.05f, 0.03f);
    glRotatef(thumbAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.05f, 0.0f, 0.0f);
    glScalef(0.1f, 0.03f, 0.03f);
    DrawCube();
    glPopMatrix();

    glPopMatrix();
}


void DrawArmSegment(float length)
{
    glPushMatrix();
    glScalef(length, 0.18f, 0.12f);
    glTranslatef(0.5f, 0.0f, 0.0f);
    DrawCube();
    glPopMatrix();
}

void DrawArm()
{
    GLUquadric* q = gluNewQuadric();

    glPushMatrix();

    // ===== Shoulder =====
    glTranslatef(-0.3f, 0.0f, 0.0f);
    glRotatef(shoulderAngle, 0.0f, 0.0f, 1.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rColor);

    // ===== Shoulder Joint =====
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);
    gluSphere(q, 0.4, 16, 16);
    glPopMatrix();

    DrawArmSegment(0.6f);

    glTranslatef(0.6f, 0.0f, 0.0f);

    // ===== Elbow Joint =====
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);
    gluSphere(q, 0.4, 16, 16);
    gluDeleteQuadric(q);
    glPopMatrix();

    // ===== Elbow =====
    glRotatef(elbowAngle, 0.0f, 0.0f, 1.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gColor);
    DrawArmSegment(0.6f);

    glTranslatef(0.6f, 0.0f, 0.0f);

    // ===== Wrist Joint =====
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);
    DrawCube();
    glPopMatrix();

    // ===== Wrist =====
    glPushMatrix();
    glTranslatef(0.05f, 0.0f, 0.0f);
    glRotatef(wristAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.08f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bColor);
    DrawHand();

    glPopMatrix();
}