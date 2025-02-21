#include <iostream>
#include "RedBlackTree.h"
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>

// 명령 구분을 열거형
enum class Command
{
	Node,
	Insert,
	Delete,
	Find,
	Print,
	Quit,
};

// 화면 지우는 함수 
void ClearScreen()
{
	system("cls");
}

void ProcessCommand(const int& commandInput, RedBlackTree& tree);
void ProcessParamInput(int& param);
void ProcessCommandInput(int& commandInput);

void Initialization(const char* path, RedBlackTree* tree)
{
	if (tree == nullptr)
	{
		std::cout << "오류: 전달된 트리가 null 입니다.\n";
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file, path, "r");
	if (file == nullptr)
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		return;
	}

	char line[1024] = { };
	if (!fgets(line, 1024, file))
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		fclose(file);
		return;
	}

	fclose(file);

	std::vector<int> datas;

	// 첫 토근 읽기.
	char* context = nullptr;
	char* splitString = strtok_s(line, ",", &context);
	if (splitString)
	{
		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 나머지 토근 읽기.
	while (context)
	{
		splitString = strtok_s(nullptr, ",", &context);
		if (!splitString)
		{
			break;
		}

		if (int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 트리에 데이터 추가.
	for (auto data : datas)
	{
		tree->Insert(data);
	}

	// 초기 데이터를 설정한 후의 데이터 출력.
	std::cout << "초기 데이터가 적용되었습니다.\n";
	tree->Print();
	std::cout << "\n";
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 레들 블랙 트리 생성
	RedBlackTree tree;
	Initialization("../Assets/InitData.txt", &tree);
	while (true)
	{
		// 명령 입력 처리
		int commandInput = 0;
		ProcessCommandInput(commandInput);

		// 명령 처리
		ProcessCommand(commandInput, tree);

		// 종료 처리
		if (commandInput == (int)Command::Quit)
		{
			break;
		}
	}

}

void ProcessCommand(const int& commandInput, RedBlackTree& tree)
{
	// 입력 값을 열거형으로 변환
	Command command = (Command)commandInput;
	if (command == Command::Print)
	{
		ClearScreen();
		tree.Print();
		return;
	}

	if (command == Command::Quit)
	{
		return;
	}

	int param = 0;
	ProcessParamInput(param);

	switch (command)
	{
	case Command::Insert:
	{
		ClearScreen();
		tree.Insert(param);
	} break;

	case Command::Delete:
	{
		ClearScreen();
		tree.Remove(param);
	} break;

	case Command::Find:
	{
		ClearScreen();
		// 검색
		Node* result = nullptr;
		if (!tree.Find(param, &result))
		{
			// 검색 실패
			std::cout << "노드를 찾지 못했습니다. (검색 값: " << param << ")\n";
			return;
		}

		if (result->GetColor() == Color::Red)
		{
			SetTextColor(TextColor::Red);
		}
		else
		{
			SetTextColor(TextColor::White);
		}

		// 검색 결과 출력
		std::cout
			<< "검색된 노드: " << result->Data()
			<< " (Color: " << result->ColorString()
			<< ")\n";

		// 색상 복구
		SetTextColor(TextColor::White);
	} break;
	}
}

void ProcessCommandInput(int& commandInput)
{
	// 입력 처리
	char inputBuffer[100] = {};

	while (true)
	{
		std::cout << "명령 숫자를 입력하세요.\n";
		std::cout << "1.노드추가, 2.노드 삭제, 3.노드 검색, 4.노드 출력, 5.종료\n";
		std::cin >> inputBuffer;

		// atoi: ascii to integer
		if (commandInput = atoi(inputBuffer))
		{
			// 예외처리.
			if (commandInput <= (int)Command::Node || commandInput > (int)Command::Quit)
			{
				ClearScreen();
				std::cout << "오류: 잘못된 숫자를 입력했습니다\n";
				continue;
			}
			break;
		}

		// 예외처리
		ClearScreen();
		std::cout << "오류: 명령은 숫자만 입력해야 합니다\n";
	}
}

void ProcessParamInput(int& param)
{
	// 입력 처리 버퍼
	char inputBuffer[100];

	// 입력 처리 루프
	while (true)
	{
		std::cout << "파라미터를 입력하세요 (1-200).\n";
		std::cin >> inputBuffer;

		// 검증
		if (param = atoi(inputBuffer))
		{
			// 예외처리
			if (param < 1 || param > 200)
			{
				ClearScreen();
				std::cout << "오류: 파라미터는 1-200 사이의 숫자만 입력해야 합니다.\n";
			}
			break;
		}
		// 예외처리
		ClearScreen();
		std::cout << "오류: 명령은 숫자만 입력해야 합니다\n";
	}
}