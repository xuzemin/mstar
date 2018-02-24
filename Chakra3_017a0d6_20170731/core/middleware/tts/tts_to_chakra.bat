@echo "put <lib_AEON_SepData> under <middleware>"

xcopy /i /y /s ..\lib_AEON_SepData\gcc4.1.2\* cbr\aeon\.

xcopy /y /s ..\lib_AEON_SepData\data\* cbr\data\.


rem copy ..\lib_AEON_SepData\libTTS2.h .
copy ..\lib_AEON_SepData\ttsConst.h cbr\aeon\.

pause