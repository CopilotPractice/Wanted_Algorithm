#include "QuadTree.h"

#include <iostream>

int main()
{
    // 0, 0을 왼쪽 상단으로 하는 (200, 200) 크기의 영역 선언
    QuadTree tree(Bounds(0, 0, 200, 200));

    // 삽입
    tree.Insert(new Node(Bounds(60, 80)));
    tree.Insert(new Node(Bounds(50, 50)));
    tree.Insert(new Node(Bounds(90, 120)));
    tree.Insert(new Node(Bounds(150, 150)));
    tree.Insert(new Node(Bounds(10, 10)));

    std::cout << "노드 삽입 완료\n";

    Node testNode(Bounds(45, 45, 20, 40));
    std::vector<Node*> intersects = tree.Query(&testNode);
    if (intersects.size() == 0)
    {
        std::cout << "겹치는 노드를 찾지 못했습니다\n";
    }
    else
    {
        std::cout << "겹치는 노드를 " << intersects.size() << "개 찾았습니다\n";
    }
}