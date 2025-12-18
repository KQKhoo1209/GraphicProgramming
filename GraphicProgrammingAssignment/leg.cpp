#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "leg.h"
#include "texture.h"

// joint
float hipRotation = 0.0f;
float kneeRotation = 0.0f;

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

    glEnable(GL_TEXTURE_2D);

    // ================= SIDE ARMOR =================
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

    // ================= FRONT SHIN =================
    glBindTexture(GL_TEXTURE_2D, steelTexture);

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

    // === Toe armor (front) ===
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, z + 0.06f);
    drawCuboid(w * 0.6f, h * 0.6f, 0.08f);
    glPopMatrix();

    // === Left toe plate ===
    glPushMatrix();
    glTranslatef(-x * 0.6f, 0.0f, z * 0.7f);
    drawCuboid(w * 0.25f, h * 0.5f, 0.08f);
    glPopMatrix();

    // === Right toe plate ===
    glPushMatrix();
    glTranslatef(x * 0.6f, 0.0f, z * 0.7f);
    drawCuboid(w * 0.25f, h * 0.5f, 0.08f);
    glPopMatrix();

    // === Heel block ===
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -z - 0.06f);
    drawCuboid(w * 0.5f, h * 0.6f, 0.1f);
    glPopMatrix();
}

void drawSegmentedLeg(float w, float h, float d, int segments)
{
    float step = h / segments;

    for (int i = 0; i < segments; i++)
    {
        glPushMatrix();
        glTranslatef(0.0f, -step * i, 0.0f);
        drawCuboid(w, step, d);
        glPopMatrix();
    }
}

// leg
void drawSingleLeg(float xOffset)
{
    glPushMatrix();

    // Move leg left / right
    glTranslatef(xOffset, 0.0f, 0.0f);

    // ===== Hip joint =====
    glRotatef(hipRotation, 1, 0, 0);

    // ===== Upper leg =====
    glTranslatef(0.0f, -0.4f, 0.0f);
    drawSegmentedLeg(0.3f, 0.8f, 0.3f, 6);
    drawLegDetails(0.3f, 0.8f, 0.3f);

    // ===== Knee joint =====
    glTranslatef(0.0f, -0.4f, 0.0f);
    glRotatef(kneeRotation, 1, 0, 0);

    // ===== Lower leg =====
    glTranslatef(0.0f, -0.45f, 0.0f);
    drawCuboid(0.25f, 0.9f, 0.25f);

    // ===== Foot =====
    glTranslatef(0.0f, -0.55f, 0.15f);
    drawCuboid(0.45f, 0.15f, 0.7f);
    drawFootDetails(0.45f, 0.15f, 0.7f);

    glPopMatrix();
}

// both legs
void drawRobotLegs()
{
    // Left leg
    drawSingleLeg(-0.35f);

    // Right leg
    drawSingleLeg(0.35f);
}
