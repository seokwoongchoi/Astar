#pragma once
#include "./PathFinder/PathNode/AStarNode.h"

class Tile :public AStarNode
{
public:
	Tile();
	virtual ~Tile();

	void Initialize(class Context* context);

	Texture2D* GetTexture() const { return texture; }
	const D3DXVECTOR3 GetPosition() const;
	const D3DXVECTOR3 GetSize() const;
	const D3DXVECTOR2& GetSpriteOffset() const { return spriteOffset; }
	const D3DXVECTOR2& GetSpriteSize() const { return spriteSize; }
	const D3DXCOLOR& GetColor() const { return color; }
	const bool& IsWalkable()const { return bWalkable; }

	void SetTexture(const string& filePath);
	void SetSpriteData(const D3DXVECTOR2& offset, const D3DXVECTOR2& size);
	void SetSpriteData(const float& x, const float& y, const float& size);
	void SetTileLocation(const D3DXVECTOR2& position, const D3DXVECTOR2& size);
	void SetTileLocation(const float& x, const float& y, const float& size);
	void SetColor(const D3DXCOLOR& color) 
	{
		this->color = color; 
		if (color == D3DXCOLOR(1, 0, 0, 1))
			bWalkable = false;
	}
	void SetIsWalkable(const bool& bWalkable) { this->bWalkable = bWalkable; }
	
	const float GetLocalDistance(AStarNode* node)
	{
   		if (node->GetX() != x && node->GetY() != y)
			return 1.41421356237f; //만약에 대각선이면 디스턴스를 루트2로 반환
		else
			return 1.0f;
	}

	const float GetDistance(AStarNode* node)override
	{
		//휴리스틱에 들어간다. 
		//Euclidean Distance: L=sqrt(|x1-x2|^2 +|y1-y2|^2);
		
		float newX = x - node->GetX();
		float newY = y - node->GetY();

		return sqrt((newX*newX) + (newY*newY));

		//Manhattan Distance: L=|x1-x2|+|y1+y2|;

		/*float newX = Math::Abs(x - node->GetX());
		float newY = Math::Abs(y - node->GetY());

		return newX + newY;*/
	}

private:
	class Context* context;
	class ResourceManager* resourceMgr;

	Texture2D* texture;
	D3DXVECTOR2 spriteOffset;
	D3DXVECTOR2 spriteSize;
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	D3DXCOLOR color;
	bool bWalkable;
};