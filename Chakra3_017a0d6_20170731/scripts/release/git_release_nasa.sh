#!/bin/bash

cd ../..

targetDir=`pwd`
date_info=`date +%Y%m%d_%k%M`
#zipFile="chakra3_$date_info_$1.tar.gz"
zipFile="chakra3_"$date_info"_$1.tar.gz"

git log -1 > revision.txt
cd ../

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

###############################################################
# remember to remove .git folder
# remember to remove .git folder
# remember to remove .git folder
###############################################################

exclude=""
filter=(    
.git
ck3*
BD_MST015B_*
BD_MST024B_*
BD_MST042B_*
BD_MST132*
BD_MST165*
FILES_COMMON_EULER*
FILES_MIPS_A7*
FILES_R2_EULER*
bootloader_A7.ld
target_A7.ld
target.ld
MIUSEL_A7_*
MIUSEL_EULER_*
MMAP_ATVMM_EULER*
MMAP_DTVMM_A7*
MMAP_DTVMM_EULER_*
sysinfo2_a7.h
sysinfo2_euler.h
SW_Config_Trunk_EULER*
a7_nos_mips
euler_nos*
a7
A7
euler
EULER
s7ld
S7LD

eden_nos_r2m      
euler_nos_r2m  
melody_nos_r2m      
milan_nos_mips  
waltz_nos_r2m   
whisky_nos_r2m_32m
emerald_nos_mips  
maya_nos_r2m   
melody_nos_r2m_32m  
whisky_nos_r2m

eden  
emerald  
euler  
maya  
melody  
milan  
whisky

Bin_*
Obj_*
)

# nasa_nos_r2m    
# nasa
# ./chip
# ./core/bin
# ./core/driver/pq
# ./core/driver/pq/hal

for i in "${filter[@]}" ; do
  exclude="$exclude --exclude=$i"
done




echo -----
echo $targetDir
echo $zipFile
echo $exclude
echo -----
tar -zcvf $zipFile $exclude -C $targetDir/ `ls $targetDir`

echo ' '
echo 'Use below command to decompress the tgz file'
echo 'tar -xvzf' $zipFile
exit 0

