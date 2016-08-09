#!/bin/bash

uk_dale_path=/media/users/Shared/Seminar
for flac_file in $uk_dale_path/UkDale/house_1/*.flac; do
    valgrind -v --tool=callgrind ../build/performanceanalysis/performanceanalysis $flac_file $uk_dale_path/UkDale/house_1/calibration.cfg $uk_dale_path/uk-power-data-zip-download/house_1/
done
