#pragma once

class Scene;

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
protected:
	std::vector<Scene*> sceneVec;

	SceneIds startScene;
	SceneIds currentScene;
public:
	void Init();
	void Release();

	SceneIds GetCurrentSceneId() const { return currentScene; }

	Scene* GetCurrentScene() const { return sceneVec[(int)currentScene]; }
	void ChangeScene(SceneIds id);

	void Update(float deltaTime);
	void FixedUpdate(float fixedDeltaTime);
	void Render(sf::RenderWindow& window);

protected:
	SceneManager() = default;
	virtual ~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
};

#define SCENE_MANAGER (SceneManager::GetInstance())