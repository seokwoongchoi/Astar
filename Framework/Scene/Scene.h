#pragma once

class Scene
{
public:
	Scene(class Context* context);
	virtual ~Scene();

	void Update();
	void Render();

private:
	class Context* context;
	class Camera* camera;
	class Tilemap* tilemap;
};