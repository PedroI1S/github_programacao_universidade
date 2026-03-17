#include <msp430.h>

void ini_uCOn(void);
void ini_P1_P2(void);
void ini_Timer0(void);
void ini_ADC10(void);

float   v_in = 0.0;

unsigned int ADC10_vetor[64], soma = 0, media = 0;
unsigned char i = 0;

/**
 * main.c
 */
void main(void)
{
    ini_uCOn();
    ini_P1_P2();
    ini_Timer0();
    ini_ADC10();

    do{
      __bis_SR_register(LPM0_bits + GIE);
    }while(1);
}
//------------------------------

#pragma vector=ADC10_VECTOR
__interrupt void RTI_ADC10(void){

    ADC10CTL0 &= ~ENC;

    soma = 0;
    for(i=0; i<64; i++){
        soma = soma + ADC10_vetor[i];
    }
    media = soma/64;

    /* LDR quando com luz inscidente 1k ohms = 2,27V
     * LDR quando sem luz inscidente 500k ohms = 0.05V
     */

    v_in = (2.2 * (float)media)/1023.0;

    if(v_in <= 1){           //Se V menor que 1V liga led
        P1OUT |= BIT0;
    }else{
        P1OUT &= ~BIT0;
    }

    ADC10SA = (unsigned int)&ADC10_vetor[0];
    ADC10CTL0 |= ENC;
}


void ini_ADC10(void){

    ADC10CTL0 = SREF0 + REFOUT + REF2_5V + REFON + ADC10ON + ADC10IE + MSC;

    ADC10CTL1 = INCH0 + INCH2 + SHS0 + ADC10SSEL0 + ADC10SSEL1 + ADC10DIV0 + ADC10DIV1 + CONSEQ1;

    ADC10AE0 = BIT4 + BIT5;

    ADC10DTC1 = 64;

    ADC10SA = (unsigned int)&ADC10_vetor[0];

    ADC10CTL0 |= ENC + ADC10SC;
}

void ini_Timer0(void){
    /*IGUAL DO EXEMPLO FEITO EM AULA
     * fa = 10 Hz .:. Ta = 100 ms
     * --> O modulo 1 do Timer 0 vai gerar sinal PWM de gatilho
     * para disparar conversões do ADC a cada 100 ms (Ta).
     *
     * CONTADOR
     *      - Clock: SMCLK ~ 2 MHz
     *          - Fdiv: 4
     *      - Modo contador: UP
     *      - Int.: DESABILITADA
     *
     * MODULO 0
     *      - Funcao: comparacao (nativa)
     *      - TA0CCR0 = ( (2M/4) * 0,1) - 1 = 49.999
     *      - Int.: DESABILITADA
     *
     * MODULO 1
     *      - Funcao: comparacao (nativa)
     *      - TA0CCR1 = 24999;
     *      - Modo de saida: 7 (Reset/Set)
     *      - Int.: DESABILITADA
     */
    TA0CTL = TASSEL1 + ID1 + MC0;
    TA0CCTL1 = OUTMOD0 + OUTMOD1 + OUTMOD2;
    TA0CCR0 = 49999;
    TA0CCR1 = 24999;
}


void ini_P1_P2(void){

    P1DIR = 0xFF;
    P1OUT = 0;
    P2DIR = 0xFF;
    P2OUT = 0;
}


void ini_uCOn(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL2 = DIVS0 + DIVS1;
    BCSCTL3 = XCAP0 + XCAP1;

    while(BCSCTL3 & LFXT1OF);

    __enable_interrupt();
}
