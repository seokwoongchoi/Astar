#pragma once

class BoundBox
{
public:
	BoundBox();
	BoundBox(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
	BoundBox(const vector<VertexTexture>& vertices);
	virtual ~BoundBox();

	const D3DXVECTOR3& GetMin() const { return minBox; }
	const D3DXVECTOR3& GetMax() const { return maxBox; }
	const D3DXVECTOR3 GetCenter() const { return (maxBox + minBox) * 0.5; }
	const D3DXVECTOR3 GetSize() const { return maxBox - minBox; }
	const D3DXVECTOR3 GetExtents() const { return (maxBox - minBox) * 0.5f; }

	Intersection IsInside(const D3DXVECTOR3& point);
	Intersection IsInside(const BoundBox& box);

	BoundBox Transformed(const D3DXMATRIX& transform);

	BoundBox& operator=(const BoundBox& rhs)
	{
		minBox = rhs.minBox;
		maxBox = rhs.maxBox;
		return *this;
	}

	bool operator==(const BoundBox& other)
	{
		bool bCheck = true;
		bCheck &= minBox == other.minBox;
		bCheck &= maxBox == other.maxBox;
		return bCheck;
	}

private:
	D3DXVECTOR3 minBox;
	D3DXVECTOR3 maxBox;
};