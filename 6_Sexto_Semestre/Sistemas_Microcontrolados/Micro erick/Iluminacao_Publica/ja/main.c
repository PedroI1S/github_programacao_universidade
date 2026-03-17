#include <msp430.h>
#include <stdio.h>

#define ADC_MIN     906  // Valor ADC para pouca luz (precisa MAIS LED)
#define ADC_MAX     1005 // Valor ADC para muita luz (precisa MENOS LED)
#define PWM_STEP    100  // Passo maior para resposta mais rápida
#define PWM_MIN     200  // PWM mínimo para evitar LED muito fraco
#define PWM_MAX     19000 // PWM máximo (95% do período)
#define SENSOR_CANAL     INCH_5     // Canal A5
#define DEBOUNCE_TIME   20000  // Tempo de debounce em ciclos de SMCLK

volatile unsigned int ADC_vetor[16];
volatile unsigned char sistema_ligado = 0;  // Flag para controlar se o sistema está ativo
volatile unsigned char debounce_ativo = 0;  // Flag para controle de debounce
volatile unsigned int leitura_sensor = 0;   // Última leitura do sensor
unsigned char i = 0;

// --- Protótipos ---
void ini_uCon(void);
void ini_P1_P2(void);
void ini_Timer0_ADC(void);
void ini_Timer1_PWM(void);
void ini_ADC10(void);
void Ini_USCI_UART(void);

// ==============================================================================
// FUNÇÃO PRINCIPAL
// ==============================================================================
int main(void)
{
    // Primeiro, inicialize TUDO
    ini_uCon();
    ini_P1_P2();
    ini_Timer0_ADC();
    ini_Timer1_PWM();
    ini_ADC10();
    Ini_USCI_UART();

    // SÓ DEPOIS de tudo configurado, habilite as interrupções
    __enable_interrupt();

    while (1) {
        // Agora sim, entre em modo de baixo consumo
        __low_power_mode_0();
    }
}

// ==============================================================================
// INICIALIZAÇÕES
// ==============================================================================

void ini_uCon(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    DCOCTL = CALDCO_8MHZ;
    BCSCTL1 = CALBC1_8MHZ;
    BCSCTL2 = DIVS0;  // SMCLK = DCO/2 = 4MHz
    BCSCTL3 = XCAP0 + XCAP1;

    while(BCSCTL3 & LFXT1OF);
}

void ini_P1_P2(void)
{
    // Botão S2 (P1.3) como entrada com pull-up e interrupção
    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;
    P1IES |= BIT3;
    P1IFG &= ~BIT3;
    P1IE |= BIT3;

    // Sensor (P1.5) como entrada analógica
    P1SEL |= BIT5;
    P1DIR &= ~BIT5;

    // UART (P1.1 e P1.2)
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    // Saída PWM (P2.1) para o Timer1_A
    P2DIR |= BIT1;
    P2SEL |= BIT1;
}

void ini_Timer0_ADC(void)
{
    // Usar a configuração original que funcionou
    TA0CTL = TASSEL1 | MC0 | ID0 + ID1;  // Mantém configuração original
    TA0CCR0 = 49999; // Gera interrupção a cada 50000 / 500kHz = 0.1s (10 Hz)

    // Configura canal 1 para gerar o trigger para o ADC (OUTMOD_3 = set/reset)
    TA0CCTL1 = OUTMOD1 + OUTMOD0;  // Mantém configuração original
    TA0CCR1 = 25000; // Pulso com 50% de duty cycle

    // Adiciona canal 2 para debounce do botão
    TA0CCTL2 = 0;  // Inicialmente desabilitado
    TA0CCR2 = DEBOUNCE_TIME;
}

void ini_Timer1_PWM(void)
{
    // Mantém configuração original que funcionou
    TA1CTL = TASSEL1 | MC0;  // Configuração original
    TA1CCTL1 = OUTMOD0 + OUTMOD1 + OUTMOD2; // Modo PWM Reset/Set original
    TA1CCR0 = 19999;     // Período para 200 Hz (com SMCLK = 4 MHz)
    TA1CCR1 = 0;         // Inicia com LED desligado
}

