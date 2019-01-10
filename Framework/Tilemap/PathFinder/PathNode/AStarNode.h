#pragma once
#include "stdafx.h"
#include "IPathNode.h"

class AStarNode :public IPathNode
{
public:
	AStarNode()
		:f(0.0f),g(0.0f),h(0.0f),x(0.0f),y(0.0f),bOpen(false),bClosed(false){}
	virtual ~AStarNode(){}

	const float& GetX()const { return x; }
	const float& GetY()const { return y; }
	const float& GetF()const { return f; }
	const float& GetG()const { return g; }
	const float& GetH()const { return h; }

	const bool& IsOpen()const { return bOpen; }
	const bool& IsClose()const { return bClosed; }

	void SetPosition(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}
	void SetF(const float& f){this->f=f;}
	void SetG(const float& g) { this->g = g; }
	void SetH(const float& h){this->h=h;}

	void SetIsOpen(const bool& bOpen) { this->bOpen = bOpen; }
	void SetIsClosed(const bool& bClosed) { this->bClosed = bClosed; }

	virtual const float GetDistance(AStarNode* node) = 0;

	void Release()
	{
		bOpen = bClosed = false;
		f = g = h = x = y = 0.0f;
		parent = nullptr;
	}

protected:
	float f; //비용
	float g; //시작점부터 새로운 지점까지의 이동비용 - 현재상태의 비용
	float h; //최종 목적점 까지의 예상 이동비용- 휴리스틱(heuristic:발견법,추단법)
	//어림잡아서 예상
	float x; //노드의 x위치
	float y; //노드의 y위치
	bool bOpen; //노드가 열린 목록인지
	bool bClosed; //노드가 닫힌 목록인지
	
};

struct CompareLessAStarNode //오름차순
{
	bool operator()(const AStarNode* lhs, const AStarNode* rhs)const
	{
		return lhs->GetF() < rhs->GetF();
	}
};
struct CompareGreaterAStarNode //내림차순
{
	bool operator()(const AStarNode* lhs, const AStarNode* rhs)const
	{
		return lhs->GetF() > rhs->GetF();
	}
};

