#ifndef __MERCKU_TOOLS_LINUX_AUTH_H__
#define __MERCKU_TOOLS_LINUX_AUTH_H__

#include <core/mercku_error.h>
#include <stdbool.h>

MError *encrypt_password(const char *salt, const char *password, char *crypt_passwd);
bool validate_user_password(const char *username, const char *password);

#endif // __MERCKU_TOOLS_LINUX_AUTH_H__