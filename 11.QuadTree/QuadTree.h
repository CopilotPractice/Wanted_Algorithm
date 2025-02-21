#pragma once
#include "Node.h";

class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	void Insert(Node* node);

	//전달한 노드와 겹치는 노드를 반환하는 함수.
	std::vector<Node*> Query(Node* queryNode);
public:
	//나눌 수 있는 트리의 최대 깊이 값.
	static const int maxDepth = 4; // 객체 생성 초기화 시점이랑 다르기때문에 ??
private:
	Node* root = nullptr;
};