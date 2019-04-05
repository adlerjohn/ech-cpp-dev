# Ethereum Cash is Ethereum
 [![Build Status](https://travis-ci.com/adlerjohn/ech-cpp-dev.svg?token=thfx7xMP5jxRY8q9pnoA&branch=master)](https://travis-ci.com/adlerjohn/ech-cpp-dev)
 [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/adlerjohn/ech-cpp-dev/raw/master/LICENSE)

This repository contains a proof-of-concept implementation for ECH, a scalable side chain for Ethereum.

## Dependencies

Install the following libraries as dependencies before compiling.

```sh
apt install libcrypto++-dev libboost-dev librocksdb-dev
```

## Compiling

```sh
mkdir build; cd build
cmake ..
cmake --build .
```

## Running

```sh
bin/echd
```

