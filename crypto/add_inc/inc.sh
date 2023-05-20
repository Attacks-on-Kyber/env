#!/bin/bash
DIR=$1
HEADER=$(basename "$DIR").h
echo "#ifndef __ALL_HEADERS__" > "$HEADER"
echo "#define __ALL_HEADERS__" >> "$HEADER"
for file in "$DIR"/*.h
do
    echo "#include \"$file\"" >> "$HEADER"
done
echo "#endif" >> "$HEADER"
