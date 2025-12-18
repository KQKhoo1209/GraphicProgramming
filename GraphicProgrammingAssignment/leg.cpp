#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include "leg.h"
#include "texture.h"

// joint
float hipRotation = 0.0f;
float kneeRotation = 0.0f;
static GLUquadric* quad = nullptr;

bool isWalking = false;
float walkPhase = 0.0f;

float hipAnim = 0.0f;
float kneeAnim = 0.0f;

static const float animSpeed = 0.01f;
static const float maxPhase = 6.28f; 

void drawCuboid(float w, float h, float d)
{
    float x = w * 0.5f;
    float y = h * 0.5f;
    float z = d * 0.5f;

    glBegin(GL_QUADS);

    // Front
    glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, -y, z);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, -y, z);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, z);

    // Back
    glNormal3f(0, 0, -1);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, -y, -z);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-x, -y, -z);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, y, -z);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, -z);

    // Left
    glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, -y, -z);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-x, -y, z);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-x, y, z);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, -z);

    // Right
    glNormal3f(1, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, -y, z);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, -y, -z);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, -z);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, z);

    // Top
    glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, y, z);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, -z);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, -z);

    // Bottom
    glNormal3f(0, -1, 0);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, -y, -z);
	glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, -y, -z);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, -y, z);
	glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, -y, z);

    glEnd();
}

void drawLegDetails(float w, float h, float d)
{
    float x = w * 0.5f;

    //side
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);

    // Left side armor
    glPushMatrix();
    glTranslatef(-x - 0.08f, 0.0f, 0.0f);
    drawCuboid(0.08f, h * 0.8f, d * 0.8f);
    glPopMatrix();

    // Right side armor
    glPushMatrix();
    glTranslatef(x + 0.08f, 0.0f, 0.0f);
    drawCuboid(0.08f, h * 0.8f, d * 0.8f);
    glPopMatrix();

    //shin
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, d * 0.5f + 0.05f);
    drawCuboid(w * 0.6f, h * 0.6f, 0.08f);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawFootDetails(float w, float h, float d)
{
    float x = w * 0.5f;
    float z = d * 0.5f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    // === Toe armor (front) ===
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, z + 0.06f);
    drawCuboid(w * 0.6f, h * 0.6f, 0.08f);
    glPopMatrix();

    // === Left toe plate ===
    glPushMatrix();
    glTranslatef(-x * 1.0f, 0.0f, z * 0.0f);
    drawCuboid(w * 0.25f, h * 0.5f, 0.5f);
    glPopMatrix();

    // === Right toe plate ===
    glPushMatrix();
    glTranslatef(x * 1.0f, 0.0f, z * 0.0f);
    drawCuboid(w * 0.25f, h * 0.5f, 0.5f);
    glPopMatrix();

    // === Heel block ===
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -z - 0.06f);
    drawCuboid(w * 0.5f, h * 0.6f, 0.1f);
    glPopMatrix();

    // block above foot
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.06f);
    drawCuboid(0.2f, 0.1f, 0.5f);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawSegmentedLeg(float w, float h, float d, int segments)
{
    float step = h / segments;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, darkSteelTexture);

    for (int i = 0; i < segments; i++)
    {
        glPushMatrix();
        glTranslatef(0.0f, -step * i, 0.0f);
        drawCuboid(w, step, d);
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
}

void drawVerticalRibs(float w, float h, float d, int count)
{
    float spacing = w / (count + 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    for (int i = 1; i <= count; i++)
    {
        glPushMatrix();
        glTranslatef(-w * 0.5f + spacing * i, 0.0f, d * 0.52f);
        drawCuboid(0.03f, h * 0.9f, 0.05f);
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
}

void drawCoreSphere(float radius)
{
    if (!quad)
    {
        quad = gluNewQuadric();
        gluQuadricNormals(quad, GLU_SMOOTH);
        gluQuadricTexture(quad, GL_TRUE);
    }

    gluSphere(quad, radius, 20, 20);
}

void drawPiston(float length) {
    drawCuboid(0.05f, length, 0.05);
}

// leg
void drawSingleLeg(float xOffset)
{
    if (isWalking)
    {
        float dir = (xOffset < 0.0f) ? 1.0f : -1.0f;

        hipAnim = sin(walkPhase) * 25.0f * dir;
        kneeAnim = fabs(sin(walkPhase)) * 35.0f;
    }

    glPushMatrix();

    // Move leg left / right
    glTranslatef(xOffset, 0.0f, 0.0f);

    // hip joint
    glRotatef(hipRotation + hipAnim, 1, 0, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, redSteelTexture);

    // upper leg
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    drawSegmentedLeg(0.3f, 0.8f, 0.3f, 6);
    drawLegDetails(0.3f, 0.8f, 0.3f);

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.20f);
    drawCuboid(0.1, 0.3f, 0.05f);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    // sphere
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);   // center of armor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, steelTexture); 
    drawCoreSphere(0.2f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // knee joint
    glPushMatrix();
    glTranslatef(0.0f, -0.48f, 0.0f);
    glPopMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    glRotatef(kneeRotation + kneeAnim, 1, 0, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);

    // pistons
    glPushMatrix();
    glTranslatef(0.15f, -0.3f, 0);
    drawPiston(0.4f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.15f, -0.3f, 0);
    drawPiston(0.4f);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, redSteelTexture);

    // lower leg
    glTranslatef(0.0f, -0.45f, 0.0f);
    drawCuboid(0.25f, 0.9f, 0.25f);
    drawVerticalRibs(0.25f, 0.9f, 0.25f, 4);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);

    // foot
    glTranslatef(0.0f, -0.55f, 0.15f);
    drawCuboid(0.45f, 0.2f, 0.7f);
    drawFootDetails(0.45f, 0.15f, 0.7f);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

// both legs
void drawRobotLegs()
{
    // Left leg
    drawSingleLeg(-0.35f);

    // Right leg
    drawSingleLeg(0.35f);

    if (isWalking)
    {
        walkPhase += animSpeed;

        if (walkPhase >= maxPhase)
        {
            walkPhase = maxPhase;
            isWalking = false;
        }   
    }
}
