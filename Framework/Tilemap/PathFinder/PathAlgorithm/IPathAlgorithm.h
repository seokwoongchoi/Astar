#pragma once
#include "stdafx.h"

template<class TPathNode>
class IPathAlgorithm
{
public:
	typedef TPathNode PathNodeType; //TPathNode�� �����س��´�.
public:
	virtual ~IPathAlgorithm(){}
	virtual const bool GetPath //���������� ����ã�´�.
	(
		TPathNode* start,
		TPathNode* goal,//��ǥ��
		vector<TPathNode*>& path //���鼭 ���õȱ���� �޴´�.
	) = 0;
	virtual void Clear() = 0;

protected:
	const float GetDistanceBetween(TPathNode* lhs, TPathNode* rhs)
	{
		return lhs->GetDistance(rhs); //lhs���� rhs������ �Ÿ�
	}
 
	void ReconstructPath(TPathNode* node, vector<TPathNode*>& path)
	{
		TPathNode* parent = static_cast<TPathNode*>(node->GetParent());
		path.push_back(node);

		while (parent != nullptr) //�����̾���������
		{
			path.push_back(parent);
			parent = static_cast<TPathNode*>(parent->GetParent());
		}
	}
};

