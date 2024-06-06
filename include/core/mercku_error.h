#ifndef __MERCKU_ERROR__
#define __MERCKU_ERROR__

#include "gcc.h"
#include "mem.h"
#include "debug.h"

typedef enum ecode
{
    EOK = 0,
    EInvalidArg,
    EInvalidVersion,
    ENoMem,
    EInvalidSN,
    EUnsupportedMethod,
    EStrategy, // 策略问题，不允许执行
    ERpc,
    ERpcSendFailed,
    ERpcRecvFailed,
    ERpcBrokenProtocol, // 返回数据有问题
    EBlacklistFull,
    EBrokenFW,
    EPlatformNotSupport, // 平台不支持
    EAgain,              // 重试, 一般是任务未完成
    ESystemUpgrading,    // 正在升级
    ENotAllowed,         // 不允許行為
    ERepeat,             // 不允许重复操作

    // io error
    EIOFailed = 100,
    EUnknownAccount,
    EWrongPasswd,
    EFileMissing,
    // 创建文件失败
    ECreateFile,
    EBrokenFile,
    ESpaceNotEnough,
    EBrokenMtd, // mtd 有问题

    // auth error
    EAuth = 200,
    ENoUser, // 用户不存在

    // feature error
    ERuleLimit = 300,  // 超出支持的规则数量
    ECfgNotFound,      // 配置不存在
    ECfgNameConflict,  // 配置名冲突
    EBrokenCfg,        // 底层配置有问题
    ENoNewerVersion,   // 没有新版本
    EDownloadFWFailed, // 下载固件失败

    // network error
    ENetwork = 400,
    EHttp,
    EInvalidResp,
    EUbusFailed,
    EUbusUnknownObj,

    // system error
    ESystem = 900,
    ESystemCmd, // 系统命令执行失败
    ETimeout,
    EUnknownSN,  // 未知sn
    ERnServer,   // 服务器错误
    EUnknownDev, // 未知设备

    // new name 对应的消息需要再看
    EWifiDown = 600408,

    // 不能在同一子网
    EIPUltralimit,
    EIPConflict,

} ecode;

#define MERROR_CAUSE_LEN_MAX 1024

typedef struct
{
    ecode code;
    char cause[MERROR_CAUSE_LEN_MAX + 1];
    struct
    {
        const char *file;
        int line;
    } location;
} MError;

MError *merror_new_full_inner(const char *file, int line, ecode code, const char *cause);
MError *merror_new_full_fmt_inner(const char *file, int line, ecode code, const char *fmt, ...);
/**
 * @brief 将 err 序列化为可读字符串
 *
 * @param err
 * @return const char* 注意，返回的字符串指针是全局共用的，不要 free
 */
const char *merror_to_string(MError *err);

#define merror_new_full(code, cause) merror_new_full_inner(__FILE__, __LINE__, code, cause)
#define merror_new_full_fmt(code, fmt, ...) merror_new_full_fmt_inner(__FILE__, __LINE__, code, fmt, ##__VA_ARGS__)

#define merror_new_simple(code) merror_new_full(code, 0)

#define merror_free(err)        \
    ({                          \
        if (err)                \
            tracable_free(err); \
        err = NULL;             \
    })

#define merror_is_err(err, type) ((err) && (err)->code == (type))
#define merror_is_ok(err) (!err || err->code == EOK)
#define merror_must_ok(err) assert_fmt(merror_is_ok(err), "error occurs: %s", merror_to_string(err))

#define merror_log(err)                                          \
    do                                                           \
    {                                                            \
        if (!merror_is_ok(err))                                  \
        {                                                        \
            xerror("error occurs: [%s]", merror_to_string(err)); \
        }                                                        \
    } while (false)

#define merror_ok_or_else(err, elseExpr) \
    if (!merror_is_ok(err))              \
    {                                    \
        elseExpr;                        \
    }

#define merror_ok_or_goto(err, label) \
    do                                \
    {                                 \
        if (!merror_is_ok((err)))     \
        {                             \
            goto label;               \
        }                             \
    } while (false)

#define merror_ok_or_return(err)    \
    do                              \
    {                               \
        MError *tmp_err = (err);    \
        if (!merror_is_ok(tmp_err)) \
            return tmp_err;         \
    } while (false)

#define merror_return_if_not_ok(err) merror_ok_or_return(err)

#define vendor_not_support() merror_new_simple(EPlatformNotSupport)

#define merror_must_be_ok(err)                                      \
    do                                                              \
    {                                                               \
        if (!merror_is_ok(err))                                     \
        {                                                           \
            fatal("fatal error occurs: %s", merror_to_string(err)); \
        }                                                           \
    } while (false)

#define merror_ok_or_goto_but_skip(err, label, skip_code) \
    do                                                    \
    {                                                     \
        if (!merror_is_ok(err))                           \
        {                                                 \
            if (err->code != skip_code)                   \
            {                                             \
                goto label;                               \
            }                                             \
            else                                          \
            {                                             \
                merror_free(err);                         \
            }                                             \
        }                                                 \
    } while (false)

#define merror_ok_or_return_but_skip(err, skip_code) \
    do                                               \
    {                                                \
        if (!merror_is_ok(err))                      \
        {                                            \
            if (err->code != skip_code)              \
            {                                        \
                return err;                          \
            }                                        \
            else                                     \
            {                                        \
                merror_free(err);                    \
            }                                        \
        }                                            \
    } while (false)

#endif // __MERCKU_ERROR__
