#pragma once

class WindowManager : public Singleton<WindowManager>
{
	friend Singleton<WindowManager>;
private:
	sf::RenderWindow*	renderWindow;
	sf::Vector2u		resolutionSize;
	std::string			titleName;

public:
	void init(const sf::Vector2u size, const std::string& title);


	void SetResolutionSize(const sf::Vector2u resolutionSize) { this->resolutionSize = resolutionSize; }
	void SetTitleName(const std::string titleName) { this->titleName = titleName; }

	sf::RenderWindow* GetRenderWindow() { return renderWindow; }
	const sf::Vector2u& GetResolutionSize() const { return resolutionSize; }
	const std::string& GetTitleName() const { return titleName; }

protected:
	WindowManager() = default;
	~WindowManager() override;
	WindowManager(const WindowManager&) = delete;
	WindowManager& operator=(const WindowManager&) = delete;
};

