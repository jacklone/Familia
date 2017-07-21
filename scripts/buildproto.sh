#!/usr/bin/env bash

# cpp generate
protoc -I ../proto --grpc_out=../proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ../proto/familiaapi.proto

protoc -I ../proto --cpp_out=../proto ../proto/familiaapi.proto

#
python3 -m grpc_tools.protoc -I ../proto --python_out=../proto --grpc_python_out=../proto ../proto/familiaapi.proto

