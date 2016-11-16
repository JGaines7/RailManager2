#ifndef AnimationHandler_H
#define AnimationHandler_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:
        uint32_t m_startFrame;
        uint32_t m_endFrame;

        float m_duration;

        Animation(uint32_t startFrame, uint32_t endFrame, float duration)
        {
            m_startFrame = startFrame;
            m_endFrame = endFrame;
            m_duration = duration;
        }

        uint32_t getLength() {return m_endFrame - m_startFrame + 1;}

};

class AnimationHandler
{
    public:

        AnimationHandler()
        {
            m_loopTimeElapsed = 0.0f;
            m_currentAnim = -1;
        }

        AnimationHandler(const sf::IntRect& frameSize)
        {
            m_frameSize = frameSize;
            m_loopTimeElapsed = 0.0f;
            m_currentAnim = -1;
        }

        void addAnim(Animation& anim);

        void update(const float dt);

        void changeAnim(uint32_t animNum);

        //current section of texture that should be displayed.
        sf::IntRect m_bounds;

        //pixel dimensions of each frame
        sf::IntRect m_frameSize;

        virtual ~AnimationHandler();

    private:

        //Vector of loaded animations
        std::vector<Animation> m_animations;

        // Time since animation loop started;
        float m_loopTimeElapsed;

        uint32_t m_currentAnim;
};

#endif // AnimationHandler_H
