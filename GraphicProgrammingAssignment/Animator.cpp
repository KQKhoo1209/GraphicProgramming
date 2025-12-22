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

        // Jump Animation Time = 3sec
        if (jumpPhase > 3.0f)
        {
            jumpPhase = 0.0f;
            state = IDLE_ANIM;
        }
    }

    if (state == KNIFE_SEP_ANIM)
    {
        knifePhase += deltaTime * 1.0f;

        // Knife Separate Animation Time = 5sec
        if (knifePhase > 5.0f)
        {   
            knifePhase = 0.0f;
            state = IDLE_ANIM;
        }
    }

    if (state == SWING_KNIFE_ANIM)
    {
        swingPhase += deltaTime * 0.5f;
        if (swingPhase > 1.5f)
        {
            swingPhase = 0.0f;
            state = IDLE_ANIM;
        }
    }
}

void Animator::RobotWalk()
{
	state = WALK_ANIM;
}

float Animator::GetShoulderAngle(float side) const
{
    if (state == KNIFE_SEP_ANIM)
    {
        return GetSpecialShoulderAngle();
    }

    if (state == WALK_ANIM)
    {
        float offset = (side < 0.0f) ? 3.14159f : 0.0f;

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
    if (state != KNIFE_SEP_ANIM) return -90.0f;

    if (knifePhase < 2.5f)
    {
        return -75.0f + (sin(knifePhase * 10.0f) * 15.0f);
    }

    float t = (knifePhase - 2.5f) * 5.0f;
    float angle = -20.0f + (60.0f * t);
    return (angle > 0.0f) ? 0.0f : angle;
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
    float delay = index * 0.15f;
    float t = knifePhase - startSpawnTime - delay;

    if (t <= 0.0f) return 0.0f;

    float scale = t * 10.0f;
    if (scale > 1.0f) scale = 1.0f;

    return scale;
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

void Animator::SwingKnives()
{
    if (state == IDLE_ANIM || state == WALK_ANIM)
    {
        state = SWING_KNIFE_ANIM;
        swingPhase = 0.0f;
    }
}

float Animator::GetSwingShoulderAngle(float side) const
{
	float t, startAngle, targetAngle;
    if (state != SWING_KNIFE_ANIM) return 0.0f;

    if (swingPhase < 0.4f) {
        return side * -30.0f;
    }
    else if (swingPhase < 1.0f) { 
        t = (swingPhase - 0.4f) / 0.6f;
        startAngle = side * -30.0f;
        targetAngle = 0.0f;
        return startAngle + t * (targetAngle - startAngle);
    }
    else {
        t = (swingPhase - 1.0f) / 0.5f;
        startAngle = 0.0f;
        targetAngle = side * -90.0f;
        return startAngle + t * (targetAngle - startAngle);
    }
}

float Animator::GetSwingElbowAngle(float side) const
{
    if (state != SWING_KNIFE_ANIM) return 0.0f;

    if (swingPhase < 0.4f) {
        return side * -90.0f;
    }
    else if (swingPhase < 1.0f) {
        float t = (swingPhase - 0.4f) / 0.6f;
        float startAngle = side * -90.0f;
        float targetAngle = 0.0f; 
        return startAngle + t * (targetAngle - startAngle);
    }
    else {
        float t = (swingPhase - 1.0f) / 0.5f;
        float startAngle = 0.0f;
        float targetAngle = side * -90.0f;
        return startAngle + t * (targetAngle - startAngle);
    }
}

float Animator::GetSwingWristAngle(float side) const
{
    if (state != SWING_KNIFE_ANIM) return 0.0f;

    return 0.0f; 
}

float Animator::GetSwingFingerAngle(float side) const
{
    if (state != SWING_KNIFE_ANIM) return 0.0f;
    return -80.0f;
}

float Animator::GetSwingThumbAngle(float side) const
{
    if (state != SWING_KNIFE_ANIM) return 0.0f;
    return -40.0f;
}

void Animator::Stop()
{
    state = IDLE_ANIM;
}