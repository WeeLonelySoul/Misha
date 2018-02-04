#!/bin/sh

CURRENT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"


export PREFIX=$CURRENT_PATH
export TARGET=i686-elf
export COMPILER_SOURCE_LOCATION="./src/compilers"



echo -e "Compiling binutils"

cd $COMPILER_SOURCE_LOCATION
wget ftp://ftp.gnu.org/gnu/binutils/binutils-2.30.tar.xz -O ./binutils-2.30.tar.xz
tar xf binutils-2.30.tar.xz 
mkdir build-binutils 
cd build-binutils 
../binutils-2.30/configure --target=$TARGET --prefix=$PREFIX/"../../compilers" --with-sysroot --disable-nls --disable-werror && make && make install 

cd ../

echo -e "Compiling gcc"
wget ftp://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz -O ./gcc-7.3.0.tar.gz
tar xf gcc-7.3.0.tar.gz
mkdir build-gcc 
cd build-gcc 
../gcc-7.3.0/configure --target=$TARGET --prefix=$PREFIX/"../../compilers" --disable-nls --enable-languages=c,c++ --without-headers && make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc

#rm -r build-binutils binutils-2.30
#rm -r build-gcc gcc-7.3.0
