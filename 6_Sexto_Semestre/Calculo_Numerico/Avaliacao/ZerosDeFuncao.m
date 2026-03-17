
% -- Limpeza do Ambiente --

clear;
clc;
close all;

%% -- Definicao das Variaveis --

syms x;
f_sym = x - cos(x);
df_sym = diff(f_sym, x);

fprintf('Função que está sendo usada: f(x) = %s\n', char(f_sym));
fprintf('Derivada da função: f''(x) = %s\n', char(df_sym));

f = matlabFunction(f_sym);
df = matlabFunction(df_sym);

tol = 5e-5;
max_iter = 100;

%% -- Execucao das Funcoes --

fprintf('\n--- Método da Bisseção ---\n');

a = 0;  % intervalo
b = pi/2; % da raiz

[raiz_bissecao, iter_bissecao] = metodo_bissecao(f, a, b, tol, max_iter);
f_valor_bissecao = subs(f_sym, x, raiz_bissecao);

if ~isnan(raiz_bissecao)
    fprintf('Raiz encontrada: %f\n', raiz_bissecao);
    fprintf('Número de iterações: %d\n', iter_bissecao);
    fprintf('Valor de f(raiz): %e\n\n', f_valor_bissecao);
end

fprintf('--- Método de Newton ---\n');

x0 = -2.8; % Chute inicial

[raiz_newton, iter_newton] = metodo_newton(f, df, x0, tol, max_iter);
f_valor_newton = subs(f_sym, x, raiz_newton);

if ~isnan(raiz_newton)
    fprintf('Raiz encontrada: %f\n', raiz_newton);
    fprintf('Número de iterações: %d\n', iter_newton);
    fprintf('Valor de f(raiz): %e\n\n', f_valor_newton);
end

%% -- Funcoes Newton e Bissecao --

function [raiz, iter] = metodo_bissecao(f, a, b, tol, max_iter)
    if f(a) * f(b) >= 0
        fprintf('Erro: f(a) e f(b) devem ter sinais opostos para garantir uma raiz no intervalo.\n');
        raiz = NaN;
        iter = 0;
        return;
    end
    for iter = 1:max_iter
        c = (a + b) / 2;
        if (b - a) / 2 < tol
            raiz = c;
            return;
        end
        if f(a) * f(c) < 0
            b = c;
        else
            a = c;
        end
    end
    fprintf('Aviso: O método da Bisseção atingiu o número máximo de iterações (%d).\n', max_iter);
    raiz = c;
end

function [raiz, iter] = metodo_newton(f, df, x0, tol, max_iter)
    x_atual = x0;
    for iter = 1:max_iter
        fx = f(x_atual);
        dfx = df(x_atual);
        if abs(dfx) < 1e-12
            fprintf('Erro: Derivada próxima de zero. O método de Newton falhou.\n');
            raiz = NaN;
            return;
        end
        x_prox = x_atual - fx / dfx;
        if abs(x_prox - x_atual) < tol
            raiz = x_prox;
            return;
        end
        x_atual = x_prox;
    end
    fprintf('Aviso: O método de Newton atingiu o número máximo de iterações (%d).\n', max_iter);
    raiz = x_prox;
end

%% Principais Diferenças entre os Métodos

% Método da Bisseção
% Garantia de Convergência: Sempre converge para uma raiz se o intervalo inicial [a, b] for válido (f(a) * f(b) < 0), e a função for continua no intervalo.
% Velocidade: É relativamente lento, pois reduz o intervalo pela metade a cada passo (convergência linear).
% Requisitos: Não precisa da derivada da função.


% Método de Newton
% Garantia de Convergência: A convergência não é garantida. Depende fortemente de um bom "chute" inicial e do comportamento da função.
% Velocidade: É muito mais rápido que a bisseção quando converge (convergência quadrática).
% Requisitos: Requer o cálculo da derivada da função, o que pode ser um ponto negativo se a derivada for complexa ou computacionalmente cara.


