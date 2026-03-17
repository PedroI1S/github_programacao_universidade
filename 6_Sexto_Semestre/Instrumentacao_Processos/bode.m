% --- SCRIPT PARA GERAR DIAGRAMA DE BODE (VERSÃO CORRIGIDA) ---

% Limpa a área de trabalho e fecha figuras anteriores
clear;
clc;
close all;

% --- 1. Definição dos Parâmetros do Filtro ---
K = 4;          % Ganho na banda passante (linear, V/V)
fc = 50000;     % Frequência de corte (em Hz)

% --- 2. Criação da Função de Transferência ---
wc = 2 * pi * fc; % Conversão da frequência de corte para rad/s
num = K * wc;
den = [1, wc];
H = tf(num, den);

disp('Função de Transferência H(s):');
printsys(num, den, 's');

% --- 3. Geração do Diagrama de Bode ---
figure; % Cria uma nova janela para a figura

% Opções do gráfico
opts = bodeoptions;
opts.FreqUnits = 'Hz';
opts.Title.String = 'Diagrama de Bode - Filtro Passa-Baixa Ativo';

% Gera o gráfico de Bode
bode(H, opts);
grid on; % Ativa o grid no gráfico

% --- 4. Adicionar Marcadores ao Gráfico Existente ---
% Esta seção foi ajustada para ser mais robusta

% Pega os eixos (subplots) que o comando 'bode' acabou de criar
all_axes = findall(gcf, 'type', 'axes');
ax_mag = all_axes(2);   % O eixo da magnitude
ax_phase = all_axes(1); % O eixo da fase

% Adiciona o marcador no gráfico de MAGNITUDE
hold(ax_mag, 'on'); % Ativa o 'hold' apenas para o subplot da magnitude
ganho_db = 20*log10(K);
mag_em_fc = ganho_db - 3;
plot(ax_mag, fc, mag_em_fc, 'r*', 'LineWidth', 2, 'MarkerSize', 10);
text(ax_mag, fc * 1.2, mag_em_fc, sprintf('Ponto de Corte\n%.2f dB @ %d kHz', mag_em_fc, fc/1000), 'Color', 'red');
hold(ax_mag, 'off');

% Adiciona o marcador no gráfico de FASE
hold(ax_phase, 'on'); % Ativa o 'hold' apenas para o subplot da fase
[~, phase_em_fc] = bode(H, wc); % Pega o valor da fase em fc
plot(ax_phase, fc, phase_em_fc, 'r*', 'LineWidth', 2, 'MarkerSize', 10);
text(ax_phase, fc * 1.2, phase_em_fc, sprintf('Fase de -45°\n@ %d kHz', fc/1000), 'Color', 'red');
hold(ax_phase, 'off');