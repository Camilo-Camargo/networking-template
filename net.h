#ifndef __NET__
#define __NET__
#define NET_VERSION "0.0.1"

#include <stdio.h>
#include <stdbool.h>

typedef int Socket;
bool NET_is_valid_socket(Socket* socket);
void NET_close_socket(Socket* socket);
int NET_get_errno();

#define NET_DEBUG 1
#define NET_LOG(format, ...) if(NET_DEBUG) fprintf(stdout, "[LOG] " format "\n", ##__VA_ARGS__)
#define NET_WARN(format, ...) fprintf(stdout, "[WARN] " format "\n", ##__VA_ARGS__)
#define NET_ERROR(format, ...) fprintf(stderr, "[ERROR] " format "\n", ##__VA_ARGS__)

struct _NET_Generic_Item;
typedef struct _NET_Generic_Item NET_Item;

void NET_init();
void NET_close();

#endif
