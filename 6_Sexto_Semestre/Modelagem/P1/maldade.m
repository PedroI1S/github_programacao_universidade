%% PROVA DE SISTEMAS DE CONTROLE - SCRIPT DE APOIO (VERSÃO ATUALIZADA)

clear; clc; close all;
s = tf('s');
fprintf('Script atualizado e pronto para os desafios da prova!\n');
fprintf('======================================================\n\n');

%% ========================================================================
%  0.A: IDENTIFICAÇÃO DE SISTEMA DE 1ª ORDEM (Resolve a Questão 1)
%  ========================================================================
%{
    DIDÁTICA: Para um sistema de 1ª ordem T(s) = K_dc / (tau*s + 1),
    identificamos os parâmetros a partir do gráfico da resposta ao degrau unitário:
    1. Ganho Estático (K_dc): O valor final para o qual a resposta estabiliza.
    2. Constante de Tempo (tau): O tempo que a resposta leva para atingir 63.2% do valor final.
       Alternativamente, se o problema der o Tempo de Estabilização (Ts) para 4 constantes de tempo, então tau = Ts / 4.
%}
fprintf("\n>> 0.A: IDENTIFICAÇÃO DE SISTEMA DE 1ª ORDEM (Questão 1)...\n");

% --- Insira os dados do gráfico da Questão 1 ---
K_dc_q1 = 0.8; % Valor final no gráfico é 0.8
Ts_q1 = 1.0;   % Tempo de estabilização dado no enunciado
tau_q1 = Ts_q1 / 4; % tau = 1.0 / 4 = 0.25

% --- Construir a Função de Transferência de Malha Fechada T(s) ---
T_q1 = tf(K_dc_q1, [tau_q1 1]);
fprintf("Função de Transferência de Malha Fechada T(s) identificada:\n");
T_q1_simplified = zpk(T_q1) % zpk simplifica a fração

% --- Derivar a Função de Transferência de Malha Aberta G(s) ---
% Fórmula: G = T / (1 - T) para realimentação unitária
G_q1 = T_q1 / (1 - T_q1);
fprintf("Função de Transferência de Malha Aberta G(s) derivada:\n");
G_q1_simplified = zpk(G_q1)

%% ========================================================================
%  0.B: IDENTIFICAÇÃO DE SISTEMA DE 2ª ORDEM (Resolve a Questão 4)
%  ========================================================================
%{
    DIDÁTICA: Para um sistema de 2ª ordem, extraímos parâmetros do gráfico
    para encontrar o Fator de Amortecimento (zeta) e a Frequência Natural (wn).
    1. Valor Final (x_ss): Para onde o sistema estabiliza.
    2. Valor de Pico (x_pico): O valor máximo atingido pela resposta.
    3. Tempo de Pico (Tp): O instante em que ocorre o valor de pico.
    4. Overshoot Percentual (UP): UP = (x_pico - x_ss) / x_ss
    5. Fórmulas:
       zeta = -log(UP) / sqrt(pi^2 + (log(UP))^2)
       wn = pi / (Tp * sqrt(1 - zeta^2))
%}
fprintf("\n>> 0.B: IDENTIFICAÇÃO DE SISTEMA DE 2ª ORDEM (Questão 4)...\n");

% --- Insira os dados do gráfico da Questão 4 ---
F_amp = 100; % Amplitude do degrau de entrada
x_ss_q4 = 1e-2; % Valor final de deslocamento (aprox. do gráfico)
x_pico_q4 = 1.7e-2; % Valor de pico (aprox. do gráfico)
Tp_q4 = 0.28; % Tempo de pico em segundos (aprox. do gráfico)

% --- Cálculos ---
UP_q4 = (x_pico_q4 - x_ss_q4) / x_ss_q4;
zeta_q4 = -log(UP_q4) / sqrt(pi^2 + (log(UP_q4))^2);
wn_q4 = pi / (Tp_q4 * sqrt(1 - zeta_q4^2));

fprintf("Parâmetros de 2ª Ordem estimados:\n");
fprintf("Overshoot (UP) = %.4f (%.2f%%)\n", UP_q4, UP_q4*100);
fprintf("Fator de Amortecimento (zeta) = %.4f\n", zeta_q4);
fprintf("Frequência Natural (wn) = %.4f rad/s\n", wn_q4);

