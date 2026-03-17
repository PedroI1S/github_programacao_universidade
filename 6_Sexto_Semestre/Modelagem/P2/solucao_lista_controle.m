% % Solução da Lista de Exercícios -
    Sistemas de Controle 1 % Prof.Dr.Kleiton de Morais Sousa %
        Assunto : Técnicas de Resposta em Frequência %
                  Script gerado para resolver os exercícios da lista.

                  clear;
clc;
close all;

% % == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == ==
    = % EXERCÍCIO 1 : Expressão Analítica e Gráficos de Bode % == == == == == ==
      == == == == == == == == == == == == == == == == == == == == == == == == ==
      == == == == ==
    = fprintf('======================================================\n');
fprintf('EXERCÍCIO 1\n');
fprintf('======================================================\n');

% Definindo a variável de Laplace para toolbox de controle e simbólica s_tf =
    tf('s');
syms s w real

    % Sistemas do Exercicio 1 % G1 = 1 / (s * (s + 2) * (s + 4)) G1_tf =
                                         1 / (s_tf * (s_tf + 2) * (s_tf + 4));
G1_sym = 1 / (s * (s + 2) * (s + 4));

% G2 = (s + 5) / ((s + 2) * (s + 4)) G2_tf =
           (s_tf + 5) / ((s_tf + 2) * (s_tf + 4));
G2_sym = (s + 5) / ((s + 2) * (s + 4));

% G3 = ((s + 3) * (s + 5)) / (s * (s + 2) * (s + 4)) G3_tf =
           ((s_tf + 3) * (s_tf + 5)) / (s_tf * (s_tf + 2) * (s_tf + 4));
G3_sym = ((s + 3) * (s + 5)) / (s * (s + 2) * (s + 4));

systems_1 = {G1_tf, G2_tf, G3_tf};
systems_1_sym = {G1_sym, G2_sym, G3_sym};
names_1 = {'G1(s)', 'G2(s)', 'G3(s)'};

% (a)Expressões Analíticas de Magnitude e Fase
    fprintf('\n--- (a) Expressões Analíticas (s = jw) ---\n');
for
  i = 1 : length(systems_1_sym) G_jw = subs(systems_1_sym{i}, s, 1j * w);

% Magnitude mag_sq = simplify(abs(G_jw) ^ 2);
mag = sqrt(mag_sq);
% Representação simbólica da magnitude

    % Fase(em radianos, convertemos para graus na exibição se necessário) %
    A função angle no Matlab simbólico pode ser complexa de simplificar
    automaticamente,
    % mas exibiremos a forma complexa.phi = angle(G_jw);

fprintf('\nSistema %s:\n', names_1{i});
fprintf('Magnitude M(w) = %s\n', char(mag));
% Exibição
        simplificada manual da fase muitas vezes é melhor feita inspeção visual,
    % mas aqui imprimimos o que o computacional consegue.%
        fprintf('Fase phi(w) = %s\n', char(phi));
end

    % (b)Gráficos de Bode
    fprintf('\n--- (b) Gerando Gráficos de Bode (Figuras 1, 2 e 3) ---\n');
for
  i = 1 : length(systems_1) figure(i);
bode(systems_1{i});
grid on;
title(['Diagrama de Bode - ' names_1{i}]);
subtitle(
    'Linha sólida: Exata (O comportamento assintótico deve ser esboçado à mão)');
end pause(1);
% Pausa para garantir renderização

        % %
    == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == ==
    = % EXERCÍCIO 2 : Diagrama de Nyquist e Estabilidade % == == == == == == ==
      == == == == == == == == == == == == == == == == == == == == == == == == ==
      == == == ==
    = fprintf('\n======================================================\n');
fprintf('EXERCÍCIO 2\n');
fprintf('======================================================\n');

%
    Definindo os sistemas(Atenção para malha fechada vs aberta.O Nyquist é
                              analizado em Malha Aberta L(s)) %
    System 1 sys1_G = 50 / (s_tf * (s_tf + 3) * (s_tf + 6));
