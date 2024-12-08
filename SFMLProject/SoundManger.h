#pragma once

class SoundManger : public Singleton<SoundManger>
{
	friend Singleton<SoundManger>;

protected:
	SoundManger() = default;
	virtual ~SoundManger() = default;

	SoundManger(const SoundManger& other) = delete;
	SoundManger& operator=(const SoundManger& other) = delete;

	sf::Sound bgm;

	std::list<sf::Sound*> playing;
	std::list<sf::Sound*> waiting;

	float totalVolum = 10.f;
	float sfxVolume = 5.f;
	float bgmVolume = 10.f;

public:

	void SetBgmVolume(float v)
	{
		bgmVolume = v;

		if(totalVolum == 0.f)
			bgm.setVolume(0.f);
		else
			bgm.setVolume(bgmVolume * totalVolum * 0.01f);
	}

	void SetTotalVolume(float v) 
	{ 
		totalVolum = v;
		SetBgmVolume(bgmVolume);
		SetSfxVolume(sfxVolume);
	}
	void SetSfxVolume(float v);

	void Init(int totalChannels = 64);
	void Release();
	void Update(float dt);

	void PlayBgm(std::string id, bool loop = true);
	void PlayBgm(sf::SoundBuffer& buffer, bool loop = true);
	void StopBgm();

	float GetTotalVolum() { return totalVolum; }
	float GetSfxVolum() { return sfxVolume; }
	float GetBgmVolume() { return bgmVolume; }

	sf::Sound* PlaySfxGet(std::string id, bool loop = false);
	sf::Sound* PlaySfxGet(sf::SoundBuffer& buffer, bool loop = false);
	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx();
};