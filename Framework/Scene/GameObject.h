#pragma once

class GameObject
{
public:
	GameObject(Context* context, class Camera* camera);
	virtual ~GameObject();

	class Transform* GetTransform() const { return transform; }
	class Collider* GetCollider() const { return collider; }

	void Update();
	void Render();

	bool IsContain(const D3DXVECTOR3& mousePose);

private:
	class Context* context;
	class Timer* timer;
	class Input* input;
	class Camera* camera;

	class Shader* shader;
	class Mesh* mesh;
	class Texture2D* texture;
	class SpriteAnimator* animator;
	class Transform* transform;
	class Collider* collider;
};