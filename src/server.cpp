#include "inc.h"
#include "utils/utils.h"
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "aes.h"

#define MAX_MARKER_LEN 50
#define KAT_SUCCESS 0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  // pk, sk, ct
  unsigned char pk[CRYPTO_PUBLICKEYBYTES];
  unsigned char ss[CRYPTO_BYTES];
  unsigned char ct[CRYPTO_CIPHERTEXTBYTES];

  /* socket start */
  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // Receiving pk
  if ((valread = read(new_socket, pk, CRYPTO_PUBLICKEYBYTES)) < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }
  printf("Received public key from server\n");

  crypto_kem_enc(ct, ss, pk);

  printf("Received pk\n");
  print_hex(pk, CRYPTO_PUBLICKEYBYTES);

  // Sending ct
  if (send(new_socket, ct, CRYPTO_CIPHERTEXTBYTES, 0) < 0) {
    perror("send");
    exit(EXIT_FAILURE);
  }
  printf("Sent ciphertext to server\n");
  print_hex(ct, CRYPTO_CIPHERTEXTBYTES);

  printf("Shared secret\n");
  print_hex(ss, CRYPTO_BYTES);

  // encrypt communication
  while (1){
    
  }
}
