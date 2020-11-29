unset label
set title "Value of the 10-dimensional integral "
set ylabel "I"
set xlabel "numbers of steps N"
set term png                #will produce .png output
set output 'mean-N.png'#output to any filename.png you want        
set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid xtics lc rgb "#bbbbbb" lw 1 lt 0
plot 'mean.dat' using 1:2 title 'Simple sampling' w l, 'mean.dat' using 1:3 title 'Rejection method' w l, 'mean.dat' using 1:4 title 'MC with importance sampling' w l
