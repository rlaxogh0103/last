#include<stdio.h>
#include<stdbool.h>
#include<windows.h>

void CursorView(char show);
void SetConsoleView();

int main() {
	SetConsoleView();
	while (true) {
		static int legFlag = true;
		printf("        $$$$$$$ \n");		// 8, 7, 1
		printf("       $$ $$$$$$\n");		// 7, 2, 1, 6
		printf("       $$$$$$$$$\n");		// 7, 9
		printf("$      $$$      \n");		// 1, 6, 3, 6
		printf("$$     $$$$$$$  \n");		// 2, 5, 7, 2
		printf("$$$   $$$$$     \n");		// 3, 3, 5, 5
		printf(" $$  $$$$$$$$$$ \n");		// 1, 2, 2, 10, 1
		printf(" $$");									// 1, 2
		printf("원광대");
		printf("$$$    \n");						// 3, 4
		printf("  $$$");								// 2, 3
		printf("컴소공");
		printf("$    \n");							// 1, 4
		printf("    $$$$$$$$    \n");		// 4, 8, 4
		printf("     $$$$$$     \n");		// 5, 6, 5
		if (legFlag) {
			printf("     $    $$$   \n");
			printf("     $$         ");
			legFlag = false;
		}
		else {
			printf("     $$$  $     \n");
			printf("          $$    ");
			legFlag = true;
		}

		Sleep(60);
		system("cls");
	}
}

void CursorView(char show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void SetConsoleView() {
	system("mode con:cols=120 lines=30");
	system("title 창의실무프로젝트 구글 공룡 게임 [By. Taeho Kim]");
	CursorView(false);
}