#include "Astar.h"
#include "Node.h"

Astar::Astar()
{
}

Astar::~Astar()
{
    for (Node* node : openList)
    {
        SafeDelete(node);
    }
    openList.clear();
    for (Node* node : closedList)
    {
        SafeDelete(node);
    }
    closedList.clear();
}

void Astar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
    for (const Node* node : path)
    {
        grid[node->position.y][node->position.x] = 2;
    }

    //맵 출력
    for (int y = 0; y < (int)grid.size(); ++y)
    {
        for (int x = 0; x < (int)grid[0].size(); ++x)
        {
            if (grid[y][x] == 1)
            {
                std::cout << "1 ";
            }
            else if (grid[y][x] == 2)
            {
                std::cout << "+ ";
            }
            else if (grid[y][x] == 0)
            {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

std::vector<Node*> Astar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid)
{
    this->startNode = startNode;
    this->goalNode = goalNode;
    openList.emplace_back(startNode);

    std::vector<Direction> directions = {
        //하상우좌 = 비용 1
        {0, 1, 1.0f}, {0, -1, 1.0f}, {1, 0, 1.0f}, {-1, 0, 1.0f},

        //대각선 = 비용 root(2)
        {1, 1, 1.1414f},{1, -1, 1.1414f},{-1, 1, 1.1414f}, {-1, -1, 1.1414f}

    };
    while (!openList.empty())
    {
        // 현재 열린 리스트에서 비용(fCost)이 가장 낮은 노드 검색
        // 최적화 가능(우선 순위 큐, 힙)
        Node* lowestNode = openList[0];

        for (Node* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
            {
                lowestNode = node;
            }
        }

        //비용이 가장 작은 노드를 현재 노드로 선택
        Node* currentNode = lowestNode;

        //현재 노드가 목표 노드인지 확인
        if (IsDestination(currentNode))
        {
            return ConstructPath(currentNode);
        }

        //방문 처리를 위해 현재 노드를 열린 리스트에서 제거
        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            // 두 노드의 위치를 기반으로 같은지 확인
            if (*openList[ix] == *currentNode)
            {
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        // 방문 처리를 위해 닫힌 리스트에 추가.
        // 이미 추가 된 노드는 제외
        // 최적화 가능성 有
        bool isNodeInList = false;
        for (Node* node : closedList)
        {
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        //이미 있으면 무시
        if(isNodeInList)
        {
            continue;
        }
        //없으면 닫힌 리스트에 추가
        closedList.emplace_back(currentNode);

        //이웃노드 방문(하상우좌 .. 차례로 방문)
        for (const Direction& direction : directions)
        {
            // 다음에 이동할 위치 확인
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;

            //그리드 벗어나면 무시
            if (!IsInRange(newX, newY, grid))
            {
                continue;
            }

            //이동 할 노드가 이동 가능한지 확인.
            if (grid[newY][newX] == 1)
            {
                continue;
            }

            //이미 방문했는지 확인
            if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
            {
                continue;
            }
            //방문할 노드 생성(비용 계산)
            Node* neighborNode = new Node(newX, newY, currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            //열린 리스트에 추가
            //이미 리스트에 있는지 확인
            Node* openListNode = nullptr;
            for (Node* node : openList)
            {
                if (*node == *neighborNode)
                {
                    openListNode = node;
                    break;
                }
            }

            // 이웃노드가 리스트에 없으면 바로 추가
            //리스트에 있으면 비용을 비교해 더 저렴하면 추가
            if (openListNode == nullptr || neighborNode->gCost < openListNode->gCost
                || neighborNode->fCost < openListNode->fCost)
            {
                openList.emplace_back(neighborNode);
            }
            else
            {
                SafeDelete(neighborNode);
            }
        }
    }
    //initialize_list (c++)
    //return {};
    return std::vector<Node*>(); // 경로가 없으면 빈 리스트 return
}


std::vector<Node*> Astar::ConstructPath(Node* goalNode)
{
    // 목표 노드로부터 부모 노드를 따라 역추적하면서 경로 설정
    std::vector<Node*> path; //한 번에 이전 이전 부모노드를 확인 불가
    Node* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // 시작 지점부터 목표 지점으로 향하도록 배열 뒤집기
    std::reverse(path.begin(), path.end());
    return path;
}

float Astar::CalculateHeuristic(Node* currentNode, Node* goalNode) //구하는 공식 多
{
    Position diff = *currentNode - *goalNode;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

bool Astar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size()) // 범위 벗어났는지 아닌지 확인
    {
        return false;
    }
    return true;
}

bool Astar::HasVisited(int x, int y, float gCost)
{
    // 열린/닫힌 리스트에 이미 해당 위치가 있으면 방문한 것으로 판단.
    for (int ix = 0; ix < (int)openList.size(); ++ix)
    {
        Node* node = openList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            //위치도 같고, 비용이 더 크면 방문할 이유 없음.
            if (gCost >= node->gCost)
            {
                return true;
            }
            // 새 노드의 비용이 작은 경우에는 기존 노드 제거
            openList.erase(openList.begin() + ix);
            SafeDelete(node);
        }
    }

    for (int ix = 0; ix < (int)closedList.size(); ++ix)
    {
        Node* node = closedList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            //위치도 같고, 비용이 더 크면 방문할 이유 없음.
            if (gCost >= node->gCost)
            {
                return true;
            }
            // 새 노드의 비용이 작은 경우에는 기존 노드 제거
            closedList.erase(closedList.begin() + ix);
            SafeDelete(node);
        }
    }
    return false;
}

bool Astar::IsDestination(const Node* node)
{
    return *node == *goalNode;
}
