#!/bin/bash

wget http://nginx.org/download/nginx-1.6.3.tar.gz
tar zxvf nginx-1.6.3.tar.gz

mkdir src
mkdir src/auto
mkdir src/core
mkdir src/event
mkdir src/http
mkdir src/os src/os/unix

cd nginx-1.6.3
./configure

cp -r objs/ngx_auto_config.h ../src/auto/
cp -r objs/ngx_auto_headers.h ../src/auto/
cp -r objs/ngx_modules.c ../src/auto/

cp -r src/core/* ../src/core/
cp -r src/event/* ../src/event/
cp -r src/http/* ../src/http/
cp -r src/os/unix/* ../src/os/unix/

cp -r ../Makefile objs/

make
cp -r objs/libnginx.so ../
