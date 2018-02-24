#!/bin/bash
export LANG="en_US.UTF-8"
#set -xv   ###For DEBUG ssed

FILE_NAME=$1
test ! -e $FILE_NAME && echo "The profile '$FILE_NAME' NOT EXIST!" && exit 0

cat $FILE_NAME | while read line
do
COMMAND_CASETYPE=`echo $line | awk -F , '{print $1}'`
if [ "$COMMAND_CASETYPE" == "Case1" ]; then
    BIN_FILE_NAME=`echo $line | awk -F"," '{print $2}'`
    MMAP_FILE_NAME=`echo $line | awk -F", " '{print $3}'`
    DEFINE_BUFF_NAME=`echo $line | awk -F", " '{print $4}' | tr -d '\r'`

    GET_BIN_FILE_SIZE=`du -b $BIN_FILE_NAME | awk '{print $1}'`
    GET_MMAP_BUFF_RECORD_SIZE=`cat $MMAP_FILE_NAME | awk -v "buff_name=$DEFINE_BUFF_NAME" '{if($1 == "#define"&&$2 == buff_name){print $3}}' $MMAP_FILE_NAME`

    SUBHEX_SIZE=`echo $GET_MMAP_BUFF_RECORD_SIZE | cut -c 3-12`
    HEX_TO_DEC_SIZE=`echo "ibase=16; $SUBHEX_SIZE" | bc`

    if [ "$GET_BIN_FILE_SIZE" -lt "$HEX_TO_DEC_SIZE" ]; then
        echo "Case1 size is guarantee."
    else
        echo -e "The bin_file :\t" $BIN_FILE_NAME " size is\t" $GET_BIN_FILE_SIZE "Bytes"
        echo -e "The mmap_file :\t" $MMAP_FILE_NAME
        echo -e "The define_buffname :" $DEFINE_BUFF_NAME " size is\t" $HEX_TO_DEC_SIZE "Bytes"
        echo "This Case1 is not matched."
        exit 1
    fi
elif [ "$COMMAND_CASETYPE" == "Case2" ]; then
    BIN_FILE_NAME=`echo $line | awk -F", " '{print $2}'`
    GET_BIN_FILE_SIZE=`du -b $BIN_FILE_NAME | awk '{print $1}'`
    EXPECT_SIZE=`echo $line | awk -F", " '{print $3}' | tr -d '\r' `

    if [ "$GET_BIN_FILE_SIZE" -lt "$EXPECT_SIZE" ]; then
        echo "Case2 size is guarantee."
    else
        echo -e "The bin_file :\t" $BIN_FILE_NAME " size is\t" $GET_BIN_FILE_SIZE "Bytes"
        echo -e "The define_size :\t"$EXPECT_SIZE "Bytes"
        echo "This Case2 is not matched."
        exit 1
    fi
fi
done