#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>

class head
{
private:
	float headRotX;
	float headRotY;
	GLUquadricObj* robotHead;
public:
	head();   // constructor
	~head();  // destructor
	void InitializeHeadQuadratics();
	void Eyes();
	void MouthCover();
	void HeadCover();
	void DrawHead();
	void RotateY(float delta);
	void RotateX(float delta);
	float GetRotationX() const { return headRotX; }
	float GetRotationY() const { return headRotY; }
};