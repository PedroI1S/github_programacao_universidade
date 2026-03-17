function U = triangulariza(A)
    [n, m] = size(A);
    if n ~= m
        error('A matriz inserida deve ser quadrada');
    end

    U = A;
    for k = 1:n-1
        for i = k+1:n
            factor = U(i,k) / U(k,k);
            U(i, k:end) = U(i, k:end) - factor * U(k, k:end);
        end
    end
end

A = [4, 2, 3, 5; 
     2, 3, 1, 3; 
     1, 1, 2, 1;
     3, 4, 2, 1w];

U = triangulariza(A);

disp('Matriz de superior positiva: ');
disp(U);