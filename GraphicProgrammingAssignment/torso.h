#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>

class torso
{
private:
	GLUquadricObj* robotTorso;
	float ringDotAngle;
	float ringX;
	float ringY;
public:
	torso();   // constructor
	~torso();  // destructor
	void InitializeTorsoQuadratics();
	void TorsoFrontPattern();
	void TorsoBackPattern();
	void TorsoFront();
	void TorsoUpper();
	void TorsoSide();
	void TorsoBack();
	void middleCylinder();
	void DrawTorso();
};

