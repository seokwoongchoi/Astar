#pragma once
//struct Checkgoal
//{
//	uint goalcol=19;
//	uint goalrow=39;
//};

struct InstanceData //기본데이터 취급 ia에 들어간다 버텍스퍼랑묶여서 들어간다.
{
	D3DXMATRIX World;
	D3DXVECTOR2 TextureSize; 
	D3DXVECTOR2 SpriteOffset;
	D3DXVECTOR2 SpriteSize;
	float Padding[2]; //패딩안해주면 칼라값이 짤려서 들어가서 이상한데이터가 나올수있다.
	D3DXCOLOR Color;
};
class Tilemap
{
public:
	Tilemap(class Context* context);
	virtual ~Tilemap();

	void Create(const uint& w, const uint& h, const uint& size = 32);
	void Clear();

	void Update(class Camera* camera);
	void Render();

	void FindPath(Camera* camera,
		const D3DXVECTOR2& start= D3DXVECTOR2(0, 0),
		const D3DXVECTOR2& goal = D3DXVECTOR2(0, 0)
		
	);

private:
	class Context* context;
	class Input* input;
	class Tile** tiles;
	class Grid* grid;
	class Shader* shader;
	class Mesh* mesh;
	class Texture2D* texture;
	class Transform* transform;
	class ConstantBuffer* spriteBuffer;
	class ConstantBuffer* colorBuffer;
	
	/*vector<Checkgoal> goaltiles;
	Checkgoal checkgoal;*/

	uint col;
	uint row;
	uint spacing;
	bool bRenderGrid;
	bool bLoop;
	//tiles[열][행]
	//열 - 세로 - column
	//행 - 가로 - row

	//instance
	ID3D11Buffer* instanceBuffer;
	vector<InstanceData> instanceDatas; //버텍스버퍼만드는거랑 똑같다.
};