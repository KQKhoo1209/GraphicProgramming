#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "hat.h"
#include "texture.h"

void DrawHat()
{
    GLUquadric* hat = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, hatWhiteTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(hat, 0.45, 0.45, 0.15, 24, 4);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, hatRedTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(hat, 0.45, 0.05, 0.9, 24, 10);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, hatWhiteTexture);
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    gluSphere(hat, 0.15, 16, 16);
    glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(hat);
}
