/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_GOLANG_MODULE_H
#define NGX_HTTP_GOLANG_MODULE_H

#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_config.h>
#include <nginx.h>

#define NGX_HTTP_GOLANG_MODULE_NAME "ngx_golang"
#define NGX_HTTP_GOLANG_MODULE_VERSION "0.0.1"

extern ngx_module_t ngx_http_golang_module;
ngx_http_request_t *ngx_golang_request;

typedef struct {
    unsigned enabled_content_handler:1;
} ngx_http_golang_main_conf_t;

typedef struct {

    ngx_int_t (*content_handler)(ngx_http_request_t *r);
} ngx_http_golang_loc_conf_t;

typedef struct ngx_http_golang_rputs_chain_list_t {
    ngx_chain_t **last;
    ngx_chain_t *out;
} ngx_http_golang_rputs_chain_list_t;

typedef struct ngx_http_golang_ctx_t {
    ngx_http_golang_rputs_chain_list_t *rputs_chain;
    unsigned request_body_more : 1;
    
} ngx_http_golang_ctx_t;

#endif