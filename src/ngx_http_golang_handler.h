/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_GOLANG_HANDLER_H
#define NGX_HTTP_GOLANG_HANDLER_H

#include <nginx.h>
#include <ngx_http.h>

#include "ngx_http_golang_module.h"

ngx_int_t ngx_http_golang_content_handler(ngx_http_request_t *r);
ngx_int_t ngx_http_golang_content_func_handler(ngx_http_request_t *r);

#endif
