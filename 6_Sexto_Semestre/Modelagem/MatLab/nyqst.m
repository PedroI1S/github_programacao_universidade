% Definir a variável complexa 's'
s = tf('s');

% Definir a Função de Transferência G(s)
% Numerador: 100 * (s + 5)
% Denominador: s * (s + 3) * (s^2 + 4)
G = (100 * (s + 5)) / (s * (s + 3) * (s^2 + 4));

% Criar o Diagrama de Nyquist
figure;
nyquist(G);
title('Diagrama de Nyquist do Sistema 4');
grid on;

% Opcional: Ajustar limites dos eixos se o gráfico ficar muito afastado
axis([-20 20 -20 20]);