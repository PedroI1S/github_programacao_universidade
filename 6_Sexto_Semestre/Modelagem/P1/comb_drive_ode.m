function dydt = comb_drive_ode(t,y,params,vinfun,ffun)
% ODE do atuador comb-drive acoplado a circuito RL
% Estados y = [x; xdot; q; i]
% Parametros: params.epsilon, params.A, params.d0, params.M, params.b, params.k, params.R, params.L
% Entradas: vinfun(t) (V), ffun(t) (N)

x    = y(1);
xdot = y(2);
q    = y(3);
i    = y(4);

% Capacitancia variavel C(x) = eps*A/(d0 - x).
% IMPORTANTE: d(x) = d0 - x > 0 para manter placas sem toque.
d = params.d0 - x;
% Pequena protecao numerica (evita d ~ 0). Ajuste com cuidado se estudar pull-in.
if d < 1e-12
    d = 1e-12;
end
C = params.epsilon*params.A / d;

% Tensao no capacitor: v_c = q / C(x)
vc = q / C;

% Forca eletrostatica (modulo): fe = q^2/(2*eps*A); direcao contraria a +x
fe = (q^2)/(2*params.epsilon*params.A);

% Dinamica mecanica: M*xddot + b*xdot + k*x = f(t) - fe (opoe-se ao +x)
M = params.M; b = params.b; k = params.k;
ft = ffun(t);
xddot = (ft - params.fe_sign*fe - b*xdot - k*x) / M;

% Dinamica eletrica: L*idot + R*i + v_c = v_in(t)
R = params.R; L = params.L;
vin = vinfun(t);
idot = (vin - R*i - vc) / L;

% qdot = i
qdot = i;

% Monta vetor de derivadas
dydt = [xdot; xddot; qdot; idot];
end
