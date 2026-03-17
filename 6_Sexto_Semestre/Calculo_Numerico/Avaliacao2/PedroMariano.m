%% 1. INTERPOLAÇÃO DE LAGRANGE
clear; clc; close all;

% --- Dados do problema ---
X = [-1, 0, 1, 2];
Y = [1, 3, 1, -5];
xi = 1.5; % Ponto que queremos descobrir

n = length(X);
yi = 0; % Acumulador para o resultado

fprintf('Interpolando para x = %.4f:\n', xi);

% Loop principal do somatório de Lagrange
for k = 1:n
    % Calcula o L_k(x)
    num = 1;
    den = 1;
    
    for j = 1:n
        if k ~= j % Não podemos ter divisão por zero (x_k - x_k)
            num = num * (xi - X(j));
            den = den * (X(k) - X(j));
        end
    end
    
    L_k = num / den;
    yi = yi + Y(k) * L_k;
    
    fprintf('  Termo L_%d: %.6f\n', k-1, L_k);
end

fprintf('P(%.4f) = %.6f\n', xi, yi);

% --- Parte visual (Montar a string do polinômio) ---
% Usando polyfit só pra pegar os coeficientes e mostrar a equação
p = polyfit(X, Y, n-1); 
msg_poly = 'P(x) =';

for k = 1:length(p)
    coef = p(k);
    grau = length(p)-k;
    
    % Só mostra se o coeficiente for relevante
    if abs(coef) > 1e-4 
        if coef >= 0, sinal = '+'; else, sinal = '-'; end
        if k==1 && coef>0, sinal=''; end % Tira o + do começo
        
        % Formata o x^n
        if grau == 0, str_x = ''; 
        elseif grau == 1, str_x = '*x'; 
        else, str_x = sprintf('*x^%d', grau); end
        
        msg_poly = [msg_poly sprintf(' %s %.4g%s', sinal, abs(coef), str_x)];
    end
end
fprintf('%s\n\n', msg_poly);


%% 2. INTERPOLAÇÃO DE NEWTON (Diferenças Divididas)
clear; clc;

% --- Entradas ---
X = [-1, 0, 1, 2];       
Y = [1, 3, 1, -5];      
target = 1.5;
n = length(X);

% Matriz das diferenças divididas
% A primeira coluna é o próprio Y
DD = zeros(n, n); 
DD(:, 1) = Y';

% Montando a tabela
for j = 2:n
    for i = 1:n-j+1
        numerador = DD(i+1, j-1) - DD(i, j-1);
        denominador = X(i+j-1) - X(i);
        DD(i, j) = numerador / denominador;
    end
end

b = DD(1, :); % Os coeficientes são a primeira linha da tabela

fprintf('Tabela de Diferenças:\n'); 
disp(DD);
fprintf('Coeficientes do polinômio: '); 
disp(b);

% Calculando o valor interpolado na mão
res = b(1); 
multiplicatorio = 1;

for k = 2:n
    multiplicatorio = multiplicatorio * (target - X(k-1));
    res = res + b(k) * multiplicatorio; 
end

fprintf('P(%.4f) = %.6f\n\n', target, res);


%% 3. INTEGRAÇÃO NUMÉRICA (Regra dos Trapézios)
clear; clc;

func = @(x) exp(x); % Função a integrar
a = 1; 
b = 2;
n = 4; % Número inicial de subintervalos

% Configurações
tol = 5e-5;
modo_busca = false; % true = busca N ideal | false = usa N fixo

referencia = integral(func, a, b); % Valor exato do Matlab pra comparar

if ~modo_busca
    % Cálculo direto
    h = (b - a) / n; 
    x_vec = a:h:b; 
    y_vec = func(x_vec);
    
    soma_meio = sum(y_vec(2:end-1));
    Area = (h/2) * (y_vec(1) + 2*soma_meio + y_vec(end));
    
    fprintf('Trapézios (Fixo): n = %d, h = %.6f\n', n, h);
    fprintf('>>> Área ≈ %.8f (Erro: %.2e)\n', Area, abs(Area-referencia));
else
    % Loop para achar a precisão
    fprintf('Buscando N para erro < %g...\n', tol);
    n_try = 1;
    while true
        h = (b - a) / n_try; 
        x_vec = a:h:b; 
        y_vec = func(x_vec);
        
        soma_meio = sum(y_vec(2:end-1));
        Area = (h/2) * (y_vec(1) + 2*soma_meio + y_vec(end));
        
        if abs(Area - referencia) < tol
            fprintf('>>> Convergiu! n = %d (h=%.6f)\n', n_try, h);
            fprintf('>>> Área ≈ %.8f (Erro real: %.2e)\n', Area, abs(Area-referencia));
            break;
        end
        
        n_try = n_try + 1;
        if n_try > 50000, fprintf('Desisto. Não convergiu.\n'); break; end
    end
