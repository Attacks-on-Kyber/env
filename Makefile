CC = gcc
CXX = g++
CFLAGS += -O3 -march=native -fomit-frame-pointer
CXXFLAGS += -O3 -march=native -fomit-frame-pointer
LDFLAGS = -lcrypto

KYBER_PATH = ./crypto/kyber_kem/kyber512
KYBER_HEADERS = $(KYBER_PATH)/api.h $(KYBER_PATH)/cbd.h $(KYBER_PATH)/fips202.h \
     $(KYBER_PATH)/indcpa.h $(KYBER_PATH)/ntt.h $(KYBER_PATH)/params.h \
     $(KYBER_PATH)/poly.h $(KYBER_PATH)/polyvec.h $(KYBER_PATH)/reduce.h \
     $(KYBER_PATH)/rng.h $(KYBER_PATH)/verify.h $(KYBER_PATH)/symmetric.h
KYBER_SOURCE = $(KYBER_PATH)/cbd.c $(KYBER_PATH)/fips202.c $(KYBER_PATH)/indcpa.c \
		 $(KYBER_PATH)/kem.c $(KYBER_PATH)/ntt.c $(KYBER_PATH)/poly.c \
		 $(KYBER_PATH)/polyvec.c $(KYBER_PATH)/reduce.c $(KYBER_PATH)/rng.c \
		 $(KYBER_PATH)/verify.c $(KYBER_PATH)/symmetric-shake.c

HEADERS = $(KYBER_HEADERS) \
		./src/inc.h ./src/utils/utils.h ./src/aes.h
SOURCE_CLIENT = $(KYBER_SOURCE) \
		./src/client.cpp ./src/utils/utils.cpp ./src/aes.cpp
SOURCE_SERVER = $(KYBER_SOURCE) \
		./src/server.cpp ./src/utils/utils.cpp ./src/aes.cpp
TAEGET_CLIENT = ./bin/client
TAEGET_SERVER = ./bin/server

client: $(SOURCE_CLIENT) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TAEGET_CLIENT) $(SOURCE_CLIENT) $(LDFLAGS)

server: $(SOURCE_SERVER) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TAEGET_SERVER) $(SOURCE_SERVER) $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(TAEGET_CLIENT) $(TAEGET_SERVER)