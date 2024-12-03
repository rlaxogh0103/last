#include<stdio.h>
#include<stdbool.h>
#include<windows.h>
#include<time.h>

#define DINO_BOTTOM_Y 17
#define CACTUS_BOTTOM_Y 25
#define CACTUS_BOTTOM_X 45

void CursorView(char show);
void SetColor(unsigned short text);
void SetConsoleView();
void DrawDino(int dinoY);
void GotoXY(int x, int y);
void DrawCactus(int cactusX);
int IsCollision(const int cactusX, const int dinoY);

enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

void SetColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

int main() {
	SetConsoleView();
	while (true) {
		int isJumping = false;
		int isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int cactusX = CACTUS_BOTTOM_X;
		while (true) {
			if (IsCollision(cactusX, dinoY)) break;
			cactusX -= 2;
			if (cactusX <= 0) cactusX = CACTUS_BOTTOM_X;

			if (GetKeyDown() == ' ' && isBottom) {
				isJumping = true;
				isBottom = false;
			}

			if (isJumping) dinoY -= gravity;
			else dinoY += gravity;

			if (dinoY >= DINO_BOTTOM_Y) {
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			if (dinoY <= 3) isJumping = false;

			cactusX -= 2;
			if (cactusX <= 0) cactusX = CACTUS_BOTTOM_X;

			DrawDino(dinoY);
			DrawCactus(cactusX);
			Sleep(60);
			system("cls");
		}
	}
}

int GetKeyDown() {
	if (_kbhit() != 0)return _getch();
	return false;
}

void DrawCactus(int cactusX) {
	SetColor(GREEN);
	GotoXY(cactusX, CACTUS_BOTTOM_Y);
	printf("  $");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 1);
	printf("$ $  ");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 2);
	printf("$ $ $");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 3);
	printf("$$$$$");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 4);
	printf("  $  ");
}

void GotoXY(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void DrawDino(int dinoY) {
	SetColor(SKYBLUE);
	GotoXY(0, dinoY);
	static int legFlag = true;
	printf("        $$$$$$$ \n");		// 8, 7, 1
	printf("       $$ $$$$$$\n");		// 7, 2, 1, 6
	printf("       $$$$$$$$$\n");		// 7, 9
	printf("$      $$$      \n");		// 1, 6, 3, 6
	printf("$$     $$$$$$$  \n");		// 2, 5, 7, 2
	printf("$$$   $$$$$     \n");		// 3, 3, 5, 5
	printf(" $$  $$$$$$$$$$ \n");		// 1, 2, 2, 10, 1
	printf(" $$");									// 1, 2
	SetColor(RED); printf("원광대");
	SetColor(SKYBLUE);
	printf("$$$    \n");						// 3, 4
	printf("  $$$");								// 2, 3
	SetColor(BLUE); printf("컴소공");
	SetColor(SKYBLUE);
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

int IsCollision(const int cactusX, const int dinoY) {
	GotoXY(0, 0);
	printf("cactusX : %2d,dinoY : %2d", cactusX, dinoY);
	if (cactusX <= 8 && cactusX >= 2 && dinoY > 12) return true;
	return false;
}