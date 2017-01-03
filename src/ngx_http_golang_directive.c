/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#include "ngx_http_golang_directive.h"
#include "ngx_http_golang_module.h"

char *
ngx_http_golang_content_phase(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_golang_main_conf_t *gmcf;
    ngx_http_golang_loc_conf_t *plcf;
    ngx_str_t *value;

    if (cmd->post == NULL) {
        return NGX_CONF_ERROR;
    }

    gmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_golang_module);
    plcf = conf;

    if (plcf->content_handler != NULL) {
        return "is deplicated";
    }

    value = cf->args->elts;

    plcf->content_handler = cmd->post;

    gmcf->enabled_content_handler = 1;

    return NGX_CONF_OK;
}