#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"
#include "ImguiManger.h"
#include "algorithm"
#include "TileMap.h"

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b) const
	{
		if (a->GetLayerType() != b->GetLayerType())
			return a->GetLayerType() > b->GetLayerType();
		return a->sortingOrder > b->sortingOrder;
	}
};

Scene::Scene(const SceneIds id)
	: id(id)
	, cameraSpeed(500.f)
	, isFreeView(false)
	, mainCamera(nullptr)
	, uICamera(nullptr)
	, freeCamera(nullptr)
{
	gameObjectVectors.resize((int)LayerType::End);
	cameraPosition = sf::Vector2f::zero;

	mainCamera = new Camera(WindowManager::GetInstance().GetRenderWindow()->getDefaultView(), CameraType::Main);
	freeCamera = new Camera(WindowManager::GetInstance().GetRenderWindow()->getDefaultView(), CameraType::Main);
	uICamera = new Camera(WindowManager::GetInstance().GetRenderWindow()->getDefaultView(), CameraType::UI);
}

Scene::~Scene()
{
	if (mainCamera != nullptr)
	{
		delete mainCamera;
		mainCamera = nullptr;
	}
	if (uICamera != nullptr)
	{
		delete uICamera;
		uICamera = nullptr;
	}

	if (freeCamera != nullptr)
	{
		delete freeCamera;
		freeCamera = nullptr;
	}
}

void Scene::Init()
{
	mainCamera->Awake();
	uICamera->Awake();

	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			object->Awake();
		}
	}
}

void Scene::Release()
{
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			object->Release();
			delete object;
		}
		objectVector.clear();
	}
	// gameObjectVectors.clear();

	for (auto& object : destroyObjects)
	{
		object->Release();
		delete object;
	}
	destroyObjects.clear();
}

void Scene::Enter()
{
	mainCamera->Start();
	uICamera->Start();
	for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			object->Start();
		}
	}
}

void Scene::Exit()
{
	ColliderManager::GetInstance().Clear();
	Release();

	ResourcesManager<sf::Texture>::GetInstance().UnloadAll();
	ResourcesManager<sf::Font>::GetInstance().UnloadAll();
	ResourcesManager<sf::SoundBuffer>::GetInstance().UnloadAll();
}

void Scene::Update(float deltaTime)
{

	for (int i = 0; i < (int)LayerType::UI; ++i)
	{
		const sf::Vector2f& cameraPosition = mainCamera->GetCameraPosition();
		auto cameraSize = mainCamera->GetView().getSize();

		for (auto iter = gameObjectVectors[i].begin(); iter != gameObjectVectors[i].end();)
		{
			if ((*iter)->GetDestory())
			{
				iter = gameObjectVectors[i].erase(iter);
			}
			else
			{
				if (!(*iter)->IsActive())
				{
					++iter;
					continue;
				}
				if ((cameraSize.x + (*iter)->GetScale().x) * 0.5f + 300.f > abs(cameraPosition.x - (*iter)->GetPosition().x))
					(*iter)->Update(deltaTime);

				++iter;
			}
		}
	}

	for (int i = (int)LayerType::UI; i < (int)LayerType::End; ++i)
	{
		for (auto iter = gameObjectVectors[i].begin(); iter != gameObjectVectors[i].end();)
		{
			
			if ((*iter)->GetDestory())
			{
				iter = gameObjectVectors[i].erase(iter);
			}
			else
			{
				if (!(*iter)->IsActive())
				{
					++iter;
					continue;
				}
				(*iter)->Update(deltaTime);

				++iter;
			}
		}
	}


	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::F2))
	{
		if (isFreeView)
		{
			isFreeView = !isFreeView;
			TimeManager::GetInstance().SetTimeScale(1.f);
		}
		else
		{
			isFreeView = !isFreeView;
			TimeManager::GetInstance().SetTimeScale(0.f);
		}
	}

	if (InputManager::GetInstance().GetKeyUp(sf::Keyboard::F3))
		ImguiManger::GetInstance().OnGUI = !ImguiManger::GetInstance().OnGUI;

	if (isFreeView)
	{
		if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::LShift))
			cameraSpeed = 1000.f;
		else
			cameraSpeed = 500.f;

		if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Left))
			freeCamera->SetCameraPosition(freeCamera->GetCameraPosition() + sf::Vector2f::left * cameraSpeed * TimeManager::GetInstance().GetUnScaleDeletaTime());
		if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Right))
			freeCamera->SetCameraPosition(freeCamera->GetCameraPosition() + sf::Vector2f::right * cameraSpeed * TimeManager::GetInstance().GetUnScaleDeletaTime());
		if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Up))
			freeCamera->SetCameraPosition(freeCamera->GetCameraPosition() + sf::Vector2f::up * cameraSpeed * TimeManager::GetInstance().GetUnScaleDeletaTime());
		if (InputManager::GetInstance().GetKeyPressed(sf::Keyboard::Down))
			freeCamera->SetCameraPosition(freeCamera->GetCameraPosition() + sf::Vector2f::down * cameraSpeed * TimeManager::GetInstance().GetUnScaleDeletaTime());
	}

	mainCamera->Update(deltaTime);
	uICamera->Update(deltaTime);
}

