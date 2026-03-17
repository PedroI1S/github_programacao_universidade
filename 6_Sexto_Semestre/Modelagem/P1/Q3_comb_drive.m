% Q3_comb_drive.m
% Simulacao do atuador tipo comb-drive (capacitor variavel) acoplado a RL.
% Estados: x (m), xdot (m/s), q (C), i (A)
% Equacoes (derivadas no enunciado/solucao):
%   M*xddot + b*xdot + k*x = f(t) - fe(q)
%   fe(q) = q^2/(2*epsilon*A) (direcao opondo +x)
%   qdot = i
%   L*idot + R*i + vc = vin(t),  vc = q / C(x),  C(x) = epsilon*A/(d0 - x)
%
% Ajuste os parametros abaixo conforme o seu caso. Valores sao apenas exemplo.

clear; clc;

% ---------- Parametros fisicos (edite conforme necessario) ----------
params.epsilon = 8.854e-12;   % permissividade eletrica [F/m]
params.A       = 1e-8;        % area efetiva das placas [m^2] (placeholder)
params.d0      = 2e-6;        % folga inicial entre placas [m]

params.M = 2e-6;              % massa [kg]
params.b = 1e-5;              % amortecimento mecanico [N*s/m]
params.k = 0.5;               % rigidez [N/m]

params.R = 100;               % resistencia [ohm]
params.L = 1e-3;              % indutancia [H]

params.fe_sign = 1;           % +1: fe se opoe a +x (adicionado com sinal negativo na dinamica)

% ---------- Entradas ----------
V0 = 5;                        % passo de tensao (V)
vinfun = @(t) V0.*(t>=0);      % vin(t)
ffun   = @(t) 0.*t;            % forca mecanica externa f(t)

% ---------- Simulacao ----------
tspan = [0 0.05];              % tempo de simulacao (s)
y0 = [0; 0; 0; 0];             % [x; xdot; q; i] iniciais

opts = odeset('RelTol',1e-6,'AbsTol',1e-9);
[t,y] = ode45(@(t,y) comb_drive_ode(t,y,params,vinfun,ffun), tspan, y0, opts);

x    = y(:,1);
xdot = y(:,2);
q    = y(:,3);
i    = y(:,4);

% Grandezas derivadas
C    = params.epsilon*params.A./max(params.d0 - x, 0.1*params.d0);
vc   = q ./ C;                      % tensao no capacitor
fe   = (q.^2)./(2*params.epsilon*params.A);   % modulo da forca eletrostatica

% ---------- Equilibrio estatico para vin = V0, f = 0 ----------
% Para degrau de tensao Vin=V0 e f(t)=0, no regime: i=0, xdot=0 =>
% q* = C(x*)*V0 e k*x* = -fe(x*) (com nossa convencao de sinal padrao fe_sign=+1)
% fe(x) = (epsilon*A*V0^2)/(2*(d0 - x)^2)
% Aproximacao p/ |x| << d0: x* ≈ -(epsilon*A*V0^2)/(2*k*d0^2)
xss_approx = -(params.epsilon*params.A*V0^2)/(2*params.k*params.d0^2);

% Solucao numerica precisa via fzero
try
    xss_num = comb_drive_equilibrium(V0, 0, params, params.fe_sign);
catch
    xss_num = NaN;
end

% ---------- Graficos ----------
figure('Name','Comb-drive: respostas');
subplot(2,2,1); plot(t,x,'LineWidth',1.4); hold on;
yl = ylim; 
plot([t(1) t(end)],[xss_approx xss_approx],'--','Color',[0.2 0.6 0.2],'LineWidth',1.0);
if ~isnan(xss_num)
    plot([t(1) t(end)],[xss_num xss_num],':','Color',[0.85 0.33 0.1],'LineWidth',1.2);
end
ylim(yl); grid on;
xlabel('t (s)'); ylabel('x (m)'); title('Deslocamento x(t)');
legend({'x(t)','x* aprox','x* numerico'},'Location','best');

subplot(2,2,2); plot(t,q,'LineWidth',1.4); grid on;
xlabel('t (s)'); ylabel('q (C)'); title('Carga q(t)');

subplot(2,2,3); plot(t,i,'LineWidth',1.4); grid on;
xlabel('t (s)'); ylabel('i (A)'); title('Corrente i(t)');

subplot(2,2,4); plot(t,vc,'LineWidth',1.4); grid on;
xlabel('t (s)'); ylabel('v_c (V)'); title('Tensao no capacitor v_c(t)');

% Informacoes finais no console
fprintf('Simulacao concluida. Max |x| = %.3e m, Max |q| = %.3e C, Max |i| = %.3e A\n', ...
    max(abs(x)), max(abs(q)), max(abs(i)));
fprintf('Equilibrio (aprox pequeno deslocamento): x* ≈ % .3e m\n', xss_approx);
if ~isnan(xss_num)
    fprintf('Equilibrio (numerico):                  x* = % .3e m\n', xss_num);
end

% Observacoes:
% - As constantes aqui sao ilustrativas; ajuste-as para o seu dispositivo.
% - O guard max(d0-x, 0.1*d0) evita d -> 0 durante a numerica. Para estudo de
%   puxamento (pull-in), reduza esse limite com cautela.
