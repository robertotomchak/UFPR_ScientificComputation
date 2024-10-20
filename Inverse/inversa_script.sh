#!/bin/bash
perf_output=$(likwid-perfctr -O -C 3 -g FLOPS_DP ./inversa)
size=$(echo "$perf_output" | head -n 6 | tail -n 1)
inverse_output=$(echo "$perf_output" | head -n $((8 + $size)) | tail -n $((3 + $size)))
first_line=$(echo "$perf_output" | grep "^FP_ARITH_INST_RETIRED_SCALAR_DOUBLE*" | cut -d"," -f1,3)
second_line=$(echo "$perf_output" | grep "^DP*" | cut -d"," -f1,2)

echo "$inverse_output"
echo ""
echo "$first_line"
echo "$second_line"
