#pragma once

class torso
{
private:
	GLUquadricObj* robotTorso;
	float ringDotAngle;
	float ringX;
	float ringY;
	float torsoRotY;
	float torsoRotZ;
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
	void RotateY(float delta);
	void RotateZ(float delta);
	float GetRotationY() const { return torsoRotY; }
	float GetRotationZ() const { return torsoRotZ; }
};

