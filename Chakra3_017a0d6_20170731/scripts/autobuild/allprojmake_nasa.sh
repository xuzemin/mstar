# How to add a new project
# 1. increase iProjNumber
# 2. add the following project informaiton  
#   projName[x]=R2_NASA_ZUI_32MB_ATVMM
#   boardType[x]=BD_MST195C_D01A_S_NASA
#   tunerType[x]=MxL_601SI_TUNER
#

export CC=/usr/bin/gcc

cd ../../
rm -r -f BIN_NASA_ALL
mkdir BIN_NASA_ALL



#===============================================================

BOARD_DIR=./project/boarddef

CFG_FILE=./.config

VER_FILE=${BOARD_DIR}/Board

#=============================================================================

if [ "$1" == "" ]; then
	echo "No Version Number"
else
    cp ${VER_FILE}.h ${VER_FILE}.org
    sed -i 's/#define AUTO_BUILD_SW_VER.*/#define AUTO_BUILD_SW_VER                 '${1}'/g' ${VER_FILE}.h
fi


cp config.tmpl .config -f

#==================================================================================================
iProjNumber=3


projName[0]=R2_NASA_ZUI_64MB_DTMB_AUTOTEST
boardType[0]=BD_MST195C_D01A_S_NASA
tunerType[0]=MxL_601SI_TUNER

projName[1]=R2_NASA_ZUI_64MB_DTMB_SZ
boardType[1]=BD_MST060B_10AZBT_13502
tunerType[1]=MxL_661SI_TUNER

projName[2]=R2_NASA_ZUI_64MB_DTMB_SZ
boardType[2]=BD_MST061B_10AZU_14014
tunerType[2]=MxL_661SI_TUNER




iProjIndex=0

while [ "$iProjIndex" != "$iProjNumber" ]
#for iProjIndex in $(seq 1 3)
do

    echo "iProjIndex=$iProjIndex"

    # Get project name
    ProjName=${projName[$iProjIndex]}
    BoardType=${boardType[$iProjIndex]}
    TunerType=${tunerType[$iProjIndex]}
    BD_FILE=${BOARD_DIR}/${BoardType}.h
    
    echo "ProjName=$ProjName"

	  #change Board type and tuner type
	  sed -i 's/BOARD_TYPE_SEL ?=.*/BOARD_TYPE_SEL ?= '${BoardType}'/g' ${CFG_FILE}
	  sed -i 's/#define FRONTEND_TUNER_TYPE.*/#define FRONTEND_TUNER_TYPE             '${TunerType}'/g' ${BD_FILE}

    # Get project name and make    
    PROJ=${ProjName} make autobuild

    # Move bin folder to BIN_NASA_ALL
    PROJ=${ProjName}
    mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_${TunerType}
    mv -v Bin_R2_NASA_* ./BIN_NASA_ALL/
    rm -r Obj_${PROJ}

    iProjIndex=$(($iProjIndex+1))
done


# Move all bin folder
#mv -v Bin_R2_NASA_* ./BIN_NASA_ALL/
#rm -r Bin_R2_NASA_*


cp config.tmpl .config -f

if [ "$1" == "" ]; then
	echo "No Version Number"
else
    # Recover board.h
    cp ${VER_FILE}.org ${VER_FILE}.h
    rm -r ${VER_FILE}.org
fi

exit 0

#==================================================================================================

BD_NAME=BD_MST195B_D01A_S_NASA
BD_FILE=${BOARD_DIR}/$BD_NAME
#TUNER_TYPE=SILAB_2158_TUNER

# Backup BD_xxx.h
echo "Backup ${BD_FILE}.h to ${BD_FILE}.org"
cp ${BD_FILE}.h ${BD_FILE}.org

# Modify DB_XXX.h
#sed -i 's/#define FRONTEND_TUNER_TYPE.*/#define FRONTEND_TUNER_TYPE             '${TUNER_TYPE}'/g' ${BD_FILE}.h

# Modify .config
#sed -i 's/BOARD_TYPE_SEL ?=.*/BOARD_TYPE_SEL ?= '${BD_NAME}'/g' ${CFG_FILE}

PROJ=R2_NASA_ZUI_64MB_ATVMM make autobuild
PROJ=R2_NASA_ZUI_64MB_ATVMM
#cp -r Bin_${PROJ} Bin_${PROJ}_${BD_NAME}_${TUNER_TYPE}
#mv -v Bin_${PROJ} Bin_${PROJ}_${BD_NAME}
#rm -r Bin_${PROJ}
rm -r Obj_${PROJ}

#recovery to original file
cp ${BD_FILE}.org ${BD_FILE}.h
rm -rf ${BD_FILE}.org


#==================================================================================================

# Move all bin folder
mv -v Bin_R2_NASA_* ./BIN_NASA_ALL/
#rm -r Bin_R2_NASA_*


cp config.tmpl .config -f

if [ "$1" == "" ]; then
	echo "No Version Number"
else
# Recover board.h
cp ${VER_FILE}.org ${VER_FILE}.h
rm -r ${VER_FILE}.org
fi
