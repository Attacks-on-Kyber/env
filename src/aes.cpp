#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/rand.h>

int aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                unsigned char *iv, unsigned char *ciphertext) {
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new())) {
    printf("EVP_CIPHER_CTX_new error\n");
    return -1;
  }

  /* Initialise the encryption operation. */
  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
    printf("EVP_EncryptInit_ex error\n");
    return -1;
  }

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
    printf("EVP_EncryptUpdate error\n");
    return -1;
  }
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
    printf("EVP_EncryptFinal_ex error\n");
    return -1;
  }
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int aes_decrypt(unsigned char *ciphertext, int ciphertext_len,
                unsigned char *key, unsigned char *iv,
                unsigned char *plaintext) {
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new())) {
    printf("EVP_CIPHER_CTX_new error\n");
    return -1;
  }

  /* Initialise the decryption operation. */
  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
    printf("EVP_DecryptInit_ex error\n");
    return -1;
  }

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext,
                             ciphertext_len)) {
    printf("EVP_DecryptUpdate error\n");
    return -1;
  }
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
    printf("EVP_DecryptFinal_ex error\n");
    return -1;
  }
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}