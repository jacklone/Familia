#!/usr/bin/env bash

BinFile=../cmake-build-debug/extract_server

ModelDir="./model/news"
LdaConf="lda.conf"

$BinFile --model_dir="$ModelDir" --conf_file="$LdaConf"
