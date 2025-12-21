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

    jumpPhase = 0.0f;
    knifePhase = 0.0f;
}

void Animator::AnimUpdate(float deltaTime)
{
    if (state == WALK_ANIM)
    {
        phase += speed * deltaTime;

        if (phase >= maxPhase)
            phase -= maxPhase;
    }

    if (state == JUMP_ANIM)
    {
        jumpPhase += deltaTime * 2.5f;

        if (jumpPhase > 3.0f)
        {
            jumpPhase = 0.0f;
            state = IDLE_ANIM;
        }
    }

    if (state == KNIFE_SEP_ANIM)
    {
        knifePhase += deltaTime * 1.0f;

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

// Add this to Animator.cpp

float Animator::GetShoulderAngle(float side) const
{
    // 1. Priority: Knife Animation (Existing logic)
    if (state == KNIFE_SEP_ANIM)
    {
        return GetSpecialShoulderAngle();
    }

    // 2. Walking Animation (New logic)
    if (state == WALK_ANIM)
    {
        // Arms swing opposite to legs.
        // Left Arm (side -1) needs offset PI (3.14) to be opposite to Left Leg (0.0)
        // Right Arm (side 1) needs offset 0.0 to be opposite to Right Leg (3.14)
        float offset = (side < 0.0f) ? 3.14159f : 0.0f;

        // Swing amplitude of 25 degrees
        return sin(phase + offset) * 25.0f;
    }
    return 0.0f;
}

void Animator::RobotJump()
{
    if (state == IDLE_ANIM || state == WALK_ANIM)
    {
        state = JUMP_ANIM;
        jumpPhase = 0.0f;
    }
}

float Animator::GetJumpHeight() const
{
    if (state != JUMP_ANIM) return 0.0f;

    if (jumpPhase < 0.5f) return 0.0f;
    if (jumpPhase > 2.5f) return 0.0f;

    float t = (jumpPhase - 0.5f) * (3.14159f / 2.0f);

    return sin(t) * 2.0f;
}

float Animator::GetJumpKneeAngle() const
{
    if (state != JUMP_ANIM) return 0.0f;

    return 30.0f * sin(jumpPhase);
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
    // Jumping Logic
    if (state == JUMP_ANIM)
    {
        if (jumpPhase < 0.5f) {
            return -30.0f * (jumpPhase / 0.5f);
        }
        else if (jumpPhase > 2.5f) {
            return -30.0f * ((3.0f - jumpPhase) / 0.5f);
        }
        else {
            return 0.0f;
        }
    }

    // Knife Spawning Leg Move
    if (state == KNIFE_SEP_ANIM)
    {
        bool isLeft = (side < 0.0f);
        return GetSpecialLegAngle(isLeft);
    }

    // Walking Logic
    if (state != WALK_ANIM) return 0.0f;

    float offset = (side < 0.0f) ? 0.0f : 3.14159f;
    return sin(phase + offset) * 25.0f;
}

float Animator::GetKneeAngle(float side) const
{
    if (state == JUMP_ANIM)
    {
        if (jumpPhase < 0.5f) {
            return 60.0f * (jumpPhase / 0.5f);
        }
        else if (jumpPhase > 2.5f) {
            return 60.0f * ((3.0f - jumpPhase) / 0.5f);
        }
        else {
            return 10.0f;
        }
    }

    if (state != WALK_ANIM) return 0.0f;
    float offset = (side < 0.0f) ? 0.0f : 3.14159f;
    return fabs(sin(phase + offset)) * 35.0f;
}