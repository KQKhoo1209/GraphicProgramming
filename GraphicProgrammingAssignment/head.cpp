#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "head.h"
#include "helperFunction.h"
#include "texture.h"
#include <math.h>

extern GLfloat whiteColor[];

void DrawUpperFaceRing(int sides, float radius)
{
    float angleStep = 360.0f / sides;

    for (int i = 0; i < sides; i++)
    {
        float angle = i * angleStep;

        glPushMatrix();
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glTranslatef(-radius, 0.0f, 0.0f);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLES);
        glTexCoord2f(0.5f, 1.0f); glVertex3f(0.12f, 0.05f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.05f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.05f);
        glEnd();
        glPopMatrix();
    }
}

void DrawMiddleFaceRing(int sides, float radius)
{
    float angleStep = 360.0f / sides;

    for (int i = 0; i < sides; i++)
    {
        float angle = i * angleStep;

        /*if (angle > 330.0f || angle < 30.0f)
            continue;*/

        glPushMatrix();
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glTranslatef(-radius, 0.0f, 0.0f);

        DrawCustomBox(
            -0.025f, -0.05f, 0.1f,
            0.025f, -0.05f, 0.025f,
            0.15f, 0.05f, 0.02f,
            0.1f, 0.07f, 0.0475f,

            -0.025f, -0.05f, -0.1f,
            0.025f, -0.05f, -0.025f,
            0.15f, 0.05f, -0.02f,
            0.1f, 0.07f, -0.0475f
        );
        glPopMatrix();
    }
}

void DrawBottomFaceRing(int sides, float radius)
{
    float angleStep = 360.0f / sides;

    for (int i = 0; i < sides; i++)
    {

        float angle = i * angleStep;

        if (angle > 330.0f || angle < 30.0f)
            continue;

        glPushMatrix();
        glRotatef(i * angleStep, 0.0f, 1.0f, 0.0f);
        glTranslatef(-radius, 0.0f, 0.0f);

        DrawCustomBox(
            -0.025f, -0.15f, 0.1f,
            0.025f, -0.15f, 0.078f,
            0.025f, 0.15f, 0.078f,
            -0.025f, 0.15f, 0.1f,

            -0.025f, -0.15f, -0.1f,
            0.025f, -0.15f, -0.078f,
            0.025f, 0.15f, -0.078f,
            -0.025f, 0.15f, -0.1f
        );

        glPopMatrix();
    }
}

head::head() : robotHead(nullptr)
{
    headRotY = 0.0f;
    headRotX = 0.0f;
    robotHead = gluNewQuadric();
}

head::~head()
{
    if (robotHead)
    {
        gluDeleteQuadric(robotHead);
        robotHead = nullptr;
    }

}

void head::InitializeHeadQuadratics()
{
    gluQuadricTexture(robotHead, GL_TRUE);
    gluQuadricDrawStyle(robotHead, GLU_FILL);
    gluQuadricNormals(robotHead, GLU_SMOOTH);
}

void head::RotateX(float delta)
{
    headRotX += delta;

    if (headRotX > 15.0f)
        headRotX = 15.0f;
    else if (headRotX < -15.0f)
        headRotX = -15.0f;
}

void head::RotateY(float delta)
{
    headRotY += delta;
}

