#include "../net.h"

#include <errno.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <stdbool.h>
#include <unistd.h>


void NET_init() { NET_LOG("initialize unix adapter."); }

void NET_close() { NET_LOG("closed unix adapter."); }

void NET_close_socket(Socket *socket){
  close(*socket);
}

int NET_get_errno(){
  return errno;
}

bool NET_is_valid_socket(Socket *socket){
  return (*socket) >= 0;
}
