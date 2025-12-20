#include "helperFunction.h"
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

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