% --- Estimar m, c, k ---
% FT do sistema: X(s)/F(s) = 1 / (m*s^2 + c*s + k)
% Ganh o DC: X(inf) / F(inf) = 1/k
k_q4 = F_amp / x_ss_q4;
% Comparando denominadores: m*s^2 + c*s + k = m * (s^2 + (c/m)s + k/m)
% com a forma padrão: s^2 + 2*zeta*wn*s + wn^2
% Temos: wn^2 = k/m  e  2*zeta*wn = c/m
m_q4 = k_q4 / wn_q4^2;
c_q4 = 2 * zeta_q4 * wn_q4 * m_q4;

fprintf("\nParâmetros do sistema mecânico estimados (m, c, k):\n");
fprintf("m = %.4f kg\n", m_q4);
fprintf("c = %.4f N-s/m\n", c_q4);
fprintf("k = %.4f N/m\n", k_q4);

%% ========================================================================
%  1. DEFINIÇÃO E ANÁLISE GERAL DE SISTEMAS (Estrutura principal)
%  ========================================================================
% Esta secção mantém-se para análise geral, como fizemos antes.
% Pode preenchê-la com os dados de um problema específico.
% G = tf(...) , H = tf(...) , T = feedback(G,H)
% ... e assim por diante.

%% ========================================================================
%  2. ANÁLISE SIMBÓLICA AVANÇADA (Ajuda a resolver a Questão 5)
%  ========================================================================
%{
    DIDÁTICA: Para problemas com variáveis (como K2) ou diagramas de blocos
    complexos, usamos a Symbolic Math Toolbox para manipular as equações.
%}
fprintf("\n>> 2. ANÁLISE SIMBÓLICA AVANÇADA (Questão 5)...\n");

% --- Definir variáveis e blocos simbolicamente ---
syms s K1 K2 De Ke

% --- Escrever as equações a partir do diagrama de blocos ---
% Sinal após o 2º somador (entrada de K1): E2 = E1 - w*K2
% Sinal w_ref: w_ref = K1 * E2
% Sinal w: w = w_ref * (1/s)
% Sinal theta: theta = w * (1/s)
% Sinal F: F = theta * (De*s + Ke)
% Sinal E1: E1 = F_cmd - F

% --- Substituir e resolver para F em função de F_cmd ---
% w = K1*(F_cmd - F - w*K2)*(1/s) => w*(s + K1*K2) = K1*(F_cmd - F)
% w = K1*(F_cmd - F) / (s + K1*K2)
% theta = w/s
% F = (w/s) * (De*s + Ke) => F = (K1*(F_cmd - F) / (s*(s + K1*K2))) * (De*s + Ke)
% F * s*(s + K1*K2) = K1*(F_cmd - F)*(De*s + Ke)
% F * (s^2 + s*K1*K2) = (K1*F_cmd - K1*F)*(De*s + Ke)
% F * (s^2 + s*K1*K2) = K1*F_cmd*(De*s + Ke) - K1*F*(De*s + Ke)
% F * (s^2 + s*K1*K2 + K1*(De*s + Ke)) = K1*F_cmd*(De*s + Ke)

syms F F_cmd
T_simbolica_num = K1*(De*s + Ke);
T_simbolica_den = s^2 + s*K1*K2 + K1*(De*s + Ke);
T_simbolica = T_simbolica_num / T_simbolica_den;

fprintf("FT de malha fechada F(s)/F_cmd(s) simbólica:\n");
pretty(T_simbolica)

% --- Cálculo do Erro em Regime Permanente para Rampa ---
% E = F_cmd - F = F_cmd * (1 - T)
% F_cmd para rampa unitária = 1/s^2
E_simbolico = F_cmd * (1 - T_simbolica);
ess_rampa_simbolico = limit(s * E_simbolico, s, 0);

% Substituir F_cmd por 1/s^2 no limite, resulta em:
ess_rampa_q5 = limit(s * (1/s^2) * (1 - T_simbolica), s, 0);

fprintf("Erro em regime permanente para entrada rampa:\n");
pretty(ess_rampa_q5)

% A partir do resultado `(K1 K2 + De K1)/(Ke K1)`, podemos resolver a inequação:
% (K1*K2 + De*K1)/(Ke*K1) < 0.1
% (K2 + De)/Ke < 0.1  =>  K2 < 0.1*Ke - De
fprintf("\nPara ess < 10%% (0.1), a condição para K2 é: K2 < 0.1*Ke - De\n");