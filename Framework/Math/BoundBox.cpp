#include "stdafx.h"
#include "BoundBox.h"

BoundBox::BoundBox()
{
	minBox = D3DXVECTOR3
	(
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity()
	);

	maxBox = D3DXVECTOR3
	(
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity()
	);
}

BoundBox::BoundBox(const D3DXVECTOR3 & min, const D3DXVECTOR3 & max)
	: minBox(min)
	, maxBox(max)
{
}

BoundBox::BoundBox(const vector<VertexTexture>& vertices)
{
	minBox = D3DXVECTOR3
	(
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity(),
		numeric_limits<float>::infinity()
	);

	maxBox = D3DXVECTOR3
	(
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity(),
		-numeric_limits<float>::infinity()
	);

	for (auto vertex : vertices)
	{
		minBox.x = Math::Min(minBox.x, vertex.Position.x);
		minBox.y = Math::Min(minBox.y, vertex.Position.y);
		minBox.z = Math::Min(minBox.z, vertex.Position.z);

		maxBox.x = Math::Max(maxBox.x, vertex.Position.x);
		maxBox.y = Math::Max(maxBox.y, vertex.Position.y);
		maxBox.z = Math::Max(maxBox.z, vertex.Position.z);
	}
}

BoundBox::~BoundBox()
{
}

Intersection BoundBox::IsInside(const D3DXVECTOR3 & point)
{
	bool bCheck = true;
	bCheck &= point.x > minBox.x;
	bCheck &= point.y > minBox.y;
	bCheck &= point.x < maxBox.x;
	bCheck &= point.y < maxBox.y;

	if (bCheck)
		return Intersection::Inside;
	else
		return Intersection::Outside;
}

Intersection BoundBox::IsInside(const BoundBox & box)
{
	if (
		box.maxBox.x < minBox.x || box.minBox.x > maxBox.x ||
		box.maxBox.y < minBox.y || box.minBox.y > maxBox.y ||
		box.maxBox.z < minBox.z || box.minBox.z > maxBox.z)
		return Intersection::Outside;
	else if (
		box.minBox.x < minBox.x || box.maxBox.x > maxBox.x ||
		box.minBox.y < minBox.y || box.maxBox.y > maxBox.y ||
		box.minBox.z < minBox.z || box.maxBox.z > maxBox.z)
		return Intersection::Intersect;
	else
		return Intersection::Inside;
}

BoundBox BoundBox::Transformed(const D3DXMATRIX & transform)
{
	D3DXVECTOR3 newCenter(0, 0, 0);
	D3DXVec3TransformCoord(&newCenter, &GetCenter(), &transform);

	D3DXVECTOR3 oldEdge = GetSize() * 0.5f;
	D3DXVECTOR3 newEdge = D3DXVECTOR3
	(
		Math::Abs(transform._11) * oldEdge.x + Math::Abs(transform._21) * oldEdge.y + Math::Abs(transform._31) * oldEdge.z,
		Math::Abs(transform._12) * oldEdge.x + Math::Abs(transform._22) * oldEdge.y + Math::Abs(transform._32) * oldEdge.z,
		Math::Abs(transform._13) * oldEdge.x + Math::Abs(transform._23) * oldEdge.y + Math::Abs(transform._33) * oldEdge.z
	);

	return BoundBox(newCenter - newEdge, newCenter + newEdge);
}
