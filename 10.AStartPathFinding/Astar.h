#pragma once

#include <vector>

//������ ���� �Լ�
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

//A* ��ã�� ��� ó�� Ŭ����
class Node;
class Astar
{
	//�̵� ���� ����ü(��� ����� ����)
	struct Direction
	{//�ȿ����� ���� �ǵ��� class �ȿ� ����ü ����
		//����
		int x = 0;
		int y = 0;

		//���
		float cost = 0.0f;
	};

public:
	Astar();
	~Astar();

	//��� �˻��Լ�
	std::vector<Node*> FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid);

	//�׸��� ��� �Լ�(�� �����ִ� �Լ�)
	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid, //path�� ���� grid�� ���� �ٸ��� �ؾ���
		const std::vector<Node*>& path
	);


private:
	//Ž���� �Ϸ��� �Ŀ� ���� ��θ� ��ȯ�ϴ� �Լ�
	//��ǥ���� ���� �θ� ��带 �������ؼ� ����
	std::vector<Node*> ConstructPath(Node* goalNode);

	// ����� ����� ��� �Լ�
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	//Ž���Ϸ��� ���� �̵� ������ ������
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	//�̹� �湮�� ��ġ���� Ȯ���ϴ� �Լ�
	bool HasVisited(int x, int y, float gCost);

	bool IsDestination(const Node* node);
private:
	std::vector<Node*>openList; // Ž�� �ؾ��� ���
	std::vector<Node*>closedList;

	Node* startNode = nullptr;
	Node* goalNode = nullptr;

};