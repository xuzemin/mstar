# How to add a new project
# 1. increase iProjNumber
# 2. add the following project informaiton  
#   projName[x]=R2_NASA_ZUI_32MB_ATVMM
#   boardType[x]=BD_MST195C_D01A_S_NASA
#   tunerType[x]=MxL_601SI_TUNER
#   swType[x]=SW_CONFIG_TRUNK_MILAN_128M_ALL

export CC=/usr/bin/gcc

cd ../../
rm -r -f BIN_MILAN_ALL
mkdir BIN_MILAN_ALL



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
iProjNumber=4

projName[0]=MIPS_MILAN_ZUI_MM_128MB_ALL_SZ
boardType[0]=BD_MST073B_10AGS
tunerType[0]=SILAB_2151_TUNER
swType[0]=SW_CONFIG_TRUNK_MILAN_128M_ALL

projName[1]=MIPS_MILAN_ZUI_MM_64MB_ALL_SZ
boardType[1]=BD_MST074B_10AGS
tunerType[1]=SILAB_2151_TUNER
swType[1]=SW_CONFIG_TRUNK_MILAN_64M_ALL

projName[2]=MIPS_MILAN_ZUI_MM_128MB_ALL_AUTOTEST
boardType[2]=BD_MST073B_10AGS
tunerType[2]=SILAB_2151_TUNER
swType[2]=SW_CONFIG_TRUNK_MILAN_128M_ALL

projName[3]=MIPS_MILAN_ZUI_MM_128MB_ALL_SZ_BLOADER
boardType[3]=BD_MST073B_10AGS
tunerType[3]=SILAB_2151_TUNER
swType[3]=SW_CONFIG_TRUNK_MILAN_128M_ALL


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

    # Move bin folder to BIN_MILAN_ALL
    PROJ=${ProjName}
    mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_${TunerType}
    mv -v Bin_MIPS_MILAN_* ./BIN_MILAN_ALL/
    rm -r Obj_${PROJ}
	
	  if [ "$ProjName" == "MIPS_MILAN_ZUI_MM_64MB_ALL_SZ" ]; then
		echo "ENABLE_MADMONITOR option DISABLE version create!"
		sed -i 's/#define ENABLE_MADMONITOR.*/#define ENABLE_MADMONITOR               DISABLE/g' ${SW_FILE}
	    PROJ=${ProjName} make autobuild
		PROJ=${ProjName}
		mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_MONITOR_OFF
		mv -v Bin_MIPS_MILAN_* ./BIN_MILAN_ALL/
		rm -r Obj_${PROJ}
		
		sed -i 's/#define ENABLE_MADMONITOR.*/#define ENABLE_MADMONITOR               ENABLE/g' ${SW_FILE}
		echo "ENABLE_MADMONITOR option DISABLE version finish!" 
	  elif [ "$ProjName" == "MIPS_MILAN_ZUI_MM_128MB_ALL_SZ" ]; then
	  	echo "ENABLE_MADMONITOR option DISABLE version create!"
		sed -i 's/#define ENABLE_MADMONITOR.*/#define ENABLE_MADMONITOR               DISABLE/g' ${SW_FILE}
	    PROJ=${ProjName} make autobuild
		PROJ=${ProjName}
		mv -v Bin_${PROJ} Bin_${PROJ}_${BoardType}_MONITOR_OFF
		mv -v Bin_MIPS_MILAN_* ./BIN_MILAN_ALL/
		rm -r Obj_${PROJ}
		
		sed -i 's/#define ENABLE_MADMONITOR.*/#define ENABLE_MADMONITOR               ENABLE/g' ${SW_FILE}
		echo "ENABLE_MADMONITOR option DISABLE version finish!" 
	  fi
	
    iProjIndex=$(($iProjIndex+1))
done


# Move all bin folder
#mv -v Bin_R2_NASA_* ./BIN_MILAN_ALL/
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
