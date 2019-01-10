#include "stdafx.h"
#include "Tilemap.h"
#include "Tile.h"
#include "../Component/Grid.h"
#include "../Camera/Camera.h"
#include "./PathFinder/PathAlgorithm/AStar.h"
#include "./PathFinder/PathFinder.h"

Tilemap::Tilemap(Context * context)
   : context(context)
   , tiles(nullptr)
   , texture(nullptr)
   , col(0)
   , row(0)
   , spacing(0)
	,bLoop(false)
{
   input = context->GetSubsystem<Input>();
   auto resourceMgr = context->GetSubsystem<ResourceManager>();

   mesh = resourceMgr->LoadFromFile<Mesh>("Quad");
   shader = resourceMgr->LoadFromFile<Shader>("Tileinstance.hlsl");

   spriteBuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
   spriteBuffer->Create<SpriteData>();

   colorBuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
   colorBuffer->Create<ColorData>();

   transform = new Transform(context);
   grid = new Grid(context);
  
   
}

Tilemap::~Tilemap()
{
   Clear();

   SAFE_DELETE(grid);
   SAFE_DELETE(transform);
   SAFE_DELETE(colorBuffer);
   SAFE_DELETE(spriteBuffer);
}

void Tilemap::Create(const uint & w, const uint & h, const uint & size)
{
   Clear();

   uint width   = (w % size) == 0 ? w : w - (w % size);
   uint height = (h % size) == 0 ? h : h - (h % size);

   row = width / size;
   col = height / size;
   spacing = size;

   tiles = new Tile*[col];
   for (uint y = 0; y < col; y++)
   {
      tiles[y] = new Tile[row];
      for (uint x = 0; x < row; x++)
      {
         tiles[y][x].Initialize(context);
         tiles[y][x].SetTileLocation(x * spacing, y * spacing, spacing);
         tiles[y][x].SetTexture("tree.png");
         tiles[y][x].SetSpriteData
         (
            D3DXVECTOR2(0, 0),
            tiles[y][x].GetTexture()->GetSize()
         );
		 tiles[y][x].SetColor({ 1,0,0,1 });

		 transform->SetWorldPosition(tiles[y][x].GetPosition());
		 transform->SetWorldScale(tiles[y][x].GetSize());

		 InstanceData data;
		 data.World = transform->GetWorldMatrix();
		 data.SpriteOffset = tiles[y][x].GetSpriteOffset();
		 data.SpriteSize = tiles[y][x].GetSpriteSize();
		 data.TextureSize = tiles[y][x].GetTexture()->GetSize();
		 data.Color = tiles[y][x].GetColor();
		 instanceDatas.emplace_back(data);
      }
   }

   grid->Create(width, height, spacing);
   
   D3D11_BUFFER_DESC desc;
   desc.Usage = D3D11_USAGE_IMMUTABLE;
   desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //인스턴스데이터는 버텍스버퍼에 같이 집어넣는다.
   desc.ByteWidth = sizeof(InstanceData)*instanceDatas.size();
   desc.CPUAccessFlags = 0;
   desc.MiscFlags = 0;
   desc.StructureByteStride = 0;

   D3D11_SUBRESOURCE_DATA subData;
   subData.pSysMem = instanceDatas.data();

   auto device = context->GetSubsystem<Graphics>()->GetDevice();
   HRESULT hr = device->CreateBuffer
   (
	   &desc,
	   &subData,
	   &instanceBuffer
   );
   assert(SUCCEEDED(hr));

}

void Tilemap::Clear()
{
   for (uint y = 0; y < col; y++)
      SAFE_DELETE_ARRAY(tiles[y]);
   SAFE_DELETE_ARRAY(tiles);
}

void Tilemap::Update(Camera* camera)
{
	
   if (input->BtnPress(0))
   {
	   
      D3DXVECTOR3 mousePos = input->GetMousePosition();
      D3DXVECTOR3 mouseWorld = camera->ScreenToWorldPoint(D3DXVECTOR2(mousePos.x, mousePos.y));
      
      bool bCheck = true;
      bCheck &= mouseWorld.x > 0;
      bCheck &= mouseWorld.y > 0;
      bCheck &= mouseWorld.x < row*spacing;
      bCheck &= mouseWorld.y < col*spacing;

      if (bCheck)
      {
         uint x = static_cast<uint>(mouseWorld.x / spacing);
         uint y = static_cast<uint>(mouseWorld.y / spacing);

        tiles[y][x].SetColor(D3DXCOLOR(1, 0, 0, 1));
		
		
		/* checkgoal.goalcol = y;
		 checkgoal.goalrow = x;
		 goaltiles.push_back(checkgoal);
		 bLoop = true;*/
		 
      }
   }
   grid->Update();
}

