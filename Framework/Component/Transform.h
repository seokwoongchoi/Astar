#pragma once

class Transform
{
public:
	Transform(class Context* context);
	virtual ~Transform();

	const D3DXVECTOR3& GetLocalScale() const { return localScale; }
	const D3DXVECTOR3& GetLocalRotate() const { return localRotate; }
	const D3DXVECTOR3& GetLocalPosition() const { return localPosition; }

	const D3DXVECTOR3 GetWorldScale() const;
	const D3DXVECTOR3 GetWorldRotate() const;
	const D3DXVECTOR3 GetWorldPosition() const;

	const D3DXMATRIX& GetLocalMatrix() const { return local; }
	const D3DXMATRIX& GetWorldMatrix() const { return world; }
	const D3DXMATRIX GetWorldRotationMatrix() const;

	const D3DXVECTOR3 GetRight();
	const D3DXVECTOR3 GetUp();
	const D3DXVECTOR3 GetForward();

	Transform* GetRoot() { return HasParent() ? GetParent()->GetRoot() : this; }
	Transform* GetParent() { return parent; }
	Transform* GetChildFromIndex(const uint& index);
	const vector<Transform*>& GetChilds() const { return childs; }
	const uint GetChildsCount() const { return childs.size(); }

	void SetLocalScale(const D3DXVECTOR3& vec);
	void SetLocalRotate(const D3DXVECTOR3& vec);
	void SetLocalPosition(const D3DXVECTOR3& vec);

	void SetWorldScale(const D3DXVECTOR3& vec);
	void SetWorldRotate(const D3DXVECTOR3& vec);
	void SetWorldPosition(const D3DXVECTOR3& vec);

	void SetParent(Transform* newParent);

	void AddChild(Transform* child);

	bool HasParent() { return parent ? true : false; }
	bool HasChild() { return !childs.empty(); }

	void UpdateTransform();

	void BindPipeline();

private:
	class Context* context;
	class ConstantBuffer* transformBuffer;

	D3DXVECTOR3 localScale;
	D3DXVECTOR3 localRotate;
	D3DXVECTOR3 localPosition;

	D3DXMATRIX local;
	D3DXMATRIX world;

	Transform* parent;
	vector<Transform*> childs;
};