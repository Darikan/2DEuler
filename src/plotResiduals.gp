set output 'graphs.eps';
set size 2,2
set multiplot layout 1, 2
set grid
set logscale y
set title "Convergence process"
set xlabel "Iterations"
set ylabel "Residuals"
set datafile separator ","
plot "residuals.csv" using 1:2  with lines title "rho_x", '' using 1:3 with lines title "rho_y", '' using 1:4 with lines title "p", '' using 1:5 with lines title "rho", '' using 1:6 with lines title "e"

set title "Cl coefficient"
unset logscale y
set xlabel "Iterations"
set ylabel "Cl"
plot "cls.csv" using 1:2 with lines title "Cl"

unset multiplot
pause mouse

