#!/bin/bash

uk_dale_path=/media/users/Shared/Seminar

valgrind -v --tool=callgrind ../build/performanceanalysis/performanceanalysis $uk_dale_path/UkDale/house_1/vi-1462982400_208337.flac  $uk_dale_path/UkDale/house_1/calibration.cfg $uk_dale_path/uk-power-data-zip-download/house_1/
