#ifndef CPU_H
#define CPU_H 

#include<stdint.h>
#include<stdio.h>
#include"MemoryFile.h"

class CPU{ 
    public: 
        CPU(MemoryFile * _mmu, uint8_t _ConsoleMode ) ;
        void clock();
        void interrupt(uint8_t ID); 
        //IO
        uint8_t   input_port[4];
        uint8_t   output_port[7]; 
        //STATUS 
        uint8_t InterruptsEnabled;
		uint8_t Halt;
		uint64_t ClockCount;
		uint64_t InstructionCount;
		uint8_t ConsoleMode;
		uint16_t Get_PC();
 
		MemoryFile * mmu;
        // Ports + SpaceInvaders custom hardware
		uint16_t reg_SHIFT;
		uint8_t ShiftOffset;

        // Temp Vars
		uint16_t WorkValue;

        uint8_t* reg_M;
		uint8_t true_reg_A;
		uint8_t* reg_A = &true_reg_A;
        uint16_t reg_BC;
		uint8_t* reg_B = ((uint8_t*) &reg_BC) + 1;
		uint8_t* reg_C = ((uint8_t*) &reg_BC);
		uint16_t reg_DE;
		uint8_t* reg_D = ((uint8_t*) &reg_DE) + 1;
		uint8_t* reg_E = ((uint8_t*) &reg_DE);
		uint16_t reg_HL;
		uint8_t* reg_H = ((uint8_t*) &reg_HL) + 1;
		uint8_t* reg_L = ((uint8_t*) &reg_HL);
        uint16_t PC, SP;


		//flag
        uint8_t flag_Z; // Zero
		uint8_t flag_S; // Sign
		uint8_t flag_P; // Parity
		uint8_t flag_C; // Carry
		uint8_t flag_AC;// AC 
		uint8_t FlagZSP[0xFF]; 

		//function calls 
		void Syscall (uint8_t ID);
		void Execute (uint8_t Instruction);
		
		//functions mem 
		uint8_t GetByteAt (uint16_t Address);
		//int GetByteAt (uint16_t Address);
		void SetByteAt (uint16_t Address, uint8_t Value);
		uint16_t GetWordAt (uint16_t Address);
		void SetWordAt (uint16_t Address, uint16_t Value);
		void PushPSW ();
		void PopPSW ();

		//stack managment 
		uint16_t StackPop ();
		void StackPush (uint16_t Value);
		
		//flag managment 
		void SetFlagsAdd (uint8_t OpA, uint8_t OpB, uint8_t Carry, uint8_t CarryMode);
		void SetFlagsSub (uint8_t OpA, uint8_t OpB, uint8_t Carry, uint8_t CarryMode);
		void SetZSP (uint8_t Value);
};	

#endif
