#!/bin/bash

#echo current dir
#pwd

BIN_FOLDER=${RES_FOLDER}/osdbin
HEADER_FILE_FOLDER=${RES_FOLDER}/include

BMP_REDUCE_DIR=./scripts/bmp_reduce
echo "BMP_REDUCE_DIR=${BMP_REDUCE_DIR}"

#RES_FOLDER=../../tv-ap/dvb/ui2/res1366x768x565/osdcomposer
RES_FOLDER=./tv-ap/dvb/ui2/res1366x768x565/osdcomposer
echo "RES_FOLDER=${RES_FOLDER}"

SRC_BMP_BIN_NAME=ZUI_bitmap_SW_LOAD

REDUCE_BMP_CFG=${BMP_REDUCE_DIR}/Reduce_bmp_cfg.txt
echo "REDUCE_BMP_CFG=${REDUCE_BMP_CFG}"	

#Gen the parameter file of Reduce_bmp
echo "${RES_FOLDER}/include/ZUI_bitmap_EnumIndex.h[bitmap enum file]" > ${REDUCE_BMP_CFG}
echo "${RES_FOLDER}/osdbin/${SRC_BMP_BIN_NAME}.bin[input binary name]" >> ${REDUCE_BMP_CFG}
echo "${RES_FOLDER}/osdbin/${SRC_BMP_BIN_NAME}_no_POP.bin[output binary name]" >> ${REDUCE_BMP_CFG}


${BMP_REDUCE_DIR}/Reduce_bmp ${BMP_REDUCE_DIR}/Reduce_bmp_cfg.txt ${BMP_REDUCE_DIR}/EPOP.txt