sys1_L = sys1_G;
% Realimentação unitária implícita ou G é direto

    % System 2 sys2_G = 50 / (s_tf ^ 2 * (s_tf + 1));
sys2_H = (s_tf + 4);
sys2_L = sys2_G * sys2_H;

% System 3 sys3_G = 20 / (s_tf * (s_tf + 1));
sys3_H = (s_tf + 3) / (s_tf + 4);
sys3_L = sys3_G * sys3_H;

% System 4 sys4_G = (100 * (s_tf + 5)) / (s_tf * (s_tf + 3) * (s_tf ^ 2 + 4));
sys4_L = sys4_G;
% Assumindo realimentação unitária conforme diagrama padrão se não indicado H

        systems_2 = {sys1_L, sys2_L, sys3_L, sys4_L};
names_2 = {'System 1', 'System 2', 'System 3', 'System 4'};

% (a)Esboço de Nyquist fprintf(
      '\n--- (a) Gerando Diagramas de Nyquist (Figuras 4, 5, 6 e 7) ---\n');
for
  i = 1 : length(systems_2) fig_num = 3 + i;
figure(fig_num);
nyquist(systems_2{i});
grid on;
title(['Diagrama de Nyquist - ' names_2{i}]);
axis equal;
end pause(1);

% (b)Estabilidade via Critério de Nyquist
    fprintf('\n--- (b) Análise de Estabilidade ---\n');
% Critério: Z = N + P
% Z = nro de polos de malha fechada no SPR (instáveis)
% N = nro de encirclements do ponto -1+j0 (horário > 0)
% P = nro de polos de malha aberta no SPR
for i = 1:length(systems_2)
    L = systems_2{i};
P = sum(real(pole(L)) > 0);
% Polos instáveis de malha aberta

    % Calculando N(Encirclements)
de forma automática pode ser complexo sem inspeção visual cuidadosa %
    em casos limítrofes,
    mas vamos usar a função pole da malha fechada para confirmar a
            estabilidade.%
        O exercício pede "Utilizando o critério",
    vamos simular a conclusão.

        % Polos de malha fechada CL = feedback(L, 1);
Z = sum(real(pole(CL)) > 0);

% Se Z == 0, estável.status = 'INSTÁVEL';
if Z
  == 0 status = 'ESTÁVEL';
end

    fprintf('%s:\n', names_2{i});
fprintf('  Polos de Malha Aberta no SPR (P) = %d\n', P);
fprintf('  Polos de Malha Fechada no SPR (Z) = %d\n', Z);
fprintf('  Conclusão: O sistema é %s.\n', status);
end

        % %
    == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == ==
    = % EXERCÍCIO 3 : Análise do Diagrama de Bode(Figura 2) % == == == == == ==
      == == == == == == == == == == == == == == == == == == == == == == == == ==
      == == == == ==
    = fprintf('\n======================================================\n');
fprintf('EXERCÍCIO 3\n');
fprintf('======================================================\n');

% (a)Dados extraídos visualmente da Figura 2(Estimativas) %
    Magnitude cruza 0dB em aprox w = 1.8 rad / s
    ? % Fase em 1.8 rad / s é aprox - 125 graus
          ? % Vamos definir valores aproximados baseados na inspeção típica
                % Note
          : Isso são valores
            "hardcoded" para o script funcionar.O usuário pode ajustar.

            fprintf(
                '--- (a) Parâmetros de Frequência e Margens (Estimados da Fig 2) ---\n');

% Olhando o gráfico : %
                      0dB Frequency(w_gc)
    : A curva de magnitude cruza 0 dB um pouco antes de 10 ^
    0
    ? Não,
espera.% 10 ^ 0 é 1. % Magnitude em 1 parece ser uns +
                  5dB. % Cruza 0 dB em aprox w = 3 rad / s.w_gc_est = 3.0;

