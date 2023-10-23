#include "net.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#endif

int main() {
  NET_init();
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;       // IPV4 address
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;     // wildcard to used in bind()

  struct addrinfo *bind_address;
  char *port_number = "8080";
  getaddrinfo(0, port_number, &hints, &bind_address);

  Socket socket_listen;
  socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
                         bind_address->ai_protocol);

  if (!NET_is_valid_socket(&socket_listen)) {
    NET_ERROR("socket() failed with error number: %d", NET_get_errno());
    return 1;
  }

  if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
    NET_ERROR("bind failed with error number: %d", NET_get_errno());
    return 1;
  }

  freeaddrinfo(bind_address);

  if (listen(socket_listen, 10)) {
    NET_ERROR("listen() failed with error number: %d", NET_get_errno());
  }

  struct sockaddr_storage client_address;
  socklen_t client_len = sizeof(client_address);
  Socket socket_client =
      accept(socket_listen, (struct sockaddr *)&client_address, &client_len);

  if (!NET_is_valid_socket(&socket_client)) {
    NET_ERROR("accept() failed invalid socket with number %d", NET_get_errno());
    return 1;
  }

  char client_address_buffer[BUFSIZ];
  getnameinfo((struct sockaddr *)&client_address, client_len,
              client_address_buffer, sizeof(client_address_buffer), 0, 0,
              NI_NUMERICHOST);
  NET_WARN("Client connected with ip: %s", client_address_buffer);

  char request[1024];
  int request_bytes_recieved = recv(socket_client, request, sizeof(request), 0);

  if (request_bytes_recieved < 0) {
    NET_ERROR("Client send 0 bytes");
    return 1;
  }

  const char *response = "HTTP/1.1 200 OK\r\n"
                         "Connection: close\r\n"
                         "Content-Type: text/plain\r\n\r\n"
                         "Local time is: ";

  int response_bytes_send = send(socket_client, response, strlen(response), 0);

  time_t timer;
  time(&timer);
  char *time_msg = ctime(&timer);
  response_bytes_send = send(socket_client, time_msg, strlen(time_msg), 0);
  NET_close_socket(&socket_client);
  NET_close();
}
