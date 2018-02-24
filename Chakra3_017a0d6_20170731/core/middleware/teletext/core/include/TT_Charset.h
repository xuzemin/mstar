/***********************************************************************
 * MODULE     : TT_Charset
 * FILE       : TT_Charset.c
 * COPYRIGHT  : TARA Systems GmbH
 * DESCRIPTION:
 *   Translate the teletext specific parameters Character, Accent,
 *   CharSet and Language to CharCode and FontSelector for the DSP
 *   this function maps accented characters and languagespecific
 *   characters to CharCodes in the Extended Font Segment.
 *
 *   call once :
 *
 *   TT_CharsetCreate()                    - to create instance data
 *   TT_CharsetSetDefaultLanguages()       - to set default languages
 *   TT_CharsetSetLanguageGroup()          - to set language group
 *
 *   call with each TeleText page :
 *
 *   TT_CharsetReset()
 *   TT_Charset_Set_Language_Index_X28X29() - to set info from X28/X29 (option)
 *   TT_CharsetSetNationalOption()        - to set C12 C13 C14       (option)
 *   TT_Charset_Fix_Language()              - to fix language & font from current settings
 *
 ***********************************************************************/

#ifndef TT_CHARSET_H
#define TT_CHARSET_H


/*
language index
a language index is a pointer into the tables
"Default G0 / G2 Character Set Designation and National Option"
"Second Language Designation and Nation Option"
*/
typedef unsigned char TT_Charset_LG_Index;

/*
enum for primary & secondary language
*/
typedef enum
{
  TT_Charset_Primary,
  TT_Charset_Secondary

} TT_Charset_Order;

/*
language
*/
typedef enum
{
  TT_Charset_LG_Czech,      /* Czech/Slovak               */
  TT_Charset_LG_English,    /* English                    */
  TT_Charset_LG_Estonian,   /* Estonian                   */
  TT_Charset_LG_French,     /* French                     */
  TT_Charset_LG_German,     /* German                     */
  TT_Charset_LG_Italian,    /* Italian                    */
  TT_Charset_LG_Lettish,    /* Lettish/Lithuanian         */ 
  TT_Charset_LG_Polish,     /* Polish                     */
  TT_Charset_LG_Spanish,    /* Portuguese/Spanish         */
  TT_Charset_LG_Rumanian,   /* Rumanian                   */
  TT_Charset_LG_Serbian,    /* Serbian/Croatian/Slovenian */
  TT_Charset_LG_Swedish,    /* Swedish/Finnish/Hungarian  */
  TT_Charset_LG_Turkish,    /* Turkish                    */
  TT_Charset_LG_Cyrillic1,  /* Serbian/Croatian           */
  TT_Charset_LG_Cyrillic2,  /* Russian/Bulgarian          */
  TT_Charset_LG_Cyrillic3,  /* Ukrainian                  */
  TT_Charset_LG_Greek,      /* Greek                      */
  TT_Charset_LG_Hebrew,     /* Hebrew                     */
  TT_Charset_LG_Arabic,     /* Arabic                     */
  TT_Charset_LG_English_A,  /* English-Arabic             */
  TT_Charset_LG_French_A,   /* French-Arabic              */
  TT_Charset_LG_Farsi,      /* Farsi                      */

  TT_Charset_NotUsed = 0xFF

} TT_Charset_LG;


/*
font property
*/
typedef struct
{
  TT_Charset_Font
    /*
    primary/secondary font selector G0, G2
    */
    FontSelG0,
    FontSelG2;

  TT_Charset_LG
    /*
    primary/secondary language
    */
    Language;

} TT_Charset_Font_Property;

/*
character property
do not change series of variables, 
because TT_ROM tables are initialized using this entry
*/
typedef struct
{
  TT_Charset_Font
    /* font */
    Font;

  TT_U8 
    /* character code */
    Code;

} TT_Charset_Char_Property;


/*
language set
*/
typedef struct
{
  TT_Charset_LG
    /* 
    primary and secondary language
    */
    Language[2];

} TT_Charset_LG_Set;


/*
language group
*/
typedef struct
{
  TT_Charset_LG_Set
    /*
    lanuage set for each national option (c12,13,14)
    */
    NatOptLanguageSet[8];
    
} TT_Charset_LG_Group;

/*
settings for module character set
*/
typedef struct
{
  TT_U8
    /* 
    national option 
    */
    NatOpt;

  TT_Charset_LG
    /* 
    default language (primary / secondary ) 
    */
    LG_Default[2];

  TT_Charset_LG_Index
    /*
    language index from X28/X29 (primary / secondary ) 
    */
    LG_Index[2][2];

  TT_ROM TT_Charset_LG_Group *
    LG_Group;

  TT_Charset_Font_Property
    /*
    initial font (primary / secondary ) 
    */
    Font_Init[2],

    /*
    primary/secondary current font
    as copy of initial font
    may be changed by parallel attribut 
    "modified G0 and G2 character set designation"
    */
    Font[2];

} TT_Charset_Data;

