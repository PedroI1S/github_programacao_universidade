%metodo de newton
clear
%dados: f, chute inicial, maximo de itercoes e tolerancia
f=@(x) x^3-9*x+3;
df=@(x) 3*x^2-9;
x(1)=0;
tol=0.0005;
max_iter=1000;
%metodo
for k = 1 : max_iter
    x(k+1)=x(k)-f(x(k))/df(x(k));
    if abs(x(k+1)-x(k))<tol && abs(f(x(k+1)))<tol
        break;
    end       
end
num_iterac=k;
sol_aprox=x(k+1);
f_x_k=f(sol_aprox);
