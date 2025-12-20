#include <Windows.h>
#include "torso.h"
#include "helperFunction.h"
#include "texture.h"
#include <math.h>

extern GLfloat blackColor[];
extern GLfloat whiteColor[];

void DrawUpperBoxRing(int sides, float radius)
{
    float angleStep = 360.0f / sides;
    int halfSides = sides / 2;   // <-- THIS makes it half

    for (int i = 0; i < halfSides; i++)
    {
        glPushMatrix();

        glRotatef(i * angleStep, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, radius, 0.0f);

        DrawCustomBox(
            -0.15f, -0.025f, 0.0825f,
            0.15f, -0.025f, 0.0825f,
            0.15f, 0.025f, 0.1f,
            -0.15f, 0.025f, 0.1f,

            -0.15f, -0.025f, -0.0825f,
            0.15f, -0.025f, -0.0825f,
            0.15f, 0.025f, -0.1f,
            -0.15f, 0.025f, -0.1f
        );

        glPopMatrix();
    }
}

void DrawBottomBoxRing(int sides, float radius)
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

void DrawCenterTriangleRing(int sides, float radius)
{
    float angleStep = 360.0f / sides;

    for (int i = 0; i < sides; i++)
    {
        glPushMatrix();

        glRotatef(i * angleStep, 0.0f, 1.0f, 0.0f);
        glTranslatef(-radius, 0.0f, 0.0f);

        DrawCustomBox(
            -0.02f, -0.05f, 0.04f,
            0.02f, -0.05f, 0.02f,
            0.02f, 0.05f, 0.02f,
            -0.02f, 0.05f, 0.04f,

            -0.02f, -0.05f, -0.04f,
            0.02f, -0.05f, -0.02f,
            0.02f, 0.05f, -0.02f,
            -0.02f, 0.05f, -0.04f
        );

        glPopMatrix();
    }
}

torso::torso()
{
    robotTorso = gluNewQuadric();
    ringDotAngle = 0.0f;
    ringX = 0.0f;
    ringY = 0.0f;

    lightOffset = 0.0f;
}

torso::~torso()
{
    if (robotTorso)
    {
        gluDeleteQuadric(robotTorso);
        robotTorso = nullptr;
    }
}

void torso::InitializeTorsoQuadratics()
{
    gluQuadricTexture(robotTorso, GL_TRUE);
    gluQuadricDrawStyle(robotTorso, GLU_FILL);
    gluQuadricNormals(robotTorso, GLU_SMOOTH);
}

// Light Effect
void torso::DrawMovingLightSource()
{
    static float offset = 0.0f;
    static bool forward = true;

    // Update position
    if (forward) {
        offset += 0.00005f;
        if (offset > 0.05f) forward = false;
    }
    else {
        offset -= 0.00005f;
        if (offset < 0.0f) forward = true;
    }

    // Position for the light
    float lightX = 0.0f;
    float lightY = 0.225f;
    float lightZ = 0.1f + offset;

    // OPTION 1: Create an OpenGL light that illuminates other objects
    if (true) {  // Change to false if you don't want this
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT2);  // Use LIGHT2 to avoid conflicts

        GLfloat lightPos[] = { lightX, lightY, lightZ, 1.0f };
        GLfloat lightColor[] = { 0.6f, 0.7f, 0.8f, 1.0f };  // Orange light

        glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor);
    }

    // OPTION 2: Draw a visible light bulb
    glPushMatrix();
    glTranslatef(lightX, lightY, lightZ);

    // Disable textures for the light bulb
    glDisable(GL_TEXTURE_2D);

    // Draw light rays/glow
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDepthMask(GL_FALSE);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glPopMatrix();
}

