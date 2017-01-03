/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#include "ngx_http_golang_module.h"
#include "ngx_http_golang_handler.h"

#include <libcgongx.h>

ngx_int_t 
ngx_http_golang_content_handler(ngx_http_request_t *r)
{
    ngx_http_golang_loc_conf_t *plcf;
    plcf = ngx_http_get_module_loc_conf(r, ngx_http_golang_module);
    if (plcf->content_handler == NULL) {
        return NGX_DECLINED;
    }
    return plcf->content_handler(r);
}

ngx_int_t
ngx_http_golang_content_func_handler(ngx_http_request_t *r)
{
    //ngx_http_golang_loc_conf_t *glcf = ngx_http_get_module_loc_conf(r, ngx_http_golang_module);
    ngx_http_golang_ctx_t *ctx = ngx_http_get_module_ctx(r, ngx_http_golang_module);

    ngx_int_t rc;

    if (ctx == NULL) {
        ctx = ngx_pcalloc(r->pool, sizeof(*ctx));
        if (ctx == NULL) {
            return NGX_ERROR;
        }
    }

    ctx->request_body_more = 1;
    ngx_http_set_ctx(r, ctx, ngx_http_golang_module);

    ngx_golang_request = r;

    ngx_http_golang_rputs_chain_list_t *chain;
    chain = ctx->rputs_chain;

    if (ctx->rputs_chain == NULL){
        ngx_buf_t *b;
        ngx_str_t ns;
        u_char *u_str;
        
        //ns.data = (u_char *)" ";
        //ns.len = 1;
        char *str = "abc";
        ns.data = (u_char *) cgo_ngx_echo(str);
        ns.len = strlen((char *)ns.data);
        
        chain = ngx_pcalloc(r->pool, sizeof(ngx_http_golang_rputs_chain_list_t));
        chain->out = ngx_alloc_chain_link(r->pool);
        chain->last = &chain->out;
    
        b = ngx_calloc_buf(r->pool);
        (*chain->last)->buf = b;
        (*chain->last)->next = NULL;

        u_str = ngx_pstrdup(r->pool, &ns);
        //u_str[ns.len] = '\0';
        (*chain->last)->buf->pos = u_str;
        (*chain->last)->buf->last = u_str + ns.len;
        (*chain->last)->buf->memory = 1;
        ctx->rputs_chain = chain;

        if (r->headers_out.content_length_n == -1){
            r->headers_out.content_length_n += ns.len + 1;
        }else {
            r->headers_out.content_length_n += ns.len;
        }
    }



    //r->headers_out.content_type.len = sizeof("text/html") - 1;
    //r->headers_out.content_type.data = (u_char *)"text/html";
    if (!r->headers_out.status){
        r->headers_out.status = NGX_HTTP_OK;
    }

    if (r->method == NGX_HTTP_HEAD){
        rc = ngx_http_send_header(r);
        if (rc != NGX_OK){
            return rc;
        }
    }

    if (chain != NULL){
        (*chain->last)->buf->last_buf = 1;
    }

    rc = ngx_http_send_header(r);
    if (rc != NGX_OK){
        return rc;
    }

    ngx_http_output_filter(r, chain->out);

    ngx_http_set_ctx(r, NULL, ngx_http_golang_module);

    return NGX_OK;
}

