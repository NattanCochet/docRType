/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Drawable
*/

#include "../../include/Components/Drawable.hpp"

Drawable::FrameRect::FrameRect(int rectLeft, int rectTop, int rectWidth, int rectHeight)
    : _rectLeft(rectLeft), _rectTop(rectTop), _rectWidth(rectWidth), _rectHeight(rectHeight)
{
}

Drawable::Drawable::Drawable(
    std::string type, bool isAnimated, sf::Vector2f scale,
    std::vector<FrameRect> defaultFrame, float secondForDefaultFrame,
    std::vector<FrameRect> frameUP, float secondForFrameUp,
    std::vector<FrameRect> frameDown, float secondForFrameDown,
    std::vector<FrameRect> frameLeft, float secondForFrameLeft,
    std::vector<FrameRect> frameRight, float secondForFrameRight
) : _type(type),
    _isAnimated(isAnimated),
    _scale(scale),
    _defaultFrame(defaultFrame),
    _secondForDefaultFrame(secondForDefaultFrame),
    _frameUP(frameUP),
    _secondForFrameUp(secondForFrameUp),
    _frameDown(frameDown),
    _secondForFrameDown(secondForFrameDown),
    _frameLeft(frameLeft),
    _secondForFrameLeft(secondForFrameLeft),
    _frameRight(frameRight),
    _secondForFrameRight(secondForFrameRight),
    _currentFrame(0),
    _directionFrame(0)
{
    if (_defaultFrame.empty()) {
        throw ErrorNoObject("defaultFrame", "Drawable::Drawable::Drawable");
    }
}

Drawable::Drawable::~Drawable()
{
}

std::string &Drawable::Drawable::getType() noexcept
{
    return (this->_type);
}

sf::Vector2f &Drawable::Drawable::getScale() noexcept
{
    return (this->_scale);
}

const bool &Drawable::Drawable::getIsAnimate() const noexcept
{
    return (this->_isAnimated);
}

Drawable::FrameRect &Drawable::Drawable::getCurrentRect() noexcept
{
    switch (this->_directionFrame) {
    case 0:
        return (this->_defaultFrame[this->_currentFrame]);
    case 1:
        return (this->_frameUP[this->_currentFrame]);
    case 2:
        return (this->_frameRight[this->_currentFrame]);
    case 3:
        return (this->_frameDown[this->_currentFrame]);
    case 4:
        return (this->_frameLeft[this->_currentFrame]);

    default:
        return (this->_defaultFrame[this->_currentFrame]);
    }
}

const std::vector<Drawable::FrameRect> &Drawable::Drawable::getDefaultFrame() noexcept
{
    return (this->_defaultFrame);
}

const std::vector<Drawable::FrameRect> &Drawable::Drawable::getFrameUp() noexcept
{
    return (this->_frameUP);
}

const std::vector<Drawable::FrameRect> &Drawable::Drawable::getFrameDown() noexcept
{
    return (this->_frameDown);
}

const std::vector<Drawable::FrameRect> &Drawable::Drawable::getFrameLeft() noexcept
{
    return (this->_frameLeft);
}

const std::vector<Drawable::FrameRect> &Drawable::Drawable::getFrameRight() noexcept
{
    return (this->_frameRight);
}

const float Drawable::Drawable::getSecondForDefaultFrame() const noexcept
{
    return (this->_secondForDefaultFrame);
}

const float Drawable::Drawable::getSecondForFrameUp() const noexcept
{
    return (this->_secondForFrameUp);
}

const float Drawable::Drawable::getSecondForFrameDown() const noexcept
{
    return (this->_secondForFrameDown);
}

const float Drawable::Drawable::getSecondForFrameLeft() const noexcept
{
    return (this->_secondForFrameLeft);
}

const float Drawable::Drawable::getSecondForFrameRight() const noexcept
{
    return (this->_secondForFrameRight);
}

void Drawable::Drawable::setType(const std::string &newType) noexcept
{
    this->_type = newType;
}

void Drawable::Drawable::setScale(const sf::Vector2f &newScale) noexcept
{
    this->_scale = newScale;
}

