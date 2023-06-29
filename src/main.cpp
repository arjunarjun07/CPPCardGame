#include "StartGame.h"

int main()
{

	StartGame *S=new StartGame(2);
	S->Game_main_Loop();
	char ch;
	ch = getchar();
	delete S;
	return 0;
}