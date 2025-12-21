#pragma once

enum AnimState
{
    IDLE_ANIM,
    WALK_ANIM,
    KNIFE_SEP_ANIM
};

class Animator
{
private:
    AnimState state = IDLE_ANIM;

    float phase = 0.0f;
    float speed = 6.0f;
    float maxPhase = 6.28318f;

    float knifePhase = 0.0f;
public:
    Animator();

    void AnimUpdate(float dt);

    void RobotWalk();
    void KnifeAnimation();
    void Stop();

    float GetHipAngle(float side) const;
    float GetKneeAngle(float side) const;

    // Knife Spawning Animation
    AnimState GetState() const { return state; }
    float GetKnifeScale(int index) const;
    float GetKnifeOffset(int index) const;
    float GetSpecialHeadAngle() const;
    float GetSpecialTorsoAngle() const;
    float GetSpecialLegAngle(bool isLeft) const;
    float GetSpecialShoulderAngle() const;
    float GetSpecialElbowAngle() const;
};

extern Animator animator;