void torso::TorsoFrontPattern()
{
    glBindTexture(GL_TEXTURE_2D, darkSteelTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.1f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.1f);
    glRotatef(-45, 1.0f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(5.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4f, 0.4f, 0.1f);
    glRotatef(-45, 1.0f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(5.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f, 0.4f, 0.1f);
    glRotatef(-45, 1.0f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(5.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, redSteelTexture);
    glPushMatrix();
    glTranslatef(0.0f, -0.35f, 0.0f);
    glRotatef(30, 1.0f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(4.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.31f, -0.325f, 0.0f);
    glRotatef(20, 1.0f, 0.0f, 0.0f);
    glRotatef(-15, 0.0f, 1.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(7.0f, 4.0f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.31f, -0.325f, 0.0f);
    glRotatef(20, 1.0f, 0.0f, 0.0f);
    glRotatef(15, 0.0f, 1.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(7.0f, 4.0f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, steelTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.225f, 0.1f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.06f, 0.06f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.06f, 0.06f, 0.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(0.00f, -0.05f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, 0.5f, 0.2f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    DrawCenterTriangleRing(10, 0.18f);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, darkSteelTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.095f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        ringDotAngle = i * (3.14 / 180);
        ringX = 0.12f * cos(ringDotAngle);
        ringY = 0.12f * sin(ringDotAngle);

        glVertex2f(ringX, ringY + 0.2f);
    }
    glEnd();
    glPopMatrix();

    // Breathe Light Effect
    DrawMovingLightSource();
}

void torso::TorsoBackPattern()
{
    // Back Large Cube
    glBindTexture(GL_TEXTURE_2D, steelTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.575f, -0.075f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glScalef(8.0f, 7.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, 0.3f, -0.049f);
    DrawCustomBox( -0.05f, -0.15f,  0.025f ,
        0.05f, -0.125f, 0.025f,
        0.05f, 0.125f, 0.025f,
         -0.05f, 0.15f, 0.025f,
         -0.05f, -0.15f, -0.025f,
        0.05f, -0.125f, -0.025f,
        0.05f, 0.125f, -0.025f,
         -0.05f, 0.15f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, 0.3f, -0.049f);
    DrawCustomBox( -0.05f, -0.125f,  0.025f ,
        0.05f, -0.15f, 0.025f,
        0.05f, 0.15f, 0.025f,
         -0.05f, 0.125f, 0.025f,
         -0.05f, -0.125f, -0.025f,
        0.05f, -0.15f, -0.025f,
        0.05f, 0.15f, -0.025f,
         -0.05f, 0.125f, -0.025f
    );
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, darkSteelTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.515f, 0.0f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 8.5f, 3.0f);
    DrawCube(0.05f);
    glPopMatrix();

    // Back Ladder Cube
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.05f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 0.05f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 8.5f, 1.0f);
    DrawCube(0.05f);
    glPopMatrix();

    // Back Pillar Cube
    glPushMatrix();
    glTranslatef(0.225f, 0.24f, -0.08f);
    glScalef(1.0f, 7.0f, 5.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.225f, 0.24f, -0.08f);
    glScalef(1.0f, 7.0f, 5.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.225f, -0.07f, -0.01f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 8.5f, 4.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.225f, -0.07f, -0.01f);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    glScalef(1.0f, 8.5f, 4.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.35f, 0.3f, -0.05f);
    glScalef(0.5f, 6.0f, 2.0f);
    DrawCube(0.05f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.35f, 0.3f, -0.05f);
    glScalef(0.5f, 6.0f, 2.0f);
    DrawCube(0.05f);
    glPopMatrix();
}

void TorsoUpperPattern()
{
    glBindTexture(GL_TEXTURE_2D, carbonTexture);
    glPushMatrix();
    glTranslatef(-0.6f, -0.2f, 0.0f);
    glRotatef(45, 0.0f, 0.0f, 1.0f);
    glRotatef(-75, 1.0f, 0.0f, 0.0f);
    DrawUpperBoxRing(10, 0.281f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.45f, -0.2f, 0.0f);
    glRotatef(15, 0.0f, 0.0f, 1.0f);
    glRotatef(-75, 1.0f, 0.0f, 0.0f);
    DrawUpperBoxRing(10, 0.281f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, -0.2f, 0.0f);
    glRotatef(-45, 0.0f, 0.0f, 1.0f);
    glRotatef(-75, 1.0f, 0.0f, 0.0f);
    DrawUpperBoxRing(10, 0.281f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.45f, -0.2f, 0.0f);
    glRotatef(-15, 0.0f, 0.0f, 1.0f);
    glRotatef(-75, 1.0f, 0.0f, 0.0f);
    DrawUpperBoxRing(10, 0.281f);
    glPopMatrix();
}

void TorsoBottomPattern() 
{
    glBindTexture(GL_TEXTURE_2D, darkSteelTexture);
    glPushMatrix();
    glTranslatef(-0.45f, -0.4f, 0.0f);
    glRotatef(-75, 0.0f, 1.0f, 0.0f);
    DrawBottomBoxRing(10, 0.28f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.45f, -0.4f, 0.0f);
    glRotatef(110, 0.0f, 1.0f, 0.0f);
    DrawBottomBoxRing(10, 0.28f);
    glPopMatrix();
}

void torso::TorsoFront()
{
    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);
    glPushMatrix();
    QuadNormal(
        -0.19f, 0.5f, 0.0f,
        -0.2f, 0.0f, 0.1f,
        0.2f, 0.0f, 0.1f,
        0.19f, 0.5f, 0.0f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.19f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.19f, 0.5f, 0.0f);
    glEnd();
    QuadNormal(
        -0.2f, 0.0f, 0.1f,
        -0.2f, -0.2f, -0.1f,
        0.2f, -0.2f, -0.1f,
        0.2f, 0.0f, 0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f, 0.0f, 0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.2f, -0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, -0.2f, -0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.1f);
    glEnd();
    QuadNormal(
        -0.2f, -0.2f, -0.1f,
        -0.21f, -0.5f, -0.1f,
        0.21f, -0.5f, -0.1f,
        0.2f, -0.2f, -0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f, -0.2f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.21f, -0.5f, -0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.21f, -0.5f, -0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, -0.2f, -0.1f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.1f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4f, 0.1f, -0.1f);
    glEnd();
    glPopMatrix();

    // Left
    glPushMatrix();
    glTranslatef(-0.2f, 0.0f, 0.0f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    QuadNormal(
        -0.5f, 0.45f, -0.05f,
        -0.4f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.1f,
        0.0f, 0.5f, 0.0f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.45f, -0.05f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 0.0f, 0.0f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, -0.2f, 0.0f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    QuadNormal(
        -0.4f, 0.2f, 0.0f,
        -0.49f, -0.2f, -0.17f,
        -0.06f, -0.3f, -0.14f,
        0.0f, 0.2f, 0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.2f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.49f, -0.2f, -0.17f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.06f, -0.3f, -0.14f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.1f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, 0.5f, 0.0f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        -0.215f, 0.1f, -0.064f,
        -0.5f, -0.05f, -0.05f,
        0.0f, 0.0f, 0.0f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.215f, 0.1f, -0.064f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.05f, -0.05f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Right
    glPushMatrix();
    glTranslatef(0.2f, 0.0f, 0.0f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    QuadNormal(
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.1f,
        0.4f, 0.0f, 0.0f,
        0.5f, 0.45f, -0.05f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.45f, -0.05f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2f, -0.2f, 0.0f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    QuadNormal(
        0.0f, 0.2f, 0.1f,
        0.06f, -0.3f, -0.14f,
        0.49f, -0.2f, -0.17f,
        0.4f, 0.2f, 0.0f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.06f, -0.3f, -0.14f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.49f, -0.2f, -0.17f); 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2f, 0.5f, 0.0f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        0.215f, 0.1f, -0.064f,
        0.0f, 0.0f, 0.0f,
        0.5f, -0.05f, -0.05f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.215f, 0.1f, -0.064f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.05f, -0.05f);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, darkSteelTexture);
    // Left Black
    glPushMatrix();
    glTranslatef(-0.2f, 0.0f, 0.0f);
    glRotatef(-1, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.3f,
        0.0f, -0.5f, 0.1f,
        0.0f, -0.5f, -0.15f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.15f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.22f, 0.0f, 0.0f);
    glRotatef(-2, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.3f,
        0.0f, -0.5f, 0.1f,
        0.0f, -0.5f, -0.15f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.15f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.21f, 0.0f, 0.0f);
    glRotatef(-1, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.01f, 0.5f, 0.0f,
        -0.01f, 0.5f, 0.0f,
        -0.01f, 0.0f, 0.3f,
        0.01f, 0.0f, 0.3f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.01f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.01f, 0.5f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.01f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.01f, 0.0f, 0.3f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.21f, 0.0f, 0.0f);
    glRotatef(-1, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.01f, 0.0f, 0.3f,
        -0.01f, 0.0f, 0.3f,
        -0.02f, -0.5f, 0.1f,
        0.02f, -0.5f, 0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.01f, 0.0f, 0.3f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.01f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.02f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.02f, -0.5f, 0.1f);
    glEnd();
    glPopMatrix();

    // Right Black
    glPushMatrix();
    glTranslatef(0.2f, 0.0f, 0.0f);
    glRotatef(1, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.3f,
        0.0f, -0.5f, 0.1f,
        0.0f, -0.5f, -0.15f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.15f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22f, 0.0f, 0.0f);
    glRotatef(2, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.3f,
        0.0f, -0.5f, 0.1f,
        0.0f, -0.5f, -0.15f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -0.5f, -0.15f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.21f, 0.0f, 0.0f);
    glRotatef(1, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.01f, 0.5f, 0.0f,
        -0.01f, 0.5f, 0.0f,
        -0.01f, 0.0f, 0.3f,
        0.01f, 0.0f, 0.3f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.01f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.01f, 0.5f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.01f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.01f, 0.0f, 0.3f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.21f, 0.0f, 0.0f);
    glRotatef(1, 0.0f, 0.0f, 1.0f);
    QuadNormal(
        0.01f, 0.0f, 0.3f,
        -0.01f, 0.0f, 0.3f,
        -0.02f, -0.5f, 0.1f,
        0.02f, -0.5f, 0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.01f, 0.0f, 0.3f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.01f, 0.0f, 0.3f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.02f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.02f, -0.5f, 0.1f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    TorsoFrontPattern();
    glPopMatrix();
}

void torso::TorsoUpper()
{
    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);
    // Middle Upper
    glPushMatrix();
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.0f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, 0.0f, -0.1f);
    glEnd();
    glPopMatrix();

    // Front Upper
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.2f);
    QuadNormal(
        -0.3f, 0.0f, -0.1f,
        -0.4f, -0.05f, 0.05f,
        0.4f, -0.05f, 0.05f,
        0.3f, 0.0f, -0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.0f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, -0.05f, 0.05f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4f, -0.05f, 0.05f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, 0.0f, -0.1f);
    glEnd();
    glPopMatrix();

    // Back Upper
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.2f);
    QuadNormal(
        -0.4f, -0.05f, -0.05f,
        -0.3f, 0.0f, 0.1f,
        0.3f, 0.0f, 0.1f,
        0.4f, -0.05f, -0.05f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, -0.05f, -0.05f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4f, -0.05f, -0.05f);
    glEnd();
    glPopMatrix();

    // Upper Left
    glPushMatrix();
    glTranslatef(-0.3f, 0.0f, 0.0f);
    QuadNormal(
        -0.45f, -0.15f, 0.1f,
        -0.38f, -0.2f, 0.2125f,
        -0.1f, -0.05f, 0.25f,
        0.0f, 0.0f, 0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f, -0.15f, 0.1f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.38f, -0.2f, 0.2125f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, -0.05f, 0.25f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.1f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, 0.0f, 0.0f);
    QuadNormal(
        -0.395f, -0.15f, -0.1985f,
        -0.45f, -0.15f, -0.1f,
        0.0f, 0.0f, -0.1f,
        -0.1f, -0.05f, -0.25f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.395f, -0.15f, -0.1985f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f, -0.15f, -0.1f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f, -0.05f, -0.25f); 
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, 0.0f, 0.0f);
    QuadNormal(
        -0.45f, -0.15f, -0.1f,
        -0.45f, -0.15f, 0.1f,
        0.0f, 0.0f, 0.1f,
        0.0f, 0.0f, -0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f, -0.15f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f, -0.15f, 0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -0.1f);
    glEnd();
    glPopMatrix();

    // Upper Right
    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    QuadNormal(
        0.0f, 0.0f, 0.1f,
        0.1f, -0.05f, 0.25f,
        0.38f, -0.2f, 0.2125f,
        0.45f, -0.15f, 0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, -0.05f, 0.25f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.38f, -0.2f, 0.2125f); 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.45f, -0.15f, 0.1f); 
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    QuadNormal(
        0.1f, -0.05f, -0.25f,
        0.0f, 0.0f, -0.1f,
        0.45f, -0.15f, -0.1f,
        0.395f, -0.15f, -0.1985f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1f, -0.05f, -0.25f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.45f, -0.15f, -0.1f); 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.395f, -0.15f, -0.1985f); 
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    QuadNormal(
        0.0f, 0.0f, -0.1f,
        0.0f, 0.0f, 0.1f,
        0.45f, -0.15f, 0.1f,
        0.45f, -0.15f, -0.1f
    );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -0.1f); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.45f, -0.15f, 0.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.45f, -0.15f, -0.1f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    TorsoUpperPattern();
    glPopMatrix();
}

void torso::TorsoSide()
{
    glBindTexture(GL_TEXTURE_2D, steelTexture);

    // Left Side
    glPushMatrix();
        glTranslatef(-0.75f, 0.0f, 0.0f);
        glRotatef(-90, 0.0f, 1.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);  glVertex3f(-0.1f, 0.5f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);  glVertex3f(0.1f, 0.5f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);  glVertex3f(0.1f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);  glVertex3f(-0.1f, 0.0f, 0.0f);
        glEnd();

        QuadNormal(
            -0.1f, -0.1f, -0.1f,
            0.1f, -0.1f, -0.1f,
            0.1f, 0.0f, 0.0f,
            -0.1f, 0.0f, 0.0f
        );
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, -0.1f, -0.1f); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, -0.1f, -0.1f); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f, 0.0f, 0.0f);
        glEnd();

        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, -0.1f, -0.1f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, -0.1f, -0.1f);
        glTexCoord2f(1.0f, 0.0f);  glVertex3f(0.1f, -0.4f, -0.1f);
        glTexCoord2f(1.0f, 1.0f);  glVertex3f(-0.1f, -0.4f, -0.1f);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.59f, 0.0f, 0.28f);
        glRotatef(-10, 0.0f, 1.0f, 0.0f);
        TriNormal(
            -0.19f, 0.5f, -0.15f,
            -0.19f, 0.0f, -0.15f,
            0.0f, 0.0f, 0.0f
        );
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.19f, 0.5f, -0.15f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.19f, 0.0f, -0.15f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();

        TriNormal(
            -0.19f, 0.5f, -0.15f,
            0.0f, 0.0f, 0.0f,
            -0.1f, 0.45f, -0.05f
        );
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.19f, 0.5f, -0.15f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, 0.45f, -0.05f);
        glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.59f, 0.0f, 0.28f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        -0.19f, 0.0f, -0.15f,
        -0.09f, -0.1f, -0.175f,
        0.0f, 0.0f, 0.0f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.19f, 0.0f, -0.15f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f, -0.1f, -0.175f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.59f, 0.0f, 0.28f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        -0.09f, -0.1f, -0.175f,
        -0.09f, -0.4f, -0.17f,
        0.0f, 0.0f, 0.0f 
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.09f, -0.1f, -0.175f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f, -0.4f, -0.17f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.59f, 0.0f, -0.28f);
        glRotatef(10, 0.0f, 1.0f, 0.0f);
        TriNormal(
            -0.19f, 0.5f, 0.15f,
            -0.017f, 0.0f, 0.0625f, 
            -0.19f, 0.0f, 0.15f
        );
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.19f, 0.5f, 0.15f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.017f, 0.0f, 0.0625f); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.19f, 0.0f, 0.15f);
        glEnd();

        TriNormal(
            -0.118f, 0.5f, 0.0625f,
            -0.017f, 0.0f, 0.0625f,
            -0.19f, 0.5f, 0.15f 
        );
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.118f, 0.5f, 0.0625f); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.017f, 0.0f, 0.0625f); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.19f, 0.5f, 0.15f);
        glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.59f, 0.0f, -0.28f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        -0.017f, 0.0f, 0.0625f,
        -0.09f, -0.1f, 0.175f,
        -0.19f, 0.0f, 0.15f 
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.017f, 0.0f, 0.0625f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f, -0.1f, 0.175f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.19f, 0.0f, 0.15f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.59f, 0.0f, -0.28f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        -0.09f, -0.1f, 0.175f,
        -0.017f, 0.0f, 0.0625f,
        -0.09f, -0.4f, 0.17f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.09f, -0.1f, 0.175f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.017f, 0.0f, 0.0625f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.09f, -0.4f, 0.17f);
    glEnd();
    glPopMatrix();

    // Right Side
    glPushMatrix();
        glTranslatef(0.75f, 0.0f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 0.5f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, 0.5f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f, 0.0f, 0.0f);
        glEnd();

        QuadNormal(
            -0.1f, 0.0f, 0.0f,
            -0.1f, -0.1f, -0.1f,
            0.1f, -0.1f, -0.1f,
            0.1f, 0.0f, 0.0f 
        );
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f, -0.1f); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1f, -0.1f, -0.1f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1f, 0.0f, 0.0f);
        glEnd();

        glNormal3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, -0.1f, -0.1f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, -0.1f, -0.1f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1f, -0.4f, -0.1f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f, -0.4f, -0.1f);
        glEnd();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0.59f, 0.0f, 0.28f);
        glRotatef(10, 0.0f, 1.0f, 0.0f);
        TriNormal(
            0.19f, 0.5f, -0.15f,
            0.0f, 0.0f, 0.0f,
            0.19f, 0.0f, -0.15f
        );
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(0.19f, 0.5f, -0.15f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.19f, 0.0f, -0.15f); 
        glEnd();

        TriNormal(
            0.19f, 0.5f, -0.15f,
            0.1f, 0.45f, -0.05f,
            0.0f, 0.0f, 0.0f
        );
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(0.19f, 0.5f, -0.15f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, 0.45f, -0.05f); 
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.59f, 0.0f, 0.28f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        0.0f, 0.0f, 0.0f,
        0.09f, -0.1f, -0.175f,
        0.19f, 0.0f, -0.15f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.09f, -0.1f, -0.175f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.19f, 0.0f, -0.15f); 
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.59f, 0.0f, 0.28f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        0.09f, -0.1f, -0.175f,
        0.0f, 0.0f, 0.0f,
        0.09f, -0.4f, -0.17f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.09f, -0.1f, -0.175f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.09f, -0.4f, -0.17f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.59f, 0.0f, -0.28f);
        glRotatef(-10, 0.0f, 1.0f, 0.0f);
        TriNormal(
            0.19f, 0.5f, 0.15f,
            0.19f, 0.0f, 0.15f,
            0.017f, 0.0f, 0.0625f
        );
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(0.19f, 0.5f, 0.15f);
        glTexCoord2f(0.0f, 0.0f);  glVertex3f(0.19f, 0.0f, 0.15f);
        glTexCoord2f(1.0f, 0.0f);  glVertex3f(0.017f, 0.0f, 0.0625f);

        TriNormal(
            0.19f, 0.5f, 0.15f,
            0.017f, 0.0f, 0.0625f,
            0.118f, 0.5f, 0.0625f
        );
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(0.19f, 0.5f, 0.15f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.017f, 0.0f, 0.0625f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.118f, 0.5f, 0.0625f);
        glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.59f, 0.0f, -0.28f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        0.19f, 0.0f, 0.15f,
        0.09f, -0.1f, 0.175f,
        0.017f, 0.0f, 0.0625f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.19f, 0.0f, 0.15f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.09f, -0.1f, 0.175f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.017f, 0.0f, 0.0625f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.59f, 0.0f, -0.28f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    TriNormal(
        0.09f, -0.1f, 0.175f,
        0.09f, -0.4f, 0.17f,
        0.017f, 0.0f, 0.0625f
    );
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.09f, -0.1f, 0.175f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.09f, -0.4f, 0.17f); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.017f, 0.0f, 0.0625f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    TorsoBottomPattern();
    glPopMatrix();
}

