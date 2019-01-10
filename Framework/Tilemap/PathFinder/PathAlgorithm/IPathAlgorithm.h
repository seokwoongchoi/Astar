#pragma once
#include "stdafx.h"

template<class TPathNode>
class IPathAlgorithm
{
public:
	typedef TPathNode PathNodeType; //TPathNode을 저장해놓는다.
public:
	virtual ~IPathAlgorithm(){}
	virtual const bool GetPath //실질적으로 길을찾는다.
	(
		TPathNode* start,
		TPathNode* goal,//목표점
		vector<TPathNode*>& path //가면서 선택된길들을 받는다.
	) = 0;
	virtual void Clear() = 0;

protected:
	const float GetDistanceBetween(TPathNode* lhs, TPathNode* rhs)
	{
		return lhs->GetDistance(rhs); //lhs부터 rhs까지의 거리
	}
 
	void ReconstructPath(TPathNode* node, vector<TPathNode*>& path)
	{
		TPathNode* parent = static_cast<TPathNode*>(node->GetParent());
		path.push_back(node);

		while (parent != nullptr) //갈길이없을때까지
		{
			path.push_back(parent);
			parent = static_cast<TPathNode*>(parent->GetParent());
		}
	}
};

