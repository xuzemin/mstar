/***********************************************************************
 * MODULE     : TT_Config
 * FILE       : TT_Config.h
 * COPYRIGHT  : TARA Systems GmbH
 * DESCRIPTION:
 *   Configuration header for Teletext. This file consists of the following
 *   sections:
 *   1. Internal definitions section
 *
 *   2. Common feature definition section
 *   2.1 Error correction settings
 *   2.2 Serial parallel conversion engine settings
 *   2.3 Display CLUT settings
 *   2.4 Subpage bar feature settings
 *   2.5 TOP menu feature settings
 *   2.6 Page catch feature settings
 *   2.7 Cursor feature settings
 *   2.8 Clock feature settings
 *   2.9 ACI feature settings
 *
 *   3. Target definitions for TT_TARGET_PC and TT_LEVEL_15
 *   3.1 General decoder settings
 *   3.2 Definitions for memory allocation
 *   3.3 Definitions for display
 *   3.4 Definitions for top
 *   3.5 Definitions for queues
 *   3.6 Definitions for packetbuffer
 *   3.7 Definitions for database
 *   3.8 Definitions for acq
 *   3.9 Definitions for slicer simulation
 *
 *   4. Target definitions for TT_TARGET_XX and TT_LEVEL_15
 *   4.1 General decoder settings
 *   4.2 Definitions for memory allocation
 *   4.3 Definitions for display
 *   4.4 Definitions for top
 *   4.5 Definitions for queues
 *   4.6 Definitions for packetbuffer
 *   4.7 Definitions for database
 *   4.8 Definitions for acq
 *   4.9 Definitions for slicer simulation
 *
 *   5. Definitions for Version String
 *
 ***********************************************************************/


/***********************************************************************
 *
 * 1. Internal definitions section
 *
 ***********************************************************************/

#ifndef _TT_CONFIG_H_
#define _TT_CONFIG_H_

#define LEVEL_25                                1 /* Always set as 2.5 */

/* switch on/off */
#define ENABLED                                 1 /* feature enabled switch */
#define DISABLED                                0 /* feature disabled switch */

/* pagecatch algorithm level */
#define TT_SIMPLE                               1 /* simple pagecatch algorithm */
#define TT_NORMAL                               2 /* normal pagecatch algorithm */
#define TT_ADVANCED                             3 /* advanced pagecatch algorithm */

/* memory allocation mode */
#define TT_MEM_ALLOC_INTRAM                     1 /* RAM is internal      */
#define TT_MEM_ALLOC_EXTRAM                     2 /* RAM is external      */
#define TT_MEM_ALLOC_SRAM                       3 /* RAM is external SRAM */

/* slicer input */
#define TT_SLICER_INPUT_EPR                     1 /* slicer input is EPR file */
#define TT_SLICER_INPUT_ROM                     2 /* slicer input is ROM array */
#define TT_SLICER_INPUT_SIGNAL                  3 /* slicer input is Analog Signal */

/* method for the page request system */
#define TT_SIMPLE_PAGE_REQUEST_SYSTEM           1 /* optimized and faster page request system */
#define TT_ENHANCED_PAGE_REQUEST_SYSTEM         2 /* intelligent but very slow page request system */

/* subpage acquisition handling */
#define TT_SUBPAGE_COLLECT_MODE                 1 /* all incoming subpages are collected */
#define TT_SUBPAGE_OVERWRITE_MODE               2 /* only store one subpage */

/* decoding level */
#define TT_LEVEL_15                            15 /* level 1.5 is used for decoding */
#define TT_LEVEL_25                            25 /* level 2.5 is used for decoding */

/* methods for database lookup table */
#define TT_USE_FULL_LOOKUP                      1 /* use full array */
#define TT_USE_DYNAMIC_LOOKUP                   2 /* use dynamic array */

/* decryption modes */
#define TT_HAMMING_DECODE                       1 /* decode only */
#define TT_HAMMING_CORRECT                      2 /* correct */

/* decoder clock mode */
#define TT_DECODER_CLOCK_MODE_MIX               1 /* display clock in mix mode */
#define TT_DECODER_CLOCK_MODE_DOUBLE_HEIGHT     2 /* display clock in double height */

