# Ethereum Cash (name subject to change) is Ethereum
 [![Build Status](https://travis-ci.com/adlerjohn/ech-cpp-dev.svg?token=thfx7xMP5jxRY8q9pnoA&branch=master)](https://travis-ci.com/adlerjohn/ech-cpp-dev)
 [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/adlerjohn/ech-cpp-dev/raw/master/LICENSE)

This repository contains a proof-of-concept implementation for Ethereum Cash (name subject to change), a scalable side chain for Ethereum.
Work based on [source](https://arxiv.org/abs/1904.06441) paper.

## Disclaimer

This software is in early development, and as such is not meant to be used for anything by anyone.

## Dependencies

Install the following libraries as dependencies before compiling.
If you're using a Ubuntu <Bionic (18.04) then you may need to install [libsecp256k1](https://github.com/bitcoin-core/secp256k1) manually. 

```sh
sudo apt install libboost-dev librocksdb-dev libsecp256k1-dev \
    libcurl4-gnutls-dev libmicrohttpd-dev libjsoncpp-dev libargtable2-dev libhiredis-dev
```

[Crypto++](https://www.cryptopp.com/) needs to be installed separately, as the version in repositories is too old and doesn't have Keccak hashing.

```sh
wget -O cryptopp.zip https://www.cryptopp.com/cryptopp810.zip
unzip cryptopp.zip -d cryptopp
cd cryptopp
make
sudo make install
```

[libjsonrpc-cpp](https://github.com/cinemast/libjson-rpc-cpp) also needs to be installed separately.

```sh
wget -O libjson-rpc-cpp.tar.gz https://github.com/cinemast/libjson-rpc-cpp/archive/v1.2.0.tar.gz
tar -zxvf libjson-rpc-cpp.tar.gz
mkdir -p libjson-rpc-cpp-1.2.0/build
cd libjson-rpc-cpp-1.2.0/build
cmake .. && make
sudo make install
sudo ldconfig
```

## Build

```sh
mkdir build; cd build
cmake ..
cmake --build .
```

## Test

```sh
cd build
ctest -V
```

## Benchmark

```sh
bin/ech-benchmark
```

## Run

```sh
bin/echd
```
