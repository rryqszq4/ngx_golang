package main

import "C"
import "fmt"

//export cgo_ngx_echo
func cgo_ngx_echo(*C.char) *C.char {
    fmt.Println("I am a GoExportedFunc!")
    //f := C.intFunc(C.fortytwo)
    //fmt.Println(int(C.bridge_int_func(f)))

    return C.CString("I am a GoExportedFunc!");
}
