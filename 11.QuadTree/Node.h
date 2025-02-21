#pragma once

#include "Bounds.h"
#include <vector>

template<typename T>
void SafeDelete(T*& t)
{
	if (t) // nullptr이 아닌지 확인
	{
		delete t;
		t = nullptr;
	}
}

//영역 구분을 위한 열거형
enum class NodeIndex
{
	TopLeft,  //경계선에 걸치치 않고 완전 포함
	TopRight,
	BottomLeft,
	BottomRight,
	Straddling, // 경계선에 걸친 경우
	OutOfArea //영역을 벗어난 경우
};

class Node
{
public:
    Node(const Bounds& bounds, int depth = 0);
    ~Node();

    // 삽입(Insert).
    void Insert(Node* node);

    // 질의(Query).
    void Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes);

    // 정리.
    void Clear();

    Bounds GetBounds() const { return bounds; }

    const std::vector<Node*>& Points() const { return points; }

    Node* TopLeft() const { return topLeft; }
    Node* TopRight() const { return topRight; }
    Node* BottomLeft() const { return bottomLeft; }
    Node* BottomRight() const { return bottomRight; }
private:
    
    bool Subdivide();

    bool IsDivided();

    void ClearChildren();

    NodeIndex TestRegion(const Bounds& bounds);

    //전달한 영역이 포함되거나 걸치는 영역을 모두 구할 때 사용할 함수
    std::vector<NodeIndex> GetQuads(const Bounds& bounds);

private:
    // 현재 노드의 깊이.
    int depth = 0;

    // 현재 노드의 영역.
    Bounds bounds;

    // 현재 영역에 포함된 노드.
    std::vector<Node*> points;

    // 자식 노드.
    Node* topLeft = nullptr;
    Node* topRight = nullptr;
    Node* bottomLeft = nullptr;
    Node* bottomRight = nullptr;
};