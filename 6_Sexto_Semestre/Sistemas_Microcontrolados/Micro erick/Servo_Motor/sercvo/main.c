#include <msp430.h>


void ini_Timer0_debouncer(void);
void ini_Timer1_PWM_centro(void);
void uni_Ucon0(void);
void ini_P1_P2(void);






int main(void){

    ini_Timer0_debouncer();
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


    if((~P1IN) & BIT4){
        if((~P1IN) & BIT5){//Verifica o sentido da rotação do encoder
            if(TA1CCR1 > 2000)
                TA1CCR1 -= 200;//Diminui de 0,5%
        }
        else{
            if(TA1CCR1 < 4000)
                TA1CCR1 += 200;//Aumenta de 0,5%
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


    TA1CTL = TASSEL1 +  MC0;// Sel. UP, f= 40 khz

    TA1CCTL0 = 0; // Opcional, uma vez que o Mod. 0 não geral sinal

                                                  //pedir explicação, tentei passar para a porta p2.4 e não deu certo
    TA1CCTL1 = OUTMOD0 + OUTMOD1 + OUTMOD2;       //configurando o modo de saída do módulo 1 do Timer1_A, saida 111 é ideal PWM


    TA1CCR0 = 39999; // Período/Frequência do sinal 50h.
    TA1CCR1 = 1999; // Rca -> 5%


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


     P2SEL |= BIT1;          // gerando apenas um sinal pwm na saida 4 do micro
     P2DIR = 0xFF;
     P2OUT = 0;


}