void torso::TorsoBack()
{
    glBindTexture(GL_TEXTURE_2D, blueSteelTexture);
    // Left
    glPushMatrix();
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTranslatef(-0.2f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glNormal3f(-0.3f, 0.0f, -0.95f);
    glTranslatef(-0.4f, 0.0f, 0.0f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.0f, 0.6f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glNormal3f(-0.3f, 0.0f, -0.95f);
    glTranslatef(-0.4f, 0.0f, 0.0f);
    glRotatef(10, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f, 0.0f, 0.0f); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.275f, -0.4f, 0.1075f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -0.4f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Right
    glPushMatrix();
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTranslatef(0.2f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f, 0.5f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, -0.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glNormal3f(0.3f, 0.0f, -0.95f);
    glTranslatef(0.4f, 0.0f, 0.0f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.6f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glNormal3f(0.3f, 0.0f, -0.95f);
    glTranslatef(0.4f, 0.0f, 0.0f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.275f, -0.4f, 0.1075f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -0.4f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    TorsoBackPattern();
    glPopMatrix();
}

void torso::middleCylinder()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, whiteMetalTexture);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(robotTorso, 0.175f, 0.175f, 1.0f, 8, 1);
    glPopMatrix();
}

void torso::DrawTorso()
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    middleCylinder();
    glPopMatrix();

    // Upper Side
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    TorsoUpper();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    TorsoSide();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.35f);
    TorsoFront();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.2f, -0.25f);
    TorsoBack();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}