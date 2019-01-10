#pragma once
//struct Checkgoal
//{
//	uint goalcol=19;
//	uint goalrow=39;
//};

struct InstanceData //�⺻������ ��� ia�� ���� ���ؽ��۶������� ����.
{
	D3DXMATRIX World;
	D3DXVECTOR2 TextureSize; 
	D3DXVECTOR2 SpriteOffset;
	D3DXVECTOR2 SpriteSize;
	float Padding[2]; //�е������ָ� Į���� ©���� ���� �̻��ѵ����Ͱ� ���ü��ִ�.
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
	//tiles[��][��]
	//�� - ���� - column
	//�� - ���� - row

	//instance
	ID3D11Buffer* instanceBuffer;
	vector<InstanceData> instanceDatas; //���ؽ����۸���°Ŷ� �Ȱ���.
};