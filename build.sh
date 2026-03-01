#!/bin/bash
set -e

# Default: Redis-only build (ENABLE_SSDB_ROCKS=OFF). Pass -DENABLE_SSDB_ROCKS=ON to enable SSDB/RocksDB.
mkdir -p cmakebuild
cd cmakebuild
cmake "$@" .. 

START=$(date +%s)
make
#make test ARGS="-VV"
END=$(date +%s)
echo "Total build time (real) = $(( $END - $START )) seconds"
