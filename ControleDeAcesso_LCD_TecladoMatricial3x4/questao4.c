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
void caracteres_especiais(void);


//Mostrar mensagens no display
void mostrar_LCD();
void mostrar_saudacao(void);
void mostrar_senha_invalida(void);
void mostrar_acesso_liberado(void);

//Teclado
char varre_teclado(void);

#define comando_dado LATCbits.LATC0
#define pulso LATCbits.LATC1
#define linha1 PORTBbits.RB3
#define linha2 PORTBbits.RB2
#define linha3 PORTBbits.RB1
#define linha4 PORTBbits.RB0
#define coluna1 LATBbits.LATB4
#define coluna2 LATBbits.LATB5
#define coluna3 LATBbits.LATB6
#define LED LATBbits.LATB7


char tecla;
char senha[4] = {'0','0','0','0'};
char chave[4] = {'1','4','1','7'};
int cadeado = 0;
int contador = 0;
int i = 0;
int passou = 0;
int verificador = 0;



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


void caracteres_especiais(){

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

void mostrar_LCD(){
	delay_ms(300);
	envia_dado(3);
}


char varre_teclado(void){
	while(passou == 0){
			coluna1 = 0;
			coluna2 = 1;
			coluna3 = 1;
		
			if(!linha1){
				while(!linha1){passou = 1;};
				contador++;
				return '1';
			}
			if(!linha2){
				while(!linha2){passou = 1;};
				contador++;
				return '4';
			}
			if(!linha3){
				while(!linha3){passou = 1;};
				contador++;
				return '7';
			}
			if(!linha4){
				while(!linha4){passou = 1;};
				contador++;
				return '*';
			}
	delay_ms(10);
			coluna1 = 1;
			coluna2 = 0;
			coluna3 = 1;
		
			if(!linha1){
				while(!linha1){passou = 1;};
				contador++;
				return '2';
			}
			if(!linha2){
				while(!linha2){passou = 1;};
				contador++;
				return '5';
			}
			if(!linha3){
				while(!linha3){passou = 1;};
				contador++;
				return '8';
			}
			if(!linha4){
				while(!linha4){passou = 1;};
				contador++;
				return '0';
			}
	delay_ms(10);
			coluna1 = 1;
			coluna2 = 1;
			coluna3 = 0;
		
			if(!linha1){
				while(!linha1){passou = 1;};
				contador++;
				return '3';
			}
			if(!linha2){
				while(!linha2){passou = 1;};
				contador++;
				return '6';
			}
			if(!linha3){
				while(!linha3){passou = 1;};
				contador++;
				return '9';
			}
			if(!linha4){
				while(!linha4){passou = 1;};
				contador++;
				return '#';
			}
	delay_ms(10);
	}
}



void main (void)

{	
	//área de configuração (só roda uma vez)
	ADCON1 = 0B00001111; // Seta portas 0, 1, 2 e 3 como analogicas

	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;	//OSC = 8MHz (interno)
	
	//BIT=1 -> PORTA DE ENTRADA, BIT=0 -> PORTA DE SAÍDA
	TRISB=0B00001111;
	TRISC=0B00000000;	 
	TRISD=0B00000000;
	

	inicializar();
	LATBbits.LATB7 = 1;
	LATCbits.LATC2 = 0;
	caracteres_especiais();
	mostrar_saudacao();
	
	while(1){ 
		if (varre_teclado()){
			break;
		}
	}

	while(1){
		envia_comando(0b00000001);
		envia_comando(0x80);
		envia_dado(2);
		if(LED == 1){
			delay_ms(600);
			LED = 0;
		}
		tecla = varre_teclado();
		delay_ms(10);
		passou = 0;
		senha[0] = tecla;
		while(contador == 1){
			envia_comando(0x82);
			mostrar_LCD();
			tecla = varre_teclado();
			delay_ms(10);
			passou = 0;
			senha[1] = tecla;
			while(contador == 2){
				mostrar_LCD();
				tecla = varre_teclado();
				delay_ms(10);
				passou = 0;
				senha[2] = tecla;
				while(contador == 3){
					mostrar_LCD();
					tecla = varre_teclado();
					delay_ms(10);
					passou = 0;
					senha[3] = tecla;
					while(contador == 4){
						mostrar_LCD();
						verificador = 0;
						for(i=0; i<4; i++){
							if(chave[i]==senha[i]){
								verificador++;
							}
						}
						contador = 0;
						if(verificador == 3){
							LATCbits.LATC2 = 1;
							inicializar();
							mostrar_acesso_liberado();
							delay_s(2);
							
						}
						else{
							LATBbits.LATB7 = 1;
							inicializar();
							mostrar_senha_invalida();
							delay_s(2);
						}	
					};
				};
			};
		};
		break;
	};

}