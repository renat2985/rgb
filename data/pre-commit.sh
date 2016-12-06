#!/bin/bash
gzip -vrkf css/*.css
gzip -vrkf *.htm
gzip -vrkf js/*.js
gzip -vrkf lang/lang.*.json
