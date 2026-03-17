% -- Limpeza do Ambiente --

clear;
clc;
close all;

%% -- Definicao das Variaveis --

% Modo 1: Usa Valores selecionados pelo usuário
% Modo 2: Usa uma fórmula única para todos os elementos.
% Modo 3: Usa uma fórmula onde as regras são definidas pela posição da linha.
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
tol = 1e-6;
max_iter = 5000;

fprintf('-------------------------------------------\n\n');

%% -- Execucao das Funcoes --

fprintf('--- 1. Solução por Eliminação Gaussiana ---\n');

try
    x_gauss = eliminacao_gaussiana(A, b);
    fprintf('O vetor solução x é:\n');
    disp(x_gauss);
catch ME
    fprintf('Erro: %s\n\n', ME.message);
end

fprintf('--- 2. Solução por Fatoração LU ---\n');

try
    x_lu = resolver_por_lu(A, b);
    fprintf('O vetor solução x é:\n');
    disp(x_lu);
    residuo_lu = norm(A*x_lu - b);
    fprintf('Norma do resíduo ||Ax - b||: %e\n\n', residuo_lu);
catch ME
    fprintf('Erro: %s\n\n', ME.message);
end

fprintf('--- 3. Solução por Eliminação Gaussiana com Pivotamento ---\n');

try
    x_pivot = gauss_com_pivoteamento(A, b);
    fprintf('O vetor solução x é:\n');
    disp(x_pivot);
catch ME
    fprintf('Erro: %s\n\n', ME.message);
end

%% -- Metodos E. Gaussiana, Fatoracao LU e E. Gauss por Pivotamento--

function x = eliminacao_gaussiana(A, b)
    [n, ~] = size(A);
    Ab = [A, b];

    for j = 1:n-1
        if abs(Ab(j,j)) < 1e-12
            error('Pivô nulo encontrado.');
        end
        for i = j+1:n
            m = Ab(i,j) / Ab(j,j);
            Ab(i, j:end) = Ab(i, j:end) - m * Ab(j, j:end);
        end
    end
    U = Ab(:, 1:n);
    c = Ab(:, n+1);
    x = zeros(n, 1);
    for i = n:-1:1
        x(i) = (c(i) - U(i, i+1:n) * x(i+1:n)) / U(i,i);
    end
    fprintf('Solução encontrada.\n');
end

function [L, U] = fatoracao_lu(A)
    [n, m] = size(A);
    if n ~= m
        error('A matriz A deve ser quadrada.');
    end
    
    % Inicializa L como matriz identidade e U como uma cópia de A.
    L = eye(n);
    U = A;
    
    for j = 1:n-1
        if abs(U(j,j)) < 1e-12
            error('Pivô nulo encontrado. A fatoração LU sem pivotamento não é possível.');
        end
        
        for i = j+1:n
            multiplicador = U(i,j) / U(j,j);
            L(i,j) = multiplicador;
            U(i, j:n) = U(i, j:n) - multiplicador * U(j, j:n);
        end
    end
end


function x = resolver_por_lu(A, b)
    [L, U] = fatoracao_lu(A); 
    [n, ~] = size(A);
    
    y = zeros(n, 1);
    y(1) = b(1) / L(1,1);
    for i = 2:n
        soma = L(i, 1:i-1) * y(1:i-1);
        y(i) = (b(i) - soma) / L(i,i);
    end
    
    x = zeros(n, 1);
    for i = n:-1:1
        soma = U(i, i+1:n) * x(i+1:n);
        x(i) = (y(i) - soma) / U(i,i);
    end
end

function x = gauss_com_pivoteamento(A, b)
    [n, ~] = size(A);
    Ab = [A, b];
    for j = 1:n-1
        [~, indice_max] = max(abs(Ab(j:n, j)));
        indice_max = indice_max + j - 1;
        if indice_max ~= j
            Ab([j, indice_max], :) = Ab([indice_max, j], :);
        end
        if abs(Ab(j,j)) < 1e-12
            error('Matriz é singular.');
        end
        for i = j+1:n
            m = Ab(i,j) / Ab(j,j);
            Ab(i, j:end) = Ab(i, j:end) - m * Ab(j, j:end);
        end
    end
    U = Ab(:, 1:n);
    c = Ab(:, n+1);
    x = zeros(n, 1);
    for i = n:-1:1
        x(i) = (c(i) - U(i, i+1:n) * x(i+1:n)) / U(i,i);
    end
end

%% Análise dos Métodos

% Eliminação Gaussiana Simples:
% Prós: É o método mais fundamental e fácil de entender conceitualmente.
% Contras: É numericamente instável. Se um elemento pivô (o A(j,j) usado para dividir) for zero ou muito próximo de zero, o método falha ou acumula grandes erros de arredondamento.

% Fatoração LU:
% Prós: Extremamente eficiente, especialmente se você precisar resolver o mesmo sistema Ax=b para vários vetores b diferentes. Uma vez que a decomposição L e U é feita (que é a parte mais "cara"), resolver para um novo b é muito rápido.
% Contras: O conceito pode ser um pouco mais abstrato que a eliminação direta.

% Eliminação Gaussiana com Pivotamento Parcial:
% Prós: É a versão robusta da Eliminação Gaussiana. Ao trocar as linhas para sempre usar o maior pivô possível, ele evita a divisão por zero e minimiza os erros de arredondamento, tornando-o numericamente estável para a grande maioria das matrizes não singulares.
% Contras: Um pouco mais complexo de implementar que a versão simples, pois exige a lógica de busca e troca de linhas.

