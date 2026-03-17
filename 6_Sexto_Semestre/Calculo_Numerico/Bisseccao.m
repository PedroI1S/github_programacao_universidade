
function root = bisec(func, a, b, tol)
    if func(a) * func(b) > 0
        error('The function must change signs over the interval [a, b].');
    end

    fprintf('Initial interval: [%f, %f]\n', a, b);

    midpoints = [];

    while (b - a) / 2 > tol
        c = (a + b) / 2;
        midpoints = [midpoints, c];
        fprintf('Current bounds: [%f, %f], Midpoint: %f, f(c): %f\n', a, b, c, func(c));

        if func(c) == 0
            break;
        elseif func(a) * func(c) < 0
            b = c;
        else
            a = c;
        end
    end

    root = (a + b) / 2;
    fprintf('Final approximation of root: %f\n', root);

    figure;
    plot(midpoints, func(midpoints), '.', 'MarkerSize', 8);
    xlabel('Midpoints');
    ylabel('Function Value');
    title('Bisection Method Convergence');
    grid on;
    hold on;
    yline(0, 'r-');
    xline(0, 'r-');
    legend('Midpoints', 'f(x) = 0');
    hold off;
end

approx_root_bissec = bisec(@(x) x.^2 - 2, 1, 2, 1e-6);