/* subpage display mode */
#define TT_DECODER_SUBPAGEBAR_DYNAMIC_DISPLAY   1 /* display only received subpages */
#define TT_DECODER_SUBPAGEBAR_FIXED_DISPLAY     2 /* display all subpages */

/* subpage overwrite symbol display */
#define TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL_ON     FALSE
#define TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL_OFF    TRUE

/* manaul/automatic subpage bar */
#define TT_DECODER_SUBPAGEBAR_MANUAL_ON               TRUE
#define TT_DECODER_SUBPAGEBAR_MANUAL_OFF              FALSE

/* serial parallel conversion engine */
#define TT_DECODER_SPC                          1 /* use SPC to decode TeleText packets */
#define TT_DECODER_SPT                          2 /* use SPT to decode TeleText packets */

/* LEVEL_15 or LEVEL_25 must be definded in the compiler settings! */
#ifdef LEVEL_15
  #define TT_LEVEL TT_LEVEL_15
#elif LEVEL_25
  #define TT_LEVEL TT_LEVEL_25
#else
  #error "Error: LEVEL_15 or LEVEL_25 must be defined!!!"
#endif

#define BASEx   32
/* 16 bits or 32 bits tracking in ACQ */
#if (BASEx == 16)
    #define U_INTx          TT_U16
#else
    #define U_INTx          TT_U32
#endif


/***********************************************************************
 * 2. Common feature definition section
 *
 ***********************************************************************/

/***********************************************************************
 * 2.1 Error correction settings
 *
 * #define TT_HAMMING
 *   with TT_HAMMING_CORRECT or TT_HAMMING_DECODE
 *
 * DESCRIPTION:
 *   Defines whether hamming errors should be corrected or only decoded.
 *
 ***********************************************************************/
#define TT_HAMMING TT_HAMMING_CORRECT


/***********************************************************************
 * 2.2 Serial parallel conversion engine settings
 *
 * #define TT_DECODER
 *   with TT_DECODER_SPT or TT_DECODER_SPC
 *
 * DESCRIPTION:
 *   Defines which serial parallel conversion engine will be used.
 *   For level 1.5 and less performance systems the SPC should be used.
 *   For level 2.5 and more performance systems the SPT should be used.
 *
 ***********************************************************************/
//#if ( TT_LEVEL == TT_LEVEL_25)
  //#define TT_DECODER        TT_DECODER_SPT
//#else
  #define TT_DECODER        TT_DECODER_SPC
//#endif


/***********************************************************************
 * 2.3 Display CLUT settings
 *
 * #define TT_DSP_FIRST_COLOR_INDEX
 *   with first color index used in CLUT
 *
 * #define TT_DSP_LAST_COLOR_INDEX
 *   with last color index used in CLUT
 *
 * DESCRIPTION:
 *   Defines the first and last color index which will be used within
 *   the palette.
 *
 ***********************************************************************/




/***********************************************************************
 * 2.4 Subpage bar feature settings
 *
 * #define TT_DECODER_SUBPAGEBAR_DISPLAY
 *   with TT_DECODER_SUBPAGEBAR_FIXED_DISPLAY
 *   or TT_DECODER_SUBPAGEBAR_DYNAMIC_DISPLAY
 *
 * DESCRIPTION:
 *   Defines the subpage display method. In fixed display mode all
 *   subpages up to the highest received subpage number are displayed.
 *   In dynamic display mode only the already received subpages are
 *   displayed.
 *
 * #define TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL
 *   with TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL_ON
 *   or TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL_OFF
 *
 * DESCRIPTION:
 *   Defines whether the subpage overwrite symbol should be displayed
 *   or not. If enabled and the user selects the overwrite symbol, every
 *   incoming subpage is automatically displayed.
 *
 * #define TT_DECODER_SUBPAGEBAR_BACKGROUND
 *   with TT_COLOR_XXX
 *
 * #define TT_DECODER_SUBPAGEBAR_FOREGROUND_RECEIVED
 *   with TT_COLOR_XXX
 *
 * #define TT_DECODER_SUBPAGEBAR_FOREGROUND_NOT_RECEIVED
 *   with TT_COLOR_XXX
 *
 * #define TT_DECODER_SUBPAGEBAR_BACKGROUND_CURSOR
 *   with TT_COLOR_XXX
 *
 * #define TT_DECODER_SUBPAGEBAR_FOREGROUND_CURSOR
 *   with TT_COLOR_XXX
 *
 * DESCRIPTION:
 *   Defines the subpage bar colors in different states.
 *
 ***********************************************************************/
