#!/usr/bin/env bash

source $1/bin/activate
python3 src/resource_generation/generate.py --xml-file $2 --result-dir $3 --render-script $4
