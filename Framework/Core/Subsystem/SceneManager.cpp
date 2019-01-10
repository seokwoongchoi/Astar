#include "stdafx.h"
#include "SceneManager.h"
#include "../../Scene/Scene.h"

SceneManager::SceneManager(Context * context)
	: ISubsystem(context)
	, currentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	//map<string, Scene*>::iterator iter = sceneTable.begin();
	//for (; iter != sceneTable.end(); iter++)
	//	SAFE_DELETE(iter->second);

	for (auto scene : sceneTable)
		SAFE_DELETE(scene.second);
}

Scene * SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::SetCurrentScene(const string & sceneName)
{
	assert(sceneTable.count(sceneName) > 0);
	currentScene = nullptr;
	currentScene = sceneTable[sceneName];
}

void SceneManager::RegistScene(const string & sceneName, Scene * scene)
{
	assert(sceneTable.count(sceneName) < 1);
	sceneTable[sceneName] = scene;
}

void SceneManager::Update()
{
	if (currentScene)
		currentScene->Update();
}

void SceneManager::Render()
{
	if (currentScene)
		currentScene->Render();
}
