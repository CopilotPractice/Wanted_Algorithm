#include <iostream>
#include "Astar.h"
#include <vector>
#include "Node.h"

// 그리드 생성.
    // 0: 이동 가능.
    // 1: 이동 불가(장애물).
    // 2: 시작 위치.
    // 3: 목표 위치.
int main() {
    std::vector<std::vector<int>> grid =
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };

    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    bool initialized = false;
    for (int y = 0; y < (int)grid.size(); ++y)
    {
        // 이미 찾았으면 종료
        if (startNode && goalNode)
        {
            initialized = true;
            break;
        }
        for (int x = 0; x < (int)grid[0].size(); ++x)
        {
            if (startNode && goalNode)
            {
                initialized = true;
                break;
            }

            if (grid[y][x] == 2)
            {
                startNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }
            if (grid[y][x] == 3)
            {
                goalNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }
        }
    }

    //Astar 객체
    Astar aStar;

    //경로 탐색.                          startNode는 astar 객체 안에 있어서 소멸자에서 같이 소멸
    std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

    //결과확인
    if (!path.empty())
    {
        std::cout << "경로를 찾았습니다. 탐색 경로: \n";
        for (Node* node : path)
        {
            std::cout << "(" << node->position.x << ", " << node->position.y << ") ->";
        }
        std::cout << "도착\n";
        std::cout << "경로를 맵에 표시한 결과: \n";
        aStar.DisplayGridWithPath(grid, path);
    }
    else {
        std::cout << "경로를 찾지 못했습니다.\n";
    }
    
    //목표 노드만 제거
    SafeDelete(goalNode);
}
