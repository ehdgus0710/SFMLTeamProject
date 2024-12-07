#include "stdafx.h"
#include "SoundManger.h"
void SoundManger::Init(int totalChannels)
{
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundManger::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundManger::Update(float dt)
{
	auto it = playing.begin();
	while (it != playing.end())
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			waiting.push_back(*it);
			it = playing.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void SoundManger::PlayBgm(std::string id, bool loop)
{
	PlayBgm(ResourcesManager<sf::SoundBuffer>::GetInstance().Get(id), loop);
}

void SoundManger::PlayBgm(sf::SoundBuffer& buffer, bool loop)
{
	bgm.stop();
	bgm.setVolume(bgmVolume);
	bgm.setLoop(loop);
	bgm.setBuffer(buffer);
	bgm.play();
}

void SoundManger::StopBgm()
{
	bgm.stop();
}

sf::Sound* SoundManger::PlaySfxGet(std::string id, bool loop)
{
	return PlaySfxGet(ResourcesManager<sf::SoundBuffer>::GetInstance().Get(id), loop);
}

sf::Sound* SoundManger::PlaySfxGet(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setVolume(sfxVolume);
	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);

	return sound;
}

void SoundManger::PlaySfx(std::string id, bool loop)
{
	PlaySfx(ResourcesManager<sf::SoundBuffer>::GetInstance().Get(id), loop);
}

void SoundManger::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setVolume(sfxVolume);
	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);
}

void SoundManger::SetSfxVolume(float v)
{
	sfxVolume = v;
	
	for (auto sound : playing)
	{
		if (totalVolum == 0.f)
			sound->setVolume(0.f);
		else
			sound->setVolume(sfxVolume * totalVolum * 0.01f);
	}
}

void SoundManger::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}