end
fprintf('\n');


%% 4. INTEGRAÇÃO NUMÉRICA (Simpson 1/3)
clear; clc;

func = @(x) sqrt(x);
a = 1; 
b = 4;
tol = 5e-5;
modo_busca = false; % Se quiser buscar o N, muda pra true

referencia = integral(func, a, b);

if ~modo_busca
    n = 4;
    % Simpson 1/3 precisa de N par
    if mod(n,2) ~= 0
        n = n+1; 
        fprintf('Aviso: Ajustei n para %d (tem que ser par)\n', n); 
    end
    
    h = (b-a)/n; 
    x = a:h:b; 
    y = func(x);
    
    % Pesos: Extremos=1, Impares=4, Pares=2
    soma_impar = 4 * sum(y(2:2:end-1));
    soma_par   = 2 * sum(y(3:2:end-2));
    
    Area = (h/3) * (y(1) + soma_impar + soma_par + y(end));
    
    fprintf('Simpson 1/3: n = %d, h = %.6f\n', n, h);
    fprintf('>>> Área ≈ %.8f (Erro: %.2e)\n', Area, abs(Area-referencia));
else
    n_try = 2; % Começa com 2
    while true
        h = (b-a)/n_try; 
        x = linspace(a, b, n_try+1); 
        y = func(x);
        
        soma_impar = 4 * sum(y(2:2:end-1));
        soma_par   = 2 * sum(y(3:2:end-2));
        Area = (h/3) * (y(1) + soma_impar + soma_par + y(end));
        
        if abs(Area - referencia) < tol
            fprintf('>>> Convergiu! n = %d (h=%.6f)\n', n_try, h);
            fprintf('>>> Área ≈ %.8f\n', Area);
            break;
        end
        n_try = n_try + 2; % Passo de 2 em 2
        if n_try > 50000, fprintf('Sem convergencia.\n'); break; end
    end
end
fprintf('\n');


%% 5. INTEGRAÇÃO COM DADOS TABULADOS (Híbrido)
clear; clc;

% Dados tabelados
X = [0.0, 0.2, 0.4, 0.6, 0.8, 1.0];
Y = [1.0, 1.2408, 1.5735, 2.0333, 2.6965, 3.7183];

n_intervalos = length(X) - 1; 
h = X(2) - X(1);

% Lógica: Se for par, vai de Simpson direto. Se for ímpar, Simpson + Trapézio no final.
if mod(n_intervalos, 2) == 0
    fprintf('Método: Simpson 1/3 (Puro)\n');
    soma_4 = 4 * sum(Y(2:2:end-1));
    soma_2 = 2 * sum(Y(3:2:end-2));
    I = (h/3) * (Y(1) + soma_4 + soma_2 + Y(end));
else
    fprintf('Método: Misto (Simpson até o penúltimo + Trapézio no último)\n');
    
    % Parte do Simpson (até o penúltimo ponto)
    Ys = Y(1:end-1);
    Is = (h/3) * (Ys(1) + 4*sum(Ys(2:2:end-1)) + 2*sum(Ys(3:2:end-2)) + Ys(end));
    
    % Parte do Trapézio (último intervalo)
    It = (h/2) * (Y(end-1) + Y(end));
    
    I = Is + It;
end

fprintf('>>> Integral Total ≈ %.6f\n\n', I);


%% 6. QUADRADOS MÍNIMOS (Ajuste Polinomial)
clear; clc; close all;

% Dados experimentais
x_exp = [1, 2, 3, 4, 5, 6, 7, 8];
y_exp = [0.5, 0.6, 0.9, 0.8, 1.2, 1.5, 1.7, 2.0];

graus_teste = [1, 2]; % Testar Reta e Parábola

figure; 
plot(x_exp, y_exp, 'wo', 'MarkerFaceColor', 'k', 'MarkerSize', 6); 
hold on;

cores = {'b', 'r', 'g'};
legenda = {'Dados'};

fprintf('--- Ajuste MMQ ---\n');
x_smooth = linspace(min(x_exp), max(x_exp), 200);