#define TT_DECODER_SUBPAGEBAR_DISPLAY TT_DECODER_SUBPAGEBAR_DYNAMIC_DISPLAY

#define TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL TT_DECODER_SUBPAGEBAR_OVERWRITE_SYMBOL_ON

#if 0

//#if (TT_LEVEL == TT_LEVEL_25)
  #define TT_DECODER_SUBPAGEBAR_BACKGROUND                      TT_COLOR_GREY
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND                      TT_COLOR_BLACK
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND_RECEIVED             TT_COLOR_RED
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND_NOT_RECEIVED         TT_COLOR_DARK_GREY
  #define TT_DECODER_SUBPAGEBAR_BACKGROUND_CURSOR               TT_COLOR_RED
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND_CURSOR               TT_COLOR_DARK_GREY

 /* TT_LEVEL_15 */
  /* only a view colors are available */
  #define TT_DECODER_SUBPAGEBAR_BACKGROUND                      TT_COLOR_GREY
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND                      TT_COLOR_BLACK
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND_RECEIVED             TT_COLOR_BLACK
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND_NOT_RECEIVED         TT_COLOR_DARK_GREY
  #define TT_DECODER_SUBPAGEBAR_BACKGROUND_CURSOR               TT_COLOR_BLUE
  #define TT_DECODER_SUBPAGEBAR_FOREGROUND_CURSOR               TT_COLOR_LIGHT_GREY
#endif /* TT_LEVEL */

#define TT_DECODER_SUBPAGEBAR_BACKGROUND                      TT_COLOR_GREY
#define TT_DECODER_SUBPAGEBAR_FOREGROUND                      TT_COLOR_BLACK
#define TT_DECODER_SUBPAGEBAR_FOREGROUND_RECEIVED             TT_COLOR_BLACK
#define TT_DECODER_SUBPAGEBAR_FOREGROUND_NOT_RECEIVED         TT_COLOR_DARK_GREY
#define TT_DECODER_SUBPAGEBAR_BACKGROUND_CURSOR               TT_COLOR_BLUE
#define TT_DECODER_SUBPAGEBAR_FOREGROUND_CURSOR               TT_COLOR_LIGHT_GREY

#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_BACKGROUND TT_DECODER_SUBPAGEBAR_BACKGROUND
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_CYCLE_SYMBOL_FOREGROUND     TT_DECODER_SUBPAGEBAR_FOREGROUND
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_CYCLE_SYMBOL_BACKGROUND     TT_COLOR_RED
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_CYCLE_SYMBOL_FOREGROUND   TT_DECODER_SUBPAGEBAR_FOREGROUND
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_CYCLE_SYMBOL_BACKROUND    TT_DECODER_SUBPAGEBAR_BACKGROUND
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_SUBPAGE_FOREGROUND          TT_DECODER_SUBPAGEBAR_FOREGROUND
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_ACTIVE_SUBPAGE_BACKGROUND          TT_COLOR_RED
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_SUBPAGE_FOREGROUND   TT_DECODER_SUBPAGEBAR_FOREGROUND
#define TT_DEFAULT_CUSTOM_SUBPAGEBAR_DEACTIVE_SUBPAGE_BACKROUND    TT_DECODER_SUBPAGEBAR_BACKGROUND


/***********************************************************************
 * 2.5 TOP menu feature settings
 *
 * #define TT_TOP_MENU_FEATURE
 *   with DISABLED or ENABLED
 *
 * DESCRIPTION:
 *   Defines whether the TOP menu should be enabled or not.
 *
 ***********************************************************************/
#define TT_TOP_MENU_FEATURE      ENABLED


/***********************************************************************
 * 2.6 Page catch feature settings
 *
 * #define TT_PAGECATCH_FEATURE
 *   with DISABLED or ENABLED
 *
 * DESCRIPTION:
 *   Defines whether the page catch feature should be enabled or not.
 *   Patent by Grundig ?
 *
 * #define TT_PAGECATCH_ALGORITHM
 *   with TT_SIMPLE, TT_NORMAL or TT_ADVANCED
 *
 * DESCRIPTION:
 *   Defines which page catch algorithm should be used. Three different
 *   kinds are available: simple, normal or advanced.
 *
 ***********************************************************************/
