#!/bin/bash

echo "
set terminal png size 800,520 medium
set output 'event_plot.png'

stats '$1' using 1 nooutput name 'Y_'
stats  '$1' using ((\$0-320)/16000) nooutput name 'X_'
x_margin = (X_max-X_min) * 0.075
set xrange [X_min -x_margin: X_max + x_margin]
set yrange [Y_min*1.15:Y_max*1.15]

set xlabel 'seconds'
set ylabel 'current'

plot '$1' using ((\$0-320)/16000):1 title '$1' with points lc rgb '#0066cc' ps 0.7" | gnuplot
