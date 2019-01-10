#pragma once
#include "App.h"

class Game : public App
{
public:
	Game() {}
	virtual ~Game() {}

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Destroy() override;

private:
	class SceneManager* sceneManager;
	class EffectManager* effectManager;
	class ResourceManager* resourceManager;

	//TODO : ���߿� Ŭ����ȭ �Ұ�
	class Camera* camera;
	class Shader* shader;
	class Mesh* mesh;
	class RenderTexture* renderTexture;
};