#pragma once

#include <vector>

//포인터 삭제 함수
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

//A* 길찾기 기능 처리 클래스
class Node;
class Astar
{
	//이동 방향 구조체(비용 계산을 위해)
	struct Direction
	{//안에서만 적용 되도록 class 안에 구조체 만듦
		//방향
		int x = 0;
		int y = 0;

		//비용
		float cost = 0.0f;
	};

public:
	Astar();
	~Astar();

	//경로 검색함수
	std::vector<Node*> FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid);

	//그리드 출력 함수(맵 보여주는 함수)
	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid, //path에 따라서 grid의 값을 다르게 해야함
		const std::vector<Node*>& path
	);


private:
	//탐색을 완료한 후에 최적 경로를 반환하는 함수
	//목표노드로 부터 부모 노드를 역추적해서 구함
	std::vector<Node*> ConstructPath(Node* goalNode);

	// 경로의 비용을 계산 함수
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	//탐색하려는 곳이 이동 가능한 곳인지
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	//이미 방문한 위치인지 확인하는 함수
	bool HasVisited(int x, int y, float gCost);

	bool IsDestination(const Node* node);
private:
	std::vector<Node*>openList; // 탐색 해야할 노드
	std::vector<Node*>closedList;

	Node* startNode = nullptr;
	Node* goalNode = nullptr;

};