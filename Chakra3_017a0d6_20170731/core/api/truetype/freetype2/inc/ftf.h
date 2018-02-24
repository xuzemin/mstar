
#ifndef __FTF_H__
#define __FTF_H__

#include <ft2build.h>
#include <sfnt.h>
#include <tttypes.h>

FT_BEGIN_HEADER

typedef FT_Error (*FTF_Loader_Init_Func)( TT_Loader loader,
                                         FT_Size size,
                                         FT_GlyphSlot glyph,
                                         FT_Int32 load_flags,
                                         FT_Bool glyf_table_only );

typedef struct FTF_Interface_
{
    TT_Load_Face_Func       load_face;
    FTF_Loader_Init_Func    loader_init;
}FTF_Interface, *FTF_Service;


typedef FT_ULong
(*FTF_GET_GLYPH_LOCATION)( TT_Face face,
                          FT_UInt gindex,
                          FT_UInt *asize );

typedef struct FTF_InitParmRec_
{
    FTF_GET_GLYPH_LOCATION get_location;
}FTF_InitParmRec, *FTF_InitParm;

#define FT_PARAM_TAG_FULLTYPE  FT_MAKE_TAG( 'f', 'u', 'l', 'l' )

FT_END_HEADER

#endif
