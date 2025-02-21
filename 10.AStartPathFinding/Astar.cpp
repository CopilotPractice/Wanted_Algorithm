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

    //�� ���
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
        //�ϻ���� = ��� 1
        {0, 1, 1.0f}, {0, -1, 1.0f}, {1, 0, 1.0f}, {-1, 0, 1.0f},

        //�밢�� = ��� root(2)
        {1, 1, 1.1414f},{1, -1, 1.1414f},{-1, 1, 1.1414f}, {-1, -1, 1.1414f}

    };
    while (!openList.empty())
    {
        // ���� ���� ����Ʈ���� ���(fCost)�� ���� ���� ��� �˻�
        // ����ȭ ����(�켱 ���� ť, ��)
        Node* lowestNode = openList[0];

        for (Node* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
            {
                lowestNode = node;
            }
        }

        //����� ���� ���� ��带 ���� ���� ����
        Node* currentNode = lowestNode;

        //���� ��尡 ��ǥ ������� Ȯ��
        if (IsDestination(currentNode))
        {
            return ConstructPath(currentNode);
        }

        //�湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����
        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            // �� ����� ��ġ�� ������� ������ Ȯ��
            if (*openList[ix] == *currentNode)
            {
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        // �湮 ó���� ���� ���� ����Ʈ�� �߰�.
        // �̹� �߰� �� ���� ����
        // ����ȭ ���ɼ� ��
        bool isNodeInList = false;
        for (Node* node : closedList)
        {
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        //�̹� ������ ����
        if(isNodeInList)
        {
            continue;
        }
        //������ ���� ����Ʈ�� �߰�
        closedList.emplace_back(currentNode);

        //�̿���� �湮(�ϻ���� .. ���ʷ� �湮)
        for (const Direction& direction : directions)
        {
            // ������ �̵��� ��ġ Ȯ��
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;

            //�׸��� ����� ����
            if (!IsInRange(newX, newY, grid))
            {
                continue;
            }

            //�̵� �� ��尡 �̵� �������� Ȯ��.
            if (grid[newY][newX] == 1)
            {
                continue;
            }

            //�̹� �湮�ߴ��� Ȯ��
            if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
            {
                continue;
            }
            //�湮�� ��� ����(��� ���)
            Node* neighborNode = new Node(newX, newY, currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            //���� ����Ʈ�� �߰�
            //�̹� ����Ʈ�� �ִ��� Ȯ��
            Node* openListNode = nullptr;
            for (Node* node : openList)
            {
                if (*node == *neighborNode)
                {
                    openListNode = node;
                    break;
                }
            }

            // �̿���尡 ����Ʈ�� ������ �ٷ� �߰�
            //����Ʈ�� ������ ����� ���� �� �����ϸ� �߰�
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
    return std::vector<Node*>(); // ��ΰ� ������ �� ����Ʈ return
}


std::vector<Node*> Astar::ConstructPath(Node* goalNode)
{
    // ��ǥ ���κ��� �θ� ��带 ���� �������ϸ鼭 ��� ����
    std::vector<Node*> path; //�� ���� ���� ���� �θ��带 Ȯ�� �Ұ�
    Node* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // ���� �������� ��ǥ �������� ���ϵ��� �迭 ������
    std::reverse(path.begin(), path.end());
    return path;
}

float Astar::CalculateHeuristic(Node* currentNode, Node* goalNode) //���ϴ� ���� ��
{
    Position diff = *currentNode - *goalNode;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

bool Astar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size()) // ���� ������� �ƴ��� Ȯ��
    {
        return false;
    }
    return true;
}

bool Astar::HasVisited(int x, int y, float gCost)
{
    // ����/���� ����Ʈ�� �̹� �ش� ��ġ�� ������ �湮�� ������ �Ǵ�.
    for (int ix = 0; ix < (int)openList.size(); ++ix)
    {
        Node* node = openList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            //��ġ�� ����, ����� �� ũ�� �湮�� ���� ����.
            if (gCost >= node->gCost)
            {
                return true;
            }
            // �� ����� ����� ���� ��쿡�� ���� ��� ����
            openList.erase(openList.begin() + ix);
            SafeDelete(node);
        }
    }

    for (int ix = 0; ix < (int)closedList.size(); ++ix)
    {
        Node* node = closedList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            //��ġ�� ����, ����� �� ũ�� �湮�� ���� ����.
            if (gCost >= node->gCost)
            {
                return true;
            }
            // �� ����� ����� ���� ��쿡�� ���� ��� ����
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
