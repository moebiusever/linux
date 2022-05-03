#!/bin/bash
export CPUS=`grep -c processor /proc/cpuinfo`

make distclean
make imx6ull_defconfig
make zImage -j${CPUS}
make dtbs -j${CPUS}

rm -rf ./.tmp
make modules -j${CPUS}
make modules_install INSTALL_MOD_PATH=./.tmp/rootfs/
cd .tmp/rootfs/
tar -jcvf modules.tar.bz2 *

cd ../../
mkdir -p ./.tmp/image
cp ./arch/arm/boot/zImage ./.tmp/image/
cp ./.tmp/rootfs/modules.tar.bz2 ./.tmp/image
echo "img copy complete"
cp ./arch/arm/boot/dts/imx6ull-fcu1104-gpmi.dtb ./.tmp/image
cp ./arch/arm/boot/dts/imx6ull-fcu1104-emmc.dtb ./.tmp/image

echo -e "\033[44;37;5m finish \033[0m"

