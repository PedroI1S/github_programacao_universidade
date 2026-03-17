% Limpa ambiente
clc; clear; close all;

% Dados de entrada
n = 10;          % Grau do polinomio trigonometrico
L = pi;          % Intervalo [-L, L]
m = 100;         % Divisoes da integral (trapezio)

% Função alvo
func_f = @(x) x;

% Configuração da grade
dx = (2*L) / m;
x_int = linspace(-L, L, m+1); % Pontos de integração

% Dimensão do sistema (a0 + n cossenos + n senos)
dim = 2*n + 1;

A = zeros(dim, dim);
B = zeros(dim, 1);

% Montagem do sistema linear (Produtos Internos)
% Loop percorre todas as funções base
for i = 1:dim
    phi_i = calcula_base(i, x_int, n, L);
    
    % Preenche matriz A
    for j = i:dim % Aproveita simetria da matriz (opcional, mas eficiente)
        phi_j = calcula_base(j, x_int, n, L);
        
        % Integral numerica (Trapezio) de phi_i * phi_j
        prod = phi_i .* phi_j;
        integ = (dx/2) * (prod(1) + 2*sum(prod(2:end-1)) + prod(end));
        
        A(i, j) = integ;
        A(j, i) = integ; % Matriz simetrica
    end
    
    % Preenche vetor B (Integral de f * phi_i)
    prod_b = func_f(x_int) .* phi_i;
    integ_b = (dx/2) * (prod_b(1) + 2*sum(prod_b(2:end-1)) + prod_b(end));
    B(i) = integ_b;
end

% Resolve o sistema linear
coeficientes = resolver_gauss(A, B);

% Separa os coeficientes a0, an e bn para exibir
a0 = coeficientes(1);
ak = coeficientes(2:n+1);
bk = coeficientes(n+2:end);

disp('Resultados obtidos:');
fprintf('a0 = %.4f\n', a0);
disp('Vetor ak (cossenos):'); disp(ak');
disp('Vetor bk (senos):'); disp(bk');

% --- Plotagem ---
x_graf = linspace(-L, L, 200);
y_exata = func_f(x_graf);
y_aprox = zeros(size(x_graf));

% Calcula a série truncada nos pontos do gráfico
for k = 1:length(x_graf)
    val = a0; % Termo constante
    
    % Soma somatorios de cos e sin
    for termo = 1:n
        val = val + ak(termo) * cos(termo*pi*x_graf(k)/L);
        val = val + bk(termo) * sin(termo*pi*x_graf(k)/L);
    end
    y_aprox(k) = val;
end

figure;
plot(x_graf, y_exata, 'b', 'LineWidth', 1.5); hold on;
plot(x_graf, y_aprox, 'r--', 'LineWidth', 1.5);
title(['Aproximacao Quadrados Minimos (n=' num2str(n) ')']);
legend('f(x)', 'phi(x)');
grid on;
xlabel('x'); ylabel('y');


% Funcoes Locais

% Retorna o vetor da k-ésima função base avaliada em x
function y = calcula_base(idx, x, n, L)
    if idx == 1
        y = ones(size(x)); % a0 -> cos(0)
    elseif idx <= n + 1
        k = idx - 1;
        y = cos(k * pi * x / L);
    else
        k = idx - (n + 1);
        y = sin(k * pi * x / L);
    end
end

% Implementacao de Eliminacao Gaussiana com Pivoteamento
function x = resolver_gauss(A, b)
    N = length(b);
    M = [A, b]; % Matriz aumentada
    
    % Escalonamento
    for k = 1:N-1
        % Pivoteamento parcial
        [~, p] = max(abs(M(k:N, k)));
        p = p + k - 1;
        
        if p ~= k
            M([k p], :) = M([p k], :);
        end
        
        for i = k+1:N
            fator = M(i, k) / M(k, k);
            M(i, k:end) = M(i, k:end) - fator * M(k, k:end);
        end
    end
    
    % Substituicao retroativa
    x = zeros(N, 1);
    x(N) = M(N, end) / M(N, N);
    
    for i = N-1:-1:1
        soma = M(i, i+1:N) * x(i+1:N);
        x(i) = (M(i, end) - soma) / M(i, i);
    end
end