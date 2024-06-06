#ifndef __LIBASYNC_CLIENT_H__
#define __LIBASYNC_CLIENT_H__

#include <nng/nng.h>
#include <async_task.pb-c.h>

#define DFT_SOCKET "tcp://127.0.0.1:8899"

typedef struct
{
    nng_socket sock;
} Client;

Client *client_new(const char *url);
void client_free(Client *client);
RPCResponse *client_call(Client *client, const RPCRequest *req);

RPCResponse *client_async_reboot(Client *client, int delay_ms);
RPCResponse *client_async_reset(Client *client, int delay_ms);
RPCResponse *client_simple_call(Client *self, RPCMethod method, int delayMS);

#endif // __LIBASYNC_CLIENT_H__