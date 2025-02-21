#pragma once

#include <iostream>
#include <string>
#include "Node.h"
#include <Windows.h>

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// 노드를 검색하는 함수.
	bool Find(int data, Node** outNode);

	// 노드 삭제 함수 (데이터 사용).
	bool Remove(int data);

	// 노드 추가 함수 (데이터 사용).
	bool Insert(int data);

	// 출력 함수.
	void Print(int depth = 0, int blackCount = 0);
	
private:
	
	Node* CreateNode(int data = 0, Color color = Color::Red);

	bool FindRecursive(Node* node, Node** outNode, int data);

	//Node* Find(int data, Node** outNode);

	void Insert(Node* newNode);

	void InsertRecursive(Node* node, Node* newNode);

	void RestructureAfterInsert(Node* newNode);

	void RestructureAfterRemove(Node* node);

	void RotateToLeft(Node* node);

	void RotateToRight(Node* node);

	// 트리에서 최솟 값을 가진 노드를 검색하는 함수
	Node* FindMinRecursive(Node* node);

	// 트리에서 최댓 값을 가진 노드를 검색하는 함수
	Node* FindMaxRecursive(Node* node);

	// 노드 삭제 함수
	void RemoveImpl(Node* node);

	void DestroyRecursive(Node* node);

	void PrintRecursive(Node* node, int depth, int blackCount);

private:
	Node* root = nullptr;
	static Node* nil;
};

enum class TextColor
{
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue

};

void SetTextColor(TextColor color);
