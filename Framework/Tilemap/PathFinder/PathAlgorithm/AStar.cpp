#include "stdafx.h"
#include "AStar.h"

const bool AStar::GetPath(AStarNode * start, AStarNode * goal, vector<AStarNode*>& path)
{
	AStarNode* currentNode = nullptr, *childNode = nullptr;
	float f = 0, g = 0, h = 0;
	
	open.push_back(start);
	start->SetIsOpen(true);
	
	while (!open.empty()) //열린목록이 없을때까지
	{
		sort(open.begin(), open.end(), CompareGreaterAStarNode());
		
		currentNode = open.back(); //내림차순으로 정리해서 맨끝이 제일 작은값이다.
		//가장 비용이 적은노드
		open.pop_back();//오픈목록에서 뺴온거 지운다.
		currentNode->SetIsOpen(false);
		currentNode->SetIsClosed(true); //빼온거를 오픈에서 클로즈로 바꾼다.
		closed.push_back(currentNode);

		if (currentNode == goal) //도착했다면
		{
			ReconstructPath(currentNode, path); //경로를 재구성하고 리턴트루
			return true;
		}
		
		for (const auto& child : currentNode->GetChilds())//경로를 못찾았다면
		{
			//자신이 갈수있는 경로들을 모두 자식으로 설정하고 그 자식들중 하나선택한게 부모가된다.
			//부모를 이용해서 경로를 알수있다.
			childNode = static_cast<AStarNode*>(child.first);
			g = currentNode->GetG() + child.second;

			bool bCheck = true;
			bCheck &= childNode->IsOpen() || childNode->IsClose(); //경로가 이미다 판별된경우와
			bCheck &= childNode->GetG() < g; //이다음경로가 현재경로보다 비용이더크면

			if (bCheck)
				continue;
			//이걸 통과한 경로는  최단거리 경로이다.
			h = GetDistanceBetween(childNode, goal); //현재노드와 골사이의 거리
			f = g + h; //현재까지 내가 온비용과 내가 앞으로 갈비용을 더한것이 총비용

			childNode->SetF(f);
			childNode->SetG(g);
			childNode->SetH(h);
			childNode->SetParent(currentNode);

			if (childNode->IsClose())
				childNode->SetIsClosed(false);
			if (!childNode->IsOpen())
			{
				open.push_back(childNode);
				childNode->SetIsOpen(true);
			}
		}
	}
	return false;
}

void AStar::Clear()
{
	ReleaseNodes();

	open.clear();
	open.shrink_to_fit();

	closed.clear();
	closed.shrink_to_fit();
}

void AStar::ReleaseNodes()
{
	for (const auto& node : open)
		node->Release();

	for (const auto& node : closed)
		node->Release();
}
