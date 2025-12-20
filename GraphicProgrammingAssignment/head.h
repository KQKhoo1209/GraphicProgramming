#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>

class head
{
private:
	GLUquadricObj* robotHead;
public:
	head();   // constructor
	~head();  // destructor
	void InitializeHeadQuadratics();
	void Eyes();
	void MouthCover();
	void HeadCover();
	void DrawHead();
};