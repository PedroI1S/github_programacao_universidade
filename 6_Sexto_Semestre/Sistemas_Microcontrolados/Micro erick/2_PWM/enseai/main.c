#include <msp430.h>


void ini_Timer0_debouncer(void);
void ini_Timer1_PWM_centro(void);
void uni_Ucon0(void);
void ini_P1_P2(void);


int main(void){
2
;    ini_Timer0_debouncer();
    ini_Timer1_PWM_centro();
    uni_Ucon0();
    ini_P1_P2();


    do{

        //Loop Infinito

    }while(1);
}



#pragma vector=TIMER0_A0_VECTOR
__interrupt void RTI_M0_TimerA0(void){

    TA0CTL &= ~MC0;        // Para o Timer0 após a contagem

    if ((~P1IN) & BIT4) {  // Botão em P1.4 pressionado

            // Supomos que o período do PWM está em TA1CCR0
            unsigned int periodo = TA1CCR0;

            // Calcula incremento de 10%
            unsigned int delta = periodo / 10;

            if (P1IN & BIT5) {  // Sentido horário
                if (TA1CCR1 + delta <= periodo)
                    TA1CCR1 += delta;
                if (TA1CCR2 >= delta)
                    TA1CCR2 -= delta;
            } else {            // Sentido anti-horário
                if (TA1CCR2 + delta <= periodo)
                    TA1CCR2 += delta;
                if (TA1CCR1 >= delta)
                    TA1CCR1 -= delta;
            }
        }

        P1IFG &= ~BIT4;  // Limpa flag de P1.4
        P1IE |= BIT4;    // Reabilita interrupção de P1.4


} // FIM da RTI do Módulo 0 do TIMER 0



#pragma vector=PORT1_VECTOR
__interrupt void RTI_P1(void){

    // A Limpeza da Flag de Int. NÃO é Necessária!

    P1IE &= ~BIT4; // Desabilita Int. de P1.3

    TA0CTL |= MC0; // Ini. TIMER 0 p/ t_deb ~ 2ms, Modo de contagem UP.

}


void ini_Timer1_PWM_centro(void){


    //Duvida
    //ideal ficar mais proximos dos 65 mil?
    //nos MC0 e MC1

    TA1CTL = TASSEL1 + ID1 +  MC0 + MC1;// Sel. SMCLK. Contador UP/DOWN!  clocl 2mhz/1 = 2000khz

    TA1CCTL0 = 0; // Opcional, uma vez que o Mod. 0 não geral sinal

    TA1CCTL1 = OUTMOD1; // Modo saída 1: INVERTER/RESETAR
    TA1CCTL2 = OUTMOD1; // Modo saída 2: INVERTER/RESETAR

    TA1CCR0 = 2499; // Período/Frequência do sinal 100hz ducida nos 100hz
    TA1CCR1 = 2250; // Rca -> 90%   para 99%  2475
    TA1CCR2 = 250; // Rcb -> 10%    para 1% = 25

}


void ini_Timer0_debouncer(void){

    //Precisa do ID1 aqui? clock 2 mega hz


    TA0CTL = TASSEL1;
    TA0CCTL0 = CCIE;
    TA0CCR0 = 3999;

}




void uni_Ucon0(void){

    WDTCTL = WDTPW | WDTHOLD;    // stop watchdog timer

    DCOCTL  = CALDCO_16MHZ;      //Configura o DCO (Digitally Controlled Oscillator)
    BCSCTL1 = CALBC1_16MHZ;      //Complementa a configuração do DCO
    BCSCTL2 = DIVS0 + DIVS1;     //Define o divisor de clock para o SMCLK. divide 16 mega por 8 que dar 2 mega
    BCSCTL3 = XCAP0 + XCAP1;     //Define a capacitância de carga para o oscilador LFXT1, 32768 hz


    while(BCSCTL3 & LFXT1OF);    //Aguarda até que o oscilador de baixa frequência (LFXT1) estabilize.     //precisa pq ta usando o cristal, e se não tiver isso ele segura a cpu aqui



    __enable_interrupt();

}




void ini_P1_P2(void){

     P1DIR = ~(BIT4 + BIT5);
     P1REN = BIT4 + BIT5;
     P1OUT = BIT4 + BIT5;
     P1IES = BIT4;          //Borda de descida so na chave B, como mostra o exemplo.
     P1IFG = 0;
     P1IE  = BIT4;


     P2SEL |= BIT1 + BIT4;
     P2DIR = 0xFF;
     P2OUT = 0;


}
