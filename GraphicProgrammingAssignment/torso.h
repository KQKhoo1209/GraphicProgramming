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
	
	float lightOffset;
	float lightSpeed;
	float lightZPosition;
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

	// Breathe light effect
	void UpdateLightPosition();
	void SetupMovingLight();
	void DrawMovingLightSource();
};

