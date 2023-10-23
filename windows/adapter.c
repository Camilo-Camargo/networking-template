#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
 
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../net.h"

void NET_init(){
  NET_LOG("Initializing windows adapter.");

  WSADATA d;

  if(WSAStartup(MAKEWORD(2,2), &d)){
    NET_ERROR("Failed to initialize winsock2.");
    return;
  }
  NET_LOG("Initialize successfully.");
}

void NET_close(){
  WSACleanup();
  NET_LOG("closed windows adapter.");
}

void NET_close_socket(Socket *socket){
  closesocket(*socket);
}

int NET_get_errno(){
  return WSAGetLastError();
}

bool NET_is_valid_socket(Socket *socket){
  return (*socket) != INVALID_SOCKET;
}

