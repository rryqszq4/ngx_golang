/**
 *    Copyright(c) 2016 rryqszq4
 *
 *
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_conf_file.h>
#include <nginx.h>

#include "ngx_http_golang_module.h"
#include "ngx_http_golang_directive.h"
#include "ngx_http_golang_handler.h"

static ngx_int_t ngx_http_golang_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_golang_handler_init(ngx_http_core_main_conf_t *cmcf, ngx_http_golang_main_conf_t *gmcf);

static void *ngx_http_golang_create_main_conf(ngx_conf_t *cf);
static char *ngx_http_golang_init_main_conf(ngx_conf_t *cf, void *conf);

static void *ngx_http_golang_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_golang_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);

static ngx_int_t ngx_http_golang_init_worker(ngx_cycle_t *cycle);
static void ngx_http_golang_exit_worker(ngx_cycle_t *cycle);

static ngx_command_t ngx_http_golang_commands[] = {

    {ngx_string("content_by_golang_func"),
     NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
        |NGX_CONF_TAKE1,
     ngx_http_golang_content_phase,
     NGX_HTTP_LOC_CONF_OFFSET,
     0,
     ngx_http_golang_content_func_handler
    },

    ngx_null_command
};

static ngx_http_module_t ngx_http_golang_module_ctx = {
    NULL,
    ngx_http_golang_init,

    ngx_http_golang_create_main_conf,
    ngx_http_golang_init_main_conf,

    NULL,
    NULL,

    ngx_http_golang_create_loc_conf,
    ngx_http_golang_merge_loc_conf
};

ngx_module_t ngx_http_golang_module = {
    NGX_MODULE_V1,
    &ngx_http_golang_module_ctx,
    ngx_http_golang_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    ngx_http_golang_init_worker,
    NULL,
    NULL,
    ngx_http_golang_exit_worker,
    NULL,
    NGX_MODULE_V1_PADDING
};

static ngx_int_t
ngx_http_golang_init(ngx_conf_t *cf)
{
    ngx_http_core_main_conf_t *cmcf;
    ngx_http_golang_main_conf_t *gmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
    gmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_golang_module);

    ngx_golang_request = NULL;

    if (ngx_http_golang_handler_init(cmcf, gmcf) != NGX_OK) {
        return NGX_ERROR;
    }

    return NGX_OK;
}

static ngx_int_t
ngx_http_golang_handler_init(ngx_http_core_main_conf_t *cmcf, ngx_http_golang_main_conf_t *gmcf)
{
    ngx_int_t i;
    ngx_http_handler_pt *h;
    ngx_http_phases phase;
    ngx_http_phases phases[] = {
        NGX_HTTP_CONTENT_PHASE,
    };
    ngx_int_t phases_c;

    phases_c = sizeof(phases) / sizeof(ngx_http_phases);
    for (i = 0; i < phases_c; i++) {
        phase = phases[i];
        switch (phase) {
            case NGX_HTTP_CONTENT_PHASE:
                if (gmcf->enabled_content_handler) {
                    h = ngx_array_push(&cmcf->phases[phase].handlers);
                    if (h == NULL) {
                        return NGX_ERROR;
                    }
                    *h = ngx_http_golang_content_handler;
                }
                break;
            default:
                break;
        }
    }

    return NGX_OK;
}

static void *
ngx_http_golang_create_main_conf(ngx_conf_t *cf)
{
    ngx_http_golang_main_conf_t *gmcf;

    gmcf = ngx_pcalloc(cf->pool, sizeof(ngx_http_golang_main_conf_t));
    if (gmcf == NULL) {
        return NULL;
    }

    return gmcf;
}

static char *
ngx_http_golang_init_main_conf(ngx_conf_t *cf, void *conf)
{
    return NGX_CONF_OK;
}

static void *
ngx_http_golang_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_golang_loc_conf_t *glcf;

    glcf = ngx_pcalloc(cf->pool, sizeof(ngx_http_golang_loc_conf_t));
    if (glcf == NULL) {
        return NGX_CONF_ERROR;
    }

    return glcf;
}

static char *
ngx_http_golang_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);


    return NGX_CONF_OK;
}

static ngx_int_t
ngx_http_golang_init_worker(ngx_cycle_t *cycle)
{
    ngx_http_golang_main_conf_t *gmcf;

    gmcf = ngx_http_cycle_get_module_main_conf(cycle, ngx_http_golang_module);

    return NGX_OK;
}

static void
ngx_http_golang_exit_worker(ngx_cycle_t *cycle)
{
    
}