void Drawable::Drawable::setIsAnimate(const bool &newIsAnimate) noexcept
{
    this->_isAnimated = newIsAnimate;
}

void Drawable::Drawable::setDefaultFrame(const std::vector<FrameRect> &newDefaultFrame)
{
    this->_defaultFrame = newDefaultFrame;

    if (this->_defaultFrame.size() == 0) {
        throw ErrorNoObject("defaultFrame", "Drawable::Drawable::setDefaultFrame");
    }
}

void Drawable::Drawable::setFrameUp(const std::vector<FrameRect> &newFrameUp) noexcept
{
    this->_frameUP = newFrameUp;
}

void Drawable::Drawable::setFrameDown(const std::vector<FrameRect> &newFrameDown) noexcept
{
    this->_frameDown = newFrameDown;
}

void Drawable::Drawable::setFrameLeft(const std::vector<FrameRect> &newFrameLeft) noexcept
{
    this->_frameLeft = newFrameLeft;
}

void Drawable::Drawable::setFrameRight(const std::vector<FrameRect> &newFrameRight) noexcept
{
    this->_frameRight = newFrameRight;
}

void Drawable::Drawable::setSecondForDefaultFrame(const float &newSecondForDefaultFrame) noexcept
{
    this->_secondForDefaultFrame = newSecondForDefaultFrame;
}

void Drawable::Drawable::setSecondForFrameUp(const float &newSecondForFrameUp) noexcept
{
    this->_secondForFrameUp = newSecondForFrameUp;
}

void Drawable::Drawable::setSecondForFrameDown(const float &newSecondForFrameDown) noexcept
{
    this->_secondForFrameDown = newSecondForFrameDown;
}

void Drawable::Drawable::setSecondForFrameLeft(const float &newSecondForFrameLeft) noexcept
{
    this->_secondForFrameLeft = newSecondForFrameLeft;
}

void Drawable::Drawable::setSecondForFrameRight(const float &newSecondForFrameRight) noexcept
{
    this->_secondForFrameRight = newSecondForFrameRight;
}

void Drawable::Drawable::passNextFrame() noexcept
{
    this->_currentFrame += 1;
    switch (this->_directionFrame) {
    case 0:
        this->_currentFrame %= this->_defaultFrame.size();
        break;
    case 1:
        this->_currentFrame %= this->_frameUP.size();
        break;
    case 2:
        this->_currentFrame %= this->_frameRight.size();
        break;
    case 3:
        this->_currentFrame %= this->_frameDown.size();
        break;
    case 4:
        this->_currentFrame %= this->_frameLeft.size();
        break;

    default:
        this->_currentFrame %= this->_defaultFrame.size();
        break;
    }
}

void Drawable::Drawable::setDirectionFrame(const int &direction) noexcept
{
    if (direction % 6 != this->_directionFrame) {
        this->_directionFrame = direction % 6;

        switch (this->_directionFrame) {
            case 1: {
                if (this->_frameUP.size() == 0) {
                    this->_directionFrame = 0;
                }
                break;
            }
            case 2: {
                if (this->_frameRight.size() == 0) {
                    this->_directionFrame = 0;
                }
                break;
            }
            case 3: {
                if (this->_frameDown.size() == 0) {
                    this->_directionFrame = 0;
                }
                break;
            }
            case 4: {
                if (this->_frameLeft.size() == 0) {
                    this->_directionFrame = 0;
                }
                break;
            }

            default:
                this->_directionFrame = 0;
                break;
        }
        this->_currentFrame = 0;
    }
}

const float Drawable::Drawable::getSecondDependOnDirection() const noexcept
{
    switch (this->_directionFrame) {
    case 0:
        return (this->_secondForDefaultFrame);
    case 1:
        return (this->_secondForFrameUp);
    case 2:
        return (this->_secondForFrameRight);
    case 3:
        return (this->_secondForFrameDown);
    case 4:
        return (this->_secondForFrameLeft);

    default:
        return (this->_secondForDefaultFrame);
    }
}

sf::Clock &Drawable::Drawable::getClock() noexcept
{
    return (this->_clock);
}

std::size_t Drawable::Drawable::getCurrentFrame() const
{
    return (this->_currentFrame);
}
