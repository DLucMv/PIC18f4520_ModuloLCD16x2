#include <p18f4520.h>

#pragma config	OSC = INTIO67
#pragma config	WDT = OFF
#pragma config	MCLRE = OFF
#pragma config	PBADEN = OFF
#pragma config	BORV = 3
#pragma config 	BOREN = OFF
	
void delay_ms (int);
void delay_s (int);
void delay_us (int);

void envia_comando (char);
void envia_dado (char);
void inicializar(void);
void mostrar_LCD(void);

#define comando_dado LATBbits.LATB0
#define pulso LATBbits.LATB1


void delay_s (int s)
{
	unsigned long int i;
	for ( ; s > 0; s--)
	{
		for (i=0;i<83333;i++) {};
	}
}


void delay_ms(int ms)

{
	unsigned int i;
	for ( ;ms > 0; ms--)
	{
		for (i=0;i<130;i++) {}		//tempo de loop = 1ms
	}
}

void delay_us(int us)	//funciona a partir de 10us
{
	unsigned char i;
	for ( ;us > 0; us--){
		for (i=0;i<28;i++) {};
	};
	i=0;
}

void envia_comando (char comando)
{
		comando_dado = 0;
		pulso = 1;
		LATD = comando;
		pulso = 0;
		delay_ms(10);
}
void envia_dado (char dado)
{		
		comando_dado = 1;
		pulso = 1;
		LATD = dado;
		pulso = 0;
		delay_ms(10);
}

void inicializar(){
		envia_comando(0b00111000);
		envia_comando(0b00001100);
		envia_comando(0b00000001);	
}

void animacao_bateria(){
	envia_comando(0x40);
	envia_dado(0b00100);
	envia_comando(0x41);
	envia_dado(0b11111);
	envia_comando(0x42);
	envia_dado(0b11111);
	envia_comando(0x43);
	envia_dado(0b11111);
	envia_comando(0x44);
	envia_dado(0b11111);
	envia_comando(0x45);
	envia_dado(0b11111);
	envia_comando(0x46);
	envia_dado(0b11111);
	envia_comando(0x47);
	envia_dado(0b11111);

	envia_comando(0x48);
	envia_dado(0b00100);
	envia_comando(0x49);
	envia_dado(0b11111);
	envia_comando(0x4A);
	envia_dado(0b10001);
	envia_comando(0x4B);
	envia_dado(0b10001);
	envia_comando(0x4C);
	envia_dado(0b11111);
	envia_comando(0x4D);
	envia_dado(0b11111);
	envia_comando(0x4E);
	envia_dado(0b11111);
	envia_comando(0x4F);
	envia_dado(0b11111);

	envia_comando(0x50);
	envia_dado(0b00100);
	envia_comando(0x51);
	envia_dado(0b11111);
	envia_comando(0x52);
	envia_dado(0b10001);
	envia_comando(0x53);
	envia_dado(0b10001);
	envia_comando(0x54);
	envia_dado(0b10001);
	envia_comando(0x55);
	envia_dado(0b10001);
	envia_comando(0x56);
	envia_dado(0b11111);
	envia_comando(0x57);
	envia_dado(0b11111);

}
void mostrar_LCD(){
 	
	envia_comando(0xC0);
	envia_dado('C');
	envia_dado('A');
	envia_dado('R');
	envia_dado('R');
	envia_dado('E');
	envia_dado('G');
	envia_dado('A');
	envia_dado('N');
	envia_dado('D');
	envia_dado('O');
	envia_dado('.');
	envia_dado('.');
	envia_dado('.');

	
	while(1){
		envia_comando(0x80);
		envia_dado(2);
		envia_comando(0xCC);
		envia_dado('.');
		delay_s(1);
 		envia_comando(0x80);
		envia_dado(1);
		envia_comando(0xCC);
		envia_dado(' ');
		delay_s(1);
		envia_comando(0x80);
		envia_dado(0);
		envia_comando(0xCC);
		envia_dado('.');
		delay_s(1);
		envia_comando(0xCC);
		envia_dado(' ');
		delay_ms(500);
	}

}

main ()

{	
	//área de configuração (só roda uma vez)
	ADCON1 = 0B00001111; // Seta portas 0, 1, 2 e 3 como analogicas

	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;	//OSC = 8MHz (interno)
	
	//BIT=1 -> PORTA DE ENTRADA, BIT=0 -> PORTA DE SAÍDA
	TRISB=0B00000000;
	TRISC=0B00000000;	 
	TRISD=0B00000000;
	

	inicializar();
	LATCbits.LATC4 = 1;
	animacao_bateria();
	mostrar_LCD();
	while(1){

	}
}