#include<stdint.h>
#include<stdio.h>

class ClassIo
{
public:
	uint8_t input[4];
	uint8_t output[7];
	int shift_amt; 
	uint16_t shift_register = 0x00; 

	ClassIo() {
		input[0] = 0xE; 
		input[1] = 0x11; 
		input[2] = 0x00;
		shift_amt = 0; 
	}
	unsigned char read_port(unsigned char address)
	{
		if (address > 3) { return 0;  }
		else { return input[address];  }
	}

	void write_port(unsigned char address , unsigned char value)
	{
		uint16_t _temp = 0; 
		if (address > 6) { return;  }
		else { output[address] = value;  }
		switch (address)
		{
		case 2:
			shift_amt = value; 
			shift_register = shift_register << shift_amt;
			input[3] = (uint8_t)(shift_register >> 8); 
			break; 
		case 4: 
			shift_register = shift_register >> 8; 
			_temp = value << 8; 
			shift_register = shift_register & 0xFF;
			shift_register |= _temp; 
			break; 
		default:
			break;
		}
	}



	void set_ships(int no_ships)
	{
		if (no_ships > 6) { return; }
		switch (no_ships)
		{
		case 3:
			input[2] = input[2] & 0xFC;
			break;
		case 4:
			input[2] = input[2] & 0xFD;
			break;
		case 5: 
			input[2] = input[2] & 0xFE;
			break; 
		case 6: 
			input[2] = input[2] & 0xFF;
			break;
		}

	}

	void set_extraship_1500(bool yes)
	{
		if (!yes) {
			input[2] = input[2] & 0xFF;
		}
		else
		{
			input[2] = input[2] & 0xF7; 
		}
	}


}; 