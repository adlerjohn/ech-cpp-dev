# Ethereum Cash is Ethereum

This repository contains a proof-of-concept implementation for ECH, a scalable side chain.

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