#define TT_PAGECATCH_FEATURE    ENABLED

#define TT_PAGECATCH_ALGORITHM  TT_ADVANCED


/***********************************************************************
 * 2.7 Cursor feature settings
 *
 * #define TT_CURSOR_COLOR_MAIN
 *   with TT_COLOR_XXX
 *
 * #define TT_CURSOR_COLOR_BORDER_LIGHT
 *   with TT_COLOR_XXX
 *
 * #define TT_CURSOR_COLOR_BORDER_DARK
 *   with TT_COLOR_XXX
 *
 * DESCRIPTION:
 *   Defines the colors of the cursor (main/light border/dark border).
 *
 ***********************************************************************/
#define TT_CURSOR_COLOR_MAIN           TT_COLOR_RED
#define TT_CURSOR_COLOR_BORDER_LIGHT   TT_COLOR_USER0
#define TT_CURSOR_COLOR_BORDER_DARK    TT_COLOR_USER1


/***********************************************************************
 * 2.8 Clock feature settings
 *
 * #define TT_DECODER_CLOCK_MODE
 *   with TT_DECODER_CLOCK_MODE_DOUBLE_HEIGHT or TT_DECODER_CLOCK_MODE_MIX
 *
 * DESCRIPTION:
 *   Defines the display method of the clock mode. Either double height
 *   or mix mode is possible.
 *
 ***********************************************************************/
#define TT_DECODER_CLOCK_MODE TT_DECODER_CLOCK_MODE_DOUBLE_HEIGHT


/***********************************************************************
 * 2.9 ACI feature settings
 *
 * #define TT_ACI_FEATURE
 *   with ENABLED or ENABLED
 *
 * #define TT_ACI_STD_DISPLAY
 *   with ENABLED or ENABLED
 *
 * DESCRIPTION:
 *   Defines whether the ACI feature should be enabled or not. If ACI
 *   feature is enabled, the ACI standard display using Teletext can be
 *   used.
 *
 ***********************************************************************/
#define TT_ACI_FEATURE      DISABLED

#define TT_ACI_STD_DISPLAY  DISABLED




/***********************************************************************
 *
 * 3. Target definitions for TT_TARGET_PC and TT_LEVEL_15
 *
 ***********************************************************************/
#if (TT_TARGET == TT_TARGET_PC)// && ( TT_LEVEL == TT_LEVEL_15 )

#define far


/***********************************************************************
 * 3.1 General decoder settings
 *
 * #define TT_DECODER_SUBPAGEBAR_MANUAL
 *   with TT_DECODER_SUBPAGEBAR_MANUAL_OFF or TT_DECODER_SUBPAGEBAR_MANUAL_ON
 *
 * DESCRIPTION:
 *  Defines if the subpage bar is displayed manually or automatically.
 *
 ***********************************************************************/
#define TT_DECODER_SUBPAGEBAR_MANUAL    TT_DECODER_SUBPAGEBAR_MANUAL_ON


/***********************************************************************
 * 3.2 Definitions for memory allocation
 *
 * #define TT_INTRAM_STATIC
 *   or undefine for malloc or external memory allocation
 *
 * DESCRIPTION:
 *   Defines if the memory should be statically allocated. If not
 *   defined memory will be allocated with malloc or externally.
 *
 ***********************************************************************/
#define TT_INTRAM_STATIC


/***********************************************************************
 * 3.3 Definitions for display
 *
 * #define TT_DISPLAY_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM or TT_MEM_ALLOC_SRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the display module. Either
 *   internal memory or sram is possible.
 *
 * #define TT_DISPLAY_MODE
 *   with TT_DISPLAY_MODE_BITMAP or TT_DISPLAY_MODE_CHAR
 *
 * DESCRIPTION:
 *   Defines which display mode should be used. Bitmap mode is used
 *   on framebuffer based systems. Character mode is used on systems
 *   with a character based hardware display.
 *
 * #define TT_DISPLAY_PROCESS_ROW_BY_ROW
 *   with ENABLED or DISABLED
 *
 * DESCRIPTION:
 *   Defines the display processing. In case of row by row processing
 *   drawing of a page will be interrupted after every row. This can be
 *   used to interrupt the display task and process other tasks with
 *   higher priority. This feature is useful for non operating systems
 *   and cooperative operating systems. If this feature is disabled,
 *   the complete page will be processed without interruption.
 *
 * #define TT_DISPLAY_FLASH_CLUT_INTERNAL
 *   with ENABLED or DISABLED
 *
 * DESCRIPTION:
 *   Defines if the software CLUT animation for the flash is processed
 *   internally or externally. For external processing the function
 *   TT_DriverDisplayFlushClut() must be called every 166ms.
 *
 ***********************************************************************/
