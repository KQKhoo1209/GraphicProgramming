#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "helperFunction.h"
#include "texture.h"
#include <math.h>

class Weapon
{
private:
	GLUquadricObj* weapon;
	float weaponCircleAngle;
	float weaponCircleX;
	float weaponCircleY;
public:
	Weapon();
	~Weapon();
	void InitializeWeaponQuadratics();
	void WeaponTip();
	void WeaponHilt();
	void DrawWeapon();
};