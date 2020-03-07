#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*
===메모===
=함수명 규칙
St = Struct
Cl = Class

=타입(Type)
기본값 0

=코드(Code)
기본값 0
*/

class Cl_Entity
{
protected:
	string Name;
	string Caption;
	int Hp, MaxHp;
	int Type = 0;
	int Code = 0;
public:
	string GetName()
	{
		return Name;
	}
	string GetCaption()
	{
		return Caption;
	}
};

class Cl_Item : Cl_Entity
{
protected:
	
public:

};

class Cl_Character : Cl_Entity
{
protected:
	vector<int> Stat;
	int Mp, MaxMp;
};

class Cl_txtParser
{
protected:
	string FileRoute;
	FILE* FilePtr;
	bool ReadOpen()
	{
		try
		{
			if (FilePtr != NULL) throw 1001;
			FilePtr = fopen(FileRoute.c_str(), "r");
			if (FilePtr == NULL) throw 1002;
		}
		catch (int type) 
		{
			return false;
		}
		return true;
	}
	bool WriteOpen()
	{
		try
		{
			if (FilePtr != NULL) throw 1101;
			FilePtr = fopen(FileRoute.c_str(), "w");
			if (FilePtr == NULL) throw 1102;
		}
		catch (int type)
		{
			return false;
		}
		return true;
	}
	bool AppenOpen()
	{
		try
		{
			if (FilePtr != NULL) throw 1201;
			FilePtr = fopen(FileRoute.c_str(), "a");
			if (FilePtr == NULL) throw 1202;
		}
		catch (int type)
		{
			throw type;
			return false;
		}
		return true;
	}
	void Close()
	{
		fclose(FilePtr);
	}
public:
	void SetRoute(string route)
	{
		FileRoute = route;
	}
	vector<string> ReadData()
	{
		try
		{
			ReadOpen();
		}
		catch (int type)
		{
			return;
		}
		string StringTemp = "";
		char CharTemp;
		vector<string> DataTemp;
		CharTemp = fgetc(FilePtr);
		while (CharTemp != EOF)
		{
			if (CharTemp == '\n')
			{
				if (StringTemp.length == 0)
				{
					CharTemp = fgetc(FilePtr);
					continue;
				}
				DataTemp.push_back(StringTemp);
				StringTemp.clear();
			}
			else
			{
				StringTemp += CharTemp;
			}	
			CharTemp = fgetc(FilePtr);
		}
	}
	vector<string> ReadData(char Delimiter)
	{
		try
		{
			ReadOpen();
		}
		catch (int type)
		{
			return;
		}
		string StringTemp = "";
		char CharTemp;
		vector<string> DataTemp;
		CharTemp = fgetc(FilePtr);
		while (CharTemp != EOF)
		{
			if (CharTemp == Delimiter)
			{
				if (StringTemp.length == 0)
				{
					CharTemp = fgetc(FilePtr);
					continue;
				}
				DataTemp.push_back(StringTemp);
				StringTemp.clear();
			}
			else
			{
				StringTemp += CharTemp;
			}
			CharTemp = fgetc(FilePtr);
		}
	}
};

class Cl_Screen
{
private:
	HANDLE ScreenBuffer[2];
	int SelectBufferIndex;
	COORD Size;
	bool IsUsing;
public: 
	Cl_Screen()
	{
		ScreenBuffer[0] = INVALID_HANDLE_VALUE; //initializing
		ScreenBuffer[1] = INVALID_HANDLE_VALUE;
		IsUsing = false;
		SelectBufferIndex = 0;
		Size = { 0, 0 };
	}
	~Cl_Screen()
	{
		ReleaseBuffer();
	}
	void CreateBuffer(COORD size)
	{
		Size = size;
		SMALL_RECT rect;
		rect.Left = 0;
		rect.Right = Size.X - 1;
		rect.Top = 0;
		rect.Bottom = Size.Y - 1;

		ScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //Create Buffer
		SetConsoleScreenBufferSize(ScreenBuffer[0], Size); //Set Console Buffer size
		SetConsoleWindowInfo(ScreenBuffer[0], TRUE, &rect); // Set Console Window size


		ScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //Create Buffer
		SetConsoleScreenBufferSize(ScreenBuffer[1], Size); //Set Console Buffer size
		SetConsoleWindowInfo(ScreenBuffer[1], TRUE, &rect); // Set Console Window size
	}
	void DrawBuffer(COORD position, const char *text)
	{
		DWORD dw;
		SetConsoleCursorPosition(ScreenBuffer[SelectBufferIndex], position);
		WriteFile(ScreenBuffer[SelectBufferIndex], text, strlen(text), &dw, NULL);
	}
	void Flipping()
	{
		SetConsoleActiveScreenBuffer(ScreenBuffer[SelectBufferIndex]);
		SelectBufferIndex = !SelectBufferIndex;
	}
	void ClearBuffer()
	{
		COORD Coor = { 0, 0 };
		DWORD dw;
		FillConsoleOutputCharacter(ScreenBuffer[SelectBufferIndex], ' ', Size.X * Size.Y, Coor, &dw);
	}
	void ReleaseBuffer()
	{
		if (ScreenBuffer[0] != INVALID_HANDLE_VALUE)
		{
			CloseHandle(ScreenBuffer[0]);
			ScreenBuffer[0] = INVALID_HANDLE_VALUE;
		}
		if (ScreenBuffer[1] != INVALID_HANDLE_VALUE)
		{
			CloseHandle(ScreenBuffer[1]);
			ScreenBuffer[1] = INVALID_HANDLE_VALUE;
		}
		Size = { 0, 0 };
	}
	COORD GetSize()
	{
		return Size;
	}
};

int main()
{
    std::cout << "Hello World!\n";
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