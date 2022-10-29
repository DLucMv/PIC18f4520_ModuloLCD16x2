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
void envia_comando_lcd2 (char);
void envia_dado_lcd2 (char);

void mostrar_LCD(void);
void mostrar_LCD2(void);

#define comando_dado LATBbits.LATB0
#define comando_dado_lcd2 LATBbits.LATB3
#define pulso LATBbits.LATB1
#define pulso_lcd2 LATBbits.LATB4


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


void envia_comando_lcd2 (char comando)
{
		comando_dado_lcd2 = 0;
		pulso_lcd2 = 1;
		LATC = comando;
		pulso_lcd2 = 0;
		delay_ms(10);
}


void envia_dado_lcd2 (char dado)
{
		comando_dado_lcd2 = 1;
		pulso_lcd2 = 1;
		LATC = dado;
		pulso_lcd2 = 0;
		delay_ms(10);
}


void inicializar(){
		envia_comando(0b00111000);
		envia_comando(0b00001100);
		envia_comando(0b00000001);	
}

void inicializar_lcd2(){
		envia_comando_lcd2(0b00111000);
		envia_comando_lcd2(0b00001100);
		envia_comando_lcd2(0b00000001);	
}


void mostrar_LCD(){

	envia_dado('I');
	envia_dado('s');
	envia_dado('s');
	envia_dado('o');
	envia_dado(' ');
	envia_dado('e');
	envia_dado('h');
	envia_comando(0xC0);
	envia_dado('i');
	envia_dado('n');
	envia_dado('c');
	envia_dado('r');
	envia_dado('i');
	envia_dado('v');
	envia_dado('e');
	envia_dado('l');
	envia_dado(' ');
	envia_dado('!');

}


void mostrar_LCD2(){

	envia_dado_lcd2('T');
	envia_dado_lcd2('h');
	envia_dado_lcd2('i');
	envia_dado_lcd2('s');
	envia_dado_lcd2(' ');
	envia_dado_lcd2('i');
	envia_dado_lcd2('s');
	envia_comando_lcd2(0xC0);
	envia_dado_lcd2('a');
	envia_dado_lcd2('m');
	envia_dado_lcd2('a');
	envia_dado_lcd2('z');
	envia_dado_lcd2('i');
	envia_dado_lcd2('n');
	envia_dado_lcd2('g');
	envia_dado_lcd2(' ');
	envia_dado_lcd2('!');

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
	
	LATBbits.LATB2 = 1;
	inicializar();
	inicializar_lcd2();
	mostrar_LCD();
	mostrar_LCD2();
	while(1){

	}
}