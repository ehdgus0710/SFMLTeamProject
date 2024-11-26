#pragma once

#include "GUI.h"
#include "Animation.h"

class AnimationToolGUI : public GUI
{

private:
    sf::Sprite                  sprite;
    sf::Texture*                texture;
    std::vector<std::string>    textureVector;
    std::vector<AnimationInfo>  animInfoVector;
    std::string                 textureID;
    std::string                 animationName;

    sf::Vector2u                rectSize;
    sf::Vector2u                atlasRectSize;

    static int                  frameID;
    float                       accTime;
    bool                        isPlay;
    bool                        isRepeat;
    bool                        isButton;
    bool                        isAtlasTextrue;

public:
    void Update() override;

    void TextureLoad();
    void AnimationSave(const std::string& animationName);
    void AnimationLoad();
private:
    void AnimationPlay(int& iFrmID);
    void ChangeToolVersion();
    void AtlasTextrue();
    void DefaultTextrue();

public:
    AnimationToolGUI();
    ~AnimationToolGUI();
};

