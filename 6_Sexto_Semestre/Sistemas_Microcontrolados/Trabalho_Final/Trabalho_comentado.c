/* ****************************************************************************
 * Universidade Tecnologica do Parana - UTFPR campus Pato Branco.
 * Departamento Academico de Eng. Eletrica - DAELE
 * SM46EL/CP - Sistemas Microcontrolados
 * * PROJETO FINAL: RADAR ULTRASSÔNICO "GOLD EDITION"
 * (MSP430 + HC-SR04 + Servo + MAX7219)
 *
 * Especificacoes:
 * - Servo Motor:
 * -> Timer 0 (TA0.1) - P1.2
 * -> PWM 50Hz (20ms)
 * -> Controle suave de posicao (1000 a 5000 ticks)
 *
 * - Sensor Ultrassonico HC-SR04:
 * -> Trigger: P2.0 (Gatilho 10us)
 * -> Echo: P2.1 (Timer 1 - Capture CCI1A)
 * -> Leitura via Interrupcao (Timer 1)
 *
 * - Matriz de LEDs (MAX7219):
 * -> Interface SPI (USCI_B0)
 * -> P1.5 (CLK), P1.7 (SIMO), P1.4 (CS)
 *
 * - Interface:
 * -> Botao S2 (P1.3): Inicia/Pausa
 *
 * Data: 12/12/2025.
 ****************************************************************************/

#include <msp430.h>
#include <stdint.h>

// --- Definicoes de Hardware ---
#define CS_PIN BIT4    // P1.4
#define BTN_PIN BIT3   // P1.3
#define TRIG_PIN BIT0  // P2.0
#define ECHO_PIN BIT1  // P2.1 (TA1.1)
#define SERVO_PIN BIT2 // P1.2 (TA0.1)

// --- Variaveis Globais ---
volatile unsigned int distancia_cm = 0;
volatile unsigned int tempo_inicio = 0;
volatile unsigned int tempo_fim = 0;
volatile unsigned char radar_ativo = 0; // 0 = Pausado, 1 = Rodando
volatile unsigned int posicao_atual_servo = 1000;

// --- Prototipos das Funcoes de Inicializacao ---
void ini_uCon(void);
void ini_P1_P2(void);
void ini_Timer0_Servo(void);
void ini_Timer1_Sensor(void);
void ini_USCI_B0_SPI(void);

// --- Prototipos das Funcoes Auxiliares ---
void servo_mover_suave(unsigned int angulo_graus);
void matrix_plot(int x, int y);
void matrix_limpar_coluna(int x);
void matrix_enviar(uint8_t reg, uint8_t dado);
void spi_send(uint8_t dado);
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);

/**
 * main.c
 */
