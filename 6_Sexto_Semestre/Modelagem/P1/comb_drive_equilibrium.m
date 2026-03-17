function xss = comb_drive_equilibrium(Vin, fext, params, fe_sign)
% Resolve o equilibrio estatico para vin = Vin (constante) e f(t) = fext (constante)
% Assumimos regime: xdot=0, i=0 => q = C(x)*Vin, vc = Vin
% Equilibrio mecanico: k*x + b*0 = fext - fe_sign*fe(q(x))
% onde fe(q) = q^2/(2*eps*A), q(x) = C(x)*Vin = eps*A*Vin/(d0 - x)
% Logo fe(x) = (eps*A*Vin^2)/(2*(d0 - x)^2)

if nargin < 4
    fe_sign = 1; % mesma convencao do script
end

k = params.k; eps0 = params.epsilon; A = params.A; d0 = params.d0;

fe_fun = @(x) (eps0*A*Vin^2) ./ (2*(d0 - x).^2);
% Equacao: k*x = fext - fe_sign*fe(x)
F = @(x) k*x - (fext - fe_sign*fe_fun(x));

% Chute inicial usando aproximacao para |x| << d0
x0 = -(eps0*A*Vin^2)/(2*k*d0^2);

% Limites seguros para evitar d ~ 0
lb = -0.9*d0;  % placa afasta ate 90% do gap no sentido negativo
ub =  0.9*d0;  % aproxima ate 90% do gap

% Usa fzero com bracket
if F(lb)*F(ub) > 0
    % tenta ao redor do chute
    try
        xss = fzero(F, x0);
    catch
        % fallback em caso de falha numerica
        xss = NaN;
    end
else
    xss = fzero(F, [lb, ub]);
end
end
