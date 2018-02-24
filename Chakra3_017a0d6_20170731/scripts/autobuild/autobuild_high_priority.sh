
#how to add a new project
# 1. increase iProjNumber
# 2. add the following project informaiton
#   projName[x]=R2_NASA_ZUI_32MB_ATVMM
#   boardType[x]=BD_MST195C_D01A_S_NASA
#   tunerType[x]=MxL_601SI_TUNER
#   swType[x]=SW_CONFIG_TRUNK_MILAN_128M_ALL

./allprojmake_mazda.sh

sh ./allprojmake_marlon.sh

./allprojmake_melody.sh


echo autobuild -- build code finish
cd ../..


echo ----- checking -----------------
grep AUTO_BUILD  project/boarddef/Board.h
tail   ./tv-ap/customer/MApp_Customer_Hdcpkey*.c
echo --------------------------------


mkdir -p BIN
mv BIN_* BIN
#cp -pr Bin* BIN

echo autobuild -- backkup finish  
###
