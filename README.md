# PQ-Benchmarking
*These instructions are valid for Ubuntu 22.04 and the most recent versions of Botan and liboqs as of September 29, 2023*

## Setup
Create a fresh virtual machine with Ubuntu 22.04 (VirtualBox is recommended for a free hypervisor). After installation, be sure to update all packages to their latest versions:

    sudo apt update
    sudo apt upgrade -y

Next, install several dependencies:

    sudo apt install -y g++-aarch64-linux-gnu astyle cmake gcc ninja-build libssl-dev python3-pytest python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind

## Installing Botan
First, obtain the Botan source code from GitHub:
    
    cd $HOME
    git clone https://github.com/randombit/botan.git

Next, cross-compile Botan for ARM:
    
    mv botan botan-arm
    mkdir botan-aarch64
    cd botan-arm
    ./configure.py --os=linux --cpu=armv8 --ar-command=aarch64-linux-gnu-ar --cc-bin=$(which aarch64-linux-gnu-g++) --cc=gcc --prefix=$HOME/botan-aarch64/
    make
    make install

Now, compile Botan for x86_64 (you will need to clone the Botan source repository again, as included in the command sequence below):

    cd $HOME
    git clone https://github.com/randombit/botan.git
    mv botan botan-x86
    mkdir botan-intel
    cd botan-intel
    ./configure.py --os=linux --cpu=x86_64 --cc-bin=$(which g++) --cc=gcc --prefix=$HOME/botan-intel/
    make
    make install

## Installing liboqs

Start by creating placeholder directories for the ARM and x86 installations of liboqs:

    mkdir liboqs-aarch64 liboqs-x86

Now, obtain the liboqs source code from GitHub:

    cd $HOME
    git clone -b main https://github.com/open-quantum-safe/liboqs.git

Next, build liboqs for ARM:

    cd $HOME
    mv liboqs liboqs-arm 
    cd liboqs-arm
    mkdir build && cd build
    cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=$HOME/pq-benchmarks/arm-toolchain.cmake -DOQS_USE_OPENSSL=OFF -DCMAKE_INSTALL_PREFIX=$HOME/liboqs-aarch64 ..
    ninja
    ninja install

Now, build liboqs for x86_64:

    cd $HOME
    git clone -b main https://github.com/open-quantum-safe/liboqs.git
    mv liboqs liboqs-intel
    cd liboqs-intel
    mkdir build && cd build
    cmake -GNinja -DOQS_USE_OPENSSL=OFF -DCMAKE_INSTALL_PREFIX=$HOME/liboqs-x86 ..
    ninja
    ninja install


## Building and running benchmarking code


Finally, clone the `pq-benchmarking` repository and build the test binaries for both x86 and ARM (note that either architecture can be build alone with individual make rules. Check the included Makefile for details):

    git clone https://github.com/twardokus/pq-benchmarks.git
    cd $HOME/pq-benchmarks
    make all
