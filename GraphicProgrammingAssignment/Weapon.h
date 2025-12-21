#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "helperFunction.h"
#include "texture.h"
#include <math.h>

enum WeaponSkin
{
	SKIN_STEEL = 0,
	SKIN_CRIMSON,
	SKIN_SLAUGHTER
};

class Weapon
{
private:
	GLUquadricObj* weapon;
	float weaponCircleAngle;
	float weaponCircleX;
	float weaponCircleY;
	WeaponSkin currentSkin;
public:
	Weapon();
	~Weapon();
	void InitializeWeaponQuadratics();
	void WeaponTip();
	void WeaponHilt();
	void DrawWeapon();
	void BindWeaponTexture();
	void SetSkin(WeaponSkin skin);
};