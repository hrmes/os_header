#ifndef __NOCAPI_EXT__
#define __NOCAPI_EXT__

#include <core/nocapi.h>
#include <core/mercku_error.h>

RouterCommandResponse *router_command_response_new_error_fmt(enum Method method,
                                                             ResponseErrorCode code,
                                                             const char *fmt, ...);

// 将 MError 转换为 RouterCommandResponse.
RouterCommandResponse *merror_to_router_command_response(Method method, const MError *err);

// 将 RouterCommandResponse 转换为 MError*.不是则返回 NULL.
#define router_command_response_to_merror(resp) \
    (resp ? ((resp->error) ? merror_new_full(resp->error->code, resp->error->msg) : NULL) : merror_new_full(EInvalidResp, "resp is NULL"))

void router_model_fill(RouterModel *model, char A, char B, char J);

MError *v1_router_command_validate(RouterCommand *cmd);
FFIError v1_router_command_response_to_json(const RouterCommandResponse *self, char **json);
void v1_router_command_amend(RouterCommand *cmd);

/**
 * @brief 负责回收 map_iterate 返回的 MapTuple** 的内存。注意：只回收数组及元素本身，key/value 不会回收。
 *
 * @param tuples
 */
void map_tuple_free(MapTuple **tuples);

WireguardCfg *wireguard_cfg_clone(const WireguardCfg *cfg);

void do_router_command_debug(const RouterCommand *inst, const char *file, int line);

#define rust_router_command_debug(inst) do_router_command_debug(inst, __FILE__, __LINE__)

void do_router_command_response_debug(const RouterCommandResponse *inst, const char *file, int line);
#define rust_router_command_response_debug(inst) do_router_command_response_debug(inst, __FILE__, __LINE__)

void do_rust_app_response_debug(const AppResponse *inst, const char *file, int line);
#define rust_app_response_debug(inst) do_rust_app_response_debug(inst, __FILE__, __LINE__)

void do_rust_mtk7981_dumps_topology_debug(const Mtk7981DumpsTopology *inst, const char *file, int line);
#define rust_mtk7981_dumps_topology_debug(inst) do_rust_mtk7981_dumps_topology_debug(inst, __FILE__, __LINE__)

    uint32_t api_tx_power_to_percentage(const ApiTxPower tx_power);
ApiTxPower api_tx_power_from_percentage(const uint32_t percentage);

#endif // __NOCAPI_EXT__