void ini_ADC10(void)
{
    // Mantém configuração original que funcionou
    ADC10CTL0 = SREF0 + ADC10SHT0 + ADC10SHT1 + REFON + ADC10ON + ADC10IE;
    ADC10CTL1 = INCH0 + INCH2 + CONSEQ1 + ADC10SSEL0 + ADC10SSEL1 + SHS0 + ADC10DIV0;

    ADC10AE0 = BIT5;
    ADC10DTC1 = 16;

    ADC10SA = (unsigned int)ADC_vetor;
    // Não inicia o ADC ainda - só quando o sistema for ligado
}

void Ini_USCI_UART(void)
{
    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 = 0;
    UCA0CTL1 = UCSSEL_2 + UCSWRST;  // SMCLK + reset

    UCA0BR0 = 0xA0;  // 9600 baud com 4MHz
    UCA0BR1 = 0x01;
    UCA0MCTL = 0;
    UCA0CTL1 &= ~UCSWRST;  // Libera UART
}

// ==============================================================================
// INTERRUPÇÕES
// ==============================================================================

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    unsigned long sum = 0;
    unsigned int media = 0;
    int i = 0;

    // Só processa se o sistema estiver ligado
    if (!sistema_ligado) {
        ADC10CTL0 &= ~(ENC);
        ADC10SA = (unsigned int)&ADC_vetor[0];
        ADC10CTL0 |= ENC;
        return;
    }

    ADC10CTL0 &= ~(ENC);

    // Calcula média das 16 amostras
    for(i=0; i < 16; i++){
        sum += ADC_vetor[i];
    }
    media = sum >> 4;  // Divisão por 16
    leitura_sensor = media;  // Armazena para debug

    // LÓGICA DE CONTROLE MELHORADA:
    // - Menos luz externa (valor ADC baixo) = MAIS potência no LED
    // - Mais luz externa (valor ADC alto) = MENOS potência no LED

    if (media < ADC_MIN) {
        // POUCA LUZ EXTERNA - AUMENTA LED
        if (TA1CCR1 < (PWM_MAX - PWM_STEP)) {
            TA1CCR1 += PWM_STEP;
        } else {
            TA1CCR1 = PWM_MAX; // Satura no máximo
        }
    }
    else if (media > ADC_MAX) {
        // MUITA LUZ EXTERNA - DIMINUI LED
        if (TA1CCR1 > (PWM_MIN + PWM_STEP)) {
            TA1CCR1 -= PWM_STEP;
        } else {
            TA1CCR1 = PWM_MIN; // Satura no mínimo
        }
    }
    // Se média está entre ADC_MIN e ADC_MAX, mantém PWM atual (zona morta)

    ADC10SA = (unsigned int)&ADC_vetor[0];
    ADC10CTL0 |= ENC;
}

// INTERRUPÇÃO DO BOTÃO P1.3 (com debounce)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (P1IFG & BIT3) {
        P1IFG &= ~BIT3;  // Limpa flag

        // Se não está em processo de debounce, inicia o debounce
        if (!debounce_ativo) {
            debounce_ativo = 1;
            TA0CCR2 = TA0R + DEBOUNCE_TIME;  // Configura tempo de debounce
            TA0CCTL2 |= CCIE;  // Habilita interrupção do timer para debounce
        }
    }
}

// INTERRUPÇÃO DO TIMER0 - Canal 2 (Debounce)
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void)
{
    switch (TA0IV) {
        case 2:  // Canal 1 (trigger ADC)
            break;
        case 4:  // Canal 2 - Debounce
            TA0CCTL2 &= ~CCIE;  // Desabilita interrupção do debounce
            debounce_ativo = 0;

            // Verifica se o botão ainda está pressionado após debounce
            if (!(P1IN & BIT3)) {
                // Toggle do sistema
                sistema_ligado = !sistema_ligado;

                if (sistema_ligado) {
                    // Liga o sistema
                    ADC10CTL0 |= ENC;  // Habilita ADC
                    TA1CCR1 = 5000;    // Inicia PWM com duty cycle médio
                } else {
                    // Desliga o sistema
                    ADC10CTL0 &= ~ENC; // Desabilita ADC
                    TA1CCR1 = 0;       // Desliga PWM completamente
                }
            }
            break;
        default:
            break;
    }
}
