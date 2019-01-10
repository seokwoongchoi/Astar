#pragma once
#include "stdafx.h"
class IPathNode
{ // 타일하나하나가 이클래스를 상속받는다. 경로를찾기위해 사용하는 기본노드 객체사용 x
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

