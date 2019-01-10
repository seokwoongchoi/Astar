#pragma once

enum class ColliderType : uint
{
	Square, Circle
};

class Collider
{
public:
	Collider(class Context* context, class Transform* transform);
	virtual ~Collider();

	class Transform* GetTransform() const { return transform; }
	const ColliderType& GetCollierType() const { return type; }
	const BoundBox GetBoundBox() const;
	const D3DXVECTOR3& GetCenter() const { return center; }
	const D3DXVECTOR3& GetSize() const { return size; }

	void SetColliderType(const ColliderType& type) { this->type = type; }
	void SetCenter(const D3DXVECTOR3& center) { this->center = center; }
	void SetSize(const D3DXVECTOR3& size) { this->size = size; }

	bool AABB(Collider* collider);
	bool OBB(Collider* collider);

	void Update();

public:
	function<void()> EventFunc;

private:
	class Context* context;
	class Transform* transform;
	ColliderType type;
	D3DXVECTOR3 center;
	D3DXVECTOR3 size;
};