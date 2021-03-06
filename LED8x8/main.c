#include <reg52.h>
#include <intrins.h>
typedef unsigned char uchar;
typedef unsigned int uint;

sbit S_CLK = P3^5;
sbit R_CLK = P3^6;
sbit DIO   = P3^4;
uchar code table[5][8] = {
0xE0,0xEE,0x01,0x6D,0x01,0x6D,0x01,0xEF,//电0

0xE7,0xF7,0xF7,0xF7,0x00,0xF7,0xFB,0x81,//子1

0x81,0xE7,0xE7,0xE7,0xE7,0xE7,0xC7,0xC7,//1 2

0x81,0x9F,0xCF,0xE7,0xF3,0xF9,0x9D,0xC1,//2 3

0xFF,0xC3,0xF9,0xFD,0xE3,0xFD,0xF9,0xC3,//3 4

};

void Send_dat(uchar dat)
{
	uchar i;
	R_CLK = 0;
	S_CLK = 0;
	for(i = 0; i < 8; i++){
		DIO = (dat & 0x01);
		S_CLK = 1;
		dat >>= 1;
		S_CLK = 0;
	}
}

void main()
{
	uchar i, j, k, ROW;
	while(1){
		for(j = 0; j < 5; j++){
			for(k = 0; k < 0xff; k++){
				ROW = 0x80;
				for(i = 0; i < 8; i++){
					Send_dat(table[j][i]);
					Send_dat(ROW);
					R_CLK = 1;
					R_CLK = 0;
					ROW = _cror_(ROW, 1);
				}
		  }
		}
  }
}