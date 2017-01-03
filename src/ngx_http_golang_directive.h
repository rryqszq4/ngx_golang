/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#ifndef NGX_HTTP_GOLANG_DIRECTIVE_H
#define NGX_HTTP_GOLANG_DIRECTIVE_H

#include <ngx_config.h>
#include <ngx_conf_file.h>
#include <nginx.h>

char *ngx_http_golang_content_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

#endif
