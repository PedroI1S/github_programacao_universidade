/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430G2xx3 Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430G2xx3
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  E. Chen
//  Texas Instruments, Inc
//  May 2018
//  Built with CCS Version 8.0 and IAR Embedded Workbench Version: 7.11
//******************************************************************************

#include <msp430.h>

void ini_P1_P2(void);

void main(void)
{
    unsigned long i = 0;
    WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer

    __enable_interrupt();

    ini_P1_P2();

    while(1)
    {
        // Programa principal
        for(i=0; i<100000;i++){
          // vazio
        }
        P1OUT ^= BIT0;

    }
}
//-------------------------------------------------

#pragma vector=PORT1_VECTOR
__interrupt void RTI_Porta_1(void){
    // Limpeza de flag
    P1IFG &= ~BIT3;

    P1OUT ^= BIT6; // Alterna o estado do led VERDE

}



void ini_P1_P2(void){
/* Inicializacao das Portas 1 e 2
PORTA 1
    - P1.0 = led vm: saida digital em nivel baixo
    - P1.3 = chave S2: entrada digital com resistor de pull-up, interrupcao por borda de descida
    - P1.6 = led vd: saida digital em nivel baixo
    - P1.x = N.C.: saidas em nivel baixo

  P1DIR = 0b11110111; = 0xF7; = ~BIT3; = BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
  P1REN = BIT3;
                  ----> bit 3: configura funcao do resistor (pull-up)
                 |
  P1OUT = 0b0000 1 000; = BIT3;

  P1IES = BIT3;
  P1IFG = 0;
  P1IE = BIT3;
*/
    P1DIR = ~BIT3;
    P1REN = BIT3;
    P1OUT = BIT3;

    P1IES = BIT3;
    P1IFG = 0;
    P1IE = BIT3;

/* PORTA 2
    - P2.X = N.C. - saidas em nivel baixo
    --> Pinos 18 e 19? manter XIN e XOUT? Mudar funcao para P2.6 e P2.7

    P2DIR = 0xFF; =255; = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
    P2OUT = 0x00;

    >>> Mudar funcoes dos pinos 18 e 19. Conforme datasheet:
    P2SEL = 0x00; &= ~(BIT6 + BIT7);
    P2SEL2 = nao precisa alterar
*/
    P2DIR = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
    P2OUT = 0x00;
    P2SEL &= ~(BIT6 + BIT7);
}