void Scene::FixedUpdate(float fixedDeltaTime)
{
	/*for (auto& objectVector : gameObjectVectors)
	{
		for (auto& object : objectVector)
		{
			if (!object->IsActive())
				continue;

			object->FixedUpdate(fixedDeltaTime);
		}
	}*/
	for (int i = 0; i < (int)LayerType::UI; ++i)
	{
		const sf::Vector2f& cameraPosition = mainCamera->GetCameraPosition();
		auto cameraSize = mainCamera->GetView().getSize();

		for (auto iter = gameObjectVectors[i].begin(); iter != gameObjectVectors[i].end();)
		{
			if ((*iter)->GetDestory())
			{
				iter = gameObjectVectors[i].erase(iter);
			}
			else
			{
				if (!(*iter)->IsActive())
				{
					++iter;
					continue;
				}
				if ((cameraSize.x + (*iter)->GetScale().x) * 0.5f + 300.f > abs(cameraPosition.x - (*iter)->GetPosition().x))
					(*iter)->FixedUpdate(fixedDeltaTime);

				++iter;
			}
		}
	}

	for (int i = (int)LayerType::UI; i < (int)LayerType::End; ++i)
	{
		for (auto iter = gameObjectVectors[i].begin(); iter != gameObjectVectors[i].end();)
		{

			if ((*iter)->GetDestory())
			{
				iter = gameObjectVectors[i].erase(iter);
			}
			else
			{
				if (!(*iter)->IsActive())
				{
					++iter;
					continue;
				}
				(*iter)->FixedUpdate(fixedDeltaTime);

				++iter;
			}
		}
	}
}

void Scene::Render(sf::RenderWindow& window)
{
	auto& saveView = WindowManager::GetInstance().GetRenderWindow()->getView();

	if (isFreeView)
	{
		WindowManager::GetInstance().GetRenderWindow()->setView(freeCamera->GetView());
		const sf::Vector2f& cameraPosition = freeCamera->GetCameraPosition();
		auto cameraSize = freeCamera->GetView().getSize();

		for (int i = 0; i < (int)LayerType::UI; ++i)
		{
			for (auto& object : gameObjectVectors[i])
			{
				if (!object->IsActive())
					continue;

				object->Render(window);			
			}
		}
	}
	else
	{
		WindowManager::GetInstance().GetRenderWindow()->setView(mainCamera->GetView());
		const sf::Vector2f& cameraPosition = mainCamera->GetCameraPosition();
		auto cameraSize = mainCamera->GetView().getSize();

		for (auto& object : gameObjectVectors[0])
		{
			if (!object->IsActive())
				continue;
			if ((cameraSize.x + object->GetScale().x) * 0.5f > abs(cameraPosition.x - object->GetPosition().x)
				&& (cameraSize.y + object->GetScale().y) * 0.5f > abs(cameraPosition.y - object->GetPosition().y))
				object->Render(window);
		}

		for (auto& object : gameObjectVectors[(int)LayerType::TileMap])
		{
			if (!object->IsActive())
				continue;
			TileMap* tileMap = ((TileMap*)object);
			if ((cameraSize.x + tileMap->GetRealScale().x) * 0.5f > abs(cameraPosition.x - tileMap->GetRealPosition().x)
				&& (cameraSize.y + tileMap->GetRealScale().y) * 0.5f > abs(cameraPosition.y - tileMap->GetRealPosition().y))
				object->Render(window);
		}

		for (int i = (int)LayerType::Wall; i < (int)LayerType::UI; ++i)
		{
			for (auto& object : gameObjectVectors[i])
			{
				if (!object->IsActive())
					continue;
				if ((cameraSize.x + object->GetScale().x) * 0.5f > abs(cameraPosition.x - object->GetPosition().x)
					&& (cameraSize.y + object->GetScale().y) * 0.5f > abs(cameraPosition.y - object->GetPosition().y))
					object->Render(window);
			}
		}
	}

	WindowManager::GetInstance().GetRenderWindow()->setView(uICamera->GetView());

	for (int i = (int)LayerType::UI; i < (int)LayerType::End; ++i)
	{
		std::sort(gameObjectVectors[i].begin(), gameObjectVectors[i].end(), DrawOrderComparer());

		for (auto& object : gameObjectVectors[i])
		{
			if (!object->IsActive())
				continue;
			object->Render(window);
		}
	}

	 WindowManager::GetInstance().GetRenderWindow()->setView(saveView);
}


