#include <stdint.h>
#ifndef Memory_H 
#define Memory_H

class MemoryFile{ 
    
   public: 
        MemoryFile(uint8_t consoleMode );
     
        int8_t LoadROMData(const char* Filename);
        uint16_t ROMadresss = 0x0000 ; 
        uint16_t RAMadress = 0x2000; 
        uint16_t VRAMadress = 0x2400; 
        uint16_t RAMMirrorAddress = 0x4000;
        uint8_t* MemoryMap[0x10000];
   
        /*
         ROM:			0x0000 - 0x1FFF
         RAM:			0x2000 - 0x23FF
         VRAM:			0x2400 - 0x3FFF
         RAMMirror:	0x4000 - 0x43FF
     */
      

        private:
		uint8_t JunkValue;
		uint8_t Memory[0x10000];

}; 
#endif
