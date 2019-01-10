#pragma once
#include "stdafx.h"
#include "./PathAlgorithm/IPathAlgorithm.h"


template<class TPathNode>
class PathFinder
{
public:
	PathFinder()
		:start(nullptr)
		,goal(nullptr)
	{}
	virtual ~PathFinder(){}

	TPathNode* GetStart()const { return start; }	
	TPathNode* GetGoal()const { return goal; }

	void SetStart( TPathNode* start) { this->start = start; }
	void SetGoal( TPathNode* goal) { this->goal = goal; }

	template<typename TAlgorithm>
	const bool FindPath(vector<TPathNode*>& solution)
	{
		vector<typename TAlgorithm::PathNodeType*> path;
		TAlgorithm& algorithm = TAlgorithm::Get();

		bool bPathFound = algorithm.GetPath(start, goal, path); //알고리즘의 길찾기

		if (!bPathFound)
		{
			return false;
		}
		
		for (auto riter = rbegin(path); riter != rend(path); riter++)
		{
			solution.push_back(static_cast<TPathNode*>(*riter));
		}
		return true;
	}

private:
	TPathNode* start;
	TPathNode* goal;
};