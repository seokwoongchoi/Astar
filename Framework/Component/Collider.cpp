#include "stdafx.h"
#include "Collider.h"

Collider::Collider(Context * context, Transform * transform)
	: context(context)
	, transform(transform)
	, EventFunc(nullptr)
	, type(ColliderType::Square)
{
}

Collider::~Collider()
{
}

const BoundBox Collider::GetBoundBox() const
{
	D3DXVECTOR3 minBox = D3DXVECTOR3
	(
		center.x - size.x * 0.5f,
		center.y - size.y * 0.5f,
		center.z - size.z * 0.5f
	);

	D3DXVECTOR3 maxBox = D3DXVECTOR3
	(
		center.x + size.x * 0.5f,
		center.y + size.y * 0.5f,
		center.z + size.z * 0.5f
	);

	return BoundBox(minBox, maxBox);
}

bool Collider::AABB(Collider * collider)
{
	BoundBox boundBox = GetBoundBox();

	return boundBox.IsInside(collider->GetBoundBox());
}

bool Collider::OBB(Collider * collider)
{
	//TODO : 
	return false;
}

void Collider::Update()
{
}
