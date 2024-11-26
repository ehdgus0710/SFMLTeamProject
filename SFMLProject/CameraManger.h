#pragma once

class Camera;

class CameraManger : public Singleton<CameraManger>
{
	friend Singleton<CameraManger>;

protected:
	std::vector<Camera*> cameraVector;

public:
	void Init();
	void Release();

	Camera* GetMainCamera() { return cameraVector[0]; }

	void SetCamera(Camera* camera) { cameraVector.push_back(camera); }

	void Clear() { cameraVector.clear(); }

protected:
	CameraManger() = default;
	virtual ~CameraManger() = default;
	CameraManger(const CameraManger&) = delete;
	CameraManger& operator=(const CameraManger&) = delete;
};
