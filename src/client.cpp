#include "inc.h"
#include "utils/utils.h"
#include <arpa/inet.h>
#include <chrono>
#include <ctype.h>
#include <functional>
#include <iostream>
#include <netinet/in.h>
#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <time.h>
#include <unistd.h>
#include "aes.h"

#define MAX_MARKER_LEN 50
#define KAT_SUCCESS 0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR -3
#define KAT_CRYPTO_FAILURE -4
#define PORT 8080

int key_gen(unsigned char *pk, unsigned char *sk) {
  if (crypto_kem_keypair(pk, sk) != 0) {
    printf("crypto_kem_keypair error\n");
    return -1;
  }
  return 0;
}

int main() {
  unsigned char pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
  unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
  unsigned char ss[CRYPTO_BYTES];
  key_gen(pk, sk);

  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};

  // Create socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  // Server information
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  // Connect to the server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

  // Send pk to server
  if (send(sock, pk, CRYPTO_PUBLICKEYBYTES, 0) < 0) {
    printf("Send failed\n");
    return -1;
  }
  printf("Public key sent to server\n");
  print_hex(pk, CRYPTO_PUBLICKEYBYTES);

  // Receive ct from server
  if (recv(sock, ct, CRYPTO_CIPHERTEXTBYTES, 0) < 0) {
    printf("Receive failed\n");
    return -1;
  }
  printf("Ciphertext received from server\n");
  print_hex(ct, CRYPTO_CIPHERTEXTBYTES);

  crypto_kem_dec(ss, ct, sk);
  printf("Shared secret\n");
  print_hex(ss, CRYPTO_BYTES);

  // send "hello" to server
  unsigned char *plaintext = (unsigned char *)"hello";
  int plaintext_len = strlen((char *)plaintext);
  unsigned char ciphertext[1024];
  unsigned char iv[16];
  memset(iv, 0x00, AES_BLOCK_SIZE);
  memset(ciphertext, 0x00, AES_BLOCK_SIZE);

  // Encrypt
  int ciphertext_len = aes_encrypt(plaintext, plaintext_len, ss, iv, ciphertext);
  print_hex(ciphertext, ciphertext_len);

  return 0;
}