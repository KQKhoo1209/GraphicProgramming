#include "Animator.h"
#include <cmath>
#include "Timer.h"

Animator animator;

Animator::Animator()
{
	state = IDLE_ANIM;
	phase = 0.0f;
	speed = 6.0f;

	/*isWalking = false;
	walkPhase = 0.0f;

	hipAnim = 0.0f;
	kneeAnim = 0.0f;

	animSpeed = 0.005f;*/
	maxPhase = 6.28f;
}

void Animator::AnimUpdate(float deltaTime)
{
    if (state == WALK_ANIM)
    {
        phase += speed * deltaTime;

        if (phase >= maxPhase)
            phase -= maxPhase;
    }

    if (state == KNIFE_SEP_ANIM)
    {
        knifePhase += deltaTime * 3.0f;
        if (knifePhase > 1.0f)
            knifePhase = 1.0f;
    }
}

void Animator::RobotWalk()
{
	state = WALK_ANIM;
}

void Animator::KnifeAnimation()
{
    state = KNIFE_SEP_ANIM;

}

float Animator::GetKnifeOffset(int index) const
{
    if (state != KNIFE_SEP_ANIM)
        return 0.0f;

    float delay = index * 0.15f;
    float t = knifePhase - delay;
    if (t < 0.0f) t = 0.0f;

    return t * 0.25f;
}

void Animator::Stop()
{
	state = IDLE_ANIM;
}

float Animator::GetHipAngle(float side) const
{
    if (state != WALK_ANIM) return 0.0f;

    float offset = (side < 0.0f) ? 0.0f : 3.14159f;
    return sin(phase + offset) * 25.0f;
}

float Animator::GetKneeAngle(float side) const
{
    if (state != WALK_ANIM) return 0.0f;

    float offset = (side < 0.0f) ? 0.0f : 3.14159f;
    return fabs(sin(phase + offset)) * 35.0f;
}