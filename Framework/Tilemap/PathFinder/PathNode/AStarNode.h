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
	float f; //���
	float g; //���������� ���ο� ���������� �̵���� - ��������� ���
	float h; //���� ������ ������ ���� �̵����- �޸���ƽ(heuristic:�߰߹�,�ߴܹ�)
	//���Ƽ� ����
	float x; //����� x��ġ
	float y; //����� y��ġ
	bool bOpen; //��尡 ���� �������
	bool bClosed; //��尡 ���� �������
	
};

struct CompareLessAStarNode //��������
{
	bool operator()(const AStarNode* lhs, const AStarNode* rhs)const
	{
		return lhs->GetF() < rhs->GetF();
	}
};
struct CompareGreaterAStarNode //��������
{
	bool operator()(const AStarNode* lhs, const AStarNode* rhs)const
	{
		return lhs->GetF() > rhs->GetF();
	}
};

