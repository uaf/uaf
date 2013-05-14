#!/bin/bash

DIR=$(cd $(dirname "$0"); pwd)

rm -Rf $DIR/build/*
echo "$DIR/build has been cleaned up"

rm -Rf $DIR/lib/*
echo "$DIR/lib has been cleaned up"

rm -Rf $DIR/doc/html/*
echo "$DIR/doc/html has been cleaned up"

rm -Rf $DIR/examples/uaf/build/*
echo "$DIR/examples/uaf/build has been cleaned up"

rm -Rf $DIR/examples/uaf/bin/*
echo "$DIR/examples/uaf/bin has been cleaned up"