#define TT_DISPLAY_MEM_ALLOC            TT_MEM_ALLOC_INTRAM

#define TT_DISPLAY_PROCESS_ROW_BY_ROW   DISABLED

#define TT_DISPLAY_FLASH_CLUT_INTERNAL  ENABLED

/***********************************************************************
 * 3.4 Definitions for top
 *
 * #define TT_TOP_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM, TT_MEM_ALLOC_EXTTRAM or TT_MEM_ALLOC_SRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the top module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_TOP_MAX_STRINGS
 *    minimum 40
 *    maximum 800 (recommended for TOP menu)
 *
 * DESCRIPTION:
 *   Defines the size of the top string container. Every string needs 16
 *   bytes in memory.
 *
 ***********************************************************************/
#define TT_TOP_MEM_ALLOC                TT_MEM_ALLOC_INTRAM

#define TT_TOP_MAX_STRINGS              40


/***********************************************************************
 * 3.5 Definitions for queues
 *
 * #define TT_QUEUE_MAX_ENTRIES
 *   with number of messages for the message queue storage (6 bytes for
 *   each message are used)
 *
 * DESCRIPTION:
 *   Defines the size of the message queue. Every entry needs 6 bytes
 *   in memory.
 *
 ***********************************************************************/
#define TT_QUEUE_MAX_ENTRIES            32

#define TT_OBJECT_QUEUE_MAX_ENTRIES     50
/***********************************************************************
 * 3.6 Definitions for packetbuffer
 *
 * #define TT_PACKETBUFFER_NUM_PACKETS
 *   with number of packets for the packet buffer storage (44 bytes for
 *   each packet are used)
 *
 * DESCRIPTION:
 *   Defines the size of the packet buffer. Depending on the system
 *   performance this value must be adjusted. On slow systems a bigger
 *   packet buffer is necessary. The packet buffer must be big enough
 *   to avoid loss of packets.
 *
 ***********************************************************************/
//#define TT_PACKETBUFFER_NUM_PACKETS     360


/***********************************************************************
 * 3.7 Definitions for database
 *
 * #define TT_DATABASE_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM or TT_MEM_ALLOC_EXTTRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the database module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_DATABASE_LOOKUP_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM or TT_MEM_ALLOC_EXTTRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the database lookup module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_DATABASE_LOOKUP_METHOD
 *   with TT_USE_DYNAMIC_LOOKUP or TT_USE_FULL_LOOKUP
 *
 * DESCRIPTION:
 *   Defines the database lookup method. Full lookup need more memory
 *   (8196 bytes) but is faster. The dynamic lookup needs less memory
 *   (depending on TT_DATABASE_LOOKUP_SIZE) but is slower. For dynamic
 *   lookup the lookup dynamic size must be defined!
 *
 * #define TT_DATABASE_LOOKUP_DYNAMIC_SIZE
 *   with the number of pages which can be stored in the dynamic
 *   database lookup table.
 *
 * DESCRIPTION:
 *   For each stored page in the database lookup table an entry
 *   will be allocated. The number of pages defined here defines
 *   the maximum number of pages which can be stored in the database.
 *   Will be only used in case of the dynamic lookup method!
 *
 * #define TT_DATABASE_NUM_PACKETS
 *   with the number of packets the database should allocate (46 bytes for
 *   each packet are used if structure packing of the compiler is used. The
 *   size may depend on the compiler and it's settings)
 *
 * DESCRIPTION:
 *   Defines the database size in packets. A typical Teletext page is
 *   assumed with 30 packets per page.
 *
 * #define TT_DATABASE_TEST
 *
 * DESCRIPTION:
 *   Defines if the database check will be enabled or not. This should
 *   be only used during development! The database check is called
 *   from the decoder to verify the linking of the database.
 *
 ***********************************************************************/
