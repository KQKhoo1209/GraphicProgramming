#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "torso.h"
#include "texture.h"
#include <math.h>

extern GLfloat blackColor[];
extern GLfloat whiteColor[];

void QuadNormal(float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4) {
    float v1[3] = { x1, y1, z1 };
    float v2[3] = { x2, y2, z2 };
    float v3[3] = { x3, y3, z3 };
    float v4[3] = { x4, y4, z4 };

    float normal[3];

    // Calculate using two triangles
    float vec1[3], vec2[3];

    // First triangle (v1, v2, v3)
    vec1[0] = v2[0] - v1[0];
    vec1[1] = v2[1] - v1[1];
    vec1[2] = v2[2] - v1[2];

    vec2[0] = v3[0] - v1[0];
    vec2[1] = v3[1] - v1[1];
    vec2[2] = v3[2] - v1[2];

    normal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    normal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    normal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

    // Second triangle (v1, v3, v4)
    vec1[0] = v3[0] - v1[0];
    vec1[1] = v3[1] - v1[1];
    vec1[2] = v3[2] - v1[2];

    vec2[0] = v4[0] - v1[0];
    vec2[1] = v4[1] - v1[1];
    vec2[2] = v4[2] - v1[2];

    normal[0] += vec1[1] * vec2[2] - vec1[2] * vec2[1];
    normal[1] += vec1[2] * vec2[0] - vec1[0] * vec2[2];
    normal[2] += vec1[0] * vec2[1] - vec1[1] * vec2[0];

    // Average and normalize
    normal[0] *= 0.5f;
    normal[1] *= 0.5f;
    normal[2] *= 0.5f;

    float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (length > 0.00001f) {
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;
    }

    glNormal3fv(normal);
}

void TriNormal(float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3) {
    float v1[3] = { x1, y1, z1 };
    float v2[3] = { x2, y2, z2 };
    float v3[3] = { x3, y3, z3 };

    float normal[3];

    float vec1[3], vec2[3];
    vec1[0] = v2[0] - v1[0];
    vec1[1] = v2[1] - v1[1];
    vec1[2] = v2[2] - v1[2];

    vec2[0] = v3[0] - v1[0];
    vec2[1] = v3[1] - v1[1];
    vec2[2] = v3[2] - v1[2];

    normal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    normal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    normal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

    float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    if (length > 0.00001f) {
        normal[0] /= length;
        normal[1] /= length;
        normal[2] /= length;
    }

    glNormal3fv(normal);
}

void DrawCube(float size) {
    float half = size * 0.5f;

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, -half, half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half, -half, half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half, half, half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half, half, half);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half, -half, -half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half, half, -half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(half, half, -half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(half, -half, -half);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half, half, -half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, half, half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half, half, half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half, half, -half);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half, -half, -half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(half, -half, -half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(half, -half, half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half, -half, half);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(half, -half, -half);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half, half, -half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half, half, half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(half, -half, half);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half, -half, -half);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half, -half, half);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half, half, half);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half, half, -half);

    glEnd();
}

void DrawCustomBox(float v0x, float v0y, float v0z,
    float v1x, float v1y, float v1z,
    float v2x, float v2y, float v2z,
    float v3x, float v3y, float v3z,
    float v4x, float v4y, float v4z,
    float v5x, float v5y, float v5z,
    float v6x, float v6y, float v6z,
    float v7x, float v7y, float v7z) {

    float vertices[8][3] = {
        {v0x, v0y, v0z},
        {v1x, v1y, v1z},
        {v2x, v2y, v2z},
        {v3x, v3y, v3z},
        {v4x, v4y, v4z},
        {v5x, v5y, v5z},
        {v6x, v6y, v6z},
        {v7x, v7y, v7z}
    };

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[0]); // FBL
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[1]); // FBR
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]); // FTR
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[3]); // FTL

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[4]); // BBL
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[7]); // BTL
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[6]); // BTR
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[5]); // BBR

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[7]); // BTL
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[3]); // FTL
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[2]); // FTR
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[6]); // BTR

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[4]); // BBL
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[5]); // BBR
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[1]); // FBR
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[0]); // FBL

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[5]); // BBR
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[6]); // BTR
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[2]); // FTR
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[1]); // FBR

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[4]); // BBL
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[0]); // FBL
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[3]); // FTL
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[7]); // BTL

    glEnd();
}

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
    float ringDotAngle = 0.0f;
    float ringX = 0.0f;
    float ringY = 0.0f;

    GLfloat coreDiffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat coreSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat coreEmission[] = { 0.6f, 0.9f, 1.0f, 1.0f };

}

torso::~torso()
{
    if (robotTorso)
    {
        gluDeleteQuadric(robotTorso);
        robotTorso = nullptr;
    }
}

void torso::IntitializeTorsoQuadratics()
{
    gluQuadricTexture(robotTorso, GL_TRUE);
    gluQuadricDrawStyle(robotTorso, GLU_FILL);
    gluQuadricNormals(robotTorso, GLU_SMOOTH);
}

void torso::TorsoFrontPattern()
{
    BindTexture(darkSteelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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

    BindTexture(redSteelTexture);
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

    // Robot Middle Light
    BindTexture(steelTexture);
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

    glPushMatrix();
    glTranslatef(0.0f, 0.05f, 0.095f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        ringDotAngle = i * (3.14 / 180);
        ringX = 0.1f * cos(ringDotAngle);
        ringY = 0.1f * sin(ringDotAngle);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blackColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackColor);
        glVertex2f(ringX, ringY + 0.2f);
    }
    glEnd();
    glPopMatrix();
}

void torso::TorsoBackPattern()
{
    // Back Large Cube
    BindTexture(steelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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

    BindTexture(darkSteelTexture);
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
    BindTexture(carbonTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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
    BindTexture(darkSteelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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
    BindTexture(blueSteelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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

    BindTexture(darkSteelTexture);
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
    BindTexture(blueSteelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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
    BindTexture(steelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);

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
    BindTexture(blueSteelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
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
    BindTexture(steelTexture);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteColor);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(robotTorso, 0.1f, 0.1f, 0.9f, 8, 1);
    glPopMatrix();
}

void torso::DrawTorso()
{
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
}