typedef TT_Charset_Data * TT_Charset_Handle;

extern TT_ROM TT_Charset_LG   TT_Charset_Language_Table[];
#if (TT_TARGET == TT_TARGET_PC)
extern TT_ROM TT_U8        * FontTable                [];
#endif

#ifdef __cplusplus
  extern "C" {
#endif


/***********************************************************************
 * FUNCTION: TT_CharsetCreate
 *
 * DESCRIPTION:
 *   Create the Charset instance.
 *
 * RETURN:
 *   pointer to Charset instance, NULL if failed
 *
 ***********************************************************************/
PUBLIC TT_Charset_Handle
  TT_CharsetCreate(void);



/***********************************************************************
 * FUNCTION: TT_CharsetDelete
 *
 * DESCRIPTION:
 *   Delete the Charset instance.
 *
 ***********************************************************************/
PUBLIC void
  TT_CharsetDelete(void);



/***********************************************************************
 * FUNCTION: TT_CharsetGetHandle
 *
 * DESCRIPTION:
 *   Returns the Charset handle
 *
 * RETURN:
 *   The Charset handle.
 ***********************************************************************/
PUBLIC TT_Charset_Handle
  TT_CharsetGetHandle(void);



/***********************************************************************
 * FUNCTION: TT_CharsetReset
 *
 * DESCRIPTION:
 *   Reset the character settings
 *
 * PARAMETERS:
 *   hCharset    - handle of TT_Charset
 *
 ***********************************************************************/
PUBLIC void
  TT_CharsetReset(
  TT_Charset_Handle   hCharset);



/***********************************************************************
 * FUNCTION: TT_CharsetGetCharCodeAndFont
 *
 * DESCRIPTION:
 *   Translate the teletext specific parameters Character, Accent,
 *   CharSet and Language to CharCode and FontSelector for the DSP
 *   this function maps accented characters and languagespecific
 *   characters to CharCodes in the Extended Font Segment.
 *
 * PARAMETERS:
 *   aCharacter    - character code
 *   aAccent       - accent
 *   aCharSet      - character set 
 *   aLanguage     - langauge
 *   aCharCode     - character code
 *   aFontSelector - font selector
 ***********************************************************************/
PUBLIC void
  TT_CharsetGetCharCodeAndFont(
  TT_U8         aCharacter,
  TT_U8         aAccent,
  TT_U8         aCharSet,
  TT_Charset_LG  aLanguage,
  TT_U8*        aCharCode,
  TT_U8*        aFontSelector );



/***********************************************************************
 * FUNCTION   : TT_CharsetSetDefaultLanguages
 *
 * DESCRIPTION: 
 *   set default settings
 *   - default language primary
 *   - default language secondary
 *
 * PARAMETERS:
 *   hCharset    - handle of TT_Charset
 *   aPrimary    - default language primary
 *   aSecondary  - default language secondary 
 ***********************************************************************/
PUBLIC void 
TT_CharsetSetDefaultLanguages(
  TT_Charset_Handle   hCharset,
  TT_Charset_LG       aPrimary,
  TT_Charset_LG       aSecondary);



/***********************************************************************
 * FUNCTION   : TT_CharsetGetDefaultLanguage
 *
 * DESCRIPTION: 
 *   get default settings
 *   - default language primary or secondary
 *
 * PARAMETERS:
 *   hCharset       - handle of TT_Charset
 *   aLanguageType  - primary or secondary language
 *
 * RETURN:
 *  The default language
 ***********************************************************************/
PUBLIC TT_Charset_LG 
TT_CharsetGetDefaultLanguage(
  TT_Charset_Handle   hCharset,
  TT_Charset_Order    aLanguageType );



/***********************************************************************
 * FUNCTION   : TT_CharsetSetLanguageGroup
 *
 * DESCRIPTION: 
 *   set default language grput settings
 *   - language group
 *
 * PARAMETERS:
 *   hCharset    - handle of TT_Charset
 *   aGroup      - language group
 ***********************************************************************/
PUBLIC void 
TT_CharsetSetLanguageGroup(
  TT_Charset_Handle         hCharset,
  TT_Charset_LG_Group TT_ROM*  aGroup );



/***********************************************************************
 * FUNCTION   : TT_CharsetGetLanguageByNatOpt
 *
 * DESCRIPTION: 
 *   get the langugae from current langugae group by its national otpion
 *   value
 *
 * PARAMETERS:
 *   hCharset    - handle of TT_Charset
 *   aLanguageType  - primary or secondary language
 *   aNatOpt     - national option value (c-bits c12,13,14)
 *
 * RETURN:
 *  The language defined by language group
 ***********************************************************************/
PUBLIC TT_Charset_LG 
TT_CharsetGetLanguageByNatOpt(
  TT_Charset_Handle         hCharset,
  TT_U8                    aNatOpt,
  TT_Charset_Order          aLanguageType );



/***********************************************************************
 * FUNCTION   : TT_CharsetSetLanguageIndexX28X29
 *
 * DESCRIPTION: 
 *   set language index of X28/X29
 *
 * PARAMETERS:
 *   hCharset         - handle of TT_Charset
 *   PacketNumber     - X28 / X29
 *   order            - primary / secondary
 *   index            - language index
 ***********************************************************************/
PUBLIC void 
TT_CharsetSetLanguageIndexX28X29(
  TT_Charset_Handle   hCharset,
  TT_U8              PacketNumber,
  TT_Charset_Order    order,
  TT_Charset_LG_Index index);



/***********************************************************************
 * FUNCTION   : TT_CharsetSetNationalOption
 *
 * DESCRIPTION: 
 *   set national option
 *
 * PARAMETERS:
 *   hCharset         - handle of TT_Charset
 *   NatOpt           - national option
 ***********************************************************************/
PUBLIC void 
TT_Charset_SetNationalOption(
  TT_Charset_Handle   hCharset,
  TT_U8              NatOpt);

/***********************************************************************
 * FUNCTION   : TT_CharsetGetNationalOption
 *
 * DESCRIPTION: 
 *   get national option
 *
 * PARAMETERS:
 *   void
 ***********************************************************************/
PUBLIC TT_U8 
TT_Charset_GetNationalOption(void);

/***********************************************************************
 * FUNCTION   : TT_CharsetFontInit
 *
 * DESCRIPTION: 
 *   get current font from initial font
 *
 * PARAMETERS:
 *   hCharset         - handle of TT_Charset
 ***********************************************************************/
PUBLIC void 
TT_CharsetFontInit(
  TT_Charset_Handle   hCharset);



/***********************************************************************
 * FUNCTION   : TT_CharsetFixLanguage
 *
 * DESCRIPTION: 
 *   fix language settings
 *   the following function have to be called before
 *
 *   TT_CharsetReset()
 *   TT_Charset_Set_LanguageGroup()
 *   TT_Charset_Set_Language()
 *   TT_Charset_Set_Language_Index_X28X29()
 *   TT_CharsetSetNationalOption()
 *
 * PARAMETERS:
 *   hCharset         - handle of TT_Charset
 ***********************************************************************/
PUBLIC void 
TT_CharsetFixLanguage(
  TT_Charset_Handle   hCharset);



/***********************************************************************
 * FUNCTION   : TT_Charset_TestNational
 *
 * DESCRIPTION: 
 *   translate the teletext specific parameters character, 
 *   diacritical mark, FontSelector and language to 
 *   CharCode and FontSelector.
 *
 * PARAMETERS:
 *   hCharset         - handle of TT_Charset
 *   pChar            - pointer to character & font
 *   IsEsc            - switch primary / secondary
 ***********************************************************************/
PUBLIC void 
TT_CharsetTestNational(
  TT_Charset_Handle           hCharset,
  TT_Charset_Char_Property*   pChar,
  TT_BOOL                     IsEsc);

/***********************************************************************
 * FUNCTION   : TT_CharsetTestNational_WithoutESC
 *
 * DESCRIPTION: 
 *   translate the teletext specific parameters character, 
 *   diacritical mark, FontSelector and language to 
 *   CharCode and FontSelector. (but it only selects primary, for X/26)
 *
 * PARAMETERS:
 *   language         - language
 *   pChar            - pointer to character & font
 ***********************************************************************/
PUBLIC void 
TT_CharsetTestNational_WithoutESC(
    TT_U8 language,
    TT_Charset_Char_Property*   pChar);


/***********************************************************************
 * FUNCTION   : TT_CharsetAccentedChar
 *
 * DESCRIPTION: 
 *   handle accented character (called from local enhancement processing)
 *   
 *   exchange font and character code, if a valid combination 
 *   of character code and diacritical marker is found.
 *
 * PARAMETERS:
 *   hCharset         - handle of TT_Charset
 *   pChar            - pointer to character & font
 *   diacritical      - diacritical marker
 ***********************************************************************/
PUBLIC void 
TT_CharsetAccentedChar (
  TT_Charset_Handle          hCharset,
  TT_Charset_Char_Property * pChar,
  TT_U8                     diacritical);


/***********************************************************************
 * FUNCTION   : TT_CharsetSelectSetFromCode
 *
 * DESCRIPTION: 
 *   Get character set by table 34 (P.105)
 *   
 *   the code is from Triplet mode 8
 *   Modified G0 and G2 Character Set Designation
 *
 * PARAMETERS:
 *   font         - character set
 *   code        - data index from triplet
 ***********************************************************************/
PUBLIC TT_BOOL 
TT_CharsetSelectSetFromCode(TT_Charset_Font_Property *font, TT_U8 code);

#ifdef __cplusplus
  }
#endif

#endif /* TT_CHARSET_H */

/* This Headerfile was generated with C2H.pl ( C2H ) V 1.27 */
/* (c) 2003 by TARA-Systems GmbH Munich */
///*** please do not remove change list tag ***///
///***$Change: 428870 $***///