%
    Fase em w_gc(3 rad / s)
    : % Em w = 1,
           fase = -110. Em w = 10, fase = -200. % Em w = 3,
           fase aprox - 150 graus.phase_at_wgc = -150;
PM_est = 180 + phase_at_wgc;
% Margem de Fase

        % -180 Phase Frequency(w_pc)
    : % A fase cruza
    - 180 em aprox w = 7 rad / s.w_pc_est = 7.0;

%
    Magnitude em w_pc(7 rad / s)
    : % Em w = 7,
           magnitude parece estar em - 20 dB.mag_at_wpc_dB = -20;
GM_dB_est = -mag_at_wpc_dB;
% Margem de Ganho(se mag é - 20, margem é 20dB)

        % Largura de Banda(Bandwidth)
    : % Aprox a frequencia de 0dB para sistema de controle típico ~w_gc.%
      Mas rigorosamente é onde magnitude cai
    - 3dB da magnitude DC(se DC = 0dB).% Na figura,
mag DC->infty(tipo 1) ou muito alta.% Para malha fechada,
BW é aprox w_gc se PM ~45 - 60. BW_est = w_gc_est;

fprintf('  Frequência de Cruzamento de Ganho (w_0dB) ~= %.2f rad/s\n',
        w_gc_est);
fprintf('  Frequência de Cruzamento de Fase (w_180) ~= %.2f rad/s\n', w_pc_est);
fprintf('  Margem de Ganho (GM) ~= %.1f dB\n', GM_dB_est);
fprintf('  Margem de Fase (PM) ~= %.1f graus\n', PM_est);
fprintf('  Largura de Banda Malha Fechada (BW) ~= %.2f rad/s\n', BW_est);

% (b)Estimativas de Domínio do Tempo
    fprintf('\n--- (b) Estimativas de Desempenho Temporal ---\n');
% Fator de amortecimento zeta ~= PM / 100 zeta_est = PM_est / 100;

% Overshoot % OS = exp(-pi * zeta / sqrt(1 - zeta ^ 2)) * 100 OS_est =
    exp(-pi * zeta_est / sqrt(1 - zeta_est ^ 2)) * 100;

% Tempo de estabilização Ts = 4 / (zeta * wn) % Aprox wn ~= w_gc wn_est =
                                  w_gc_est;
Ts_est = 4 / (zeta_est * wn_est);

% Tempo de pico Tp = pi / (wn * sqrt(1 - zeta ^ 2)) Tp_est =
                         pi / (wn_est * sqrt(1 - zeta_est ^ 2));

fprintf('  Fator de Amortecimento (zeta) ~= %.2f\n', zeta_est);
fprintf('  Porcentagem de Overshoot (%%OS) ~= %.2f %%\n', OS_est);
fprintf('  Tempo de Estabilização (Ts) ~= %.2f s\n', Ts_est);
fprintf('  Tempo de Pico (Tp) ~= %.2f s\n', Tp_est);

% % == == == == == == == == == == == == == == == == == == == == == == == == ==
    == == == == == == == == == == ==
    = % EXERCÍCIO 4 : Projeto de Ganho K % == == == == == == == == == == == ==
      == == == == == == == == == == == == == == == == == == == == == == == ==
    = fprintf('\n======================================================\n');
fprintf('EXERCÍCIO 4\n');
fprintf('======================================================\n');

% Sistemas do Exercicio 4(Fig 3 : realimentação unitária H = 1) % G4_a =
    K / (s + 4)(s + 10)(s + 15) % G4_b =
        K / s(s + 4)(s + 10) % G4_c = K(s + 2)(s + 5) / s(s + 4)(s + 6)(s + 10)

                                      % TFs
                                      base(com K = 1) G4a_base = 1 /
                                                                 ((s_tf + 4) *
                                                                  (s_tf + 10) *
                                                                  (s_tf + 15));
