# Ethereum Cash is Ethereum
 [![Build Status](https://travis-ci.com/adlerjohn/ech-cpp-dev.svg?token=thfx7xMP5jxRY8q9pnoA&branch=master)](https://travis-ci.com/adlerjohn/ech-cpp-dev)
 [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/adlerjohn/ech-cpp-dev/raw/master/LICENSE)

This repository contains a proof-of-concept implementation for ECH, a scalable side chain for Ethereum.

## Dependencies

Install the following libraries as dependencies before compiling.
If you're using a Ubuntu <Bionic (18.04) then you may need to install [libsecp256k1](https://github.com/bitcoin-core/secp256k1) manually. 

```sh
apt install libboost-dev librocksdb-dev libsecp256k1-dev
```

[Crypto++](https://www.cryptopp.com/) needs to be installed separately, as the version in repositories is too old and doesn't have Keccak hashing.

```sh
wget https://www.cryptopp.com/cryptopp810.zip
unzip cryptopp810.zip -d cryptopp
cd cryptopp
make
sudo make install
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

