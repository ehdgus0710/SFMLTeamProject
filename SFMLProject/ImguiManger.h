#pragma once

class GUI;

class ImguiManger : public Singleton<ImguiManger>
{
	friend class Singleton<ImguiManger>;
protected:
	sf::Time*								sfTime;
	std::unordered_map<std::string, GUI*>	guiMap;

private:
	void CreateUI();

public:
	bool									OnGUI;
	bool Init(sf::RenderWindow& window, bool loadDefaultFont = true);
	void Release();
	void ProcessEvent(const sf::Window& window, const sf::Event& event);
	void Update(sf::RenderWindow& window, sf::Time dt);
	void Render(sf::RenderWindow& window);

	void Reset();
	/*virtual GUI* CreateGUI(GUI* gui);

	template<typename T>
	T* CreateGUI(T* gui);*/

protected:
	ImguiManger();
	virtual ~ImguiManger() = default;
	ImguiManger(const ImguiManger&) = delete;
	ImguiManger& operator=(const ImguiManger&) = delete;
};