void head::Eyes()
{
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0.0f, -0.025f, 0.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
    gluSphere(robotHead, 0.1f, 20, 20);
    glPopMatrix();

    BindTexture(carbonTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.075f, 0.12f);
    DrawCustomBox(
        -0.05f, -0.025f, 0.025f,
        0.05f, -0.025f, 0.025f,
        0.15f, 0.025f, 0.025f,
        -0.15f, 0.025f, 0.025f,
        -0.05f, -0.025f, -0.025f,
        0.05f, -0.025f, -0.025f,
        0.15f, 0.025f, -0.025f,
        -0.15f, 0.025f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.08f, -0.02f, 0.12f);
    glRotatef(120, 0.0f, 0.0f, 1.0f);
    DrawCustomBox(
        -0.08f, -0.025f, 0.025f,
        0.05f, -0.025f, 0.025f,
        0.1f, 0.025f, 0.025f,
        -0.05f, 0.025f, 0.025f,
        -0.08f, -0.025f, -0.025f,
        0.05f, -0.025f, -0.025f,
        0.1f, 0.025f, -0.025f,
        -0.05f, 0.025f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.08f, -0.02f, 0.12f);
    glRotatef(-120, 0.0f, 0.0f, 1.0f);
    DrawCustomBox(
        -0.05f, -0.025f, 0.025f,
        0.08f, -0.025f, 0.025f,
        0.05f, 0.025f, 0.025f,
        -0.1f, 0.025f, 0.025f,
        -0.05f, -0.025f, -0.025f,
        0.08f, -0.025f, -0.025f,
        0.05f, 0.025f, -0.025f,
        -0.1f, 0.025f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.0435f, -0.151f, 0.12f);
    DrawCustomBox(
        -0.0325f, -0.075f, 0.025f,
        0.025f, -0.075f, 0.025f,
        0.025f, 0.075f, 0.025f,
        -0.0325f, 0.075f, 0.025f,
        -0.0325f, -0.075f, -0.025f,
        0.025f, -0.075f, -0.025f,
        0.025f, 0.075f, -0.025f,
        -0.0325f, 0.075f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0435f, -0.151f, 0.12f);
    DrawCustomBox(
        -0.025f, -0.075f, 0.025f,
        0.0325f, -0.075f, 0.025f,
        0.0325f, 0.075f, 0.025f,
        -0.025f, 0.075f, 0.025f,
        -0.025f, -0.075f, -0.025f,
        0.0325f, -0.075f, -0.025f,
        0.0325f, 0.075f, -0.025f,
        -0.025f, 0.075f, -0.025f
    );
    glPopMatrix();
}

void head::MouthCover()
{
    BindTexture(carbonTexture);
    glPushMatrix();
    glTranslatef(0.0f, -0.275f, 0.175f);
    glRotatef(15, 1.0f, 0.0f, 0.0f);
    DrawCustomBox(
        -0.15f, -0.1f, 0.025f,
        0.15f, -0.1f, 0.025f,
        0.17f, 0.1f, 0.025f,
        -0.17f, 0.1f, 0.025f,
        -0.15f, -0.1f, -0.025f,
        0.15f, -0.1f, -0.025f,
        0.15f, 0.1f, -0.025f,
        -0.15f, 0.1f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.255f, -0.275f, 0.07f);
    glRotatef(-45, 0.0f, 1.0f, 0.0f);
    glRotatef(15, 1.0f, 0.0f, 0.0f);
    DrawCustomBox(
        -0.15f, 0.025f, 0.025f,
        0.15f, -0.1f, 0.025f,
        0.17f, 0.1f, 0.025f,
        -0.15f, 0.2f, 0.025f,
        -0.1f, 0.025f, -0.025f,
        0.15f, -0.1f, -0.025f,
        0.15f, 0.1f, -0.025f,
        -0.1f, 0.15f, -0.025f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.255f, -0.275f, 0.07f);
    glRotatef(45, 0.0f, 1.0f, 0.0f);
    glRotatef(15, 1.0f, 0.0f, 0.0f);
    DrawCustomBox(
        -0.15f, -0.1f, 0.025f,
        0.15f, 0.025f, 0.025f,
        0.15f, 0.2f, 0.025f,
        -0.17f, 0.1f, 0.025f,
        -0.15f, -0.1f, -0.025f,
        0.1f, 0.025f, -0.025f,
        0.1f, 0.15f, -0.025f,
        -0.15f, 0.1f, -0.025f
    );
    glPopMatrix();
}

void head::HeadCover()
{
    BindTexture(whiteMetalTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.185f, 0.0f);
    glScalef(1.0f, 0.8f, 1.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    DrawUpperFaceRing(8, 0.12f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.1275f, 0.0f);
    glScalef(1.0f, 0.8f, 1.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    DrawMiddleFaceRing(8, 0.215f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.1f, 0.0f);
    glScalef(1.0f, 1.25f, 1.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    DrawBottomFaceRing(8, 0.215f);
    glPopMatrix();
}

void head::DrawHead()
{
    glPushMatrix();
        glTranslatef(0.0f, -0.015f, 0.0f);
        glRotatef(headRotY, 0.0f, 1.0f, 0.0f);
        glRotatef(headRotX, 1.0f, 0.0f, 0.0f);
        HeadCover();

        glPushMatrix();
            glTranslatef(0.0f, -0.025f, 0.15f);
            Eyes();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.15f);
    MouthCover();
    glPopMatrix();
}