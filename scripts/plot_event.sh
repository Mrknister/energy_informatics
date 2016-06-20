#!/bin/bash

echo "plot \"$1\" using 0:1; pause mouse" | gnuplot
