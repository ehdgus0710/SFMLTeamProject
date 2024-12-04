#include "stdafx.h"
#include "SettingUIBar.h"

#include "UITextGameObject.h"
#include "ScrollButtonUI.h"
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

{
}

void SettingUIBar::CreateUIObject()
{
	TEXTURE_MANAGER.Load("OptionsAudioDot", "graphics/UI/Options_AudioDot.png");
	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();

	sf::Vector2f pos = { currentScene->GetUICamera()->GetView().getSize() * 0.5f};
	audioText = currentScene->AddGameObject(new UITextGameObject("NameFont", "audioText", 60, { 174,151,133,255 }), LayerType::UI);
	audioText->SetPosition(pos);
	audioText->SetOrigin(Origins::MiddleCenter);
	audioText->SetString(L"오디오");
	audioText->Start();
	objects.push_back(audioText);

	totalSoundScroller = currentScene->AddGameObject(new ScrollButtonUI(MoveType::LeftRight,"OptionsAudioDot", "TotalSoundScroller"), LayerType::UI);
	totalSoundScroller->SetOrigin(Origins::MiddleCenter);
	totalSoundScroller->SetStartPosition(pos + sf::Vector2f::down * 50.f, 0.f, 300.f, 150.f);
	totalSoundScroller->GetCollider()->SetScale({ 1.75f, 1.5f });
	totalSoundScroller->SetChangeValueEvent(std::bind(&SettingUIBar::SetTotalSound, this, std::placeholders::_1));

	// totalSoundScroller->SetButtonClickEvent(std::bind(&PauseUIBar::OffUIBar, this));
	totalSoundScroller->Start();	
	objects.push_back(totalSoundScroller);

	bgmSoundScroller = currentScene->AddGameObject(new ScrollButtonUI(MoveType::LeftRight, "OptionsAudioDot", "BgmSoundScroller"), LayerType::UI);
	bgmSoundScroller->SetOrigin(Origins::MiddleCenter);
	bgmSoundScroller->SetStartPosition(pos + sf::Vector2f::down * 50.f, 0.f, 300.f, 150.f);
	bgmSoundScroller->GetCollider()->SetScale({ 1.75f, 1.5f });
	bgmSoundScroller->Start();
	bgmSoundScroller->SetChangeValueEvent(std::bind(&SettingUIBar::SetBgmSound, this, std::placeholders::_1));
	// bgmSoundScroller->SetButtonClickEvent(std::bind(&PauseUIBar::OnNewGame, this));
	objects.push_back(bgmSoundScroller);

	effectSoundScroller = currentScene->AddGameObject(new ScrollButtonUI(MoveType::LeftRight, "OptionsAudioDot", "BgmSoundScroller"), LayerType::UI);
	effectSoundScroller->SetOrigin(Origins::MiddleCenter);
	effectSoundScroller->SetStartPosition(pos + sf::Vector2f::down * 50.f, 0.f, 300.f, 150.f);
	effectSoundScroller->GetCollider()->SetScale({ 1.75f, 1.5f });
	effectSoundScroller->GetCollider()->SetOffsetPosition({ 0.f , 7.5f });
	effectSoundScroller->Start();
	effectSoundScroller->SetChangeValueEvent(std::bind(&SettingUIBar::SetEffectSound, this, std::placeholders::_1));
	objects.push_back(effectSoundScroller);
	// effectSoundScroller->SetButtonClickEvent(std::bind(&PauseUIBar::OnControllerBar, this));

	totalSoundText = currentScene->AddGameObject(new UITextGameObject("NameFont", "TotalSoundText", 30, { 98 , 73, 59, 255 }), LayerType::UI);
	totalSoundText->SetString(L"음량");
	totalSoundText->SetOrigin(Origins::MiddleCenter);
	totalSoundText->SetPosition(pos + sf::Vector2f::down * 60.f);
	totalSoundText->Start();
	objects.push_back(totalSoundText);

	bgmSoundText = currentScene->AddGameObject(new UITextGameObject("NameFont", "BgmSoundText", 30, { 98 , 73, 59, 255 }), LayerType::UI);
	bgmSoundText->SetString(L"음악");
	bgmSoundText->SetOrigin(Origins::MiddleCenter);
	bgmSoundText->SetPosition(pos + sf::Vector2f::down * 120);
	bgmSoundText->Start();
	objects.push_back(bgmSoundText);

	effectSoundText = currentScene->AddGameObject(new UITextGameObject("NameFont", "EffectSoundText", 30, { 98 , 73, 59, 255 }), LayerType::UI);
	effectSoundText->SetString(L"효과음");
	effectSoundText->SetOrigin(Origins::MiddleCenter);
	effectSoundText->SetPosition(pos + sf::Vector2f::down * 180.f);
	effectSoundText->Start();
	objects.push_back(effectSoundText);
}

void SettingUIBar::SetChildActive(const bool active)
{
	for (auto& object : objects)
	{
		object->SetActive(active);
	}
}

void SettingUIBar::SetTotalSound(float value)
{
	SoundManger::GetInstance().SetTotalVolume(value);
}

void SettingUIBar::SetBgmSound(float value)
{
	SoundManger::GetInstance().SetBgmVolume(value);
}

void SettingUIBar::SetEffectSound(float value)
{
	SoundManger::GetInstance().SetSfxVolume(value);
}

void SettingUIBar::SetActive(const bool active)
{
	SetChildActive(active);
	UISpriteGameObject::SetActive(active);
}

void SettingUIBar::Start()
{
	TEXTURE_MANAGER.Load("OptionsFrame", "graphics/UI/Options_Frame.png");

	UISpriteGameObject::Start();
	CreateUIObject();

	sortingOrder = 6;

	SetActive(false);
}