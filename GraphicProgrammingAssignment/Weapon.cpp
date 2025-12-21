#include "Weapon.h"

extern GLfloat whiteColor[];

Weapon::Weapon()
{
    weapon = gluNewQuadric();
    weaponCircleAngle = 0.0f;
    weaponCircleX = 0.0f;
    weaponCircleY = 0.0f;
}

Weapon::~Weapon()
{
    if (weapon)
    {
        gluDeleteQuadric(weapon);
        weapon = nullptr;
    }
}

void Weapon::InitializeWeaponQuadratics()
{
    gluQuadricTexture(weapon, GL_TRUE);
    gluQuadricDrawStyle(weapon, GLU_FILL);
    gluQuadricNormals(weapon, GLU_SMOOTH);
}

void Weapon::WeaponTip()
{
    glBindTexture(GL_TEXTURE_2D, steelTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    DrawCustomBox(
        0.0f, -0.075f, 0.0f,
        0.75f, -0.075f, 0.0f,
        0.75f, 0.0f, 0.01f,
        0.0f, 0.0f, 0.01f,
        0.0f, 0.0f, -0.01f,
        0.75f, 0.0f, -0.01f,
        1.0f, 0.075f, 0.0f,
        0.0f, 0.075f, 0.0f
    );
    glPopMatrix();
}

void Weapon::WeaponHilt()
{
    glBindTexture(GL_TEXTURE_2D, carbonTexture);
    glPushMatrix();
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 1.5f, 1.0f);
    gluCylinder(weapon, 0.05f, 0.05f, 0.25f, 16, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    DrawCustomBox(
        -0.01, -0.1f, 0.1f,
        0.01, -0.1f, 0.1f,
        0.01, 0.1f, 0.1f,
        -0.01, 0.1f, 0.1f,
        -0.01, -0.1f, -0.1f,
        0.01, -0.1f, -0.1f,
        0.01, 0.1f, -0.1f,
        -0.01, 0.1f, -0.1f
    );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25f, 0.0f, 0.0f);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        weaponCircleAngle = i * (3.14 / 180);
        weaponCircleX = 0.05f * cos(weaponCircleAngle);
        weaponCircleY = 0.075f * sin(weaponCircleAngle);

        glTexCoord2f(
            (weaponCircleX / (2.0f * 0.05f)) + 0.5f,
            (weaponCircleY / (2.0f * 0.075f)) + 0.5f
        );

        glVertex3f(weaponCircleX, weaponCircleY, 0.0f);
    }
    glEnd();
    glPopMatrix();
}

void Weapon::DrawWeapon() 
{
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glPushMatrix();
    WeaponHilt();
    WeaponTip();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}