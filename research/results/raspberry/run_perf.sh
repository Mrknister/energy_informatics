#!/bin/bash


uk_dale_dir=/mnt/Seminar
for file in $uk_dale_dir/UkDale/house_1/*.flac; do 
	echo $file
	../build/performanceanalysis/performanceanalysis $file $uk_dale_dir/UkDale/house_1/calibration.cfg $uk_dale_dir/uk-power-data-zip-download/house_1/
	number=$(shuf -i 2000-65000 -n 1)
	mv gmon.out gmon.out.$number
done
