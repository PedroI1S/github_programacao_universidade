//******************************************************************************
// SM46EL - PORTAS E/S - Exemplo 1: Pisca led VM
//******************************************************************************

#include <msp430.h>


void ini_P1_P2(void);


void main(void)
{
  unsigned long i = 0;
  // Inicializacao de PERIFERICOS
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
    
    ini_P1_P2();

    do{
      // Super loop
      P1OUT |= BIT0;  // Acende LED VM
      for(i=0; i<100000; i++){ // Delay ~ 1 s
        // Vazio
      }

      P1OUT &= ~BIT0;  // Apaga LED VM
      for(i=0; i<100000; i++){ // Delay ~ 1 s
        // Vazio
      }
      
    }while(1);
}
//--------------------------------------------------

void ini_P1_P2(void){
/* Inicializacao da Porta 1
    P1.0 -> LED VM: saida em nivel baixo (led apagado)
    P1.6 -> LED VD: saida em nivel baixo (led apagado)
    P1.x -> N.C.: saidas em nivel baixo.

    bit      7  6  5  4   3  2  1  0
    P1DIR    1  1  1  1   1  1  1  1  = 0xFF

    P1DIR = 0xFF; = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
    
    bit      7  6  5  4   3  2  1  0
    P1OUT    0  0  0  0   0  0  0  0  = 0x00 

    P1OUT = 0;

*/
P1DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
P1OUT = 0;

/* Inicializacao da Porta 2
    P2.x -> N.C.: saidas em nivel baixo.

    >>> Pinos 18 e 19: mudar funcao de XIN/XOUT para P2.6/P2.7
          P2SEL = 0x00;
          P2SEL = P2SEL & ~(BIT6 + BIT7);
          P2SEL &= ~(BIT6 + BIT7);
*/

// Mudar funcao dos pinos 18 e 19
  P2SEL &= ~(BIT6 + BIT7);
  P2DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
  P2OUT = 0x00; 

}
