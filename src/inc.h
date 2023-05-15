#ifndef INC_H
#define INC_H

#ifndef KYBER_VERSION
#define KYBER_VERSION 2 /* version 2, 3, 4 */
#endif

// #define KYBER_VERSION_90S /* commit */

#if (KYBER_VERSION == 2)
#ifdef  KYBER_VERSION_90S
#include "../crypto/kyber_kem/kyber512-90s/api.h"
#define KYBER_VERSION_STRING "KYBER_512_90S"
#else
#include "../crypto/kyber_kem/kyber512/api.h"
#define KYBER_VERSION_STRING "KYBER_512"
#endif
#elif (KYBER_VERSION == 3)
#ifdef  KYBER_VERSION_90S
#include "../crypto/kyber_kem/kyber768-90s/api.h"
#define KYBER_VERSION_STRING "KYBER_768_90S"
#else
#include "../crypto/kyber_kem/kyber768/api.h"
#define KYBER_VERSION_STRING "KYBER_768"
#endif
#elif (KYBER_VERSION == 4)
#ifdef  KYBER_VERSION_90S
#include "../crypto/kyber_kem/kyber1024-90s/api.h"
#define KYBER_VERSION_STRING "KYBER_1024_90S"
#else
#include "../crypto/kyber_kem/kyber1024/api.h"
#define KYBER_VERSION_STRING "KYBER_1024"
#endif

#endif /* INC_H */
