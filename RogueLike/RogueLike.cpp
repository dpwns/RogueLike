#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

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

typedef struct Struct_Entity 
{
	double MaxHp = 0;
	double Hp = 0;
	int Type = 0;
	int Code = 0;
}St_Entity;

class Screen
{
private:
	HANDLE ScreenBuffer[2];
	int SelectBufferIndex;
	COORD Size;
	bool IsUsing;
public: 
	Screen()
	{
		ScreenBuffer[0] = INVALID_HANDLE_VALUE; //initializing
		ScreenBuffer[1] = INVALID_HANDLE_VALUE;
		IsUsing = false;
		SelectBufferIndex = 0;
		Size = { 0, 0 };
	}
	~Screen()
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