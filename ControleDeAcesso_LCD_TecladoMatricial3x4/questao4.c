#include <p18f4520.h>

#pragma config	OSC = INTIO67
#pragma config	WDT = OFF
#pragma config	MCLRE = OFF
#pragma config	PBADEN = OFF
#pragma config	BORV = 3
#pragma config 	BOREN = OFF

//Rotinas de atraso	
void delay_ms (int);
void delay_s (int);
void delay_us (int);

//
void envia_comando (char);
void envia_dado (char);

//Inicia o display no stado padrao/default
void inicializar(void);

//Caracteres especiais
void sorriso(void);
void triste(void);
void cadeado(void);
void asterisco(void);

//Mostrar mensagens no display
void mostrar_saudacao(void);
void mostrar_senha_invalida(void);
void mostrar_acesso_liberado(void);

#define comando_dado LATCbits.LATC0
#define pulso LATCbits.LATC1


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


void sorriso(){

	envia_comando(0x40);
	envia_dado(0b00010);//1
	envia_comando(0x41);
	envia_dado(0b00001);//2
	envia_comando(0x42);
	envia_dado(0b11001);//3
	envia_comando(0x43);
	envia_dado(0b00001);//4
	envia_comando(0x44);
	envia_dado(0b00001);//5
	envia_comando(0x45);
	envia_dado(0b11001);//6
	envia_comando(0x46);
	envia_dado(0b00010);//7
	envia_comando(0x47);
	envia_dado(0b00000);//8

}


void triste(){

	envia_comando(0x48);
	envia_dado(0b00000);//1
	envia_comando(0x49);
	envia_dado(0b00001);//2
	envia_comando(0x4A);
	envia_dado(0b11010);//3
	envia_comando(0x4B);
	envia_dado(0b00010);//4
	envia_comando(0x4C);
	envia_dado(0b00010);//5
	envia_comando(0x4D);
	envia_dado(0b11010);//6
	envia_comando(0x4E);
	envia_dado(0b00001);//7
	envia_comando(0x4F);
	envia_dado(0b00000);//8

}


void cadeado(){

	envia_comando(0x50);
	envia_dado(0b01110);//1
	envia_comando(0x51);
	envia_dado(0b10001);//2
	envia_comando(0x52);
	envia_dado(0b10001);//3
	envia_comando(0x53);
	envia_dado(0b11111);//4
	envia_comando(0x54);
	envia_dado(0b11011);//5
	envia_comando(0x55);
	envia_dado(0b11011);//6
	envia_comando(0x56);
	envia_dado(0b11111);//7
	envia_comando(0x57);
	envia_dado(0b11111);//8

}


void asterisco(){

	envia_comando(0x58);
	envia_dado(0b00000);//1
	envia_comando(0x59);
	envia_dado(0b10101);//2
	envia_comando(0x5A);
	envia_dado(0b01110);//3
	envia_comando(0x5B);
	envia_dado(0b11111);//4
	envia_comando(0x5C);
	envia_dado(0b01110);//5
	envia_comando(0x5D);
	envia_dado(0b10101);//6
	envia_comando(0x5E);
	envia_dado(0b00000);//7
	envia_comando(0x5F);
	envia_dado(0b00000);//8

}


void mostrar_saudacao(){

	envia_comando(0b00000001);
	envia_comando(0x80);
	envia_dado('O');
	envia_dado('l');
	envia_dado('a');
	envia_dado(',');
	envia_dado(' ');
	envia_dado('P');
	envia_dado('o');
	envia_dado('r');
	envia_dado(' ');
	envia_dado('f');
	envia_dado('a');
	envia_dado('v');
	envia_dado('o');
	envia_dado('r');
	envia_comando(0xC0);
	envia_dado('I');
	envia_dado('n');
	envia_dado('s');
	envia_dado('i');
	envia_dado('r');
	envia_dado('a');
	envia_dado(' ');
	envia_dado('s');
	envia_dado('u');
	envia_dado('a');
	envia_dado(' ');
	envia_dado('s');
	envia_dado('e');
	envia_dado('n');
	envia_dado('h');
	envia_dado('a');
}


void mostrar_senha_invalida(){

	envia_comando(0b00000001);
	envia_comando(0x80);
	envia_dado('S');
	envia_dado('e');
	envia_dado('n');
	envia_dado('h');
	envia_dado('a');
	envia_dado(' ');
	envia_dado('i');
	envia_dado('n');
	envia_dado('v');
	envia_dado('a');
	envia_dado('l');
	envia_dado('i');
	envia_dado('d');
	envia_dado('a');
	envia_dado('!');
	envia_comando(0xC0);
	envia_dado('A');
	envia_dado('c');
	envia_dado('e');
	envia_dado('s');
	envia_dado('s');
	envia_dado('o');
	envia_dado(' ');
	envia_dado('n');
	envia_dado('e');
	envia_dado('g');
	envia_dado('a');
	envia_dado('d');
	envia_dado('o');
	envia_dado(' ');
	envia_dado(1);
}


void mostrar_acesso_liberado(){

	envia_comando(0b00000001);
	envia_comando(0x80);
	envia_dado('A');
	envia_dado('c');
	envia_dado('e');
	envia_dado('s');
	envia_dado('s');
	envia_dado('o');
	envia_dado(' ');
	envia_dado('L');
	envia_dado('i');
	envia_dado('b');
	envia_dado('e');
	envia_dado('r');
	envia_dado('a');
	envia_dado('d');
	envia_dado('o');
	envia_dado('!');
	envia_comando(0xC0);
	envia_dado('S');
	envia_dado('e');
	envia_dado('j');
	envia_dado('a');
	envia_dado(' ');
	envia_dado('b');
	envia_dado('e');
	envia_dado('m');
	envia_dado(' ');
	envia_dado('v');
	envia_dado('i');
	envia_dado('n');
	envia_dado('d');
	envia_dado('o');
	envia_dado(' ');
	envia_dado(0);
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
	LATBbits.LATB7 = 0;
	LATCbits.LATC2 = 0;
	sorriso();
	triste();
	cadeado();
	asterisco();
	mostrar_saudacao();
	delay_s(3);
	mostrar_senha_invalida();
	LATCbits.LATC2 = 0;
	LATBbits.LATB7 = 1;
	delay_s(3);
	mostrar_acesso_liberado();
	LATBbits.LATB7 = 0;
	LATCbits.LATC2 = 1;

	while(1){

	}
}