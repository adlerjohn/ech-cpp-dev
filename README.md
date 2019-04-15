# Ethereum Cash is Ethereum
 [![Build Status](https://travis-ci.com/adlerjohn/ech-cpp-dev.svg?token=thfx7xMP5jxRY8q9pnoA&branch=master)](https://travis-ci.com/adlerjohn/ech-cpp-dev)
 [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/adlerjohn/ech-cpp-dev/raw/master/LICENSE)

This repository contains a proof-of-concept implementation for ECH, a scalable side chain for Ethereum.

## Dependencies

Install the following libraries as dependencies before compiling.

```sh
apt install libboost-dev librocksdb-dev
```

CryptoPP needs to be installed separately, as the version in repositories is old.

```sh
wget https://www.cryptopp.com/cryptopp810.zip
unzip cryptopp810.zip -d cryptopp
cd cryptopp
make
sudo make install
```

## Compiling

```sh
mkdir build; cd build
cmake ..
cmake --build .
```

## Testing

```sh
cd build
ctest -V
```

## Running

```sh
bin/echd
```

