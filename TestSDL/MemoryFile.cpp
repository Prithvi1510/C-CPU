#include <cstring>
#include <stdio.h>
#include "MemoryFile.h"

#pragma warning(disable : 4996)

MemoryFile::MemoryFile(uint8_t consoleMode)
{
    memset(Memory, 0, sizeof(Memory));

    for (int i = 0; i < 0x4000; i++) //ROM + RAM + VRAM 
    {
        MemoryMap[i] = Memory + i;
    }

    if (!consoleMode)
    {
        for (int i = 0x4000; i < 0x4400; i++)
        {
            MemoryMap[i] = Memory + i - 0x2000;
        }
    }
    else
    {
        for (int i = 0x4000; i < 0xFFFF; i++)
        {
            MemoryMap[i] = Memory + i;
        }
    }




}
int8_t MemoryFile::LoadROMData(const char* Filename)
{

    FILE* ROMData;


    ROMData = fopen(Filename, "rb");
    if (ROMData == 0)
        return 0;

    fseek(ROMData, 0, SEEK_END);
    uint16_t ROMSize = ftell(ROMData);
    fclose(ROMData);

    ROMData = fopen(Filename, "rb");
    //uint8_t* Buffer = (uint8_t*) malloc(ROMSize);

    if (fread(&Memory[0], 1, ROMSize, ROMData) != ROMSize)
        return 0;



    //free (Buffer);
    fclose(ROMData);
    return 1;
    
    
}


 