void Tilemap::Render()
{
   auto dc = context->GetSubsystem<Graphics>()->GetDeviceContext();

   auto vertexBuffer = mesh->GetVertexBuffer()->GetBuffer();

   ID3D11Buffer* buffers[2]{ vertexBuffer,instanceBuffer };
   
   uint stride[2]{ sizeof(vertexBuffer),sizeof(InstanceData) }; //정점데이터를 끊어 읽는
   uint offset[2]{ 0,0 };
   dc->IASetVertexBuffers(0, 2, buffers,stride,offset);
   
   shader->BindPipeline();
   texture = tiles[0][0].GetTexture();
   texture->SetPS(0);

   dc->DrawIndexedInstanced(mesh->GetIndexCount(),instanceDatas.size()	,0,0,0	); 

   
   //for(uint y = 0; y < col; y++)
   //   for (uint x = 0; x < row; x++)
   //   {
   //      texture = tiles[y][x].GetTexture();

   //      //Transform buffer
   //      transform->SetWorldPosition(tiles[y][x].GetPosition());
   //      transform->SetWorldScale(tiles[y][x].GetSize());
   //      transform->BindPipeline();

   //      //Sprite buffer
   //      auto sData = static_cast<SpriteData*>(spriteBuffer->Map());
   //      sData->SpriteOffset = tiles[y][x].GetSpriteOffset();
   //      sData->SpriteSize = tiles[y][x].GetSpriteSize();
   //      sData->TextureSize = texture ? texture->GetSize() : D3DXVECTOR2(1, 1);
   //      spriteBuffer->Unmap();
   //      spriteBuffer->SetVS(2);

   //      //Color buffer
   //      auto cData = static_cast<ColorData*>(colorBuffer->Map());
   //      cData->color = tiles[y][x].GetColor();
   //      colorBuffer->Unmap();
   //      colorBuffer->SetPS(0);

   //      //Texture
   //      if (texture)
   //         texture->SetPS(0);
   //      else
   //      {
   //         ID3D11ShaderResourceView* null[1]{ nullptr };
   //         dc->PSSetShaderResources(0, 1, null);
   //      }

      /*   dc->DrawIndexed(mesh->GetIndexCount(), 0, 0);
      }*/

   grid->Render();
}

void Tilemap::FindPath(Camera* camera,const D3DXVECTOR2 & start, const D3DXVECTOR2 & goal)
{
	PathFinder<Tile> pathFinder;
   vector<Tile*> path;

   int newX = 0, newY = 0;
   Tile* child = nullptr;

   for (uint y = 0; y < col; y++)
   {
      for (uint x = 0; x < row; x++)
      {
         for (int i = -1; i < 2; i++)
         {
            newY = y + i;
            for (int j = -1; j < 2; j++)
            {
               newX = x + j;
               
               bool bCheck = true;
               bCheck &= newY > -1;
               bCheck &= newY < col;
               bCheck &= newX > -1;
               bCheck &= newX < row;

               if (bCheck)
               {
                  child = &tiles[newY][newX];

                  bCheck = true;
                  bCheck &= child->IsWalkable();
                  bCheck &= newX != x || newY != y;

                  if (bCheck)
                     tiles[y][x].AddChild(child, tiles[y][x].GetLocalDistance(child));
               }
            }
         }
      }//for x(row)
   }//for y(col)


   pathFinder.SetStart(&tiles[0][0]);
  /* if(bLoop)
   for (auto goal : goaltiles)
   {
	   uint rcol = goal.goalcol;
	   uint rrow = goal.goalrow;
	  
    pathFinder.SetGoal(&tiles[rcol][rrow]);
	break;
   }
   else*/
	   pathFinder.SetGoal(&tiles[col-1][row-1]);
  //pathFinder.GetGoal();
   bool bResult = pathFinder.FindPath<AStar>(path);

   for (auto& tile : path)
      tile->SetColor({ 0,1,0,1 });
}