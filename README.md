ngx_golang
==========

develop log
-----------
```sh
/usr/local/go/bin/go build -v -buildmode=c-shared -o libcgongx.so ngx_cgo_test_c.go ngx_cgo_test_api.go

./configure --prefix=/usr/local/nginx_golang_dev --with-ld-opt="-Wl,-rpath,/root/source1/ngx_golang/go/test" --add-module=/root/source1/ngx_golang

```