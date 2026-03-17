
function [L, U] = lu_factorization(A)

    n = size(A, 1);

    L = eye(n);
    U = A;

    for k = 1:n-1
        for i = k+1:n
            m = U(i,k) / U(k,k);
            U(i, :) = U(i, :) - m * U(k, :);
            L(i, k) = m;
        end
    end
end

A = [2, 3, 1; 
     4, 1, -1; 
     2, 1, 3];

[L, U] = lu_factorization(A);

disp('Matriz L:');
disp(L);
disp('Matriz U:');
disp(U);