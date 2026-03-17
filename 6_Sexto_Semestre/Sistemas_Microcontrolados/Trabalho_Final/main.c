#include <msp430.h>
#include <stdint.h>

#define CS_PIN BIT4
#define BTN_PIN BIT3
#define TRIG_PIN BIT0
#define ECHO_PIN BIT1
#define SERVO_PIN BIT2

volatile unsigned int distancia_cm = 0;
volatile unsigned int tempo_inicio = 0;
volatile unsigned int tempo_fim = 0;
volatile unsigned char radar_ativo = 0;
volatile unsigned int posicao_atual_servo = 1000;

void ini_uCon(void);
void ini_P1_P2(void);
void ini_Timer0_Servo(void);
void ini_Timer1_Sensor(void);
void ini_USCI_B0_SPI(void);

void servo_mover_suave(unsigned int angulo_graus);
void matrix_plot(int x, int y);
void matrix_limpar_coluna(int x);
void matrix_enviar(uint8_t reg, uint8_t dado);
void spi_send(uint8_t dado);
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);

void main(void) {
  ini_P1_P2();
  ini_uCon();
  ini_Timer0_Servo();
  ini_Timer1_Sensor();
  ini_USCI_B0_SPI();

  int i;
  for (i = 0; i < 16; i++) {
    matrix_plot(i, i % 8);
    delay_ms(30);
  }
  for (i = 1; i <= 8; i++)
    matrix_enviar(i, 0x00);

  while (1) {
    if (radar_ativo) {
      int sentido;
      for (sentido = 0; sentido < 2; sentido++) {

        int inicio = (sentido == 0) ? 0 : 15;
        int fim = (sentido == 0) ? 16 : -1;
        int passo = (sentido == 0) ? 1 : -1;

        int x;
        for (x = inicio; x != fim; x += passo) {
          if (!radar_ativo)
            break;

          int angulo = 15 + (x * 10);
          servo_mover_suave(angulo);

          delay_ms(30);

          distancia_cm = 0;
          P2OUT |= TRIG_PIN;
          __delay_cycles(160);
          P2OUT &= ~TRIG_PIN;

          delay_ms(40);

          matrix_limpar_coluna(x);

          if (distancia_cm > 2 && distancia_cm < 45) {
            int y = distancia_cm / 5;
            if (y > 7)
              y = 7;
            matrix_plot(x, y);
          }
        }
      }
    } else {
      servo_mover_suave(90);
      __bis_SR_register(LPM0_bits + GIE);
    }
  }
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR(void) {
  switch (TA1IV) {
  case TA1IV_TACCR1: {
    unsigned int cap = TA1CCR1;

    if (P2IN & ECHO_PIN) {
      tempo_inicio = cap;
    } else {
      tempo_fim = cap;
      int pulsos;

      if (tempo_fim >= tempo_inicio)
        pulsos = tempo_fim - tempo_inicio;

      int d = pulsos / 940;

      if (d < 400)
        distancia_cm = (unsigned int)d;
    }
    break;
  }
  }
}

#pragma vector = PORT1_VECTOR
__interrupt void RTI_Porta_1(void) {
  if (P1IFG & BTN_PIN) {
    __delay_cycles(160000);

    if (!(P1IN & BTN_PIN)) {
      radar_ativo = !radar_ativo;

      if (radar_ativo)
        __bic_SR_register_on_exit(LPM0_bits);
    }

    P1IFG &= ~BTN_PIN;
  }
}

void ini_uCon(void) {
  WDTCTL = WDTPW | WDTHOLD;

  DCOCTL = CALDCO_16MHZ;
  BCSCTL1 = CALBC1_16MHZ;
  BCSCTL3 = XCAP0 + XCAP1;

  while (BCSCTL3 & LFXT1OF)
    ;

  __enable_interrupt();
}

void ini_P1_P2(void) {
  P1DIR = 0xFF;
  P1OUT = 0;

  P1DIR &= ~BTN_PIN;
  P1REN |= BTN_PIN;
  P1OUT |= BTN_PIN;
  P1IES |= BTN_PIN;
  P1IE |= BTN_PIN;
  P1IFG &= ~BTN_PIN;

  P1DIR |= SERVO_PIN;
  P1SEL |= SERVO_PIN;

  P1DIR |= CS_PIN;
  P1OUT |= CS_PIN;
  P1SEL |= BIT5 + BIT7;
  P1SEL2 |= BIT5 + BIT7;

  P2DIR = 0xFF;
  P2OUT = 0;

  P2DIR |= TRIG_PIN;
  P2OUT &= ~TRIG_PIN;
  P2DIR &= ~ECHO_PIN;
  P2SEL |= ECHO_PIN;
}

void ini_Timer0_Servo(void) {
  TA0CTL = TASSEL1 + ID0 + ID1 + MC0 + TACLR;
  TA0CCTL0 = 0;
  TA0CCTL1 = OUTMOD0 + OUTMOD1 + OUTMOD2;
  TA0CCR0 = 40000;
  TA0CCR1 = 1000;
}

void ini_Timer1_Sensor(void) {
  TA1CTL = TASSEL1 + MC1 + TACLR;
  TA1CCTL1 = CM0 + CM1 + SCS + CAP + CCIE;
}

void ini_USCI_B0_SPI(void) {
  UCB0CTL1 |= UCSWRST;

  UCB0CTL0 = UCMSB + UCMST + UCSYNC + UCCKPH;
  UCB0CTL1 |= UCSSEL1;

  UCB0BR0 = 32;
  UCB0BR1 = 0;

  UCB0CTL1 &= ~UCSWRST;

  matrix_enviar(0x09, 0x00);
  matrix_enviar(0x0A, 0x03);
  matrix_enviar(0x0B, 0x07);
  matrix_enviar(0x0C, 0x01);

  int i;
  for (i = 1; i <= 8; i++)
    matrix_enviar(i, 0x00);
}

void servo_mover_suave(unsigned int angulo_graus) {
  if (angulo_graus > 180)
    angulo_graus = 180;

  unsigned int alvo_ticks = 1000 + ((unsigned long)angulo_graus * 4000 / 180);

  int passo = 15;

  if (alvo_ticks > posicao_atual_servo) {
    while (posicao_atual_servo < alvo_ticks) {
      posicao_atual_servo += passo;
      if (posicao_atual_servo > alvo_ticks)
        posicao_atual_servo = alvo_ticks;
      TA0CCR1 = posicao_atual_servo;
      delay_us(800);
    }
  } else {
    while (posicao_atual_servo > alvo_ticks) {
      posicao_atual_servo -= passo;
      if (posicao_atual_servo < alvo_ticks)
        posicao_atual_servo = alvo_ticks;
      TA0CCR1 = posicao_atual_servo;
      delay_us(800);
    }
  }
  TA0CCR1 = alvo_ticks;
}

void spi_send(uint8_t dado) {
  while (!(IFG2 & UCB0TXIFG))
    ;
  UCB0TXBUF = dado;
  while (UCB0STAT & UCBUSY)
    ;
}

void matrix_enviar(uint8_t reg, uint8_t dado) {
  P1OUT &= ~CS_PIN;
  spi_send(reg);
  spi_send(dado);
  spi_send(reg);
  spi_send(dado);
  P1OUT |= CS_PIN;
}

void matrix_plot(int x, int y) {
  uint8_t reg = (x % 8) + 1;
  uint8_t dado = (1 << y);

  P1OUT &= ~CS_PIN;
  if (x < 8) {
    spi_send(0);
    spi_send(0);
    spi_send(reg);
    spi_send(dado);
  } else {
    spi_send(reg);
    spi_send(dado);
    spi_send(0);
    spi_send(0);
  }
  P1OUT |= CS_PIN;
}

void matrix_limpar_coluna(int x) {
  uint8_t reg = (x % 8) + 1;
  P1OUT &= ~CS_PIN;
  if (x < 8) {
    spi_send(0);
    spi_send(0);
    spi_send(reg);
    spi_send(0);
  } else {
    spi_send(reg);
    spi_send(0);
    spi_send(0);
    spi_send(0);
  }
  P1OUT |= CS_PIN;
}

void delay_ms(unsigned int ms) {
  while (ms--)
    __delay_cycles(16000);
}

void delay_us(unsigned int us) {
  while (us--)
    __delay_cycles(16);
}