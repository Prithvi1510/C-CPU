
#include"CPU.h"
#include "MEM.h"



int main()
{
	char fnamme[10] = "invaders";
	MEM gamemem(0x00);
	CPU cpu1(&gamemem, 0x00);
	gamemem.LoadROMData(fnamme);
}
