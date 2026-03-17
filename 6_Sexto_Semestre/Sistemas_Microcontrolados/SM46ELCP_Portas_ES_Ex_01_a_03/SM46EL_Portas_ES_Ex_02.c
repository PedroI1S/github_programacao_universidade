/* ******************************************************************************
Exemplo 2 - Portas E/S - Entrada Digital sem interrupcao para controlar
                         qual led vai piscar (VD ou VM)
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

    while(1){
        // Super loop

        /* Verificar chave S2 - P1.3 - entrada com resistor de pull-up

                          ___Vdd
                           |
                          | | R pull-up
                          | |
                           |
                           |
              ----|P1.3|------ > Chave nao-pressionada: Vdd
             |                 > Chave PRESSIONADA: 0 V
             |
              \ S2
             |
            ---
             -

             P1IN - Fornece o estado da(s) entrada(s)

             bit    7  6  5  4    3  2  1  0
             P1IN   X  X  X  X    Y  X  X  X   
             BIT3   0  0  0  0    1  0  0  0 
                  ----------------------------- AND b-a-b
                    0  0  0  0    Y  0  0  0  --> Chave NAO-pressionada Y=1 (Entraria no if..)
             
             ~P1IN /X /X /X /X   /Y /X /X /X
              BIT3  0  0  0  0    1  0  0  0 
                  ----------------------------- AND b-a-b
                    0  0  0  0   /Y  0  0  0  --> Chave PRESSIONADA Y=0 .:. /Y = 1 (ENTRA no if..)

            if( (~P1IN) & BIT3  ){
                // Entra no if se a chave for PRESSIONADA
                
            }
              
        
        */

      if( (~P1IN) & BIT3  ){
          /* Piscar LED VD (P1.6)
              P1OUT ^= BIT6;  // Alterna estado do LED VD
          */
          P1OUT ^= BIT6; 
          P1OUT &= ~BIT0; // Deixa LED VM apagado
      }else{
          // Chave NAO-PRESSIONADA: Alterna o estado do LED VM
          P1OUT ^= BIT0;
          P1OUT &= ~BIT6; // Deixa LED VD apagado
      }

      for(i=0; i < 50000; i++){ // Delay aprox. 500 ms
        // Nao faz nada
      }


    }
} 
//------------------------------------------------------------------------

void ini_P1_P2(void){
	/*	Configuracao da PORTA 1
			-> P1.0 - LED VM - saida digital em nivel baixo.
			-> P1.6 - LED VD - saida digital em nivel baixo.
			-> P1.3 - S2 - entrada com resistor de pull-up.
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
		

		bits	7  6  5  4    3  2  1  0
		P1
		
	*/
	P1DIR = BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	P1REN = BIT3;
	P1OUT = BIT3;
	
}