#define TT_DATABASE_MEM_ALLOC           TT_MEM_ALLOC_INTRAM

#define TT_DATABASE_LOOKUP_MEM_ALLOC    TT_MEM_ALLOC_INTRAM

#define TT_DATABASE_LOOKUP_METHOD       TT_USE_FULL_LOOKUP

#define TT_DATABASE_LOOKUP_DYNAMIC_SIZE 25

#define TT_DATABASE_NUM_PACKETS         (30*1000)

#define TT_DATABASE_TEST                ENABLED


/***********************************************************************
 * 3.8 Definitions for acq
 *
 * #define TT_ACQ_PAGE_REQUEST_SYSTEM
 *   with TT_SIMPLE_PAGE_REQUEST_SYSTEM or TT_ENHANCED_PAGE_REQUEST_SYSTEM
 *
 * DESCRIPTION:
 *   Defines the page request algorithm. Simple page request should be
 *   used on slow systems. The enhanced page request is more intelligent
 *   but needs more cpu performance.
 *
 * #define TT_ACQ_SUBPAGE_MODE
 *   with TT_SUBPAGE_OVERWRITE_MODE  or TT_SUBPAGE_COLLECT_MODE
 *
 * DESCRIPTION:
 *   Defines the subpage mode. In subpage overwrite mode incoming
 *   subpages of a page are not stored in memory. Therefore subpage
 *   overwrite is suited for systems with less memory. In subpage collect
 *   mode all incoming subpages are stored. Subpage collect mode needs
 *   a database size with about 100 pages.
 *
 ***********************************************************************/
#define TT_ACQ_PAGE_REQUEST_SYSTEM      TT_SIMPLE_PAGE_REQUEST_SYSTEM

#define TT_ACQ_SUBPAGE_MODE             TT_SUBPAGE_COLLECT_MODE


/***********************************************************************
 * 3.9 Definitions for slicer simulation
 *
 * TT_SLICER_INPUT
 *   with TT_SLICER_INPUT_ROM or TT_SLICER_INPUT_EPR
 *
 * DESCRIPTION:
 *   Defines the slicer input. Can be used to simulate a slicer with
 *   built in EPR data. On the PC also input from a EPR file is possible.
 *
 ***********************************************************************/
#define TT_SLICER_INPUT                 TT_SLICER_INPUT_EPR


#endif /* TT_TARGET_PC && TT_LEVEL_15 */




/***********************************************************************
 *
 * 4. Target definitions for TT_TARGET_XX and TT_LEVEL_15
 *
 ***********************************************************************/
#if (TT_TARGET == TT_TARGET_XX) //&& ( TT_LEVEL == TT_LEVEL_25 )

#define far

//#define DRAW_PAGE_IN_WHOLE	DISABLED
/***********************************************************************
 * 4.1 General decoder settings
 *
 * #define TT_DECODER_SUBPAGEBAR_MANUAL
 *   with TT_DECODER_SUBPAGEBAR_MANUAL_OFF or TT_DECODER_SUBPAGEBAR_MANUAL_ON
 *
 * DESCRIPTION:
 *  Defines if the subpage bar is displayed manually or automatically.
 *
 ***********************************************************************/
#define TT_DECODER_SUBPAGEBAR_MANUAL    TT_DECODER_SUBPAGEBAR_MANUAL_ON


/***********************************************************************
 * 4.2 Definitions for memory allocation
 *
 * #define TT_INTRAM_STATIC
 *   or undefine for malloc or external memory allocation
 *
 * DESCRIPTION:
 *   Defines if the memory should be statically allocated. If not
 *   defined memory will be allocated with malloc or externally.
 *
 ***********************************************************************/
//#define TT_INTRAM_STATIC


