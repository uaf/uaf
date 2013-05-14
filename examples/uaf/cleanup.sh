#!/bin/bash

DIR=$(cd $(dirname "$0"); pwd)
rm -Rf $DIR/build/*
rm -Rf $DIR/bin/*
echo "$DIR/build and $DIR/bin/ have been cleaned up"
