package main

// #cgo CFLAGS: -I../../lib/src/core -I../../lib/src/auto -I../../lib/src/event -I../../lib/src/http/modules -I../../lib/src/http -I../../lib/src/os/unix
// #cgo LDFLAGS: -L../../lib -lnginx
// #include <stdio.h>
// #include <stdlib.h>
// #include <ngx_core.h>
// #include <ngx_http.h>
// #include <ngx_string.h>
// #include <nginx.h>
import "C"
import "fmt"

func main() {
    f := C.intFunc(C.fortytwo)
    fmt.Println(int(C.bridge_int_func(f)))
}