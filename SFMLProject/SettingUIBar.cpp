#include "stdafx.h"
#include "SettingUIBar.h"

#include "UITextGameObject.h"
#include "ScrollButtonUI.h"
#include "TextButton.h"
#include "PauseUIBar.h"
#include "Collider.h"
#include "Camera.h"

SettingUIBar::SettingUIBar(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
	, audioText(nullptr)
	, totalSoundScroller(nullptr)
	, bgmSoundScroller(nullptr)
	, effectSoundScroller(nullptr)
	, totalSoundText(nullptr)
	, bgmSoundText(nullptr)
	, effectSoundText(nullptr)
	, settingText(nullptr)
	, returnButton(nullptr)
{
}

void SettingUIBar::CreateUIObject()
{
	TEXTURE_MANAGER.Load("OptionsAudioDot", "graphics/UI/Options_AudioDot.png");
	TEXTURE_MANAGER.Load("OptionsAudioDotWhite", "graphics/UI/Options_AudioDot_White.png");

	defalutColor = { 98 , 73, 59, 255 };
	selectionColor = { 174,151,133,255 };

	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();

	sf::Vector2f pos = { currentScene->GetUICamera()->GetView().getSize() * 0.5f};

	settingText = currentScene->AddGameObject(new UITextGameObject("NameFont", "SettingText", 40, selectionColor), LayerType::UI);
	settingText->SetPosition(pos + sf::Vector2f::up * 420.f);
	settingText->SetOrigin(Origins::MiddleCenter);
	settingText->SetString(L"설정");
	settingText->Start();
	objects.push_back(settingText);

	returnButton = currentScene->AddGameObject(new TextButton("NameFont", "ReturnButton", 40, defalutColor, selectionColor), LayerType::UI);
	returnButton->SetPosition(pos + sf::Vector2f::down * 440.f);
	returnButton->SetString(L"돌아가기");
	returnButton->GetCollider()->SetScale({ 1.75f, 1.5f });
	returnButton->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	returnButton->SetButtonClickEvent(returnButtonClickEvent);
	objects.push_back(returnButton);

	audioText = currentScene->AddGameObject(new UITextGameObject("NameFont", "audioText", 40, selectionColor), LayerType::UI);
	audioText->SetPosition({ 1060.f, 250.f });
	audioText->SetOrigin(Origins::MiddleCenter);
	audioText->SetString(L"오디오");
	audioText->Start();
	objects.push_back(audioText);

	CreateTotalSoundUI(currentScene);
	CreateBGMSoundUI(currentScene);
	CreateEffectSoundUI(currentScene);
}

void SettingUIBar::SetChildActive(const bool active)
{
	for (auto& object : objects)
	{
		object->SetActive(active);
	}
}

void SettingUIBar::CreateTotalSoundUI(Scene* currentScene)
{
	totalSoundScroller = currentScene->AddGameObject(new ScrollButtonUI(MoveType::LeftRight, "OptionsArrow", "TotalSoundScroller"), LayerType::UI);
	totalSoundScroller->SetOrigin(Origins::MiddleCenter);
	totalSoundScroller->SetStartInfo({ 1500.f, 350.f }, { 300.f, 30.f }, SoundManger::GetInstance().GetTotalVolum());
	totalSoundScroller->SetScale(sf::Vector2f::one * 3.f);
	totalSoundScroller->SetChangeValueEvent(std::bind(&SettingUIBar::OnSetTotalSound, this, std::placeholders::_1));
	totalSoundScroller->SetButtonClickEnterEvent(std::bind(&SettingUIBar::OnCollisionEnterTotalSoundUI, this));
	totalSoundScroller->SetButtonClickEndEvent(std::bind(&SettingUIBar::OnCollisionEndTotalSoundUI, this));
	totalSoundScroller->SetOrigin(Origins::MiddleCenter);
	totalSoundScroller->Start();
	objects.push_back(totalSoundScroller);

	totalSoundText = currentScene->AddGameObject(new UITextGameObject("NameFont", "TotalSoundText", 30, defalutColor), LayerType::UI);
	totalSoundText->SetString(L"음량");
	totalSoundText->SetOrigin(Origins::MiddleCenter);
	totalSoundText->SetPosition({ 1050.f, 340.f });
	totalSoundText->Start();
	objects.push_back(totalSoundText);
}

void SettingUIBar::CreateBGMSoundUI(Scene* currentScene)
{
	bgmSoundScroller = currentScene->AddGameObject(new ScrollButtonUI(MoveType::LeftRight, "OptionsArrow", "BgmSoundScroller"), LayerType::UI);
	bgmSoundScroller->SetOrigin(Origins::MiddleCenter);
	bgmSoundScroller->SetScale(sf::Vector2f::one * 3.f);
	bgmSoundScroller->SetStartInfo({ 1500.f,425.f }, { 300.f, 30.f }, SoundManger::GetInstance().GetBgmVolume());
	bgmSoundScroller->SetOrigin(Origins::MiddleCenter);
	bgmSoundScroller->Start();
	bgmSoundScroller->SetChangeValueEvent(std::bind(&SettingUIBar::OnSetBgmSound, this, std::placeholders::_1));
	bgmSoundScroller->SetButtonClickEnterEvent(std::bind(&SettingUIBar::OnCollisionEnterBGMSoundUI, this));
	bgmSoundScroller->SetButtonClickEndEvent(std::bind(&SettingUIBar::OnCollisionEndBGMSoundUI, this));
	objects.push_back(bgmSoundScroller);

	bgmSoundText = currentScene->AddGameObject(new UITextGameObject("NameFont", "BgmSoundText", 30, defalutColor), LayerType::UI);
	bgmSoundText->SetString(L"음악");
	bgmSoundText->SetOrigin(Origins::MiddleCenter);
	bgmSoundText->SetPosition({1050.f, 415.f});
	bgmSoundText->Start();
	objects.push_back(bgmSoundText);
}

void SettingUIBar::CreateEffectSoundUI(Scene* currentScene)
{
	effectSoundScroller = currentScene->AddGameObject(new ScrollButtonUI(MoveType::LeftRight, "OptionsArrow", "effectSoundScroller"), LayerType::UI);
	effectSoundScroller->SetOrigin(Origins::MiddleCenter);
	effectSoundScroller->SetStartInfo({ 1500.f,500.f }, { 300.f, 30.f }, SoundManger::GetInstance().GetSfxVolum());

	effectSoundScroller->SetScale(sf::Vector2f::one * 3.f);
	effectSoundScroller->SetOrigin(Origins::MiddleCenter);
	effectSoundScroller->Start();
	effectSoundScroller->SetChangeValueEvent(std::bind(&SettingUIBar::OnSetEffectSound, this, std::placeholders::_1));
	effectSoundScroller->SetButtonClickEnterEvent(std::bind(&SettingUIBar::OnCollisionEnterEffectSoundUI, this));
	effectSoundScroller->SetButtonClickEndEvent(std::bind(&SettingUIBar::OnCollisionEndEffectSoundUI, this));
	objects.push_back(effectSoundScroller);
	// effectSoundScroller->SetButtonClickEvent(std::bind(&PauseUIBar::OnControllerBar, this));

	effectSoundText = currentScene->AddGameObject(new UITextGameObject("NameFont", "EffectSoundText", 30, defalutColor), LayerType::UI);
	effectSoundText->SetString(L"효과음");
	effectSoundText->SetOrigin(Origins::MiddleCenter);
	effectSoundText->SetPosition({ 1050.f, 500.f });
	effectSoundText->Start();
	objects.push_back(effectSoundText);
}

void SettingUIBar::OnSetTotalSound(float value)
{
	SoundManger::GetInstance().SetTotalVolume(value);
}

void SettingUIBar::OnSetBgmSound(float value)
{
	SoundManger::GetInstance().SetBgmVolume(value);
}

void SettingUIBar::OnSetEffectSound(float value)
{
	SoundManger::GetInstance().SetSfxVolume(value);
}

void SettingUIBar::OnCollisionEnterTotalSoundUI()
{
	totalSoundText->ChangeColor(selectionColor);
	totalSoundScroller->ChangeSprite("OptionsArrowWhite");
	totalSoundScroller->ChangeSpriteDot("OptionsAudioDotWhite");
}

void SettingUIBar::OnCollisionEnterBGMSoundUI()
{
	bgmSoundText->ChangeColor(selectionColor);
	bgmSoundScroller->ChangeSprite("OptionsArrowWhite");
	bgmSoundScroller->ChangeSpriteDot("OptionsAudioDotWhite");
}

void SettingUIBar::OnCollisionEnterEffectSoundUI()
{
	effectSoundText->ChangeColor(selectionColor);
	effectSoundScroller->ChangeSprite("OptionsArrowWhite");
	effectSoundScroller->ChangeSpriteDot("OptionsAudioDotWhite");
}

void SettingUIBar::OnCollisionEndTotalSoundUI()
{
	totalSoundText->ChangeColor(defalutColor);
	totalSoundScroller->ChangeSprite("OptionsArrow");
	totalSoundScroller->ChangeSpriteDot("OptionsAudioDot");
}

void SettingUIBar::OnCollisionEndBGMSoundUI()
{
	bgmSoundText->ChangeColor(defalutColor);
	bgmSoundScroller->ChangeSprite("OptionsArrow");
	bgmSoundScroller->ChangeSpriteDot("OptionsAudioDot");
}

void SettingUIBar::OnCollisionEndEffectSoundUI()
{
	effectSoundText->ChangeColor(defalutColor);
	effectSoundScroller->ChangeSprite("OptionsArrow");
	effectSoundScroller->ChangeSpriteDot("OptionsAudioDot");
}

void SettingUIBar::SetReturnClickEvent(std::function<void()> clickEvent)
{
	returnButtonClickEvent = clickEvent;
}

void SettingUIBar::SetActive(const bool active)
{
	SetChildActive(active);
	UISpriteGameObject::SetActive(active);
}

void SettingUIBar::Start()
{
	TEXTURE_MANAGER.Load("OptionsFrame", "graphics/UI/Options_Frame.png");
	TEXTURE_MANAGER.Load("OptionsArrow", "graphics/UI/Options_Arrow2.png");
	TEXTURE_MANAGER.Load("OptionsArrowWhite", "graphics/UI/Options_Arrow2_White.png");

	UISpriteGameObject::Start();
	CreateUIObject();

	sortingOrder = 6;

	SetActive(false);
}