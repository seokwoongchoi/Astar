#include "stdafx.h"
#include "AStar.h"

const bool AStar::GetPath(AStarNode * start, AStarNode * goal, vector<AStarNode*>& path)
{
	AStarNode* currentNode = nullptr, *childNode = nullptr;
	float f = 0, g = 0, h = 0;
	
	open.push_back(start);
	start->SetIsOpen(true);
	
	while (!open.empty()) //��������� ����������
	{
		sort(open.begin(), open.end(), CompareGreaterAStarNode());
		
		currentNode = open.back(); //������������ �����ؼ� �ǳ��� ���� �������̴�.
		//���� ����� �������
		open.pop_back();//���¸�Ͽ��� ���°� �����.
		currentNode->SetIsOpen(false);
		currentNode->SetIsClosed(true); //���°Ÿ� ���¿��� Ŭ����� �ٲ۴�.
		closed.push_back(currentNode);

		if (currentNode == goal) //�����ߴٸ�
		{
			ReconstructPath(currentNode, path); //��θ� �籸���ϰ� ����Ʈ��
			return true;
		}
		
		for (const auto& child : currentNode->GetChilds())//��θ� ��ã�Ҵٸ�
		{
			//�ڽ��� �����ִ� ��ε��� ��� �ڽ����� �����ϰ� �� �ڽĵ��� �ϳ������Ѱ� �θ𰡵ȴ�.
			//�θ� �̿��ؼ� ��θ� �˼��ִ�.
			childNode = static_cast<AStarNode*>(child.first);
			g = currentNode->GetG() + child.second;

			bool bCheck = true;
			bCheck &= childNode->IsOpen() || childNode->IsClose(); //��ΰ� �̴̹� �Ǻ��Ȱ���
			bCheck &= childNode->GetG() < g; //�̴�����ΰ� �����κ��� ����̴�ũ��

			if (bCheck)
				continue;
			//�̰� ����� ��δ�  �ִܰŸ� ����̴�.
			h = GetDistanceBetween(childNode, goal); //������� ������� �Ÿ�
			f = g + h; //������� ���� �º��� ���� ������ ������� ���Ѱ��� �Ѻ��

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