GameObject* Scene::AddGameObject(GameObject* obj, LayerType rayer)
{
	if (std::find(gameObjectVectors[(int)rayer].begin(), gameObjectVectors[(int)rayer].end(), obj) == gameObjectVectors[(int)rayer].end())
	{
		gameObjectVectors[(int)rayer].push_back(obj);
	}
	return obj;
}

void Scene::RemoveGameObject(GameObject* obj)
{
	for (int i = 0; i < (int)LayerType::End; ++i)
	{
		auto iter = std::find(gameObjectVectors[i].begin(), gameObjectVectors[i].end(), obj);

		if (iter != gameObjectVectors[i].end())
		{
			gameObjectVectors[i].erase(iter);
			return;
		}
	}
}

void Scene::RemoveGameObject(GameObject* obj, LayerType layer)
{
	auto iter = std::find(gameObjectVectors[(int)layer].begin(), gameObjectVectors[(int)layer].end(), obj);

	if(iter != gameObjectVectors[(int)layer].end())
		gameObjectVectors[(int)layer].erase(iter);
}

void Scene::ApplyRemoveGameObject()
{
	for (auto object : removeObjectVector)
	{
		destroyObjects.push_back(object);
	}
	removeObjectVector.clear();
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (int i = 0; i < (int)LayerType::End; ++i)
	{
		for (auto object : gameObjectVectors[i])
		{
			if (object->GetName() == name)
			{
				return object;
			}
		}
	}
	return nullptr;
}

GameObject* Scene::FindGameObject(const std::string& name, LayerType layer)
{
	int index = (int)layer;

	for (auto object : gameObjectVectors[index])
	{
		if (object->GetName() == name)
		{
			return object;
		}
	}

	return nullptr;
}

int Scene::FindGameObjectAll(const std::string& name, std::vector<GameObject*>& vector)
{
	for (int i = 0; i < (int)LayerType::End; ++i)
	{
		for (auto object : gameObjectVectors[i])
		{
			if (object->GetName() == name)
			{
				vector.push_back(object);
			}
		}
	}

	return (int)vector.size();
}


sf::Vector2f Scene::ScreenToWorld(sf::Vector2i screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, mainCamera->GetView());
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, mainCamera->GetView());
}

sf::Vector2f Scene::ScreenToFreeViewWorld(sf::Vector2i screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, freeCamera->GetView());
}

sf::Vector2i Scene::FreeViewWorldToScreen(sf::Vector2f screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, freeCamera->GetView());
}

sf::Vector2f Scene::ScreenToUI(sf::Vector2i screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, uICamera->GetView());
}

sf::Vector2i Scene::UIToScreen(sf::Vector2f screenPos)
{
	return  WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, uICamera->GetView());
}

sf::Vector2f Scene::ScreenToWorld(const sf::View& view, sf::Vector2i screenPos)
{
	return  WindowManager::GetInstance().GetRenderWindow()->mapPixelToCoords(screenPos, view);
}

sf::Vector2i Scene::WorldToScreen(const sf::View& view, sf::Vector2f screenPos)
{
	return WindowManager::GetInstance().GetRenderWindow()->mapCoordsToPixel(screenPos, view);
}

void Scene::SetMoveFreeView(const sf::Vector2f& position)
{
	freeCamera->SetCameraPosition(position);
}