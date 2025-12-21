#include "Animator.h"
#include <cmath>
#include "Timer.h"

Animator animator;

Animator::Animator()
{
	state = IDLE_ANIM;
	phase = 0.0f;
	speed = 6.0f;
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
        // Speed 1.0f so 1.0 = 1 second
        knifePhase += deltaTime * 1.0f;

        // Total time is roughly 4.5 to 5.0 seconds now
        if (knifePhase > 5.0f)
        {
            knifePhase = 0.0f;
            state = IDLE_ANIM;
        }
    }
}

void Animator::RobotWalk()
{
	state = WALK_ANIM;
}

void Animator::KnifeAnimation()
{
    state = KNIFE_SEP_ANIM;
    knifePhase = 0.0f;
}

float Animator::GetKnifeOffset(int index) const
{
    if (state != KNIFE_SEP_ANIM)
        return 0.0f;

    float delay = index * 0.15f;
    float t = knifePhase - delay;
    if (t < 0.0f) t = 0.0f;

    return t * 1.5f;
}

float Animator::GetSpecialHeadAngle() const
{
    if (state != KNIFE_SEP_ANIM) return 0.0f;
    if (knifePhase < 1.0f) return 30.0f;
    if (knifePhase < 2.5f) return 30.0f;

    return 0.0f;
}

float Animator::GetSpecialTorsoAngle() const
{
    if (state != KNIFE_SEP_ANIM) return 0.0f;

    if (knifePhase < 2.5f) return 20.0f;

    return 0.0f;
}

float Animator::GetSpecialLegAngle(bool isLeft) const
{
    if (state != KNIFE_SEP_ANIM) return 0.0f;

    if (knifePhase > 0.0f && knifePhase < 2.5f)
    {
        float speed = 15.0f;
        float offset = isLeft ? 0.0f : 3.14159f;
        return sin((knifePhase * speed) + offset) * 30.0f;
    }

    return 0.0f;
}

float Animator::GetSpecialShoulderAngle() const
{
    if (state != KNIFE_SEP_ANIM) return -60.0f;

    if (knifePhase < 2.5f)
    {
        return -20.0f + (sin(knifePhase * 10.0f) * 15.0f);
    }

    else
    {
        float t = (knifePhase - 2.5f) * 5.0f;
        float angle = -20.0f + (60.0f * t);

        if (angle > 0.0f) angle = 0.0f;
        return angle;
    }
}

float Animator::GetSpecialElbowAngle() const
{
    if (state != KNIFE_SEP_ANIM) return 0.0f;

    if (knifePhase < 2.5f)
    {
        return -90.0f;
    }

    return 0.0f;
}

float Animator::GetKnifeScale(int index) const
{
    if (state != KNIFE_SEP_ANIM) return 0.0f;

    if (knifePhase < 2.5f) return 0.0f;

    float startSpawnTime = 2.5f;
    float delay = index * 0.1f;
    float t = knifePhase - startSpawnTime - delay;

    if (t <= 0.0f) return 0.0f;

    float scale = t * 10.0f;
    if (scale > 1.0f) scale = 1.0f;

    return scale;
}

void Animator::Stop()
{
	state = IDLE_ANIM;
}

float Animator::GetHipAngle(float side) const
{
    if (state == KNIFE_SEP_ANIM)
    {
        bool isLeft = (side < 0.0f);
        return GetSpecialLegAngle(isLeft);
    }

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