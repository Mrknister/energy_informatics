#!/bin/bash

echo "
set terminal png size 800,520 medium
set output 'fft_plot.png'

stats '$1' using 1 nooutput name 'Y_'


set xrange [0:300]
set yrange [Y_min*1.15:Y_max*1.15]

set xlabel 'frequency'
set ylabel 'fft'

plot '$1' using (\$0*2):1 title '$1' with points lc rgb '#0066cc' ps 0.7" | gnuplot