void main(void) {
  // 1. Inicializacao do Sistema
  ini_P1_P2();
  ini_uCon();
  ini_Timer0_Servo();
  ini_Timer1_Sensor();
  ini_USCI_B0_SPI();

  // Animacao Inicial (Check de Matriz)
  int i;
  for (i = 0; i < 16; i++) {
    matrix_plot(i, i % 8);
    delay_ms(30);
  }
  // Limpa tela
  for (i = 1; i <= 8; i++)
    matrix_enviar(i, 0x00);

  // Loop Infinito
  while (1) {
    if (radar_ativo) {
      // --- MODO RADAR: Varredura Ida e Volta ---

      int sentido; // 0 = Ida, 1 = Volta
      for (sentido = 0; sentido < 2; sentido++) {

        int inicio = (sentido == 0) ? 0 : 15;
        int fim = (sentido == 0) ? 16 : -1;
        int passo = (sentido == 0) ? 1 : -1;

        int x;
        for (x = inicio; x != fim; x += passo) {
          if (!radar_ativo)
            break; // Sai se pausar

          // 1. Move Servo SUAVEMENTE
          // Mapeia Coluna (0-15) para Angulo (15 a 165 graus)
          int angulo = 15 + (x * 10);
          servo_mover_suave(angulo);

          // Delay para estabilizacao mecanica
          delay_ms(30);

          // 2. Leitura do Sensor HC-SR04
          distancia_cm = 0;
          P2OUT |= TRIG_PIN;
          __delay_cycles(160); // Gatilho de 10us
          P2OUT &= ~TRIG_PIN;

          // Espera eco retornar
          delay_ms(40);

          // 3. Atualiza Matriz de LEDs
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
      // --- MODO PAUSA ---
      servo_mover_suave(90);              // Centraliza suavemente
      __bis_SR_register(LPM0_bits + GIE); // Entra em modo Low Power
    }
  }
}
// --------------------------- FIM MAIN ------------------------

// RTI do Timer 1 (Capture) - Sensor Ultrassonico
#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR(void) {
  /* Precisa limpar flag de int?
   * R.: SIM/NAO dependendo do caso, mas o acesso ao TA1IV
   * limpa automaticamente a flag da interrupcao de maior prioridade.
   */
  switch (TA1IV) {
  case TA1IV_TACCR1: { // P2.1 (Echo) usa Canal 1 (CCI1A)
    unsigned int cap = TA1CCR1;

    // Verifica nivel do pino para saber se eh Borda de Subida ou Descida
    if (P2IN & ECHO_PIN) {
      tempo_inicio = cap;
    } else {
      tempo_fim = cap;
      unsigned long pulsos;

      // Calculo do delta T considerando overflow
      if (tempo_fim >= tempo_inicio)
        pulsos = tempo_fim - tempo_inicio;
      else
        pulsos = (0xFFFF - tempo_inicio) + tempo_fim;

      // Divisor 940 para obter cm em 16MHz
      // d = (pulsos * T_clk) / 58us
      unsigned long d = pulsos / 940;

      if (d < 400)
        distancia_cm = (unsigned int)d;
    }
    break;
  }
  }
}

// RTI da PORTA 1 - Botao S2
#pragma vector = PORT1_VECTOR
__interrupt void RTI_Porta_1(void) {
  // 1 - Verificar se foi P1.3
  if (P1IFG & BTN_PIN) {
    // Debounce simples via delay
    __delay_cycles(160000);

    if (!(P1IN & BTN_PIN)) {
      // Alterna estado do Radar
      radar_ativo = !radar_ativo;

      // Se ativou, acorda a CPU do LPM0
      if (radar_ativo)
        __bic_SR_register_on_exit(LPM0_bits);
    }

    // Limpar flag de INT
    P1IFG &= ~BTN_PIN;
  }
}

// ---------------- FUNCOES DE INICIALIZACAO ----------------

void ini_uCon(void) {
  WDTCTL = WDTPW | WDTHOLD; // Para Watchdog

  // Configuracao do Clock para 16 MHz
  DCOCTL = CALDCO_16MHZ;
  BCSCTL1 = CALBC1_16MHZ;
  BCSCTL2 = DIVS0;         // SMCLK = DCO = 16 MHz
  BCSCTL3 = XCAP0 + XCAP1; // Capacitor cristal (se houver)

  // Aguarda estabilizacao do oscilador (caso use LFXT1)
  while (BCSCTL3 & LFXT1OF)
    ;

  __enable_interrupt(); // Habilita interrupcoes globais (GIE)
}

void ini_P1_P2(void) {
  /* PORTA 1
   * -> P1.2 - Servo (TA0.1) - Saida/Funcao Especial
   * -> P1.3 - Botao S2 - Entrada Pull-Up + INT Borda Descida
   * -> P1.4 - SPI CS - Saida
   * -> P1.5 - SPI CLK - Funcao Especial
   * -> P1.7 - SPI SIMO - Funcao Especial
   */
  P1DIR = 0xFF; // Inicialmente tudo saida (boa pratica)
  P1OUT = 0;

  // Config S2 (P1.3)
  P1DIR &= ~BTN_PIN;
  P1REN |= BTN_PIN;
  P1OUT |= BTN_PIN; // Pull-up
  P1IES |= BTN_PIN; // Borda de descida
  P1IE |= BTN_PIN;  // Habilita INT
  P1IFG &= ~BTN_PIN;

  // Config Servo (P1.2)
  P1DIR |= SERVO_PIN;
  P1SEL |= SERVO_PIN; // Seleciona funcao periferico (TA0.1)

  // Config SPI Matriz (P1.4, P1.5, P1.7)
  P1DIR |= CS_PIN;
  P1OUT |= CS_PIN;       // CS inicia alto
  P1SEL |= BIT5 + BIT7;  // CLK e SIMO
  P1SEL2 |= BIT5 + BIT7; // Necessario para USCI_B0

  /* PORTA 2
   * -> P2.0 - Trigger Sensor - Saida
   * -> P2.1 - Echo Sensor (TA1.1) - Entrada/Funcao Especial
   */
  P2DIR = 0xFF;
  P2OUT = 0;

  // Config Sensor
  P2DIR |= TRIG_PIN; // P2.0 Saida
  P2OUT &= ~TRIG_PIN;
  P2DIR &= ~ECHO_PIN; // P2.1 Entrada
  P2SEL |= ECHO_PIN;  // Seleciona funcao Timer (CCI1A)
}

void ini_Timer0_Servo(void) {
  /* TIMER 0 - Controle do Servo Motor
   * -> f_pwm = 50 Hz _|_ T = 20 ms
   *
   * CONTADOR:
   * - Clock: SMCLK = 16 MHz
   * - Divisor (ID): /8
   * - F_timer = 2 MHz (0,5 us por tick)
   * - Modo: UP
   *
   * MODULO 0: Periodo
   * - TA0CCR0 = (20ms / 0,5us) - 1 = 40000 - 1 = 39999 (Aprox 40000)
   *
   * MODULO 1: PWM (P1.2)
   * - Modo de saida: 7 (RESET/SET)
   * - TA0CCR1 = Variavel (1000 a 5000)
   */
  TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
  TA0CCTL0 = 0;
  TA0CCTL1 = OUTMOD_7;
  TA0CCR0 = 40000;
  TA0CCR1 = 1000; // Posicao inicial
}

void ini_Timer1_Sensor(void) {
  /* TIMER 1 - Leitura do Sensor (Capture)
   *
   * CONTADOR:
   * - Clock: SMCLK = 16 MHz
   * - Divisor: /1
   * - Modo: Continuous (Conta ate 0xFFFF e volta)
   *
   * MODULO 1 (P2.1): Capture Input
   * - CM_3: Captura em ambas as bordas (Subida e Descida)
   * - SCS: Sincrono
   * - CAP: Modo Captura
   * - CCIE: INT Habilitada
   */
  TA1CTL = TASSEL_2 + MC_2 + TACLR;
  TA1CCTL1 = CM_3 + CCIS_0 + SCS + CAP + CCIE;
}

void ini_USCI_B0_SPI(void) {
  /* USCI B0 - Modo SPI Master
   * -> Controle da Matriz MAX7219
   * -> Clock: SMCLK / 32 = 500 kHz
   * -> MSB First
   * -> Phase/Polarity ajustados para MAX7219 (UCCKPH)
   */
  UCB0CTL1 |= UCSWRST; // Reset logic

  UCB0CTL0 = UCMSB + UCMST + UCSYNC + UCCKPH;
  UCB0CTL1 |= UCSSEL_2; // SMCLK

  UCB0BR0 = 32; // Divisor de clock
  UCB0BR1 = 0;

  UCB0CTL1 &= ~UCSWRST; // Libera USCI

  // Inicializacao dos registradores MAX7219
  matrix_enviar(0x09, 0x00); // No Decode
  matrix_enviar(0x0A, 0x03); // Intensity
  matrix_enviar(0x0B, 0x07); // Scan Limit
  matrix_enviar(0x0C, 0x01); // Shutdown (Wake up)

  // Limpa Matriz
  int i;
  for (i = 1; i <= 8; i++)
    matrix_enviar(i, 0x00);
}

// ---------------- FUNCOES AUXILIARES ----------------

void servo_mover_suave(unsigned int angulo_graus) {
  if (angulo_graus > 180)
    angulo_graus = 180;

  // Converte Graus -> Ticks (Range 1000 a 5000)
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
    ; // Aguarda buffer TX vazio
  UCB0TXBUF = dado;
  while (UCB0STAT & UCBUSY)
    ; // Aguarda fim da transmissao
}

void matrix_enviar(uint8_t reg, uint8_t dado) {
  P1OUT &= ~CS_PIN;
  spi_send(reg);
  spi_send(dado); // Modulo 2
  spi_send(reg);
  spi_send(dado); // Modulo 1
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
    __delay_cycles(16000); // Para 16MHz
}

void delay_us(unsigned int us) {
  while (us--)
    __delay_cycles(16);
}