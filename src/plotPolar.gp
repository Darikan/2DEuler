
set grid
set title "Polára profilu Clark-Y"
set xlabel "Cl"
set ylabel "AoA"
set datafile separator ","
plot clPolar.csv using 1:2 with lines
pause mouse

