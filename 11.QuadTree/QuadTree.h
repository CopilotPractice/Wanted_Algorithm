#pragma once
#include "Node.h";

class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	void Insert(Node* node);

	//������ ���� ��ġ�� ��带 ��ȯ�ϴ� �Լ�.
	std::vector<Node*> Query(Node* queryNode);
public:
	//���� �� �ִ� Ʈ���� �ִ� ���� ��.
	static const int maxDepth = 4; // ��ü ���� �ʱ�ȭ �����̶� �ٸ��⶧���� ??
private:
	Node* root = nullptr;
};