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

	// ��带 �˻��ϴ� �Լ�.
	bool Find(int data, Node** outNode);

	// ��� ���� �Լ� (������ ���).
	bool Remove(int data);

	// ��� �߰� �Լ� (������ ���).
	bool Insert(int data);

	// ��� �Լ�.
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

	// Ʈ������ �ּ� ���� ���� ��带 �˻��ϴ� �Լ�
	Node* FindMinRecursive(Node* node);

	// Ʈ������ �ִ� ���� ���� ��带 �˻��ϴ� �Լ�
	Node* FindMaxRecursive(Node* node);

	// ��� ���� �Լ�
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