/***********************************************************************
 * 4.3 Definitions for display
 *
 * #define TT_DISPLAY_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM or TT_MEM_ALLOC_SRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the display module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_DISPLAY_MODE
 *   with TT_DISPLAY_MODE_BITMAP or TT_DISPLAY_MODE_CHAR
 *
 * DESCRIPTION:
 *   Defines which display mode should be used. Bitmap mode is used
 *   on framebuffer based systems. Character mode is used on systems
 *   with a character based hardware display.
 *
 * #define TT_DISPLAY_PROCESS_ROW_BY_ROW
 *   with ENABLED or DISABLED
 *
 * DESCRIPTION:
 *   Defines the display processing. In case of row by row processing
 *   drawing of a page will be interrupted after every row. This can be
 *   used to interrupt the display task and process other tasks with
 *   higher priority. This feature is usefull for non operating systems
 *   and cooperative operating systems. If this feature is disabled,
 *   the complete page will be processed without interruption.
 *
 * #define TT_DISPLAY_FLASH_CLUT_INTERNAL
 *   with ENABLED or DISABLED
 *
 * DESCRIPTION:
 *   Defines if the software CLUT animation for the flash is processed
 *   internally or externally. For external processing the function
 *   TT_DriverDisplayFlushClut() must be called every 166ms.
 *
 ***********************************************************************/
#define TT_DISPLAY_MEM_ALLOC            TT_MEM_ALLOC_INTRAM

#define TT_DISPLAY_PROCESS_ROW_BY_ROW   DISABLED

#define TT_DISPLAY_FLASH_CLUT_INTERNAL  ENABLED


/***********************************************************************
 * 4.4 Definitions for top
 *
 * #define TT_TOP_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM, TT_MEM_ALLOC_EXTTRAM or TT_MEM_ALLOC_SRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the top module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_TOP_MAX_STRINGS
 *    minimum 40
 *    maximum 800 (recommended for TOP menu)
 *
 * DESCRIPTION:
 *   Defines the size of the top string container. Every string needs 16
 *   bytes in memory.
 *
 ***********************************************************************/
#define TT_TOP_MEM_ALLOC                TT_MEM_ALLOC_INTRAM

#define TT_TOP_MAX_STRINGS              40


/***********************************************************************
 * 4.5 Definitions for queues
 *
 * #define TT_QUEUE_MAX_ENTRIES
 *   with number of messages for the message queue storage (6 bytes for
 *   each message are used)
 *
 * DESCRIPTION:
 *   Defines the size of the message queue. Every entry needs 6 bytes
 *   in memory.
 *
 ***********************************************************************/
#define TT_QUEUE_MAX_ENTRIES            32

#define TT_OBJECT_QUEUE_MAX_ENTRIES     50

/***********************************************************************
 * 4.6 Definitions for packetbuffer
 *
 * #define TT_PACKETBUFFER_NUM_PACKETS
 *   with number of packets for the packet buffer storage (44 bytes for
 *   each packet are used)
 *
 * DESCRIPTION:
 *   Defines the size of the packet buffer. Depending on the system
 *   performance this value must be adjusted. On slow systems a bigger
 *   packet buffer is necessary. The packet buffer must be big enough
 *   to avoid loss of packets.
 *
 ***********************************************************************/
//#define TT_PACKETBUFFER_NUM_PACKETS     540


/***********************************************************************
 * 4.7 Definitions for database
 *
 * #define TT_DATABASE_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM or TT_MEM_ALLOC_EXTTRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the database module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_DATABASE_LOOKUP_MEM_ALLOC
 *   with TT_MEM_ALLOC_INTRAM or TT_MEM_ALLOC_EXTTRAM
 *
 * DESCRIPTION:
 *   Defines the memory location for the database lookup module. Either
 *   internal memory or SRAM is possible.
 *
 * #define TT_DATABASE_LOOKUP_METHOD
 *   with TT_USE_DYNAMIC_LOOKUP or TT_USE_FULL_LOOKUP
 *
 * DESCRIPTION:
 *   Defines the database lookup method. Full lookup need more memory
 *   (8196 bytes) but is faster. The dynamic lookup needs less memory
 *   (depending on TT_DATABASE_LOOKUP_SIZE) but is slower. For dynamic
 *   lookup the lookup dynamic size must be defined!
 *
 * #define TT_DATABASE_LOOKUP_DYNAMIC_SIZE
 *   with the number of pages which can be stored in the dynamic
 *   database lookup table.
 *
 * DESCRIPTION:
 *   For each stored page in the database lookup table an entry
 *   will be allocated. The number of pages defined here defines
 *   the maximum number of pages which can be stored in the database.
 *   Will be only used in case of the dynamic lookup method!
 *
 * #define TT_DATABASE_NUM_PACKETS
 *   with the number of packets the database should allocate (46 bytes for
 *   each packet are used if structure packing of the compiler is used. The
 *   size may depend on the compiler and it's settings)
 *
 * DESCRIPTION:
 *   Defines the database size in packets. A typical Teletext page is
 *   assumed with 30 packets per page.
 *
 * #define TT_DATABASE_TEST
 *
 * DESCRIPTION:
 *   Defines if the database check will be enabled or not. This should
 *   be only used during development! The database check is called
 *   from the decoder to verify the linking of the database.
 *
 ***********************************************************************/
