#include "AnimationHandler.h"


void AnimationHandler::update(const float dt)
{
    if(m_currentAnim >= m_animations.size() || m_currentAnim < 0) return;

    float duration = m_animations[m_currentAnim].m_duration;

    /* Check if the animation has progressed to a new frame and if so
     * change to the next frame */
    if(int((m_loopTimeElapsed + dt) / duration) > int(m_loopTimeElapsed / duration))
    {
        /* Calculate the frame number */
        int frame = int((m_loopTimeElapsed + dt) / duration);

        /* Adjust for looping */
        frame %= m_animations[m_currentAnim].getLength();

        /* Set the sprite to the new frame */
        sf::IntRect rect = m_frameSize;
        rect.left = rect.width * frame;
        rect.top = rect.height * m_currentAnim;
        m_bounds = rect;
    }

    /* Increment the time elapsed */
    m_loopTimeElapsed += dt;
    /* Adjust for looping */
    if(m_loopTimeElapsed > duration * m_animations[m_currentAnim].getLength())
    {
        m_loopTimeElapsed = 0.0f;
    }

    return;
}

void AnimationHandler::addAnim(Animation& anim)
{
    m_animations.push_back(anim);
    return;
}

void AnimationHandler::changeAnim(uint32_t animationIndex)
{
    //don't change animation if animation is active or invalid index
    if (m_currentAnim == animationIndex ||
        animationIndex >= m_animations.size() ||
        animationIndex < 0)
    {
        return;
    }

    m_currentAnim = animationIndex;

    sf::IntRect rect = m_frameSize;

    rect.top = rect.height * animationIndex;
    m_bounds = rect;
    m_loopTimeElapsed = 0.0;

    return;

}
