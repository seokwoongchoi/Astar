#pragma once
#include "ISubsystem.h"

class SceneManager : public ISubsystem
{
public:
	SceneManager(class Context* context);
	virtual ~SceneManager();

	class Scene* GetCurrentScene();
	void SetCurrentScene(const string& sceneName);

	void RegistScene(const string& sceneName, class Scene* scene);

	void Initialize() override {}
	void Update() override;

	void Render();

private:
	class Scene* currentScene;
	map<string, class Scene*> sceneTable;
};