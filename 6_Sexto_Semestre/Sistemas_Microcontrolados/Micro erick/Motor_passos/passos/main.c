#include <msp430.h>

void ini_uCOn(void);
void ini_p1_p2(void);
void ini_Timer_A0(void);
void ini_Timer_A1(void);



volatile unsigned int aux = 0;
volatile unsigned int tempo = 25000;


int main(void)
{
    ini_uCOn();
    ini_p1_p2();
    ini_Timer_A1();
    ini_Timer_A0();

    do{

    }while(1);

}

void ini_p1_p2(void){
    P1DIR = ~(BIT4 + BIT5);
    P1REN = BIT4 + BIT5;
    P1OUT = BIT4 + BIT5;

    P1IES = BIT4;
    P1IFG = ~BIT4;
    P1IE = BIT4;

    P2DIR = 0xFF;
    P2OUT =0;
}

void ini_uCOn(void){
    WDTCTL = WDTPW | WDTHOLD;

    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL2 = DIVS0 + DIVS1;
    BCSCTL3 = XCAP0 + XCAP1;

    while(BCSCTL3 & LFXT1OF);

    __enable_interrupt();
}

void ini_Timer_A0(void){
    TA0CTL = TASSEL1 + MC0;
    TA0CCTL0 = CCIE;
    TA0CCR0 = 3999;
}


void ini_Timer_A1(void){
    TA1CTL = TASSEL1 + MC0 + ID0 + ID1;
    TA1CCTL0 = CCIE;
    TA1CCR0 = tempo - 1;
}


#pragma vector=TIMER1_A0_VECTOR
__interrupt void RTI_Timer(void){
    if(aux == 0){
        P2OUT = BIT0;
        aux++;
    }
    else if (aux == 1){
        P2OUT = BIT1;
        aux++;
    }
    else if (aux == 2){
        P2OUT = BIT2;
        aux++;
    }
    else if (aux == 3){
        P2OUT = BIT3;
        aux=0;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void RTI_Porta_1(void){
    P1IFG &= ~BIT4;
    P1IE &= ~BIT4;
    TA0CTL |= MC0;

}

#pragma  vector=TIMER0_A0_VECTOR
__interrupt void RTI_M0_TA0(void){
    TA0CTL &= ~MC0;

    if((~P1IN) & BIT4){
        if(P1IN & BIT5){
            if(tempo > 1000)
                tempo -= 1000;
        }
        else{
            if(tempo < 25000)
                tempo += 1000;
        }
        TA1CCR0 = tempo - 1;
    }

    P1IFG &= ~BIT4;
    P1IE |= BIT4;
}