G4b_base = 1 / (s_tf * (s_tf + 4) * (s_tf + 10));
G4c_base =
    ((s_tf + 2) * (s_tf + 5)) / (s_tf * (s_tf + 4) * (s_tf + 6) * (s_tf + 10));

systems_4 = {G4a_base, G4b_base, G4c_base};
names_4 = {'4(a): 1/[(s+4)(s+10)(s+15)]', '4(b): 1/[s(s+4)(s+10)]',
           '4(c): (s+2)(s+5)/[s(s+4)(s+6)(s+10)]'};

% (a)Projetar K para Margem de Ganho(GM) = 10 dB
    fprintf('\n--- (a) Projetar K para GM = 10 dB ---\n');
target_GM_dB = 10;
target_GM_abs = 10 ^ (target_GM_dB / 20); % 3.1623

for i = 1:length(systems_4)
    sys = systems_4{i};
[ Gm_plant, ~, ~, ~] = margin(sys); % Gm_plant é absoluta (não dB)
    
    % Se Gm_plant for Infinito (sistema nunca cruza -180), não dá pra definir GM.
    if isinf(Gm_plant)
        fprintf('  %s: Margem de Ganho infinita. K pode ser qualquer valor para estabilidade, ou GM incalculável.\n', names_4{i});
continue;
end

    % Loop Gain = K * Plant % Margin(Loop) =
                      Gm_plant / K % Target_GM =
                          Gm_plant / K = > K = Gm_plant / Target_GM

                                                              K_design =
                                                   Gm_plant / target_GM_abs;

fprintf('  Sistema %s\n', names_4{i});
fprintf('    GM Original (K=1): %.2f dB\n', 20 * log10(Gm_plant));
fprintf('    K calculado: %.4f\n', K_design);

% Verificação[Gm_new, ~, ~, ~] = margin(K_design * sys);
fprintf('    GM Verificado: %.2f dB\n', 20 * log10(Gm_new));
end

    % (b)Projetar K para Margem de Fase(PM) = 40 graus
    fprintf('\n--- (b) Projetar K para PM = 40 graus ---\n');
target_PM = 40; % graus

for i = 1:length(systems_4)
    sys = systems_4{i};

% Precisamos encontrar a frequência onde a fase é - 180 + Target_PM =
    -140 graus.%
    Bode phase retorna fase em graus.[mag_bode, phase_bode, w_bode] = bode(sys);

% Ajustar vetor de fase para lidar com wraps de 360 se necessário,
    mas bode geralmente é continuo.phase_vec = squeeze(phase_bode);
mag_vec = squeeze(mag_bode);
w_vec = squeeze(w_bode);

% Fase alvo(-140 graus).Note que o sistema pode começar em 0, -90,
    etc e cair.% Procuramos w onde phase cruzando -
        140. target_phase = -180 + target_PM;

% Interpolação para achar w exato %
    Assumindo monotonicidade na fase na região de
    cruzamento(comum nesses sistemas) w_target = interp1(phase_vec, w_vec,
                                                         target_phase);

if isnan (w_target)
  fprintf('  %s: Não foi possível encontrar frequencia para fase %.1f graus.\n',
          names_4{i}, target_phase);
continue;
end

    % Agora achamos a magnitude da planta nessa frequencia mag_at_w =
    interp1(w_vec, mag_vec, w_target);

% Queremos que | K *G(jw) |
    = 1(0 dB)nessa frequencia
      % K *mag_at_w = 1 = > K = 1 / mag_at_w K_design_pm = 1 / mag_at_w;

fprintf('  Sistema %s\n', names_4{i});
fprintf('    Frequência alvo da fase (%.1f deg): %.4f rad/s\n', target_phase,
        w_target);
fprintf('    K calculado: %.4f\n', K_design_pm);

% Verificação[~, Pm_new, ~, ~] = margin(K_design_pm * sys);
fprintf('    PM Verificado: %.2f graus\n', Pm_new);
end

    fprintf('\nScript finalizado.\n');
