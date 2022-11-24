#!/usr/bin/bash
cd kern3f
tar xvf linux-5.19.9.tar.xz
cd linux-5.19.9
make mrproper
wget https://raw.githubusercontent.com/divyansh-4/config/main/config-rev-9-gold
mv config-rev-9-gold .config
make -j1
