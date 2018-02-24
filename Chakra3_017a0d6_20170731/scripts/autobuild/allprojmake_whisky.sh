# How to add a new project
# 1. increase iProjNumber
# 2. add the following project informaiton  
#   projName[x]=R2_NASA_ZUI_32MB_ATVMM
#   boardType[x]=BD_MST195C_D01A_S_NASA
#   tunerType[x]=MxL_601SI_TUNER
#   swType[x]=SW_CONFIG_TRUNK_MILAN_128M_ALL

export CC=/usr/bin/gcc

cd ../../
rm -r -f BIN_WHISKY_ALL
mkdir BIN_WHISKY_ALL



#===============================================================

BOARD_DIR=./project/boarddef
SW_DIR=./project/swdef

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
iProjNumber=10
#-----------------------------------------------
projName[0]=R2_WHISKY_128M_ATSC
boardType[0]=BD_MST090B_10ANU_15213
tunerType[0]=MxL_661SI_TUNER
swType[0]=SW_CONFIG_TRUNK_WHISKY_128M_ALL
#-----------------------------------------------
projName[1]=R2_WHISKY_64M_ATSC
boardType[1]=BD_MST090B_10ANU_15213
tunerType[1]=MxL_661SI_TUNER
swType[1]=SW_CONFIG_TRUNK_WHISKY_64M_ALL
#-----------------------------------------------
projName[2]=R2_WHISKY_64M_ATSC_AUTOTEST
boardType[2]=BD_MST090B_10ANU_15213
tunerType[2]=MxL_661SI_TUNER
swType[2]=SW_CONFIG_TRUNK_WHISKY_64M_ALL
#-----------------------------------------------
projName[3]=R2_WHISKY_128M_ATSC_4M
boardType[3]=BD_MST090B_10ANU_15213
tunerType[3]=MxL_661SI_TUNER
swType[3]=SW_CONFIG_TRUNK_WHISKY_128M_ALL
#-----------------------------------------------
projName[4]=R2_WHISKY_64M_ATSC_4M
boardType[4]=BD_MST090B_10ANU_15213
tunerType[4]=MxL_661SI_TUNER
swType[4]=SW_CONFIG_TRUNK_WHISKY_64M_ALL
#-----------------------------------------------
projName[5]=R2_WHISKY_32M_ATSC
boardType[5]=BD_MST090B_10ANU_15213
tunerType[5]=MxL_661SI_TUNER
swType[5]=SW_CONFIG_TRUNK_WHISKY_32M_ALL
#-----------------------------------------------
projName[6]=R2_WHISKY_128M_ATSC
boardType[6]=BD_MST233B_D01A_S
tunerType[6]=MxL_661SI_TUNER
swType[6]=SW_CONFIG_TRUNK_WHISKY_128M_ALL
#-----------------------------------------------
# socket board
projName[7]=R2_WHISKY_64M_ATSC
boardType[7]=BD_MST233B_D01A_S
tunerType[7]=MxL_661SI_TUNER
swType[7]=SW_CONFIG_TRUNK_WHISKY_64M_ALL
#-----------------------------------------------
# socket board
projName[8]=R2_WHISKY_64M_ATSC
boardType[8]=BD_MST233A_D01A_S
tunerType[8]=MxL_661SI_TUNER
swType[8]=SW_CONFIG_TRUNK_WHISKY_64M_ALL
#-----------------------------------------------
# socket board
projName[9]=R2_WHISKY_64M_ATSC_TTS_EN_ES_FR
boardType[9]=BD_MST233B_D01A_S
tunerType[9]=MxL_661SI_TUNER
swType[9]=SW_CONFIG_TRUNK_WHISKY_64M_ALL
#-----------------------------------------------
#-----------------------------------------------

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
	  SW_FILE=${SW_DIR}/${swType}.h
    
    echo "ProjName=$ProjName"

	  #change Board type and tuner type
	  sed -i 's/BOARD_TYPE_SEL ?=.*/BOARD_TYPE_SEL ?= '${BoardType}'/g' ${CFG_FILE}
	  sed -i 's/#define FRONTEND_TUNER_TYPE.*/#define FRONTEND_TUNER_TYPE             '${TunerType}'/g' ${BD_FILE}

    # Get project name and make    
    PROJ=${ProjName} make autobuild

    # Move bin folder to BIN_WHISKY_ALL
    PROJ=${ProjName}
    mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_${TunerType}
    mv -v Bin_R2_WHISKY_* ./BIN_WHISKY_ALL/
    rm -r Obj_${PROJ}
	
    iProjIndex=$(($iProjIndex+1))
done

exit 0
