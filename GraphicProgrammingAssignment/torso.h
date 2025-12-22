#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>

enum TorsoSkin
{
	TORSO_STEEL = 0,
	TORSO_CRIMSON,
	TORSO_BLUESTEEL
};

class torso
{
private:
	GLUquadricObj* robotTorso;

	TorsoSkin currentSkin;

	float ringDotAngle;
	float ringX;
	float ringY;
	
	float lightOffset;
	float lightSpeed;
	float lightZPosition;
public:
	torso();   // constructor
	~torso();  // destructor
	void SetSkin(TorsoSkin skin);
	GLuint GetBaseTorsoTexture();
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

