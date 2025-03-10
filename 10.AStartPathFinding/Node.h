#pragma once

#include <iostream>

struct Position
{
	Position(int x = 0, int y = 0)
		:x(x), y(y)
	{

	}
	int x;
	int y;
};

class Node
{
public:
	Node(int x, int y, Node* parent = nullptr)
		:position(x,y), parent(parent)
	{
	}
	~Node() = default;

	//연산자 오버로딩

	Position operator-(const Node& other)
	{
		return Position(position.x - other.position.x, position.y - other.position.y);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x && position.y == other.position.y;
	}

public:
	//노드 위치
	Position position;
	
	//비용
	//현재 노드에서 이동 노드까지(시작점에서 현재 노드까지) 비용
	float gCost = 0.0f;
	//이동 노드에서 목표 노드까지(현재 노드에서 목표 노드까지) 비용(휴리스틱, 추정)
	float hCost = 0.0f;
	// 두 비용을 합친 비용( gCost + hCost )
	float fCost = 0.0f;

	//링크 필드(부모노드) = 마지막으로 역추적해야 함
	Node* parent = nullptr;
};