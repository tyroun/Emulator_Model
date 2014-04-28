#!/bin/sh
find ./ -name "*.cpp" -o -name "*.h" -o -name "*.hpp"|xargs wc -l > tmp_log
cat tmp_log
rm -rf tmp_log
