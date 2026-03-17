% --- Limpeza do Ambiente ---
clear;
clc;
close all;

%% -- Definicao das Variaveis --

% Modo 1: Usa Valores selecionados pelo usuário
% Modo 2: Usa uma fórmula única para todos os elementos.
% Modo 3: Usa regras especiais para a primeira, última e demais linhas.
modo_gerador = 3;

switch modo_gerador
    case 1

        A = [10 -1  2;
             -1 11 -1;
             2 -1 10];

        b = [6; 25; -11];

    case 2

        func_A = @(i,j) 1/(i+j-1); % Fórmula para A(i,j)
        func_b = @(i) 1/i;         % Fórmula para b(i)
        n = 10;                    % Dimensão do sistema
        
        A = zeros(n, n);
        b = zeros(n, 1);
        for i = 1:n
            b(i) = func_b(i);
            for j = 1:n
                A(i,j) = func_A(i, j);
            end
        end

    case 3

        h = 0.1; % Parâmetro 'h'
        n = 10;  % Dimensão do sistema
        
        A = zeros(n, n);
        b = zeros(n, 1);
        diag_val = -2 * (1 + h^2); % Fórmula geratriz
        for i = 1:n
            if i == 1 % Regra para a primeira linha
                A(i, i)   = diag_val;
                A(i, i+1) = 1;
                b(i)      = 1;
            elseif i == n % Regra para a última linha
                A(i, i-1) = 1;
                A(i, i)   = diag_val;
                b(i)      = 1;
            else % Regra para as linhas intermediárias
                A(i, i-1) = 1;
                A(i, i)   = diag_val;
                A(i, i+1) = 1;
                b(i)      = 0;
            end
        end
end

fprintf('Sistema a ser resolvido:\n');
fprintf('Matriz A:\n');
disp(A);
fprintf('Vetor b:\n');
disp(b);

% parametros do calculo
x0 = zeros(size(b)); % chute inical
tol = 1e-6;
max_iter = 5000;

% verificação da convergencia
if ~eh_diagonal_dominante(A) 
    fprintf('AVISO: A matriz A não é estritamente diagonalmente dominante.\n');
    fprintf('A convergência dos métodos iterativos não é garantida.\n');
end

fprintf('-------------------------------------------\n\n');

%% -- Execucao das Funcoes --

fprintf('--- 1. Solução pelo Método de Jacobi ---\n');

[x_jacobi, iter_jacobi, erro_jacobi] = metodo_jacobi(A, b, x0, tol, max_iter);

if ~isempty(x_jacobi)
    fprintf('Solução encontrada em %d iterações.\n', iter_jacobi);
    fprintf('O vetor solução x é:\n');
    disp(x_jacobi);
    fprintf('Erro relativo final: %e\n\n', erro_jacobi);
end

fprintf('--- 2. Solução pelo Método de Gauss-Seidel ---\n');

[x_gs, iter_gs, erro_gs] = metodo_gauss_seidel(A, b, x0, tol, max_iter);

if ~isempty(x_gs)
    fprintf('Solução encontrada em %d iterações.\n', iter_gs);
    fprintf('O vetor solução x é:\n');
    disp(x_gs);
    fprintf('Erro relativo final: %e\n\n', erro_gs);
end

%% -- Metodo De Jacobi e Gauss-Seidel --

function [x, iter, erro] = metodo_jacobi(A, b, x0, tol, max_iter)
    n = length(b);
    x = x0;
    x_prox = zeros(n, 1);
    
    for iter = 1:max_iter
        for i = 1:n
            soma = A(i, :) * x - A(i, i) * x(i);
            x_prox(i) = (b(i) - soma) / A(i, i);
        end
        
        erro = norm(x_prox - x) / norm(x_prox);
        if erro < tol
            x = x_prox;
            return;
        end
        
        x = x_prox;
    end
    fprintf('ERRO: O método de Jacobi não convergiu em %d iterações.\n', max_iter);
    x = [];
    erro = [];
end

function [x, iter, erro] = metodo_gauss_seidel(A, b, x0, tol, max_iter)
    n = length(b);
    x = x0;
    
    for iter = 1:max_iter
        x_anterior = x;
        
        for i = 1:n
            soma1 = A(i, 1:i-1) * x(1:i-1);
            soma2 = A(i, i+1:n) * x_anterior(i+1:n);
            
            x(i) = (b(i) - soma1 - soma2) / A(i, i);
        end
  
        erro = norm(x - x_anterior) / norm(x);
        if erro < tol
            return;
        end
    end
    
    fprintf('ERRO: O método de Gauss-Seidel não convergiu em %d iterações.\n', max_iter);
    x = [];
    erro = [];
end

function eh_dominante = eh_diagonal_dominante(A)
    n = size(A, 1);
    for i = 1:n
        soma_linha = sum(abs(A(i, :))) - abs(A(i, i));
        if abs(A(i, i)) <= soma_linha
            eh_dominante = false;
            return;
        end
    end
    eh_dominante = true;
end

%% Análise e Explicação dos Métodos

% Condição de Convergência
% A parte mais importante para usar esses métodos é saber se eles vão funcionar. Uma condição suficiente (mas não necessária) para garantir a convergência é que a matriz A seja estritamente diagonalmente dominante.
% Isso significa que, para cada linha da matriz, o valor absoluto do elemento na diagonal principal é maior que a soma dos valores absolutos de todos os outros elementos daquela linha.
%   aii > j=1,j = i∑n a ij para todo i=1,...,n
% Eu incluí a função eh_diagonal_dominante  no script para verificar essa condição e emitir um aviso caso ela não seja satisfeita.

% Método de Jacobi
% A ideia do método de Jacobi é isolar cada variável x_i na i-ésima equação. Na iteração k+1, ele calcula cada novo componente x_i^(k+1) usando apenas os valores do vetor da iteração anterior, x^(k). Isso significa que o cálculo de todos os novos componentes pode ser feito de forma independente (ou em paralelo).

% Método de Gauss-Seidel
% Gauss-Seidel é um refinamento de Jacobi. A lógica é a mesma, mas com uma melhoria crucial: ao calcular o novo x_i^(k+1), ele utiliza imediatamente os valores x_1^(k+1), ..., x_{i-1}^(k+1) que acabaram de ser calculados na mesma iteração.

% Essa abordagem de "usar a informação mais recente assim que ela está disponível" geralmente faz com que Gauss-Seidel convirja mais rápido que Jacobi, como você provavelmente notará pela menor quantidade de iterações na saída do script.