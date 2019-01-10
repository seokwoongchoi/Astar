#include "stdafx.h"
#include "Transform.h"

Transform::Transform(Context * context)
	: context(context)
	, localScale(1, 1, 1)
	, localRotate(0, 0, 0)
	, localPosition(0, 0, 0)
	, parent(nullptr)
{
	transformBuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
	transformBuffer->Create<TransformData>();

	D3DXMatrixIdentity(&local);
	D3DXMatrixIdentity(&world);
}

Transform::~Transform()
{
	SAFE_DELETE(transformBuffer);
}

const D3DXVECTOR3 Transform::GetWorldScale() const
{
	D3DXVECTOR3 scale(1, 1, 1);
	D3DXMatrixDecompose(&scale, &D3DXQUATERNION(), &D3DXVECTOR3(), &world);
	return scale;
}

const D3DXVECTOR3 Transform::GetWorldRotate() const
{
	D3DXMATRIX rotation = GetWorldRotationMatrix();

	return D3DXVECTOR3
	(
		atan2(rotation._43, rotation._44),
		atan2(-rotation._42, sqrt(pow(rotation._43, 2) + pow(rotation._44, 2))),
		atan2(rotation._32, rotation._22)
	);
}

const D3DXVECTOR3 Transform::GetWorldPosition() const
{
	return D3DXVECTOR3(world._41, world._42, world._43);
}

const D3DXMATRIX Transform::GetWorldRotationMatrix() const
{
	D3DXVECTOR3 scale = GetWorldScale();

	bool bCheck = true;
	bCheck &= scale.x == 0.0f;
	bCheck &= scale.y == 0.0f;
	bCheck &= scale.z == 0.0f;

	if (bCheck)
		return D3DXMATRIX();

	float factorX = 1.0f / scale.x;
	float factorY = 1.0f / scale.y;
	float factorZ = 1.0f / scale.z;

	return D3DXMATRIX
	(
		world._11 * factorX, world._12 * factorX, world._13 * factorX, world._14 * factorX,
		world._21 * factorY, world._22 * factorY, world._23 * factorY, world._24 * factorY,
		world._31 * factorZ, world._32 * factorZ, world._33 * factorZ, world._34 * factorZ,
		0, 0, 0, 1
	);
}

const D3DXVECTOR3 Transform::GetRight()
{
	D3DXVECTOR3 right(0, 0, 0);
	D3DXVec3TransformNormal
	(
		&right, 
		&D3DXVECTOR3(1, 0, 0), 
		&GetWorldRotationMatrix()
	);
	return right;
}

const D3DXVECTOR3 Transform::GetUp()
{
	D3DXVECTOR3 up(0, 0, 0);
	D3DXVec3TransformNormal
	(
		&up, 
		&D3DXVECTOR3(0, 1, 0), 
		&GetWorldRotationMatrix()
	);
	return up;
}

const D3DXVECTOR3 Transform::GetForward()
{
	D3DXVECTOR3 forward(0, 0, 0);
	D3DXVec3TransformNormal
	(
		&forward, 
		&D3DXVECTOR3(0, 0, 1), 
		&GetWorldRotationMatrix()
	);
	return forward;
}

Transform * Transform::GetChildFromIndex(const uint & index)
{
	if (!HasChild())
		return nullptr;

	if (index >= childs.size())
		return nullptr;

	return childs[index];
}

void Transform::SetLocalScale(const D3DXVECTOR3 & vec)
{
	if (localScale == vec)
		return;

	localScale = vec;
	UpdateTransform();
}

void Transform::SetLocalRotate(const D3DXVECTOR3 & vec)
{
	if (localRotate == vec)
		return;

	localRotate = vec;
	UpdateTransform();
}

void Transform::SetLocalPosition(const D3DXVECTOR3 & vec)
{
	if (localPosition == vec)
		return;

	localPosition = vec;
	UpdateTransform();
}

void Transform::SetWorldScale(const D3DXVECTOR3 & vec)
{
	if (GetWorldScale() == vec)
		return;

	if (HasParent())
	{
		D3DXVECTOR3 parentScale = parent->GetWorldScale();
		D3DXVECTOR3 scale;
		scale.x = vec.x / parentScale.x;
		scale.y = vec.y / parentScale.y;
		scale.z = vec.z / parentScale.z;

		SetLocalScale(scale);
	}
	else
		SetLocalScale(vec);
}

void Transform::SetWorldRotate(const D3DXVECTOR3 & vec)
{
	if (GetWorldRotate() == vec)
		return;

	if (HasParent())
	{
		D3DXMATRIX inv;
		D3DXMatrixInverse(&inv, nullptr, &parent->GetWorldRotationMatrix());

		D3DXVECTOR3 rotate;
		D3DXVec3TransformNormal(&rotate, &vec, &inv);

		SetLocalRotate(rotate);
	}
	else
		SetLocalRotate(vec);
}

void Transform::SetWorldPosition(const D3DXVECTOR3 & vec)
{
	if (GetWorldPosition() == vec)
		return;

	if (HasParent())
	{
		D3DXMATRIX inv;
		D3DXMatrixInverse(&inv, nullptr, &parent->GetWorldMatrix());

		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &vec, &inv);

		SetLocalPosition(position);
	}
	else
		SetLocalPosition(vec);
}

void Transform::SetParent(Transform * newParent)
{
	if (!newParent)
		return;

	if (newParent == this)
		return;

	parent = newParent;
}

void Transform::AddChild(Transform * child)
{
	if (!child)
		return;

	if (child == this)
		return;

	child->SetParent(this);
	childs.push_back(child);
}

void Transform::UpdateTransform()
{
	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, localScale.x, localScale.y, localScale.z);
	D3DXMatrixRotationYawPitchRoll(&R, localRotate.y, localRotate.x, localRotate.z);
	D3DXMatrixTranslation(&T, localPosition.x, localPosition.y, localPosition.z);

	local = S * R * T;

	if (HasParent())
		world = local * parent->GetWorldMatrix();
	else
		world = local;

	for (const auto& child : childs)
		child->UpdateTransform();
}

void Transform::BindPipeline()
{
	auto data = static_cast<TransformData*>(transformBuffer->Map());
	D3DXMatrixTranspose(&data->World, &GetWorldMatrix());
	transformBuffer->Unmap();
	transformBuffer->SetVS(1);
}
