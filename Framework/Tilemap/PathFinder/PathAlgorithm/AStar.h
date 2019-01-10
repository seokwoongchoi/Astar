#pragma once
#include "IPathAlgorithm.h"
#include "../PathNode/AStarNode.h"

class AStar :public IPathAlgorithm<AStarNode>
{
public:
	static AStar& Get()
	{
		static AStar instance;
		return instance;
	}
	const bool GetPath
	(
		AStarNode* start,
		AStarNode* goal,
		vector<AStarNode*>& path
	)override;
	void Clear() override;

private:

	AStar(){}
	virtual ~AStar(){}

	void ReleaseNodes();
private:
	vector<AStarNode*> open;
	vector<AStarNode*> closed;
};

