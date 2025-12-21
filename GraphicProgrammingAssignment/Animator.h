#pragma once
#include <math.h>

enum AnimState
{
	BOOT_ANIM,
	IDLE_ANIM,
	WALK_ANIM,
	ATTACK_ANIM
};

class Animator
{
private:
	AnimState state;

	float phase;
	float speed;

	/*bool isWalking;
	float walkPhase;

	float hipAnim;
	float kneeAnim;

	float animSpeed;*/
	float maxPhase;
public:
	Animator();
	~Animator();
	void AnimUpdate(float deltaTime);

	void RobotWalk();
	void Stop();

	float GetHipAngle(float side) const;
	float GetKneeAngle(float side) const;
};