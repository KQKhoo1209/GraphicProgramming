#pragma once

enum AnimState
{
    IDLE_ANIM,
    WALK_ANIM,
    JUMP_ANIM,
    KNIFE_SEP_ANIM
};

class Animator
{
private:
    AnimState state = IDLE_ANIM;

    float phase;
    float speed;
    float maxPhase;

    float jumpPhase;
    float knifePhase;
public:
    Animator();

    void AnimUpdate(float dt);

    // Walk Animation
    void RobotWalk();

    // Jump Animation
    void RobotJump();
    float GetJumpHeight() const;
    float GetJumpKneeAngle() const;

    float GetHipAngle(float side) const;
    float GetKneeAngle(float side) const;

    // Knife Spawning Animation
    void KnifeAnimation();
    AnimState GetState() const { return state; }
    float GetKnifeScale(int index) const;
    float GetKnifeOffset(int index) const;
    float GetSpecialHeadAngle() const;
    float GetSpecialTorsoAngle() const;
    float GetSpecialLegAngle(bool isLeft) const;
    float GetSpecialShoulderAngle() const;
    float GetSpecialElbowAngle() const;

    // Back To Idle
    void Stop();
};

extern Animator animator;