#pragma once
#include "stdafx.h"
class IPathNode
{ // Ÿ���ϳ��ϳ��� ��Ŭ������ ��ӹ޴´�. ��θ�ã������ ����ϴ� �⺻��� ��ü��� x
public:
	IPathNode() : parent(nullptr){}
	virtual ~IPathNode(){}

	IPathNode* GetParent()const { return parent; }
	const vector<pair<IPathNode*, float>>& GetChilds()const { return childs; }

	void SetParent(IPathNode* parent) { this->parent = parent; }
	void AddChild(IPathNode* child, const float& distance)
	{
		childs.emplace_back(child, distance);
	}
protected:
	void ClearChilds()
	{
		childs.clear();
		childs.shrink_to_fit();
	}

protected:
	IPathNode* parent;
	vector<pair<IPathNode*, float>> childs;
};

