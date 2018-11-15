#!/usr/bin/env bash

source $1/bin/activate
python3 $2 --xml-file $3 --result-dir $4 --render-script $5
