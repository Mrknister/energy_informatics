#!/bin/bash

echo "set boxwidth 0.5;
set style fill solid;
stats \"$1\" u 0:1 nooutput;
set yrange [0:STATS_max_y + 0.3];
plot \"$1\" using 0:1 with boxes;
pause mouse" | gnuplot
