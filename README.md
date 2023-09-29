# PQ-Benchmarking
*These instructions are valid for Ubuntu 22.04 and the most recent versions of Botan and liboqs as of September 29, 2023*

## Setup
Create a fresh virtual machine with Ubuntu 22.04 (VirtualBox is recommended for a free hypervisor). After installation, be sure to update all packages to their latest versions:

    sudo apt update
    sudo apt upgrade -y

Next, install several dependencies that are required to build the various cryptographic packages and cross-compile test programs for the ARM architecture:

    sudo apt install -y g++-aarch64-linux-gnu

Once this is done, proceed with installing the Botan library. First, obtain the Botan source code from GitHub:
    
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

Finally, return to the `pq-benchmarking` repository and build the test binaries for both x86 and ARM (note that either architecture can be build alone with individual make rules. Check the included Makefile for details):

    cd $HOME/pq-benchmarking
    make all



Installing OQS:

    cd ~
    git clone https://github.com/open-quantum-safe/liboqs.git
    cd liboqs
    mkdir build && cd build
    cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/local/ ..
    make
    sudo make install
    sudo ldconfig

...
