#!/bin/bash

#echo "set boxwidth 0.5;
#set style fill solid;
#stats \"$1\" u 0:1 nooutput;
#set yrange [0:STATS_max_y + 0.3];
#plot \"$1\" using 0:1 with boxes;
#pause mouse" | gnuplot
# !/bin/bash

echo "
set terminal png size 800,520 medium
set output 'rms_plot.png'

stats '$1' using 1 nooutput name 'Y_'
set style fill solid
set boxwidth 0.5

set yrange [0:Y_max*1.15]

set xlabel 'n'
set ylabel 'rms_n'

plot '$1' using 0:1 title '$1' with boxes lc rgb '#0066cc'
" | gnuplot