#define TT_DATABASE_MEM_ALLOC           TT_MEM_ALLOC_INTRAM

#define TT_DATABASE_LOOKUP_MEM_ALLOC    TT_MEM_ALLOC_INTRAM

#define TT_DATABASE_LOOKUP_METHOD       TT_USE_FULL_LOOKUP

#define TT_DATABASE_LOOKUP_DYNAMIC_SIZE 1000

#define TT_DATABASE_NUM_PACKETS         (30*300)

//#define TT_DATABASE_TEST                ENABLED


/***********************************************************************
 * 4.8 Definitions for acq
 *
 * #define TT_ACQ_PAGE_REQUEST_SYSTEM
 *   with TT_SIMPLE_PAGE_REQUEST_SYSTEM or TT_ENHANCED_PAGE_REQUEST_SYSTEM
 *
 * DESCRIPTION:
 *   Defines the page request algorithm. Simple page request should be
 *   used on slow systems. The enhanced page request is more intelligent
 *   but needs more cpu performance.
 *
 * #define TT_ACQ_SUBPAGE_MODE
 *   with TT_SUBPAGE_OVERWRITE_MODE  or TT_SUBPAGE_COLLECT_MODE
 *
 * DESCRIPTION:
 *   Defines the subpage mode. In subpage overwrite mode incoming
 *   subpages of a page are not stored in memory. Therefore subpage
 *   overwrite is suited for systems with less memory. In subpage collect
 *   mode all incoming subpages are stored. Subpage collect mode needs
 *   a database size with about 100 pages.
 *
 ***********************************************************************/
#define TT_ACQ_PAGE_REQUEST_SYSTEM      TT_ENHANCED_PAGE_REQUEST_SYSTEM

#define TT_ACQ_SUBPAGE_MODE             TT_SUBPAGE_COLLECT_MODE


/***********************************************************************
 * 4.9 Definitions for slicer simulation
 *
 * TT_SLICER_INPUT
 *   with only TT_SLICER_INPUT_SIGNAL, other definition does not work
 *
 * DESCRIPTION:
 *   Defines the slicer input.
 *
 ***********************************************************************/
#define TT_SLICER_INPUT                 TT_SLICER_INPUT_SIGNAL

#endif /* TT_TARGET_XX && TT_LEVEL_15 */

/***********************************************************************
 * 5. Definitions for Version String
 *
 * TELETEXT_VER()
 *
 * DESCRIPTION:
 *   Defines Version ID Header, Info Class Code, Customer ID, Module ID, Chip ID, CPU,
 *   Library Code, Library Ver, Build Number, P4 CL Number, and OS.
 *
 ***********************************************************************/

#define MSIF_CHANGELIST  '0' + ENABLE_CHANGELIST1, '0' + ENABLE_CHANGELIST2, '0' + ENABLE_CHANGELIST3, '0' + ENABLE_CHANGELIST4, '0' + ENABLE_CHANGELIST5, '0' + ENABLE_CHANGELIST6, '0' + ENABLE_CHANGELIST7, '0' + ENABLE_CHANGELIST8

#define TELETEXT_VER()   'M','S','I','F',                   /* Version ID Header    */ \
                         '0','3',                           /* Info Class Code      */ \
                         0xFF,0xFF,                         /* Customer ID          */ \
                         0xFF,0xFF,                         /* Module ID            */ \
                         0xFF,0xFF,                         /* Chip ID              */ \
                         '1',                               /* CPU                  */ \
                         'T','T','2','5',                   /* Library Code         */ \
                         '0','1',                           /* Library Ver          */ \
                         '3','9',                           /* Build Number         */ \
                         MSIF_CHANGELIST,                   /* P4 CL Number         */ \
                         '0'                                /* OS                   */ \



#endif /* _TT_CONFIG_H_ */

/* eof */

///*** please do not remove change list tag ***///
///***$Change: 428870 $***///