for i = 1:length(graus_teste)
    g = graus_teste(i);
    
    % Faz o ajuste
    p = polyfit(x_exp, y_exp, g);
    
    % Calcula erro quadrático
    y_modelo = polyval(p, x_exp);
    sq_err = sum((y_exp - y_modelo).^2);
    
    % Monta string da equação
    str_eq = 'y =';
    for k = 1:length(p)
        str_eq = [str_eq sprintf(' %+.3fx^%d', p(k), length(p)-k)];
    end
    
    fprintf('Grau %d: %s (Erro: %.4f)\n', g, str_eq, sq_err);
    
    % Plota
    y_smooth = polyval(p, x_smooth);
    cor = cores{mod(i-1, length(cores)) + 1};
    plot(x_smooth, y_smooth, [cor '-'], 'LineWidth', 2);
    
    legenda{end+1} = sprintf('Grau %d (Erro: %.2f)', g, sq_err);
end

grid on; 
legend(legenda, 'Location', 'best'); 
title('Comparação dos Ajustes'); 
xlabel('Eixo X'); ylabel('Eixo Y');
fprintf('\n');


%% 7. QUADRADOS MÍNIMOS (Caso Contínuo)
% Ajuste de função f(x) por uma base de funções phi
clear; clc;

f = @(x) exp(sin(x));
intervalo = [0, 2*pi];

phi = {@(x) ones(size(x)), ...
       @(x) cos(x), @(x) sin(x), ...
       @(x) cos(2*x), @(x) sin(2*x)};

n = length(phi); 
A = zeros(n, n); 
B = zeros(n, 1);

% Monta o sistema linear A*c = B
for i = 1:n
    % Vetor independente B_i = <f, phi_i>
    B(i) = integral(@(x) f(x).*phi{i}(x), intervalo(1), intervalo(2));
    
    for j = i:n
        % Matriz A_ij = <phi_i, phi_j>
        val = integral(@(x) phi{i}(x).*phi{j}(x), intervalo(1), intervalo(2));
        A(i, j) = val; 
        A(j, i) = val; % Simetria
    end
end

% Resolve o sistema
c = A \ B;

fprintf('Coeficientes encontrados:\n'); 
disp(c');
fprintf('\n');

%% 8. EDO - EULER vs EULER MODIFICADO (Heun)
clear; clc; close all;

dydx = @(x,y) x - y + 2; % Equação diferencial

x0 = 0; 
y0 = 2;
xf = 1.0; % Vai até onde?
h = 0.1;  % Passo

% Vetores para guardar a solução
X = x0:h:xf;
N = length(X);

Y_euler = zeros(1, N); Y_euler(1) = y0;
Y_heun  = zeros(1, N); Y_heun(1)  = y0;

fprintf('%4s | %8s | %10s | %10s\n', 'Iter', 'X', 'Euler', 'Heun');

for i = 1:N-1
    x_atual = X(i);
    
    % --- Método de Euler Simples ---
    inclincacao = dydx(x_atual, Y_euler(i));
    Y_euler(i+1) = Y_euler(i) + h * inclincacao;
    
    % --- Método de Euler Modificado (Heun) ---
    y_prev = Y_heun(i);
    k1 = dydx(x_atual, y_prev);             % Inclinação no início
    
    y_predito = y_prev + h*k1;              % Preditor
    k2 = dydx(x_atual+h, y_predito);        % Inclinação no fim (estimada)
    
    Y_heun(i+1) = y_prev + (h/2)*(k1 + k2); % Corretor (Média das inclinações)
    
    fprintf('%4d | %8.4f | %10.6f | %10.6f\n', i, X(i+1), Y_euler(i+1), Y_heun(i+1));
end

% Gráfico
figure; 
plot(X, Y_euler, 'r--o', 'LineWidth', 1.5); hold on; 
plot(X, Y_heun, 'b-s', 'LineWidth', 1.5); 
legend('Euler Simples', 'Euler Melhorado (Heun)'); 
grid on; 
title('Comparação Métodos EDO');


%% FENÔMENO DE RUNGE
% Mostra por que polinômios de grau alto oscilam nas pontas
clear; clc; close all;

f_teste = @(x) 1./(1 + 25*x.^2);

n_pts = 11; % Grau será n-1 = 10 (perigoso pra interpolação equiespaçada)
a = -1; b = 1;

% Pontos de controle
x_nos = linspace(a, b, n_pts);
y_nos = f_teste(x_nos);

% Polinômio interpolador
p = polyfit(x_nos, y_nos, n_pts - 1);

% Para plotar suave
x_grid = linspace(a, b, 500);
y_exata = f_teste(x_grid);
y_poly  = polyval(p, x_grid);

figure;
plot(x_nos, y_nos, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6); hold on;
plot(x_grid, y_exata, 'b-', 'LineWidth', 2);
plot(x_grid, y_poly, 'r-', 'LineWidth', 1.5);

grid on;
legend('Pontos usados', 'Função Original', 'Polinômio (Oscilação)', 'Location', 'North');
title(['Efeito Runge com ' num2str(n_pts) ' pontos']);
xlabel('x'); ylabel('y');