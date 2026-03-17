/* ******************************************************************************
Exemplo 2 - Portas E/S - Entrada Digital COM interrupcao para alternar
                         o estado do LED VD, enquanto o VM pisca
//******************************************************************************/

#include <msp430.h>

void ini_P1_P2(void);

void main(void)
{
    /* Tipo da variavel i
      char  -127 -> 128                   |  1 Byte
      unsigned char  0 -> 255             |  1 Byte
      int  -32767 -> 32768                |  2 Bytes
      unsigned int  0 -> 65530            |  2 Bytes
      long  -2...bilhoes -> +2...bilhoes  |  4 Bytes
      unsigned long   0 -> 4..bilhoes     |  4 Bytes
    */
    unsigned int i = 0;

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    ini_P1_P2();

    __enable_interrupt();

    while(1){
      // Super loop
 
      P1OUT ^= BIT0; // Alterna o estado do LED VM

      for(i=0; i < 50000; i++){ // Delay aprox. 500 ms
        // Nao faz nada
      }
    }
} 
//------------------------------------------------------------------------

// RTI da PORTA 1
#pragma   vector=PORT1_VECTOR
__interrupt void  RTI_da_Porta_1(void){
    // --> Limpar a flag de P1.3
    P1IFG &= ~BIT3;

    P1OUT ^= BIT6; // Alterna estado do LED VD
}



void ini_P1_P2(void){
	/*	Configuracao da PORTA 1
			-> P1.0 - LED VM - saida digital em nivel baixo.
			-> P1.6 - LED VD - saida digital em nivel baixo.
			-> P1.3 - S2 - entrada com resistor de pull-up e INT. HABILITADA por borda de DESCIDA.
			-> P1.x - N.C. - saidas em nivel baixo.
			
			
		bits	7  6  5  4    3  2  1  0
		P1DIR   1  1  1  1    0  1  1  1 = 0xF7;
		
		P1DIR = BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7; ou = 0xF7; ou = 248; ou 0xb11110111;

		bits	7  6  5  4    3  2  1  0
		P1REN	0  0  0  0    1  0  0  0  = 0x08;

		P1REN = BIT3; ou = 0x08; ou = 8; ou = 0b0000100;		

							   ---> P1.3 - entrada com resistor de pull-up (0: pull-down \  1: pull-up)
							  |
		bits	7  6  5  4    3  2  1  0
		P1OUT	0  0  0  0    1  0  0  0
		
		P1OUT = BIT3; ou = 0x08; ou = 8; ou = 0b0000100;
		
    P1IES - Seleciona borda de interropcao (0 -> borda de subida .:. 1 -> borda de descida)
		bits	  7  6  5  4    3  2  1  0
		P1IES   0  0  0  0    1  0  0  0  = 0x08;

    P1IES = BIT3;

    P1IFG - Flags de Interrupcao
		bits	  7  6  5  4    3  2  1  0
		P1IFG   0  0  0  0    0  0  0  0 = 0x00

    P1IFG = 0;

    P1IE - Habilita Int. da Entrada(s)
		bits	  7  6  5  4    3  2  1  0
		P1IE    0  0  0  0    1  0  0  0  = 0x08

    P1IE = BIT3;
	*/
	P1DIR = BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	P1REN = BIT3;
	P1OUT = BIT3;

  P1IES = BIT3;
	P1IFG = 0;
  P1IE = BIT3;
}




