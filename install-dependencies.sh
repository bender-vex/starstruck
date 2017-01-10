#!/bin/sh
sudo bash -c "cat >> /etc/apt/sources.list" << LLVMAPT
# LLVM
deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty main
deb-src http://llvm.org/apt/trusty/ llvm-toolchain-trusty main
# 3.9
deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.9 main
deb-src http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.9 main
LLVMAPT
wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|sudo apt-key add -
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update
sudo apt-get install -y clang-3.9 lldb-3.9 gcc-arm-none-eabi