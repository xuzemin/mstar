==============================================================================================
How to use

1. Create a input file (You can refer to file_list.txt as example)
2. List moudles you want to retrieve version in file_list.txt
   Please check rule of format
3. Exec command ==>  ./Version_Control.pl file_list.txt
4. There will be a output file named version_result.txt

All version list in file_list.txt will show in version_result.txt




==============================================================================================
Readme of file_list.txt

// There are three method to retrieve version from a CI (configuration items)
// 1. Txt : Captre version from the first line of a txt file
// 2. Elf : Embedded version by using binutility:
//    Insert : arm-none-linux-gnueabi-objcopy --add-section .mmodule_version=version_info libXXXXX.so
//    Readelf: readelf --string-dump=.mmodule_version libXXXXX.so
// 3. MSIF: Embedded a binary string into a binary. And this string has a pre-defined format.
//           'M','S','I','F',                /* Version ID Header */\
//           '0','3',                          /* Info Class Code */\
//           0x0000,                               /* Customer ID */\
//           0x0000,                                 /* Module ID */\
//           0x0000,                                   /* Chip ID */\
//           '0',                                          /* CPU */\
//           'S','N','_','_'                     /* Library Code */\
//           '0','0',                              /* Library Ver */\
//           '0','1',                             /* Build Number */\
//           '0','0','1','2','3','4','5','5', /* P4 Change Number */\
//           '2'                                            /* OS */\

Format of file_list.txt

#ModuleName(Txt|Elf|MSIF)
Path of a module.


**if the version is attached in a archive. Please use below format
directfb-1.4.2m.tar.gz/directfb-1.4.2m/lib/libdirectfb.so