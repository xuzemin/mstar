////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTDISHSETUP_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

#include "Board.h"

#if(ENABLE_S2)
#include "MsCommon.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_DataBase.h"

#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTDishSetup.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "msAPI_Memory.h"
#include "msAPI_MSDCtrl.h"
#include "apiGOP.h"
#include "msAPI_audio.h"
#include "MApp_Audio.h"
#include "mapp_gb2unicode.h"
#include "MApp_ZUI_APIChineseIME.h"
#include "MApp_UiMenuDef.h"
#include "MApp_RestoreToDefault.h"
#include "GPIO.h"
#include "FSUtil.h"
#include "IOUtil.h"
#include <stdio.h>
#include <string.h>
#include "ZUI_tables_h.inl"
#include "MApp_TopStateMachine.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIdraw.h"

#include "MApp_ChannelChange.h"
#include "apiDTVSatTable.h"
#include "MApp_MenuChannel.h"
#include "apiDTVFreqTable.h"
#include "MApp_MenuChannel.h"
#include <math.h>//clark 0824, for delete warning info
#include <stdio.h>
#include "apiDigiTuner.h"
/*
#if(FRONTEND_DEMOD_S2_TYPE == MSTAR_MSB131X_DVBS2)
#include "drvDemod.h"
#else
#include "drvCofdmDmd.h"
#endif
*/
#include "msAPI_Demod.h"

#include "msAPI_Flash.h"

extern DTVPROGRAMID_M g_stCurS2ProggramId;

#define  TYPE_TPLIST 0
#define  TYPE_SATLIST 1

static MS_U8 u8CurEditListType = TYPE_SATLIST;
EN_DISHSETUP_STATE enDishSetupState;

#if ENABLE_S2_QUALITY_DISPLAY_PERCENT
static MS_U16   u16CurrentSatTpIndex = 0;
static MS_U8   u16SatTpDetectCount = 0;
#define DISHSETUP_SIGNAL_BAR_MONITOR_DURATION	200//500
static void vDispSignalQuality(void);
#endif
#if 1
#if 1//def DISHSETUP_MENU_ONEPAGE
//-------------------------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------------------------
#undef DBG_TRACE
#ifdef MS_DEBUG
#define DBG_TRACE(fmt, args...) printf(fmt, ##args)
#else
#define DBG_TRACE(fmt, args...) {}
#endif
//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define MAX_DIGITAL_NUM 5
#define MAX_DIGITAL_NUM_DOT 4
#define MOVE_TIME  2  //stallite move time
#define USER_DEFINE_STRING E_ZUI_STR_MAX
#define NEW_SAT_DEFAULTNAME  "SatName"
#define FORCE_TUNE_COUNT_MAX 5
#define SATELITE_MAX_PAGE_NUM 8//(TOTAL_BUILDIN_SATELLITE_NUMBER+7)/8
//-------------------------------------------------------------------------------------------------
// Local Struct
//------------------------------------------------------------------------------------------------

//for LOF list
typedef struct _LOFTYPE
{
    MS_U8 u8LOFNum;
    char*  strDisplay;
    MS_U16  u16LLOF;
    MS_U16  u16HLOF;
}LOFTYPE;

LOFTYPE stLOF[]=
{
    {2,"9750/10600",9750,10600},
    {2,"9750/10750",9750,10750},
    {1,"05150",5150,5150},
    {1,"05750",5750,5750},
    {1,"09750",9750,9750},
    {1,"10600",10600,10600},
    {1,"10750",10750,10750},
    {1,"11300",11300,11300},
    {1,"11475",11475,11475},

    //next 2 items must lay behind
    {1,"User Single",9750,9750},
    {2,"User Dual",9750,10600},
#if(SUPPORT_UNICABLE)
    {2,"Unicable",9750,10600},
#endif
};

#if(SUPPORT_UNICABLE)
//U16 u16UnicableIFeq[8]={1210,1420,1680,2040,1284,1516,1632,1748};
U16 u16UnicableIFeq[8]={1284,1400,1516,1632,1748,1864,1980,2096};
#endif
#define LOFLIST_NUM  (sizeof(stLOF)/sizeof(LOFTYPE))
#if(SUPPORT_UNICABLE)
#define USER_SIGNLE_IDX   (LOFLIST_NUM-3)
#define USER_DUAL_IDX   (LOFLIST_NUM-2)
#define USER_DEFINE_UNICABLE		(LOFLIST_NUM-1)
#else
#define USER_SIGNLE_IDX   (LOFLIST_NUM-2)
#define USER_DUAL_IDX   (LOFLIST_NUM-1)
#endif

typedef enum
{
	SCAN_DEFAULT,
	SCAN_BLIND,
	SCAN_NETWORK,
#if(ENABLE_S2_FAST_SCAN)
        SCAN_FAST,
#endif
#if(ASTRA_HD_ENABLE)
    SCAN_ASTRA_FAST,
#endif

	SCANTYPE_NUM,
}SCAN_TYPE;


typedef enum
{
	MOVE_STOP,
	MOVE_WEST,
	MOVE_EAST,
	MOVE_WEST_STEP,
	MOVE_EAST_STEP
}MOVE_STATE;

typedef enum
{
    SET_WEST_LIMIT,
    SET_EAST_LIMIT,
    GOTO_REF,
    DISABLE_LIMIT,
    GOTO_X,
    STORE_POSITON,
    GOTO_POSITON
}SET_LIMIT_STATE;

//softkeypad
#define PROGRAMNAME_MAXLENGTH MAX_SATNAME_LEN+1
static MS_U8 u8ProgName[PROGRAMNAME_MAXLENGTH];
static MS_U8 u8ProgNameCharNum=0;
static MS_BOOL bIsExtendChar = FALSE;
static MS_BOOL bIsCaptalChar = TRUE;

typedef struct _softkeypaddata
{
	HWND   hWnd;
	MS_U8  normalchar;
	MS_U8  normalcapschar;
	MS_U8  extendchar;
	MS_U8  extendcapschar;
}SOFTKEYPAD_DATA;

U8 UTL_strlen1(const char *pStr)
{
    U8 i=0;

    while(pStr[i])
    {
        i++;
    }
    return i;
}

static U16 *UTL_wcscpy1(U16 *strDst, const U16 *strSrc)
{
    int i;

    for(i=0;strSrc[i];i++)
    {
        strDst[i] = strSrc[i];
    }
    strDst[i] = '\0';
    return strDst;
}

static U8 UTL_wcslen1(const U16 *pStr)
{
    U8 i=0;

    while(pStr[i])
    {
        i++;
    }
    return i;
}

#define wcscpy1              UTL_wcscpy1
#define wcslen1              UTL_wcslen1
#define wcscat1(x, y)     wcscpy1((x) + wcslen1(x), (y))

static SOFTKEYPAD_DATA softkey[]=
{
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_1,'a','A',0xE0,0xC0},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_2,'b','B',0xE1,0xC1},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_3,'c','C',0xE2,0xC2},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_4,'d','D',0xE3,0xC3},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_5,'e','E',0xE4,0xC4},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_6,'f','F',0xE5,0xC5},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_7,'g','G',0xE6,0xC6},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_8,'h','H',0xE7,0xC7},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_9,'i','I',0xE8,0xC8},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_10,'j','J',0xE9,0xC9},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_11,'k','K',0xEA,0xCA},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_12,'l','L',0xEB,0xCB},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_13,'m','M',0xEC,0xCC},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_14,'n','N',0xED,0xCD},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_15,'o','O',0xEE,0xCE},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_16,'p','P',0xEF,0xCF},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_17,'q','Q',0xF0,0xD0},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_18,'r','R',0xF1,0xD1},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_19,'s','S',0xF2,0xD2},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_20,'t','T',0xF3,0xD3},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_21,'u','U',0xF4,0xD4},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_22,'v','V',0xF5,0xD5},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_23,'w','W',0xF6,0xD6},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_24,'x','X',0xF7,0xD7},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_25,'y','Y',0xF8,0xD8},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_26,'z','Z',0xF9,0xD9},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_27,'<','0',0xFA,0xDA},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_28,'>','1',0xFB,0xDB},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_29,'.','2',0xFC,0xDC},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_30,'|','3',0xFD,0xDD},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_31,'@','4',0xFE,0xDE},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_32,'$','5',0xFF,0xDF},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_33,'/','6','0','8'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_34,'%','7','1','9'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_35,'\'','8','2','<'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_36,'(','9','3','>'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_37,')','!','4',':'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_38,'_','?','5',';'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_39,'-','#','6','\"'},
	{HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_40,'+',',','7','*'},
	{0,0,0,0,0} //END
};

//-------------------------------------------------------------------------------------------------
// Local Variable
//------------------------------------------------------------------------------------------------
static HWND _hPrevPageFocus = HWND_MENU_DISHSETUP_LNBTYPE;
static MS_U16* const u16StringBuff=(MS_U16*) CHAR_BUFFER;

static MS_U8 _bAddSATOrTP = FALSE;

static MS_SAT_PARAM SatInfor;
static DTVPROGRAMID_M CarrierParam;
static MS_U8   u8SATNum = 0;
 MS_U8   u8CurrentEditSATId = 0; //physical id
static MS_U16   u16CurrentEditSATTPPos = 0;
static MS_U8 u8CurLofInListIdx = 0;

static MS_S16 _s16QualityPercent = 0;
static MS_U8 _u8ModifyParam = 0;

static MS_U8 u8CurrentDigitalIdx = 0;
static MS_U8 u8CurrentDigitalIdxdot = 0;
static SCAN_TYPE S2_enScanType = SCAN_DEFAULT;
#if(ENABLE_S2_FAST_SCAN)
static EN_SATELLITE_PLATFORM S2_FastScan_Type = EN_SATEPF_CANALDIGITALAL_HD;
#endif
static MS_BOOL _bIsValidSAT = FALSE;

static MS_BOOL bNeedToSaveSatellite = FALSE;
static MS_U8   _u8pLocation;

static MS_U8     _u8MoveTime = 100;
static MOVE_STATE   _s8MoveState = MOVE_STOP;
static MS_U8  _u8MoveSteps = 1;

static SCAN_SAVETYPE _eScanProgSaveType = SCAN_SAVEALL;
static SCAN_SERVICETYPE _eScanServiceType = SCAN_SERVICE_ALL;

static SET_LIMIT_STATE _enSetLimtState;
static MS_BOOL _bLongitudeMinus = FALSE;
static MS_BOOL _bLatitudeMinus  = FALSE;


static MS_U16 _enMsgTextID;

//-------------------------------------------------------------------------------------------------
// Local Function
//------------------------------------------------------------------------------------------------
BOOLEAN MApp_ZUI_ACT_ExecuteDishSetupMenuAction(U16 act);
static MS_U16 _GetCurrentSatTPNum(void);
//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Extern Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Function
//-------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////

static void MApp_ZUI_ACT_SliderbarWinPro(HWND hwnd,MS_U16 Pos,MS_U16 Num)//jme.zeng 20100821 add for sliderbar
{
	RECT rect;
	MS_S16 height = 0;
	MS_S16 step;

       memset(&rect, 0x00, sizeof(RECT)); // fix coverity 207486
	if(Num==0)
		Num=1;
	if(Pos>=Num)
		Pos=Num-1;

	if(Num > 0)
	{
		MApp_ZUI_API_GetWindowInitialRect(hwnd, &rect);
		step = rect.height/Num;
		height =step + rect.height%Num;
		rect.top= rect.top+step*Pos;
		rect.height= height;
		MApp_ZUI_API_MoveWindow(hwnd, &rect);
	}
}

static inline void _rstTimer(void)
{
    MApp_ZUI_API_SendMessage(HWND_MENU_DISHSETUP_COVER, MSG_NOTIFY_CONTENT_CHANGED, 0);
}

static inline void _disTimer(void)
{
    MApp_ZUI_API_SendMessage(HWND_MENU_DISHSETUP_COVER, MSG_NOTIFY_DISABLE, 0);
}

static inline void _enTimer(void)
{
    MApp_ZUI_API_SendMessage(HWND_MENU_DISHSETUP_COVER, MSG_NOTIFY_ENABLE, 0);
}

static MS_U8 _GetPosBySatID(MS_U8 u8ID)
{
	return MApi_DB_SAT_GetActiveSatIndexBySatID(u8ID);
}
static void _Init_satortplist(void)
{
	if(u8CurEditListType == TYPE_SATLIST)
	{
		MS_U8 u8Pos = _GetPosBySatID(u8CurrentEditSATId);

		if(u8Pos >= u8SATNum)
		{
			u8Pos = 0;
		}
		MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u8Pos, (MS_U16) u8SATNum);
		MApp_ZUI_API_SetFocus(prefocuswind);
	}
	else
	{
		MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u16CurrentEditSATTPPos, (MS_U16) _GetCurrentSatTPNum());
		MApp_ZUI_API_SetFocus(PreTpFocusWind);
	}
}

static MS_U8 _GetSatIDByPos(MS_U8 u8Pos)
{
	return MApi_DB_SAT_GetSatIDByIndexOfActiveSats(u8Pos);
}

BOOLEAN _GetSatInforByID(MS_U8 u8SATId,MS_SAT_PARAM *pSATParam)//获得卫星的信息
{
	MS_BOOL bRet =TRUE;

	if(INVALID_SATINDEX == u8SATId)
		return FALSE;

	if(TRUE==MApi_DB_SAT_GetSATParam(u8SATId,pSATParam))
		bRet = TRUE;
	else
		bRet = FALSE;
	return bRet;

}

static BOOLEAN _AddSatInfor(MS_U8* u8SatID)//添加卫星信息
{
	return MApi_DB_SAT_AddSAT(u8SatID,&SatInfor);
}

static BOOLEAN _SaveSatInfor(MS_U8 u8SATIdx)//存储卫星的信息
{
	return MApi_DB_SAT_UpdateSAT(u8SATIdx,&SatInfor);
}
static BOOLEAN _DeleteSATByPos(MS_U16 pos)
{
	MS_U8 idx;

	idx = MApi_DB_SAT_GetSatIDByIndexOfActiveSats(pos);
	MApi_SAT_SelectSATEntity(idx,FALSE);
	MApi_DB_DFT_DeleteAllPhysicalChannelBySatID(idx);
	RemoveProgram_by_Sat(idx);
	if(!(IsS2_Current_ProgramEntityActive()))
	{
		g_stCurS2ProggramId.u32S2Frequency=0xffff;
		MApi_DigiTuner_Tune2RfCh(SatInfor,&g_stCurS2ProggramId,eAutoTune);
	}
	if(TRUE==MApi_DB_SAT_DeleteSAT(idx))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

static BOOLEAN _AddCarrierParam(MS_U16* u16SATTPIdx,DTVPROGRAMID_M *pCarrierParam)
{
    MS_U16 u16AddIdx = 0;

    pCarrierParam->SatelliteId = u8CurrentEditSATId;

    if(MApi_DB_DFT_AddPhysicalChannel(&u16AddIdx,pCarrierParam))
    {
        *u16SATTPIdx = MApi_DB_DFT_PCHIndex2PositionBySatID(u16AddIdx,&u8CurrentEditSATId);
        return TRUE;
    }
    return FALSE;
}

static LPTSTR _GetSatelliteListTxt(MS_U16 idx)
{
	MS_SAT_PARAM tmpSatInfor;
       memset(&tmpSatInfor, 0x00, sizeof(MS_SAT_PARAM));	 // fix coverity 207582
	idx = idx+SatListPageNum*8;

	if(TRUE == _GetSatInforByID( _GetSatIDByPos(idx),&tmpSatInfor))
	{
		char *ptr,*str = NULL;
		char ptr_head[100]={0};
		ptr = ptr_head;
		UNUSED(str);
		if(tmpSatInfor.u16Angle>1800)
			sprintf(ptr,"%03d %03d.%d W  ",idx+1,tmpSatInfor.u16Angle/10,tmpSatInfor.u16Angle%10);
		else
			sprintf(ptr,"%03d %03d.%d E  ",idx+1,tmpSatInfor.u16Angle/10,tmpSatInfor.u16Angle%10);

		if(tmpSatInfor.eLNBType == EN_LNBTYPE_C)
		{
			strcat(ptr,"C_");
		}
		else
		{
			strcat(ptr,"Ku_");
		}
		strcat(ptr,(char*)tmpSatInfor.aSatName);
		MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, UTL_strlen1((char *)ptr_head));
		return CHAR_BUFFER;
	}
	else
	{
		return MApp_ZUI_API_GetString(Empty);
	}
}

static MS_U16  _GetCurrentSatTPNum(void)
{
	return MApi_DB_DFT_PhysicalChannelBySatID(u8CurrentEditSATId);
}

static WORD _PositionBySatID2PCHIndex(MS_U8 u8SatID,WORD wPosition)
{
    WORD wPos = 0;
    BYTE u8TmpSatID;
    WORD wPchIndex;
    BOOL eResult;
    for(wPchIndex=0;wPchIndex<MAX_DTV_S2_MUX_NUMBER;wPchIndex++)
    {
        if (TRUE == IsS2ChannelEntityActive(wPchIndex))
        {
            eResult = GetIDTable(wPchIndex, (BYTE *)&u8TmpSatID, E_DATA_ID_SATLITE);
			if(TRUE == eResult && u8TmpSatID == u8SatID)
            {
                if(wPosition == wPos)
                    break;
                wPos++;
            }
        }
    }
    if(MAX_DTV_S2_MUX_NUMBER <= wPchIndex)
        return (0xffff);
    else
        return (wPchIndex);
}

WORD MApi_DB_DFT_PositionBySatID2PCHIndex(BYTE bSatID,WORD wPosition)
{
    WORD wPchIndex;
    wPchIndex =  _PositionBySatID2PCHIndex(bSatID,wPosition);
    return wPchIndex;
}

static BOOLEAN _DeleteTP(MS_U16 u16SATTPIdx)
{
	MS_U16 u16TPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,u16SATTPIdx);

	if (MApi_DB_CM_DeleteAllProgByPCHIndex(u16TPIdx))
	{
		if(MApi_DB_DFT_DeletePhysicalChannel(u16TPIdx))
		{
			if(!(IsS2_Current_ProgramEntityActive()))
			{
				g_stCurS2ProggramId.u32S2Frequency=0xffff;
				MApi_DigiTuner_Tune2RfCh(SatInfor,&g_stCurS2ProggramId,eAutoTune);
			}
			return TRUE;
		}
	}
	return FALSE;
}

static BOOLEAN _SaveCarrierParam(MS_U16 u16SATTPIdx,DTVPROGRAMID_M *pCarrierParam)
{
    MS_U16 u16TPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,u16SATTPIdx);
    pCarrierParam->SatelliteId = u8CurrentEditSATId;

    return MApi_DB_DFT_UpdatePhysicalChannel(u16TPIdx,pCarrierParam);
}

static BOOLEAN _GetCarrierParam(MS_U16 u16SATTPIdx,DTVPROGRAMID_M *pCarrierParam)
{
	MS_U16 u16TPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,u16SATTPIdx);
	MS_U16 u16TPNum = _GetCurrentSatTPNum();
	if(u16TPNum == 0)
	{
		pCarrierParam->u32S2Frequency = 0;
		return FALSE;
	}
	if(u16SATTPIdx>= u16TPNum)
	{
		return FALSE;
	}
	if(TRUE==GetIDTable(u16TPIdx,(BYTE *)pCarrierParam,E_DATA_ID_TABLE))
		return TRUE;
	else
		return FALSE;
}

static LPTSTR _GetTPListTxt(MS_U16 idx)
{
	DTVPROGRAMID_M S2_tp_info;
	idx +=TpListPageNum*8;
	if (TRUE == _GetCarrierParam(idx,&S2_tp_info))
	{
		char ptr_head[100]={0};
		if( S2_tp_info.u8Polarity)
		{
			sprintf(ptr_head, "%03d %d V %d", idx+1,S2_tp_info.u32S2Frequency, S2_tp_info.u16SymbolRate);
		}
		else
		{
			sprintf(ptr_head, "%03d %d H %d",idx+1, S2_tp_info.u32S2Frequency, S2_tp_info.u16SymbolRate);
		}
		MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)ptr_head, UTL_strlen1((char *)ptr_head));
		return CHAR_BUFFER;
	}
	else
	{
		return NULL;
	}
	return NULL;
}

static LPTSTR _GetSatOrTpListTxt(MS_U16 idx)
{
	if(u8CurEditListType == TYPE_SATLIST)
	{
		return _GetSatelliteListTxt(idx);
	}
	else
	{
		return _GetTPListTxt(idx);
	}
}

static void _ReturnBackToSatOrTPlist(void)
{
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_SHOW);
	if(u8CurEditListType == TYPE_SATLIST)
		MApp_ZUI_API_SetFocus(prefocuswind);
	else
		MApp_ZUI_API_SetFocus(PreTpFocusWind);
}

static MS_BOOL _CheckCurrentSatChanged(void)
{
	MS_SAT_PARAM tempSATParam;
        memset(&tempSATParam, 0x00, sizeof(MS_SAT_PARAM)); // fix coverity 207487

	_GetSatInforByID(u8CurrentEditSATId,&tempSATParam);
	if(memcmp(&tempSATParam,&SatInfor,sizeof(MS_SAT_PARAM)) ==0)
	{
		return FALSE;
	}
	return TRUE;
}

static void _GetCurrentServiceSatID(void)
{

}

static void _matchCurrentServiceTP(void)
{

}

/*
static void _RefeshCurSatelliteOrTpParam(void)
{

}
*/

static BOOLEAN _CheckSameLongitude(void)
{
    MS_SAT_PARAM enSatInfor;
    int i;

    memset(&enSatInfor, 0x00, sizeof(MS_SAT_PARAM)); // fix coverity 207488
    for(i = 0;i < MAX_NUM_OF_SAT;i++)
    {
        _GetSatInforByID(_GetSatIDByPos(i),&enSatInfor);
        if(enSatInfor.u16Angle == SatInfor.u16Angle && enSatInfor.eLNBType == SatInfor.eLNBType)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static MS_U8 _softkeyboard_dispchar(HWND hWnd)
{
	MS_U8 u8Index = 0;
	MS_U8 u8Char = 0;

	while(softkey[u8Index].hWnd >0 )
	{
	     if(softkey[u8Index].hWnd == hWnd)
	     {
	          if(bIsExtendChar)
	          {
	               if(bIsCaptalChar)
	               {
	                     u8Char=softkey[u8Index].extendcapschar;
	               }
	               else
	               {
	                     u8Char=softkey[u8Index].extendchar;
	               }
	          }
	          else
	          {
	                if(bIsCaptalChar)
	               {
	                     u8Char=softkey[u8Index].normalcapschar;
	               }
	               else
	               {
	                     u8Char=softkey[u8Index].normalchar;
	               }
	          }
	          break;
	     }
	     u8Index ++;
	}

	return u8Char;
}

static void _Init_LOFlist(void)
{
	u8CurLofInListIdx = 0;
	LofListPageNum= 0;
#if(SUPPORT_UNICABLE)
	MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_LOFLIST_VSCROLLBAR, 0, 12);
#else
	MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_LOFLIST_VSCROLLBAR, 0, 11);
#endif
}

static LPTSTR _GetLOFListTxt(MS_U8 idx)
{
	idx = idx + (LofListPageNum*7);
#if(SUPPORT_UNICABLE)
	if(idx < 12)
#else
	if(idx < 11)
#endif
		MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *) stLOF[idx].strDisplay, UTL_strlen1((char *)(stLOF[idx].strDisplay)));
	else
		MApp_ZUI_API_LoadString(Empty, CHAR_BUFFER);

	return CHAR_BUFFER;
}

static void _MoveNumberWnd(HWND hWnd,MS_BOOL bLeft,MS_U8 u8DigitalNum)
{
    #define DIGITALWIDTH_1   13
    #define GAPWIDTH_1   2
    RECT rect;
    memset(&rect, 0x00, sizeof(RECT)); // fix coverity 207490

    //memset(&rect,0,sizeof(RECT));

    if((bLeft && u8CurrentDigitalIdx>0 ) ||(!bLeft && u8CurrentDigitalIdx<(u8DigitalNum-1)))
    {
         //MApp_ZUI_API_ShowWindow(hWnd, SW_HIDE);
         MApp_ZUI_API_GetWindowInitialRect(hWnd, &rect);
         printf("\r\n WindowRect left = %d width = %d ",rect.left,rect.width);

         rect.width = DIGITALWIDTH_1;
         if(bLeft)
         {
                u8CurrentDigitalIdx --;
                rect.left = rect.left +(rect.width+GAPWIDTH_1)*(u8CurrentDigitalIdx);
         }
         else
         {
               u8CurrentDigitalIdx ++;
               rect.left = rect.left + (rect.width+GAPWIDTH_1)*u8CurrentDigitalIdx;
         }

         MApp_ZUI_API_MoveWindow(hWnd, &rect);
   }
	printf("\r\n u8CurrentDigitalIdx = %d ",u8CurrentDigitalIdx);
}
static void _ShowNumberWnd(HWND hWnd)
{
    #define DIGITALWIDTH_1   13
    #define GAPWIDTH_1   2
    RECT rect;
    memset(&rect, 0x00, sizeof(RECT)); // fix coverity 207491

	MApp_ZUI_API_GetWindowInitialRect(hWnd, &rect);
	printf("\r\n WindowRect left = %d width = %d ",rect.left,rect.width);

	rect.width = DIGITALWIDTH_1;
	rect.left = rect.left +(rect.width+GAPWIDTH_1)*(u8CurrentDigitalIdx);
	MApp_ZUI_API_MoveWindow(hWnd, &rect);
}
static BOOLEAN _handlekey_setlimit(VIRTUAL_KEY_CODE key)
{
    MS_BOOL eRetval         = FALSE;

    if(key == VK_SELECT)
    {
        MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
        if(_enSetLimtState == SET_WEST_LIMIT)
        {
           eRetval = MApi_DigiTuner_DiSEqC_SetWestLimit();
        }
        else if(_enSetLimtState == SET_EAST_LIMIT)
        {
            eRetval = MApi_DigiTuner_DiSEqC_SetEastLimit();
        }
        else if(_enSetLimtState == GOTO_REF)
        {
            eRetval = MApi_DigiTuner_DiSEqC_GoReferencePoint();
        }
        else if(_enSetLimtState == DISABLE_LIMIT)
        {
            eRetval = MApi_DigiTuner_DiSEqC_DisableLimit();
        }
        else if(_enSetLimtState == GOTO_X)
        {
            eRetval = MApi_DigiTuner_DiSEqC_GotoX(SatInfor.u16Angle,SetSATLocation[_u8pLocation].MyLongitude,SetSATLocation[_u8pLocation].MyLatitude);
        }
        else if(_enSetLimtState == GOTO_POSITON)
        {
              eRetval = MApi_DigiTuner_DiSEqC_GoSatPos(SatInfor.u8Position);
        }
        else if(_enSetLimtState == STORE_POSITON)
        {
             eRetval = MApi_DigiTuner_DiSEqC_SaveSatPos(SatInfor.u8Position);
        }
    }
    else if(key == VK_EXIT)
    {
        MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
        eRetval = FALSE;
    }
    return TRUE ;
}


static void _SetMoveStep(MOVE_STATE State,MS_U8 step)
{
	UNUSED(State);
	if(_s8MoveState == MOVE_EAST_STEP)
	{
		MApi_DigiTuner_DiSEqC_MotorStepEast(step);
	}//west
	else if(_s8MoveState == MOVE_WEST_STEP)
	{
		MApi_DigiTuner_DiSEqC_MotorStepWest(step);
	}//east
}

static void _SetMoveState(MOVE_STATE State)
{
    _s8MoveState = State;
    if(State != MOVE_STOP)
    {
        if(_s8MoveState == MOVE_WEST)
        {
           MApi_DigiTuner_DiSEqC_MotorConinuteWest();
        }//west
        else if(_s8MoveState == MOVE_EAST)
        {
           MApi_DigiTuner_DiSEqC_MotorConinuteEast();
        }//east
        if(_s8MoveState == MOVE_EAST_STEP)
        {
           MApi_DigiTuner_DiSEqC_MotorStepEast(_u8MoveSteps);
        }//west
        else if(_s8MoveState == MOVE_WEST_STEP)
        {
           MApi_DigiTuner_DiSEqC_MotorStepWest(_u8MoveSteps);
        }//east
        _u8MoveTime = 0;
    }
    else
    {
        MApi_DigiTuner_DiSEqC_HaltMotor();
        switch(MApp_ZUI_API_GetFocus())
        {
            case HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE:
              MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE_LARROW,SW_SHOW);
              MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE_RARROW,SW_SHOW);
                break; // Fix coverity!?

            case HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO:
              MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_LARROW,SW_SHOW);
              MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_RARROW,SW_SHOW);
                break; // Fix coverity!?

            case HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE:
              MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE_LARROW,SW_SHOW);
              MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE_RARROW,SW_SHOW);
                break; // Fix coverity!?

            default:
                break;
        }
        _u8MoveTime = 100;
    }
}

static MOVE_STATE _GetMoveState(void)
{
    return _s8MoveState;
}

static void _MoveNumberWnddot(HWND hWnd,MS_BOOL bLeft,MS_U8 u8DigitalNum)
{
    #define DIGITALWIDTH   13
    #define GAPWIDTH   2
    #define POINTWITH  6
    RECT rect;

    memset(&rect,0,sizeof(RECT));

    if((bLeft && u8CurrentDigitalIdxdot>0 ) ||(!bLeft && u8CurrentDigitalIdxdot<(u8DigitalNum-1)))
    {
         //MApp_ZUI_API_ShowWindow(hWnd, SW_HIDE);
         MApp_ZUI_API_GetWindowInitialRect(hWnd, &rect);

         rect.width = DIGITALWIDTH;
         if(bLeft)
         {
                u8CurrentDigitalIdxdot --;
                if(u8CurrentDigitalIdxdot == 3)
                    rect.left = rect.left +(rect.width+GAPWIDTH)*u8CurrentDigitalIdxdot +POINTWITH;
                else
                    rect.left = rect.left +(rect.width+GAPWIDTH)*u8CurrentDigitalIdxdot;
         }
         else
         {
               u8CurrentDigitalIdxdot ++;
               if(u8CurrentDigitalIdxdot == 3)
                   rect.left = rect.left + (rect.width+GAPWIDTH)*u8CurrentDigitalIdxdot+POINTWITH;
               else
                   rect.left = rect.left + (rect.width+GAPWIDTH)*u8CurrentDigitalIdxdot;
         }

         MApp_ZUI_API_MoveWindow(hWnd, &rect);
   }
}
static MS_U32  _ModifyValue(MS_U32 u32Value,MS_U8 u8DigtitalVal,MS_U8 u8DigitalNum)
{
	MS_U32 u32Temp = 0;
	MS_U32 u32TempValue = u32Value;

	if(u8CurrentDigitalIdx< (u8DigitalNum - 1))
	{
		u32Temp = pow(10,u8DigitalNum-u8CurrentDigitalIdx-1);
		u32TempValue = u32TempValue/(u32Temp*10) * (u32Temp*10) + u32TempValue %u32Temp;
		u32TempValue += u8DigtitalVal*u32Temp;
	}
	else
	{
		u32TempValue = u32TempValue /10 *10 + u8DigtitalVal;
	}
	if(u32TempValue > 0xFFFF)
	{
		u32TempValue = u32Value ;
	}
	return u32TempValue;
}

static MS_U32  _ModifyValuedot(MS_U32 u32Value,MS_U8 u8DigtitalVal,MS_U8 u8DigitalNum)
{
	MS_U32 u32Temp = 0;
	MS_U32 u32TempValue = u32Value;

	if(u8CurrentDigitalIdxdot< (u8DigitalNum - 1))
	{
		u32Temp = pow(10,u8DigitalNum-u8CurrentDigitalIdxdot-1);
		u32TempValue = u32TempValue/(u32Temp*10) * (u32Temp*10) + u32TempValue %u32Temp;
		u32TempValue += u8DigtitalVal*u32Temp;
	}
	else
	{
		u32TempValue = u32TempValue /10 *10 + u8DigtitalVal;
	}
	if(u32TempValue > 1800)
	{
		u32TempValue = u32Value ;
	}
	return u32TempValue;
}

/*static void _FlushMaskWndLeftToSteadyWnd(HWND hMaskWnd,HWND steadyWnd)
{
      RECT maskWndRect,steadyWndRect;

      MApp_ZUI_API_GetWindowInitialRect(hMaskWnd, &maskWndRect);
      MApp_ZUI_API_GetWindowInitialRect(steadyWnd,&steadyWndRect);
      if(maskWndRect.left != steadyWndRect.left)
      {
           maskWndRect.left = steadyWndRect.left;
           memcpy(&GETWNDINITRECT(hMaskWnd), &maskWndRect, sizeof(RECT));
           if(MApp_ZUI_API_IsWindowVisible(hMaskWnd))
           {
                 MApp_ZUI_API_ShowWindow(hMaskWnd, SW_SHOW);
           }
      }
}*/
/*static void _ResetMaskWnd(HWND hWnd)
{
      hWnd = hWnd;
      u8CurrentDigitalIdx = 0;
      u8CurrentDigitalIdxdot = 0;
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_TP_EDIT_FREQ_MASK,HWND_MENU_DISHSETUP_TP_EDIT_FREQ_OPTION);
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_MASK,HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_OPTION);
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK,HWND_MENU_DISHSETUP_SETLOF_LLOF_VALUE);
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK,HWND_MENU_DISHSETUP_SETLOF_HLOF_VALUE);
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_MASK,HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_SET);
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_MASK,HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_SET);
      _FlushMaskWndLeftToSteadyWnd(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_MASK,HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_SET);

}*/
//#define DISEQC12_USALS_POSITION_MASK 0x3f
static MS_U8 _GetNextUnusedPosition(void)
{
	MS_SAT_PARAM tmpSatInfor;
	MS_U8 u8SatID;
	MS_U8 u8Idx,u8Status[DISEQC12_USALS_POSITION_MASK];

	memset(u8Status, 0, DISEQC12_USALS_POSITION_MASK);
    memset(&tmpSatInfor, 0x00, sizeof(MS_SAT_PARAM));  // fix coverity 207581
	for(u8Idx = 0;u8Idx <u8SATNum;u8Idx++)
	{
	    u8SatID = _GetSatIDByPos(u8Idx);
	    if(u8SatID != u8CurrentEditSATId)
	    {
	          if(_GetSatInforByID(u8SatID,&tmpSatInfor))
	          {
	                tmpSatInfor.u8Position &= DISEQC12_USALS_POSITION_MASK;
	                if(tmpSatInfor.u8Position>0)
	                {
	                      u8Status[tmpSatInfor.u8Position] = 1;
	                }
	          }
	          else
	          {
	                break;
	          }
	    }
	}
	for(u8Idx = 1;u8Idx < DISEQC12_USALS_POSITION_MASK;u8Idx++) //<= -> < Fix coverity CID 207397
	{
	    if(u8Status[u8Idx]==0)
	    {
	          break;
	    }
	}
	if(u8Idx>  DISEQC12_USALS_POSITION_MASK)
	{
	    u8Idx = 1;
	}
	return (u8Idx);
}

static U16 _GetSatSel_Bmp(MS_U16 idx)
{
    MS_U16 u16BmpIndex =~0;
	{
	    if((u8CurEditListType == TYPE_SATLIST&&MApi_SAT_IsSatEntirySelect(_GetSatIDByPos(idx+SatListPageNum*8)))
	        ||(u8CurEditListType == TYPE_TPLIST&&MApi_DFT_IsPCHEntirySelect(MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,idx+TpListPageNum*8))))
	    {
	         u16BmpIndex = E_BMP_ICON_ITEMSEL;
	    }
	    else
	    {
	         u16BmpIndex =  ~0;
	    }
	}
    return u16BmpIndex;
}

static MS_U16 _AddDefaultTPsBySatID(MS_U8 u8SatID)
{
	DTVPROGRAMID_M carrierParam;
	MS_U16 wTPPos, wTPIdx;
	MS_U16 wTPNum,wIdx;

       memset(&carrierParam, 0x00, sizeof(DTVPROGRAMID_M)); // fix coverity 218312

	wTPNum = MApi_DB_DFT_PhysicalChannelBySatID(u8SatID);
	printf("\r\nwTPNum=======%d",wTPNum);
	wIdx = 0;
	for(wTPPos=0;wTPPos<wTPNum;wTPPos++)
	{
		wTPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(u8SatID, wTPPos);
		GetIDTable(wTPIdx, (BYTE *)&carrierParam,E_DATA_ID_TABLE);
		MApp_MenuChannel_AddScanTp(carrierParam);
		wIdx++;
	}
	printf("\r\nwIdx=%d",wIdx);
	return (wIdx);
}
extern DTVPROGRAMID_M _afe_param[MAX_TPSOFSAT_NUM];
void ReMove_Patch_Program(U8 CurrentEditListType ,SCAN_TYPE SearchType)
{
	WORD i;
	SearchType=SearchType;
	if(CurrentEditListType==TYPE_SATLIST)
	{
		for(i=0;i<_u8MultiSatNum;i++)
			RemoveProgram_by_Sat( _lnb_satelliteID[i]);
	}
	else
	{
		for(i=0;i<_u16MultiTPNum;i++)
			RemoveProgram_by_TP( _afe_param[i]);
	}
}
static void _AddScanSatelliteAndTP(void)
{
	MS_U8 u8Add=0;

	MApp_MenuChannel_ResetScanSatIDList();
	MApp_MenuChannel_ResetScanTpList();
	u16ScanDtvChNum=0;
	u16ScanRadioChNum=0;
#if NORDIG_FUNC
	u16ScanDataChNum = 0;
#endif
	u8ScanPercentageNum=0;
	if(u8CurEditListType == TYPE_TPLIST)
	{
	    MS_U16 i,wPCH;
	    MS_U16 TpNum;
	    DTVPROGRAMID_M stCarrier;

	    u8Add = 0;
	    MApp_MenuChannel_AddScanSat(u8CurrentEditSATId);
	    TpNum = _GetCurrentSatTPNum();
	    for(i=0;i<TpNum;i++)
		{
			wPCH = MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,i);
			if(MApi_DFT_IsPCHEntirySelect(wPCH))
			{
				if(_GetCarrierParam(i/*wPCH*/,&stCarrier))
				{
					MApp_MenuChannel_AddScanTp(stCarrier);
					u8Add ++;
				}
			}
		}
	}
	else
	{
	    MS_U8 i;
	    MS_U8 u8SatID,u8FirstSatID=u8CurrentEditSATId;
	    u8Add = 0;
	    for(i=0;i<MAX_NUM_OF_SAT;i++)
		{
			u8SatID = _GetSatIDByPos(i);
			if(MApi_SAT_IsSatEntirySelect(u8SatID))
			{
				MApp_MenuChannel_AddScanSat(u8SatID);
				if(u8Add == 0)
				{
					u8FirstSatID = u8SatID;
				}
				u8Add ++;
			}
		}
	    if(u8Add == 0)
	    {
			u8FirstSatID = u8CurrentEditSATId;
			MApp_MenuChannel_AddScanSat(u8CurrentEditSATId);
	    }

	    if(S2_enScanType != SCAN_BLIND)
	    {
			_AddDefaultTPsBySatID(u8FirstSatID);
	    }
	}
	switch(S2_enScanType)
	{
		default:
		case SCAN_DEFAULT:
		{
			if(u8CurEditListType == TYPE_SATLIST)
			{
				MApp_MenuChannel_FullScan_Start();
				stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_AUTO;
			}
			else
			{
				if(u8Add == 1)
				{
					MApp_MenuChannel_ManuScan_Start();
					stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_MANUAL;
				}
				else
				{
					MApp_MenuChannel_FullScan_Start();
					stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_AUTO;
				}
			}
			break;
		}
		case SCAN_BLIND:
		{
			MApp_MenuChannel_BuildScan_Start();
			stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_BLIND;
			break;
		}
		case SCAN_NETWORK:
#if(ASTRA_HD_ENABLE)
        case SCAN_ASTRA_FAST:
#endif
		{
			MApp_MenuChannel_NetworkScan_Start();
			stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_NETWORK;
			break;
		}

#if(ENABLE_S2_FAST_SCAN)
        case SCAN_FAST:
        {
            if(u8CurEditListType == TYPE_SATLIST)
            {
                MApp_MenuChannel_FullScan_Start();
                stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_FAST;
            }
            else
            {
                if(u8Add == 1)
                {
                    MApp_MenuChannel_ManuScan_Start();
                    stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_FAST;
                }
                else
                {
                    MApp_MenuChannel_FullScan_Start();
                    stGenSetting.stScanMenuSetting.u8ScanType=S2_SCAN_TYPE_FAST;
                }
            }
            break;
        }
#endif
	}

#if(!ENABLE_S2_FAST_SCAN)
	if (stGenSetting.stScanMenuSetting.u8ScanType == S2_SCAN_TYPE_MANUAL)
	{
		ReMove_Patch_Program(u8CurEditListType,S2_enScanType);
	}
	else
#endif //#if(ENABLE_S2_FAST_SCAN)

	{
		msAPI_CM_ResetS2Program();
	}
}

extern void MApp_SaveGenSetting(void);
static void _GotoChannelSearch(void)
{
	//printf("u8CurrentEditSATId = %d,[%d]\n", u8CurrentEditSATId,S2_enScanType);
	if(_CheckCurrentSatChanged())
	{
		bNeedToSaveSatellite = TRUE;
		_SaveSatInfor(u8CurrentEditSATId);
	}
#if(ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION)
	g_u16SearchPosition=0xffff;
#endif
	_AddScanSatelliteAndTP();
	MApi_SAT_UnSelectAllSAT();

	MApp_SaveGenSetting();
	//printf("\r\nstScanMenuSetting.u8ScanType=%d",stGenSetting.stScanMenuSetting.u8ScanType);
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_AppShowDishSetupMenu
///  [OSD page handler] provide for showing MENU application
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

void MApp_ZUI_ACT_AppShowDishSetupMenu(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_MENU_DISHSETUP;
    	printf("MApp_ZUI_ACT_AppShowDishSetupMenu 1 \r\n");
    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    u8CurEditListType = TYPE_SATLIST;
    SatListPageNum = 0;
    TpListPageNum = 0;
    LofListPageNum = 0;
    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }
    RECT_SET(rect,
        ZUI_MENU_DISHSETUP_XSTART, ZUI_MENU_DISHSETUP_YSTART,
        ZUI_MENU_DISHSETUP_WIDTH, ZUI_MENU_DISHSETUP_HEIGHT);
    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }
printf("MApp_ZUI_ACT_AppShowDishSetupMenu 2\r\n");
    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
        //printf("wnd =%d \r\n",wnd);
    }
printf("MApp_ZUI_ACT_AppShowDishSetupMenu 3\r\n");
	MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_LOFLIST, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_RESETALLCHANNELS, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_TP_EDIT, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_CHANNELSERACH, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_FAST_SCAN, SW_HIDE);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_ITEMS, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_BG, SW_SHOW);
	MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_TITLE, SW_SHOW);
    MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1);
    prefocuswind = MApp_ZUI_API_GetFocus();
    PreTpFocusWind = MApp_ZUI_API_GetFocus();
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    printf("MApp_ZUI_ACT_AppShowDishSetupMenu 4 \r\n");
	{
	     _hPrevPageFocus = HWND_MENU_DISHSETUP_LNBTYPE;
	     _GetCurrentServiceSatID();

	     u8SATNum = MApi_DB_SAT_GetSATCount();
	     {
	           u8CurrentEditSATId = _GetSatIDByPos(0);
	     }
	     if(u8SATNum == 0)
	     {
	          _bIsValidSAT = FALSE;
	     }
	     else
	     {
	          _bIsValidSAT = _GetSatInforByID(u8CurrentEditSATId,&SatInfor);
	     }
         printf("MApp_ZUI_ACT_AppShowDishSetupMenu 5 \r\n");
	     if(_bIsValidSAT)
	     {
			_matchCurrentServiceTP();
			_GetCarrierParam(u16CurrentEditSATTPPos,&CarrierParam);
			_u8ModifyParam = 1;
	     }
	     printf("MApp_ZUI_ACT_AppShowDishSetupMenu 6 \r\n");
	     u8CurrentDigitalIdx = 0;
	     u8CurrentDigitalIdxdot = 0;
	     bNeedToSaveSatellite = FALSE;
	     u8CurEditListType = TYPE_SATLIST;
	     _u8pLocation = stGenSetting.stDvbsSetting.u8Location;
	     if(_u8pLocation >= LOCATION_NUM)
	        _u8pLocation = 0;
	     _Init_satortplist();
	     printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7 \r\n");
	     //init manual param
	     printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-1 \r\n");
	     SetSATLocation[0].MyLongitude= stGenSetting.stDvbsSetting.stManualLocation.MyLongitude;
	     printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-2 \r\n");
	     SetSATLocation[0].MyLatitude= stGenSetting.stDvbsSetting.stManualLocation.MyLatitude;
	     printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-3 \r\n");
	    _enTimer();
	    printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-4 \r\n");
	}
	MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u8CurrentEditSATId, (MS_U16) u8SATNum);
printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-5 KIMI\r\n");
	{
		if (MApi_DigiTuner_TPSGetLock() == TRUE)
		{
		    printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-6 \r\n");
			_s16QualityPercent = MApi_DigiTuner_getCurRFSignalSNR_Persent();
			printf("\r\n_s16QualityPercent=%d",_s16QualityPercent);
		}
		else
		{
		    printf("MApp_ZUI_ACT_AppShowDishSetupMenu 7-6 \r\n");
			_s16QualityPercent = 0;
		}
		printf("MApp_ZUI_ACT_AppShowDishSetupMenu 9 \r\n");
		MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_QULITY, SW_SHOW);
	#if ENABLE_S2_QUALITY_DISPLAY_PERCENT
		MApp_ZUI_API_SetTimer(HWND_MENU_DISHSETUP_QULITY, 0, DISHSETUP_SIGNAL_BAR_MONITOR_DURATION);  //for icon flash
		u16CurrentSatTpIndex = 0;
		u16SatTpDetectCount = 0;
	#endif
	    printf("MApp_ZUI_ACT_AppShowDishSetupMenu 10 \r\n");
	}

	printf("MApp_ZUI_ACT_AppShowDishSetupMenu done \r\n");
}

#if 1// DISEQC12_MOVECONTINUE_HOLDKEYPRESS
#define KEY_HOLD_CHECK_COUNT   2 //200ms
#define KEY_RELEASE_CHECK_COUNT   5//500ms
#endif
static MS_U8 _GetSatListPostion(void)
{
    MS_U8 Pos = 0;

	switch(MApp_ZUI_API_GetFocus())
	{
        case HWND_MENU_DISHSETUP_SATLIST_ITEM1:
			Pos = 0;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM2:
			Pos = 1;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM3:
			Pos = 2;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM4:
			Pos = 3;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM5:
			Pos = 4;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM6:
			Pos = 5;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM7:
			Pos = 6;
			break;
        case HWND_MENU_DISHSETUP_SATLIST_ITEM8:
			Pos = 7;
			break;
	}
	return Pos;

}

#if ENABLE_S2
BOOLEAN _DishSetup_HandleSatelliteOrTPListKey(VIRTUAL_KEY_CODE key)
#else
static BOOLEAN _DishSetup_HandleSatelliteOrTPListKey(VIRTUAL_KEY_CODE key)
#endif
{
	MS_BOOL eRetval         = FALSE;
	MS_BOOL bValidateKey    = FALSE;
	if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG))
	{
		switch(key)
		{
			case VK_SELECT:
				if( _enMsgTextID == en_str_Existed_Longitude)
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_SHOW);
					_enMsgTextID = USER_DEFINE_STRING;
					return TRUE;
				}
				break;
			case VK_EXIT:
				break;
			default:
				return TRUE;
		}
	}
#if ENABLE_S2_QUALITY_DISPLAY_PERCENT
	if(VK_UP == key || VK_CHANNEL_PLUS == key || VK_DOWN == key|| VK_CHANNEL_MINUS == key)
	{
		u16CurrentSatTpIndex = 0;
		u16SatTpDetectCount = 0;
	}
#endif
	switch(key)
	{
		case VK_UP:
		case VK_PAGE_UP:
		{
			MS_U8 u8Pos = 0;
			if(u8CurEditListType == TYPE_SATLIST && MApi_DB_SAT_GetSATCount() == 0)
			{
				SatListPageNum = 0;
				eRetval = TRUE;
				break;
			}
			else if(u8CurEditListType == TYPE_TPLIST&& _GetCurrentSatTPNum() == 0)
			{
				TpListPageNum = 0;
				eRetval = TRUE;
				break;
			}
			printf("Satellite list key up down 20100702\n");

			if(u8CurEditListType == TYPE_SATLIST )
			{
				PreTpFocusWind = HWND_MENU_DISHSETUP_SATLIST_ITEM1;
				TpListPageNum = 0;
				u16CurrentEditSATTPPos = 0;
				u8Pos = _GetSatListPostion();

				u8Pos = u8Pos + SatListPageNum*8-1;

				//u8CurrentEditSATId  =  _GetSatIDByPos(u8Pos);
				printf("\n u8CurrentEditSATId = 0x%2x",u8CurrentEditSATId);

				_GetSatInforByID(u8CurrentEditSATId,&SatInfor);
				MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_ITEMS);
				switch(MApp_ZUI_API_GetFocus())
				{
					case HWND_MENU_DISHSETUP_SATLIST_ITEM1:
					if(key == VK_UP )
					{
						if(SatListPageNum == 0)
						{
							if(u8SATNum == 0)
							{
								SatListPageNum = 0;
							}
							else
							{
								SatListPageNum = (u8SATNum+7)/8 -1;
							}
						}
						else
						{
							SatListPageNum --;
						}
						MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);
						//printf("\r\n SatListPageNum = %2bx ",SatListPageNum);
						if(SatListPageNum == (u8SATNum+7)/8 - 1)
						{
							u8Pos = u8SATNum - 1;
							//_GetSatInforByID(u8CurrentEditSATId,&SatInfor);
							MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM8 - (8 - u8SATNum%8 )*3+3);
						}
					}
					break;

					default:
						break;
				}
				u8CurrentEditSATId  =  _GetSatIDByPos(u8Pos);
				_GetSatInforByID(u8CurrentEditSATId,&SatInfor);

				MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u8Pos, (MS_U16) u8SATNum);
			}
			else
			{
				u8Pos = _GetSatListPostion();
				u8Pos = u8Pos + TpListPageNum*8-1;

				u16CurrentEditSATTPPos = u8Pos;
				_GetCarrierParam(u16CurrentEditSATTPPos, &CarrierParam);
				switch(MApp_ZUI_API_GetFocus())
				{
					case HWND_MENU_DISHSETUP_SATLIST_ITEM1:
						if(key == VK_UP )
						{
							if(TpListPageNum == 0)
							{
								TpListPageNum = ((_GetCurrentSatTPNum()+7)/8)-1;
							}
							else
							{
								TpListPageNum --;
							}
							MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);
							if(TpListPageNum == (_GetCurrentSatTPNum()+7)/8- 1)
							{
								u16CurrentEditSATTPPos = _GetCurrentSatTPNum() - 1;
								_GetCarrierParam(u16CurrentEditSATTPPos, &CarrierParam);//_GetSatInforByID(u8CurrentEditSATId,&SatInfor);
								printf("\r\n u16CurrentEditSATTPPos = %d",u16CurrentEditSATTPPos);
								MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM8 - (8 - _GetCurrentSatTPNum()%8 )*3+3);
							}
							printf("\r\n u16CurrentEditSATTPPos = %d  __2222",u16CurrentEditSATTPPos);
						}
						break;

					default:
						break;
				}
				MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u16CurrentEditSATTPPos, (MS_U16) _GetCurrentSatTPNum());
			}
			_u8ModifyParam = 1;
			break;
		}

        case VK_DOWN:
        case VK_PAGE_DOWN:
		{
			MS_U8 u8Pos;

			if(u8CurEditListType == TYPE_SATLIST && MApi_DB_SAT_GetSATCount() == 0)
			{
				SatListPageNum = 0;
				eRetval = TRUE;
				break;
			}
			else if(u8CurEditListType == TYPE_TPLIST&& _GetCurrentSatTPNum() == 0)
			{
				TpListPageNum = 0;
				eRetval = TRUE;
				break;
			}
			if(u8CurEditListType == TYPE_SATLIST )
			{
				PreTpFocusWind = HWND_MENU_DISHSETUP_SATLIST_ITEM1;
				TpListPageNum = 0;
				u16CurrentEditSATTPPos = 0;
				u8Pos = _GetSatListPostion();
				u8Pos = u8Pos + SatListPageNum*8+1;


				if(u8Pos >=u8SATNum)
				{
					u8Pos = 0;
				}
				MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_ITEMS);

				printf("\r\n u8SATNum = %2x",u8SATNum);
				printf("\r\n u8CurrentEditSATId = %2x",u8CurrentEditSATId);
				if((SatListPageNum == (u8SATNum+7)/8 -1)&&u8Pos == 0)
				{
					switch(MApp_ZUI_API_GetFocus())
					{
						case HWND_MENU_DISHSETUP_SATLIST_ITEM1:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM2:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM3:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM4:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM5:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM6:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM7:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM8:
							if(key == VK_DOWN )
							{
								if((SatListPageNum == (u8SATNum+7)/8 -1)&&u8Pos == 0 )
									SatListPageNum = 0;
								MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM8);
								MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);

								u8Pos  = 0;
								MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_ITEMS);
							}
							break;
						default:
							break;
					}
				}
				else if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SATLIST_ITEM8)
				{
					if(SatListPageNum == (u8SATNum+7)/8 -1)
						SatListPageNum = 0;
					else
						SatListPageNum ++;
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);
				}
				u8CurrentEditSATId  =  _GetSatIDByPos(u8Pos);
				_GetSatInforByID(u8CurrentEditSATId,&SatInfor);
				MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u8Pos, (MS_U16) u8SATNum);
			}
			else
			{
				u8Pos = _GetSatListPostion();
				u8Pos = u8Pos + TpListPageNum*8+1;
				u16CurrentEditSATTPPos = u8Pos;
				_GetCarrierParam(u16CurrentEditSATTPPos, &CarrierParam);
				if((TpListPageNum == (_GetCurrentSatTPNum()+7)/8-1)&&u16CurrentEditSATTPPos >= _GetCurrentSatTPNum())
				{
					switch(MApp_ZUI_API_GetFocus())
					{
						case HWND_MENU_DISHSETUP_SATLIST_ITEM1:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM2:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM3:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM4:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM5:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM6:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM7:
						case HWND_MENU_DISHSETUP_SATLIST_ITEM8:
							if(key == VK_DOWN )
							{
								if((TpListPageNum == (_GetCurrentSatTPNum()+7)/8-1)&&u16CurrentEditSATTPPos >= _GetCurrentSatTPNum())
									TpListPageNum = 0;
								MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM8);
								MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);

								u16CurrentEditSATTPPos= 0;
								_GetCarrierParam(u16CurrentEditSATTPPos, &CarrierParam);//_GetSatInforByID(u8CurrentEditSATId,&SatInfor);
								MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_ITEMS);
							}
							break;
						default:
							break;
					}
				}
				else if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SATLIST_ITEM8)
				{
					if(TpListPageNum == (_GetCurrentSatTPNum()+7)/8-1)
						TpListPageNum = 0;
					else
						TpListPageNum ++;
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);
				}
				MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u16CurrentEditSATTPPos, (MS_U16) _GetCurrentSatTPNum());
			}
			_u8ModifyParam = 1;
			break;
		}
        case VK_LEFT:
        case VK_RIGHT:
		{
			if(u8CurEditListType == TYPE_SATLIST)
				prefocuswind = MApp_ZUI_API_GetFocus();
			else
				PreTpFocusWind = MApp_ZUI_API_GetFocus();

			if(_bIsValidSAT == FALSE)
			{
				//break;
			}

			if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG))
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST, SW_HIDE);
				break;
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_HIDE);
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LNBTYPE);
			break;
		}

        case VK_SELECT:
		{
			if(_bIsValidSAT == FALSE)
			{
			//break;
			}
			//-------------------------------------------------------
			//confirm delete sat or tp
			if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG))
			{
				bNeedToSaveSatellite = TRUE;
				if(u8CurEditListType == TYPE_TPLIST)
				{
					if(u16CurrentEditSATTPPos >= _GetCurrentSatTPNum()&&u16CurrentEditSATTPPos>0)
					{
						u16CurrentEditSATTPPos --;
					}
					_DeleteTP(u16CurrentEditSATTPPos);
					if(u16CurrentEditSATTPPos>0)
						TpListPageNum=(u16CurrentEditSATTPPos-1)/8;
					else
						TpListPageNum=0;
					printf("\r\nTTTTTpListPageNum=%d,TpListPageNum=%d",u16CurrentEditSATTPPos,TpListPageNum);
					UpdateS2IDInfo();
					if(msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
					{
						msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
					}
					else if(msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
					{
						msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
					}
				#if NORDIG_FUNC //for Nordig Spec v.20
					else if(msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
					{
						msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
					}
				#endif
					else
					{
						msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
					}
					msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
					msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
				#if NORDIG_FUNC //for Nordig Spec v.20
					msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
				#endif
				}
				else
				{
					MS_U8 u8Pos = _GetPosBySatID(u8CurrentEditSATId);
					_DeleteSATByPos(u8Pos);
					u8SATNum = MApi_DB_SAT_GetSATCount();
					if(u8Pos >= u8SATNum)
					{
						u8Pos = u8SATNum -1;
					}
					SatListPageNum=u8Pos/8;
					u8CurrentEditSATId = _GetSatIDByPos(u8Pos);
					if(u8SATNum == 0)
					{
						_bIsValidSAT = FALSE;
					}
					else
					{
						_bIsValidSAT = _GetSatInforByID(u8CurrentEditSATId,&SatInfor);
					}
					if(_bIsValidSAT)
					{
						_matchCurrentServiceTP();
					}
				}
				_Init_satortplist();
				if(_bIsValidSAT)
				{
					_GetCarrierParam(u16CurrentEditSATTPPos,&CarrierParam);
				}
				_u8ModifyParam = 1;
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST,SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_ITEMS,SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_SHOW);
				if(u8CurEditListType == TYPE_TPLIST)
				{
					if( _GetCurrentSatTPNum()==0)
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1);
					else
					{
						if(u16CurrentEditSATTPPos >= _GetCurrentSatTPNum() && u16CurrentEditSATTPPos>0)
							MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1+((u16CurrentEditSATTPPos-1)%8)*3);
						else
							MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1+(u16CurrentEditSATTPPos%8)*3);
					}
					MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u16CurrentEditSATTPPos, (MS_U16) _GetCurrentSatTPNum());
				}
				else if(u8CurEditListType == TYPE_SATLIST)
				{
					if(MApi_DB_SAT_GetSATCount() == 0)
					{
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1);
					}
					else
					{
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1+(_GetPosBySatID(u8CurrentEditSATId)%8)*3);
					}
					MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_SATLIST_VSCROLLBAR, (MS_U16) u8CurrentEditSATId, (MS_U16) u8SATNum);
				}
				if(TRUE != msAPI_CM_ArrangeDataManager(TRUE,FALSE))
				{
				}

				if(msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
				{
					msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
				}
				else if(msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
				{
					msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
				}
			#if NORDIG_FUNC //for Nordig Spec v.20
				else if(msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO) > 0)
				{
					msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
				}
			#endif
				else
				{
					msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
				}
				msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
				msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
			#if NORDIG_FUNC //for Nordig Spec v.20
				msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
			#endif
			}
			else
			{
				if(u8CurEditListType == TYPE_TPLIST)
				{
					MS_U16 u16PCH = MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,u16CurrentEditSATTPPos);
					if( MApi_DFT_IsPCHEntirySelect(u16PCH))
					{
						MApi_DFT_SelectPCHEntity(u16PCH,FALSE);
					}
					else
					{
						MApi_DFT_SelectPCHEntity(u16PCH,TRUE);
					}
				}
				else
				{
					MS_U8 u8satId = (MS_U8) _GetSatIDByPos(_GetSatListPostion()+SatListPageNum*8);
					if( MApi_SAT_IsSatEntirySelect(u8satId))
					{
						MApi_SAT_SelectSATEntity(u8satId,FALSE);
					}
					else
					{
						MApi_SAT_SelectSATEntity(u8satId,TRUE);
					}
				}
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST, SW_SHOW);
			}
			eRetval = bValidateKey = FALSE;
			break;
		}

        case VK_EPG:
		{
			if(u8CurEditListType == TYPE_TPLIST)
			{
				PreTpFocusWind = MApp_ZUI_API_GetFocus();
				u8CurEditListType = TYPE_SATLIST;
			}
			else
			{
				prefocuswind = MApp_ZUI_API_GetFocus();
				u8CurEditListType = TYPE_TPLIST;
				_GetCarrierParam(u16CurrentEditSATTPPos, &CarrierParam);
			}
			_Init_satortplist();
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST, SW_SHOW);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELPBAR_GOTO_TEXT, SW_SHOW);
			if( (u8CurEditListType == TYPE_TPLIST)&&(_GetCurrentSatTPNum() == 0))
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELPBAR_GREEN, SW_HIDE);
			}
			else
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELPBAR_GREEN, SW_SHOW);
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

        case VK_RED:
        case VK_GREEN:
		{
			if(u8CurEditListType == TYPE_TPLIST)
			{
				if((_GetCurrentSatTPNum() == 0) && (key == VK_GREEN))
				{
					eRetval = TRUE;
					break;
				}
			}
			if(u8CurEditListType == TYPE_SATLIST)
			{
				if((MApi_DB_SAT_GetSATCount() == 0) && (key == VK_GREEN))
				{
					eRetval = TRUE;
					break;
				}
			}
			_bAddSATOrTP = (key == VK_RED?TRUE:FALSE);

			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_HIDE);
			if(u8CurEditListType == TYPE_TPLIST)
			{
				PreTpFocusWind = MApp_ZUI_API_GetFocus();
				if(_bAddSATOrTP)
				{
				}

				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_TP_EDIT,SW_SHOW);
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_TP_EDIT_FREQ);
			}
			else
			{
				prefocuswind = MApp_ZUI_API_GetFocus();
				if(_bAddSATOrTP)
				{
					strcpy((char*)SatInfor.aSatName,NEW_SAT_DEFAULTNAME);
					SatInfor.eLNBPwrOnOff = EN_LNBPWR_13OR18V;
					SatInfor.e22KOnOff = EN_22K_AUTO;
					SatInfor.eToneburstType = EN_TONEBURST_NONE;
					SatInfor.eSwt10Port = EN_SWT_PORT_OFF;
					SatInfor.eSwt11Port = EN_SWT_PORT_OFF;
					SatInfor.u8Position = 0;
				}
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT,SW_SHOW);
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_SATELLITENAME);
			}
			break;
		}

        case VK_BLUE:
		{
			prefocuswind = MApp_ZUI_API_GetFocus();
			if(_bIsValidSAT == FALSE)
			{
				break;
			}

			if(u8CurEditListType == TYPE_TPLIST&& _GetCurrentSatTPNum() == 0)
			{
				break;
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_CHANNELSERACH, SW_SHOW);
			S2_enScanType = SCAN_DEFAULT;
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_CHANNELSERACH_MODE);
			eRetval = bValidateKey = TRUE;
			break;
		}

        case VK_YELLOW:
		{
			if((u8CurEditListType == TYPE_SATLIST && MApi_DB_SAT_GetSATCount() != 0)
			||(u8CurEditListType == TYPE_TPLIST&& _GetCurrentSatTPNum() != 0))
			{
				_enMsgTextID = en_str_Delete;
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_HIDE);
				eRetval = TRUE;
			}
			eRetval = TRUE;
			break;
		}

        case VK_EXIT:
		{
			if(MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()) == HWND_MENU_DISHSETUP_SATLIST)
			{
				enDishSetupState = STATE_DISHSETUP_GOTO_MENU;
			}
			if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG))
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_SHOW);
				break;
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

        default:
            eRetval = bValidateKey = TRUE;
            break;
     }
     return eRetval;
}

static BOOLEAN _DishSetup_HandleSatelliteEditKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval = FALSE;

	if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG) && ((key == VK_MENU)||(key == VK_SELECT)))
	{
		MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
		return TRUE;
	}
	switch (key)
	{
		case VK_UP:
		case VK_DOWN:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE:
				{
					u8CurrentDigitalIdx = 0;
					u8CurrentDigitalIdxdot = 0;
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_MASK);
					break;
				}

				default:
					break;
			}
			break;
		}

		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE:
				{
					_MoveNumberWnddot(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_MASK,(key == VK_LEFT)?TRUE:FALSE,MAX_DIGITAL_NUM_DOT);
					break;
				}

				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_SATELLITENAME:
				{
					u8ProgNameCharNum = 0;
					memset(u8ProgName,0,PROGRAMNAME_MAXLENGTH);
					u8ProgNameCharNum = UTL_strlen1(NEW_SAT_DEFAULTNAME);
					strcpy((char*)u8ProgName,NEW_SAT_DEFAULTNAME);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD, SW_SHOW);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_1);
					break;
				}

				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_BOND:
				{
					if(SatInfor.eLNBType == EN_LNBTYPE_C)
					{
						SatInfor.eLNBType = EN_LNBTYPE_KU;
					}
					else
					{
						SatInfor.eLNBType = EN_LNBTYPE_C;
					}
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_BOND_SET);
					break;
				}

				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_DERECT:
				{
					SatInfor.u16Angle = 3600 -SatInfor.u16Angle;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_DERECT_SET);
					break;
				}

				default:
					break;
			}
			eRetval = TRUE;
			break;
		}

		case VK_EXIT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE:
				{
					u8CurrentDigitalIdx = 0;
					u8CurrentDigitalIdxdot = 0;
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_MASK);
					break;
				}
				default:
					break;
			}
			_GetSatInforByID(u8CurrentEditSATId,&SatInfor);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_ITEMS,SW_SHOW);
			_u8ModifyParam = 1;
			_ReturnBackToSatOrTPlist();
			eRetval = TRUE;
			break;
		}

		case VK_SELECT:
		{
			MS_BOOL bExitPage = TRUE;
			if(SatInfor.eLNBType == EN_LNBTYPE_KU)
			{
				SatInfor.u16LoLOF = 9750;
				SatInfor.u16HiLOF = 10600;
			}
			else
			{
				SatInfor.u16LoLOF = SatInfor.u16HiLOF = 5150;
			}

			if(_bAddSATOrTP)
			{
				if(_CheckSameLongitude() == FALSE)
				{
					MS_U8 u8SatID;
					if(_AddSatInfor(&u8SatID) == TRUE)
					{
						u8CurrentEditSATId = u8SatID;
						u8SATNum = MApi_DB_SAT_GetSATCount();
						_u8ModifyParam = 1;
						SatListPageNum = u8CurrentEditSATId/8;

						_bIsValidSAT = TRUE;

						MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);
						printf("\n u8CurrentEditSATId  =  %2x  20100709",u8CurrentEditSATId);
					}
					_bAddSATOrTP = FALSE;
					bExitPage = FALSE;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT, SW_HIDE);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_SHOW);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATLIST_ITEM1+(u8CurrentEditSATId%8)*3);
				}
				else
				{
					_enMsgTextID = en_str_Existed_Longitude;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
				}
			}
			else
			{
				MS_SAT_PARAM enSatInfor;
                            memset(&enSatInfor, 0x00, sizeof(MS_SAT_PARAM)); // fix coverity 207489
				_GetSatInforByID(u8CurrentEditSATId,&enSatInfor);

				if(SatInfor.eLNBType  == enSatInfor.eLNBType && enSatInfor.u16LoLOF>950)
				{
					SatInfor.u16LoLOF = enSatInfor.u16LoLOF;
					SatInfor.u16HiLOF = enSatInfor.u16HiLOF;
				}

				if(enSatInfor.u16Angle == SatInfor.u16Angle&&enSatInfor.eLNBType == SatInfor.eLNBType)
				{
					_SaveSatInfor(u8CurrentEditSATId);
				}
				else if(_CheckSameLongitude() == FALSE)
				{
					_SaveSatInfor(u8CurrentEditSATId);
				}
				else
				{
					bExitPage = FALSE;
					_enMsgTextID = en_str_Existed_Longitude;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
				}
			}
			if(bExitPage)
			{
				MApp_ZUI_ProcessKey(KEY_EXIT);
			}
			eRetval = TRUE;
			break;
		}

		case VK_NUM_0:
		case VK_NUM_1:
		case VK_NUM_2:
		case VK_NUM_3:
		case VK_NUM_4:
		case VK_NUM_5:
		case VK_NUM_6:
		case VK_NUM_7:
		case VK_NUM_8:
		case VK_NUM_9:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE:
				{
					MS_U8 u8West = 0;
					if(SatInfor.u16Angle >1800)
					{
						u8West = 1;
						SatInfor.u16Angle = 3600 - SatInfor.u16Angle;
					}
					SatInfor.u16Angle =_ModifyValuedot(SatInfor.u16Angle,(key - VK_NUM_0),MAX_DIGITAL_NUM_DOT);
					if(u8West)
					{
						SatInfor.u16Angle = 3600 - SatInfor.u16Angle;
					}
					_MoveNumberWnddot(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_MASK,FALSE,MAX_DIGITAL_NUM_DOT);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_SET, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_MASK, SW_SHOW);
					break;
				}

				default:
				{
					break;
				}
			}
			eRetval = TRUE;
			break;
		}

		default:
			return FALSE;
			break;
	}
	return eRetval;
}

static BOOLEAN _DishSetup_HandleTPEditKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval = FALSE;

	if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG))
	{
		MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_HIDE);
		return TRUE;
	}
	switch (key)
	{
		case VK_UP:
		case VK_DOWN:
		switch(MApp_ZUI_API_GetFocus())
		{
			case HWND_MENU_DISHSETUP_TP_EDIT_FREQ:
			case HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE:
			{
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_TP_EDIT_FREQ)
					_ShowNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_FREQ_MASK);
				else
					_ShowNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_MASK);
				break;
			}

			default:
				break;
		}
		break;

		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_TP_EDIT_FREQ:
				{
					_MoveNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_FREQ_MASK,(key == VK_LEFT)?TRUE:FALSE,MAX_DIGITAL_NUM);
					break;
				}

				case HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE:
				{
					_MoveNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_MASK,(key == VK_LEFT)?TRUE:FALSE,MAX_DIGITAL_NUM);
					break;
				}

				case HWND_MENU_DISHSETUP_TP_EDIT_POLARITY:
				{
					CarrierParam.u8Polarity = !CarrierParam.u8Polarity;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_TP_EDIT_POLARITY_OPTION);
					break;
				}

				default:
					break;
			}
			eRetval = TRUE;
			break;
		}

		case VK_EXIT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_TP_EDIT_FREQ:
				case HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE:
				{
					u8CurrentDigitalIdx = 0;
					u8CurrentDigitalIdxdot = 0;
					if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_TP_EDIT_FREQ)
						_ShowNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_FREQ_MASK);
					else
						_ShowNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_MASK);
					break;
				}

				default:
					break;
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_TP_EDIT,SW_HIDE);
			_u8ModifyParam = 1;
			_ReturnBackToSatOrTPlist();
			eRetval = TRUE;
			break;
		}

		case VK_SELECT:
		{
			MS_BOOL bExitPage = TRUE;
			if(_bAddSATOrTP)
			{
				MS_U16 u16AddIdx;
				CarrierParam.SatelliteId= u8CurrentEditSATId;
				MApi_DB_DFT_CheckIfAnySamePCH(&u16AddIdx,&CarrierParam);
				if(u16AddIdx == INVALID_PCHINDEX)
				{
					if(_AddCarrierParam(&u16AddIdx,&CarrierParam))
					{
						u16CurrentEditSATTPPos = u16AddIdx;
						_Init_satortplist();
						UpdateS2IDInfo();
					}
					else
					{
						bExitPage = FALSE;
						_enMsgTextID = en_str_Fail;
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
						break;
					}
				}
				else
				{
					bExitPage = FALSE;
					_enMsgTextID = en_str_Existed_TransPonder;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}
				_bAddSATOrTP = FALSE;
			}
			else
			{
				MS_U16 u16AddIdx;
				MApi_DB_DFT_CheckIfAnySamePCH(&u16AddIdx,&CarrierParam);
				MS_U16 u16TPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(u8CurrentEditSATId,u16CurrentEditSATTPPos);
				if(u16AddIdx != INVALID_PCHINDEX&&u16AddIdx != u16TPIdx)
				{
					bExitPage = FALSE;
					_enMsgTextID = en_str_Existed_TransPonder;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}
				else
				{
					_SaveCarrierParam(u16CurrentEditSATTPPos,&CarrierParam);
					UpdateS2IDInfo();
				}
			}

			if(bExitPage)
			{
				bNeedToSaveSatellite = TRUE;
				MApp_ZUI_ProcessKey(KEY_EXIT);
			}
			eRetval = TRUE;
			break;
		}

		case VK_NUM_0:
		case VK_NUM_1:
		case VK_NUM_2:
		case VK_NUM_3:
		case VK_NUM_4:
		case VK_NUM_5:
		case VK_NUM_6:
		case VK_NUM_7:
		case VK_NUM_8:
		case VK_NUM_9:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_TP_EDIT_FREQ:
				{
					CarrierParam.u32S2Frequency=_ModifyValue(CarrierParam.u32S2Frequency,(key - VK_NUM_0),MAX_DIGITAL_NUM);
					_MoveNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_FREQ_MASK,FALSE,MAX_DIGITAL_NUM);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_TP_EDIT_FREQ_OPTION);
					break;
				}

				case HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE:
				{
					CarrierParam.u16SymbolRate= _ModifyValue(CarrierParam.u16SymbolRate,(key - VK_NUM_0),MAX_DIGITAL_NUM);
					_MoveNumberWnd(HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_MASK,FALSE,MAX_DIGITAL_NUM);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_OPTION);
					break;
				}

				default:
				{
					break;
				}
			}
			eRetval = TRUE;
			break;
		}
		default:
			return FALSE;
			break;
	}
	return eRetval;
}


static MS_BOOL _DishSetup_HandleSoftkeyboardkey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL  eRetval = FALSE;
	switch(key)
	{
		case VK_EXIT:
		{
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD, SW_HIDE);
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_SATELLITENAME);
			eRetval = TRUE;
			break;
		}

		case VK_SELECT:
		{
			HWND TempFocus = MApp_ZUI_API_GetFocus();
			switch(TempFocus)
			{
				case HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_EXTEND:
				{
					bIsExtendChar = !bIsExtendChar;
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SOFTKEYBOARD);
					break;
				}
				case HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_CAPSON:
				{
					bIsCaptalChar = !bIsCaptalChar;
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SOFTKEYBOARD);
					break;
				}
				case HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_BACKSPACE:
				{
					if(u8ProgNameCharNum >0)
					{
					u8ProgNameCharNum --;
					u8ProgName[u8ProgNameCharNum] = 0;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD_TITLE_M);
					}
					break;
				}
				case HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_OK:
					if(_bAddSATOrTP )
					{
						u8CurrentEditSATId = u8SATNum + 1;
					}
					strcpy((char*)SatInfor.aSatName , (char*)u8ProgName);
					MApi_DB_SAT_UpdateSAT(u8CurrentEditSATId, &SatInfor);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD, SW_HIDE);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_SATELLITENAME_SET);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_SATELLITENAME);
					break;

				default:
					break;
			}
			if(TempFocus >= HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_1 && TempFocus <= HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_40)
			{
				if(u8ProgNameCharNum < PROGRAMNAME_MAXLENGTH-1)
				{
					u8ProgName[u8ProgNameCharNum]=_softkeyboard_dispchar(TempFocus);
					u8ProgNameCharNum ++;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD_TITLE_M);
				}
			}
			else if(TempFocus == HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_CANCEL)
			{
				if(u8ProgNameCharNum < PROGRAMNAME_MAXLENGTH-1)
				{
					u8ProgName[u8ProgNameCharNum]=0x20;
					u8ProgNameCharNum ++;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SOFTKEYBOARD_TITLE_M);
				}
			}
			eRetval = TRUE;
			break;
		}
		default:
		eRetval = FALSE;
		break;
	}
	return eRetval;
}

static MS_U8 _GetLofTypePos(void)
{
    MS_U8 Pos = 0;
    switch(MApp_ZUI_API_GetFocus())
	{
	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM1:
			Pos = 0;
			break;

	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM2:
			Pos = 1;
			break;

	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM3:
			Pos = 2;
			break;

	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM4:
			Pos = 3;
			break;

	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM5:
			Pos = 4;
			break;

	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM6:
			Pos = 5;
			break;

	    case HWND_MENU_DISHSETUP_LOFLIST_ITEM7:
			Pos = 6;
			break;
	}
	return Pos;
}

static BOOLEAN _DishSetup_HandleSetLOFKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval         = FALSE;
	MS_BOOL bValidateKey    = FALSE;
	MS_U8 LofTypeId;

	LofTypeId = _GetLofTypePos()+LofListPageNum*7;

	switch(key)
	{
		case VK_UP:
		case VK_DOWN:
		{
	#if(SUPPORT_UNICABLE)
		switch(MApp_ZUI_API_GetFocus())
		{
			case HWND_MENU_DISHSETUP_SETLOF_LLOF:
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(key== VK_UP)
				{
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETHLOF_CHANNEL);
					eRetval = bValidateKey = TRUE;
					break;
				}
				else
				{
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK);
					break;
				}
			case HWND_MENU_DISHSETUP_SETLOF_HLOF:
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(key== VK_UP)
				{
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK);
					break;
				}
				else
				{
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETHLOF_CHANNEL);
					eRetval = bValidateKey = TRUE;
					break;
				}
			case HWND_MENU_DISHSETUP_SETHLOF_CHANNEL:
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(key== VK_UP)
				{
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK);
					break;
				}
				else
				{
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETHLOF_FREQ_MASK);
					break;
				}
			/*case HWND_MENU_DISHSETUP_SETHLOF_FREQ:
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(key== VK_UP)
				{
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETHLOF_CHANNEL);
					break;
				}
				else
				{
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK);
					break;
				}*/

			default:
				break;
		}
	#else
		switch(MApp_ZUI_API_GetFocus())
		{
			case HWND_MENU_DISHSETUP_SETLOF_LLOF:
			case HWND_MENU_DISHSETUP_SETLOF_HLOF:
			{
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOF_LLOF)
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK);
				else
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK);
				break;
			}
			default:
				break;
		}
		break;
#endif
		}
		break;
		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLOF_LLOF:
				{
					_MoveNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK,key == VK_LEFT?TRUE:FALSE,MAX_DIGITAL_NUM);
					break;
				}

				case HWND_MENU_DISHSETUP_SETLOF_HLOF:
				{
					_MoveNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK,key == VK_LEFT?TRUE:FALSE,MAX_DIGITAL_NUM);
					break;
				}
			#if(SUPPORT_UNICABLE)
				case HWND_MENU_DISHSETUP_SETHLOF_FREQ:
				{
					_MoveNumberWnd(HWND_MENU_DISHSETUP_SETHLOF_FREQ_MASK,key == VK_LEFT?TRUE:FALSE,MAX_DIGITAL_NUM);
					break;
				}
				case HWND_MENU_DISHSETUP_SETHLOF_CHANNEL:
				{
					if(key ==VK_LEFT)
					{
						SatInfor.u8ChannelId = ((SatInfor.u8ChannelId-1)==0)?7:(SatInfor.u8ChannelId-1);
					}
					else
					{
						SatInfor.u8ChannelId = (SatInfor.u8ChannelId+1)%8;
					}
					SatInfor.u16IFreq = u16UnicableIFeq[SatInfor.u8ChannelId];
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETHLOF_CHANNEL_VALUE);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETHLOF_FREQ_VALUE);
					break;
				}
			#endif
				default:
					break;
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

		case VK_NUM_0:
		case VK_NUM_1:
		case VK_NUM_2:
		case VK_NUM_3:
		case VK_NUM_4:
		case VK_NUM_5:
		case VK_NUM_6:
		case VK_NUM_7:
		case VK_NUM_8:
		case VK_NUM_9:
		{

			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLOF_LLOF:
				{
					stLOF[u8CurLofInListIdx].u16LLOF =_ModifyValue(stLOF[u8CurLofInListIdx].u16LLOF ,(key - VK_NUM_0),MAX_DIGITAL_NUM);
					_MoveNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK,FALSE,MAX_DIGITAL_NUM);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETLOF_LLOF_VALUE);
					break;
				}

				case HWND_MENU_DISHSETUP_SETLOF_HLOF:
				{
					stLOF[u8CurLofInListIdx].u16HLOF = _ModifyValue(stLOF[u8CurLofInListIdx].u16HLOF,(key - VK_NUM_0),MAX_DIGITAL_NUM);
					_MoveNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK,FALSE,MAX_DIGITAL_NUM);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETLOF_HLOF_VALUE);
					break;
				}

			#if(SUPPORT_UNICABLE)
				/*case HWND_MENU_DISHSETUP_SETHLOF_FREQ:
				{
				stUnicable[SatInfor.u8ChannelId].u16UnicableIFFreq = _ModifyValue(stUnicable[SatInfor.u8ChannelId].u16UnicableIFFreq,(key - VK_NUM_0),MAX_DIGITAL_NUM);
				_MoveNumberWnd(HWND_MENU_DISHSETUP_SETHLOF_FREQ_MASK,FALSE,MAX_DIGITAL_NUM);
				MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETHLOF_FREQ_VALUE);
				break;
				}*/
			#endif
				default:
				{
					break;
				}
			}
			bValidateKey = eRetval = TRUE;
			break;
		}

		case VK_SELECT:
		{
			{
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOF_LLOF)
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK);
				else if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOF_HLOF)
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK);
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF, SW_HIDE);
			if(u8CurLofInListIdx == USER_SIGNLE_IDX)
				stLOF[u8CurLofInListIdx].u16HLOF =  stLOF[u8CurLofInListIdx].u16LLOF;

		#if(SUPPORT_UNICABLE)
			if(u8CurLofInListIdx == USER_DEFINE_UNICABLE)
				SatInfor.eLNBType = EN_LNBTYPE_UNICABLE;
			else if(stLOF[u8CurLofInListIdx].u8LOFNum ==2)
				SatInfor.eLNBType = EN_LNBTYPE_2LOF;
		#else
			if(stLOF[u8CurLofInListIdx].u8LOFNum ==2)
				SatInfor.eLNBType = EN_LNBTYPE_2LOF;
		#endif

			SatInfor.u16LoLOF = stLOF[u8CurLofInListIdx].u16LLOF;
			SatInfor.u16HiLOF = stLOF[u8CurLofInListIdx].u16HLOF;
			_u8ModifyParam = 1;
			MApp_ZUI_ProcessKey(KEY_EXIT);
			eRetval = bValidateKey = TRUE;
			break;
		}

		case VK_EXIT:
		{
			{
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOF_LLOF)
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_LLOF_MASK);
				else if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOF_HLOF)
					_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOF_HLOF_MASK);
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_LOFLIST, SW_SHOW);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF, SW_HIDE);
			if (u8CurLofInListIdx == 9)
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM3);
			else if(u8CurLofInListIdx == 10)
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM4);
			else
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM5);
			eRetval = bValidateKey = TRUE;
			break;
		}

		default:
			eRetval = bValidateKey = TRUE;
			break;
	}
	return eRetval;
}

static BOOLEAN _DishSetup_HandleLOFListKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval         = FALSE;
	MS_BOOL bValidateKey    = FALSE;

	switch(key)
	{
		case VK_UP:
		case VK_DOWN:
		{
			MS_U8 LofTypeId = 0;

			LofTypeId = _GetLofTypePos()+LofListPageNum*7;
			if(VK_LEFT == key)
				key = VK_PAGE_UP;
			else if(VK_RIGHT == key)
				key = VK_PAGE_DOWN;

			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_LOFLIST_ITEM1:
				if(key == VK_UP )
				{
					if(LofListPageNum== 0)
						LofListPageNum = 1;
					else
						LofListPageNum --;
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_LOFLIST);
					if(LofListPageNum == 1)
					{
				#if(SUPPORT_UNICABLE)
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM6);
				#else
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM5);
				#endif
					}
					else
					{
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM1);
					}
				}
				break;
				case HWND_MENU_DISHSETUP_LOFLIST_ITEM7:
				if(key == VK_DOWN )
				{
					if(LofListPageNum == 1)
					LofListPageNum = 0;
					else
					LofListPageNum ++;
					printf("\r\n VK_DOWN FORM ITEM 7");
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_LOFLIST);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM7);
				}
				break;
			#if(SUPPORT_UNICABLE)
				case HWND_MENU_DISHSETUP_LOFLIST_ITEM5:
			#else
				case HWND_MENU_DISHSETUP_LOFLIST_ITEM4:
			#endif
				if(key == VK_DOWN &&(LofListPageNum == 1))
				{
					LofListPageNum = 0;
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_LOFLIST);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM7);
				}
				break;
				default:
					break;
			}
		#if(SUPPORT_UNICABLE)
			if(key == VK_DOWN)
			{
				if(u8CurLofInListIdx<11)
					u8CurLofInListIdx =LofTypeId+1;
				else
					u8CurLofInListIdx = 0;
			}
			else
			{
				if(u8CurLofInListIdx > 0)
					u8CurLofInListIdx = LofTypeId-1;
				else
					u8CurLofInListIdx = 11;
			}
			printf("\r\n u8CurLofInListIdx = %d",u8CurLofInListIdx);
			MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_LOFLIST_VSCROLLBAR, (MS_U16) u8CurLofInListIdx, 12);
		#else
			if(key == VK_DOWN)
			{
				if(u8CurLofInListIdx<10)
					u8CurLofInListIdx =LofTypeId+1;
				else
					u8CurLofInListIdx = 0;
			}
			else
			{
				if(u8CurLofInListIdx > 0)
					u8CurLofInListIdx = LofTypeId-1;
				else
					u8CurLofInListIdx = 10;
			}
			printf("\r\n u8CurLofInListIdx = %d",u8CurLofInListIdx);
			MApp_ZUI_ACT_SliderbarWinPro(HWND_MENU_DISHSETUP_LOFLIST_VSCROLLBAR, (MS_U16) u8CurLofInListIdx, 11);
		#endif
			break;
		}

		case VK_SELECT:
		{
			if(!MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SETLOF)
			&&(u8CurLofInListIdx == USER_SIGNLE_IDX|| u8CurLofInListIdx == USER_DUAL_IDX))
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF, SW_SHOW);
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETLOF_LLOF);
				if(u8CurLofInListIdx == USER_SIGNLE_IDX)
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF_HLOF, SW_HIDE);
				}
				else
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF_HLOF, SW_SHOW);
				}
			#if(SUPPORT_UNICABLE)
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETHLOF_CHANNEL, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETHLOF_FREQ, SW_HIDE);
			#endif
			}
		#if(SUPPORT_UNICABLE)
			else if(!MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SETLOF)
			&&(u8CurLofInListIdx == USER_DEFINE_UNICABLE))
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF, SW_SHOW);
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETLOF_LLOF);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF_HLOF, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETHLOF_CHANNEL, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETHLOF_FREQ, SW_SHOW);
			}
			else if(u8CurLofInListIdx == USER_DEFINE_UNICABLE)
			{
				SatInfor.eLNBType = EN_LNBTYPE_UNICABLE;
				SatInfor.u16HiLOF = stLOF[u8CurLofInListIdx].u16HLOF;
				SatInfor.u16LoLOF = stLOF[u8CurLofInListIdx].u16LLOF;
			}
		#endif
			else
			{
				if(stLOF[u8CurLofInListIdx].u8LOFNum == 2)
				{
					SatInfor.eLNBType = EN_LNBTYPE_2LOF;
					SatInfor.u16HiLOF = stLOF[u8CurLofInListIdx].u16HLOF;
					SatInfor.u16LoLOF = stLOF[u8CurLofInListIdx].u16LLOF;
				}
				else
				{
					SatInfor.u16HiLOF = stLOF[u8CurLofInListIdx].u16HLOF;
					SatInfor.u16LoLOF = stLOF[u8CurLofInListIdx].u16LLOF;
				}
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_LOFLIST, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_SHOW);
				MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_LNBTYPE_OPTION);
				MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LNBTYPE);
			}
			break;
		}

		case VK_EXIT:
		{
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_LOFLIST, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_SHOW);
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LNBTYPE);
			break;
		}
		default:
			eRetval = bValidateKey = TRUE;
			break;
	}
     return eRetval;
}

static BOOLEAN _DishSetup_HandleSetLocationKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval         = FALSE;
	MS_BOOL bValidateKey    = FALSE;

	switch(key)
	{
		case VK_UP:
		case VK_DOWN:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLOCATION_LOCATION:
				{
					if(_u8pLocation != 0)
					return TRUE;
					break;
				}

				case HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE:
				case HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE:
				{
					{
						u8CurrentDigitalIdx = 0;
						u8CurrentDigitalIdxdot = 0;
						if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE)
							_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_MASK);
						else
							_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_MASK);
					}
					break;
				}
				default:
					break;
			}
			break;
		}

		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLOCATION_LATITUDEDIRECTION:
				{
					_bLatitudeMinus = _bLatitudeMinus?FALSE:TRUE;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_LATITUDEDIRECTION_SET, SW_SHOW);
					break;
				}

				case HWND_MENU_DISHSETUP_SETLOCATION_LONGITUDEDIRECTION:
				{
					_bLongitudeMinus = _bLongitudeMinus?FALSE:TRUE;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_LONGITUDEDIRECTION_SET, SW_SHOW);
					break;
				}

				case HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE:
				{
					_MoveNumberWnddot(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_MASK,(key == VK_LEFT)?TRUE:FALSE,MAX_DIGITAL_NUM_DOT);
					break;
				}
				case HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE:
				{
					_MoveNumberWnddot(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_MASK,(key == VK_LEFT)?TRUE:FALSE,MAX_DIGITAL_NUM_DOT);
					break;
				}

				case HWND_MENU_DISHSETUP_SETLOCATION_LOCATION:
				{
					if(_u8pLocation >= LOCATION_NUM)
						_u8pLocation=0;
					if(key ==VK_LEFT)
					{
						_u8pLocation += (LOCATION_NUM-1);
					}
					else
					{
						_u8pLocation++;
					}
					_u8pLocation %= LOCATION_NUM;
					if(_u8pLocation == 0)
					{
						if(SetSATLocation[_u8pLocation].MyLongitude>=0)
							_bLongitudeMinus = FALSE;
						else
							_bLongitudeMinus = TRUE;
						if(SetSATLocation[_u8pLocation].MyLatitude>=0)
							_bLatitudeMinus= FALSE;
						else
							_bLatitudeMinus= TRUE;
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE, TRUE);
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE, TRUE);
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_LATITUDEDIRECTION, TRUE);
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_LONGITUDEDIRECTION, TRUE);
					}
					else
					{
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE, FALSE);
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE, FALSE);
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_LATITUDEDIRECTION, FALSE);
						MApp_ZUI_API_EnableWindow(HWND_MENU_DISHSETUP_SETLOCATION_LONGITUDEDIRECTION, FALSE);
					}
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_LOCATION_SET, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_SET, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_SET, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_LATITUDEDIRECTION_SET, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION_LONGITUDEDIRECTION_SET, SW_SHOW);
					break;
				}

				default:
					break;
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

		case VK_NUM_0:
		case VK_NUM_1:
		case VK_NUM_2:
		case VK_NUM_3:
		case VK_NUM_4:
		case VK_NUM_5:
		case VK_NUM_6:
		case VK_NUM_7:
		case VK_NUM_8:
		case VK_NUM_9:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE:
				{
					if(SetSATLocation[0].MyLongitude<0)
					{
						int n;
						n = (-1)*SetSATLocation[0].MyLongitude;
						n =_ModifyValuedot((MS_U32)n,(key - VK_NUM_0),MAX_DIGITAL_NUM_DOT);
						SetSATLocation[0].MyLongitude = (-1)*n;
					}
					else
					{
						SetSATLocation[0].MyLongitude =_ModifyValuedot((MS_U32)SetSATLocation[0].MyLongitude,(key - VK_NUM_0),MAX_DIGITAL_NUM_DOT);
					}
					_MoveNumberWnddot(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_MASK,FALSE,MAX_DIGITAL_NUM_DOT);
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_SET);
					break;
				}
				case HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE:
				{
					if(SetSATLocation[0].MyLatitude<0)
					{
						int n;
						n = (-1)*SetSATLocation[0].MyLatitude;
						n =_ModifyValuedot((MS_U32)n,(key - VK_NUM_0),MAX_DIGITAL_NUM_DOT);
						SetSATLocation[0].MyLatitude = (-1)*n;
					}
					else
					{
						SetSATLocation[0].MyLatitude =_ModifyValuedot((MS_U32)SetSATLocation[0].MyLatitude,(key - VK_NUM_0),MAX_DIGITAL_NUM_DOT);
					}
					_MoveNumberWnddot(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_MASK,FALSE,MAX_DIGITAL_NUM_DOT);
					MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_SET);
					break;
				}
				default:
					break;
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

		case VK_SELECT:
		case VK_EXIT:
		case VK_MENU:
		{
			if(key == VK_SELECT)
			{
				if(_u8pLocation!=0)
				{
					stGenSetting.stDvbsSetting.u8Location = _u8pLocation;
					stGenSetting.stDvbsSetting.stManualLocation.MyLatitude = SetSATLocation[_u8pLocation].MyLatitude;
					stGenSetting.stDvbsSetting.stManualLocation.MyLongitude = SetSATLocation[_u8pLocation].MyLongitude;
				}
				else
				{
					SetSATLocation[_u8pLocation].MyLatitude = abs(SetSATLocation[_u8pLocation].MyLatitude);
					SetSATLocation[_u8pLocation].MyLongitude = abs(SetSATLocation[_u8pLocation].MyLongitude);
					stGenSetting.stDvbsSetting.stManualLocation.MyLatitude = SetSATLocation[_u8pLocation].MyLatitude;
					stGenSetting.stDvbsSetting.stManualLocation.MyLongitude = SetSATLocation[_u8pLocation].MyLongitude;
					if(_bLatitudeMinus)
					{
						stGenSetting.stDvbsSetting.stManualLocation.MyLatitude = stGenSetting.stDvbsSetting.stManualLocation.MyLatitude*(-1);
						SetSATLocation[_u8pLocation].MyLatitude = SetSATLocation[_u8pLocation].MyLatitude*(-1);
					}
					if(_bLongitudeMinus)
					{
						stGenSetting.stDvbsSetting.stManualLocation.MyLongitude = stGenSetting.stDvbsSetting.stManualLocation.MyLongitude*(-1);
						SetSATLocation[_u8pLocation].MyLongitude = SetSATLocation[_u8pLocation].MyLongitude*(-1);
					}
					stGenSetting.stDvbsSetting.u8Location = _u8pLocation;
				}
				//MApp_DB_SaveGenSetting();
			}
			else
			{
				_u8pLocation = stGenSetting.stDvbsSetting.u8Location;
				SetSATLocation[0].MyLongitude = stGenSetting.stDvbsSetting.stManualLocation.MyLongitude;
				SetSATLocation[0].MyLatitude = stGenSetting.stDvbsSetting.stManualLocation.MyLatitude ;
			}
			{
				u8CurrentDigitalIdx = 0;
				u8CurrentDigitalIdxdot = 0;
				if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE)
				_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_MASK);
				else if(MApp_ZUI_API_GetFocus()==HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE)
				_ShowNumberWnd(HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_MASK);
				//_ResetMaskWnd(MApp_ZUI_API_GetFocus());
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION, SW_HIDE);
			if(SatInfor.u8Position > 0)
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_EXIT, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_OK, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_SHOW);
				if(!IsUSALS(SatInfor))
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR_GREEN, SW_HIDE);
				}
			}
			else
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_HIDE);
			}

			MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SATLIST);
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_MOTOR);
			eRetval = bValidateKey = TRUE;
			break;
		}

		default:
			eRetval = bValidateKey = TRUE;
			break;
	}
	return eRetval;
}

static BOOLEAN _DishSetup_HandleSetLimitOrPositionKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval         = FALSE;
	MS_BOOL bValidateKey    = FALSE;

	if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_MSG))
	{
	return _handlekey_setlimit(key);
	}
	_enMsgTextID = USER_DEFINE_STRING;
	switch(key)
	{
		case VK_UP:
		case VK_DOWN:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE:
				case HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP:
				case HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO:
				case HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE:
				case HWND_MENU_DISHSETUP_SETPOSITION_STEP:
				{
					if(_GetMoveState() != MOVE_STOP)
					{
						_SetMoveState(MOVE_STOP);
					}
					break;
				}

				default:
					break;
			}

			break;
		}

		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE:
				case HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO:
				case HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE:
				{
					if(VK_LEFT == key)
					{
						if(_GetMoveState() == MOVE_EAST)
						{
							_SetMoveState(MOVE_STOP);
						}
						else
						{
							_SetMoveState(MOVE_WEST);
						}
					}
					else
					{
						if(_GetMoveState() == MOVE_WEST)
						{
							_SetMoveState(MOVE_STOP);
						}
						else
						{
							_SetMoveState(MOVE_EAST);
						}
					}
					if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE)
					{
						MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE_SET);
					}
					else if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO)
					{
						MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_OPTION);
					}
					else if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE)
					{
						MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE_OPTION);
					}
					break;
				}

				case HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP:
				case HWND_MENU_DISHSETUP_SETPOSITION_STEP:
				{
					if(VK_LEFT == key)
					{
						if(_GetMoveState() == MOVE_EAST_STEP)
						{
							_SetMoveState(MOVE_STOP);
						}
						else
						{
							_SetMoveState(MOVE_WEST_STEP);
						}
					}
					else
					{
						if(_GetMoveState() == MOVE_WEST_STEP)
						{
							_SetMoveState(MOVE_STOP);
						}
						else
						{
							_SetMoveState(MOVE_EAST_STEP);
						}
					}
					if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP)
					{
						MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP_SET);
					}
					else if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETPOSITION_STEP)
					{
						MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_SETPOSITION_STEP_OPTION);
					}
					break;
				}

				case HWND_MENU_DISHSETUP_SETLIMIT_SETWESTLIMIT:
				{
					_enSetLimtState = SET_WEST_LIMIT;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}
				case HWND_MENU_DISHSETUP_SETLIMIT_SETEASTLIMIT:
				{
					_enSetLimtState = SET_EAST_LIMIT;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}
				case HWND_MENU_DISHSETUP_SETLIMIT_GOTOREF:
				case HWND_MENU_DISHSETUP_SETPOSITION_GOTOREF:
				{
					_enSetLimtState = GOTO_REF;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}
				case HWND_MENU_DISHSETUP_SETLIMIT_DISABLELIMIT:
				{
					_enSetLimtState = DISABLE_LIMIT;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}

				case HWND_MENU_DISHSETUP_SETPOSITION_STORE:
				{
					_enSetLimtState = STORE_POSITON;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}

				case HWND_MENU_DISHSETUP_SETPOSITION_GOTOPOS:
				{
					_enSetLimtState = GOTO_POSITON;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}

				case HWND_MENU_DISHSETUP_SETPOSITION_GOTOX:
				{
					_enSetLimtState = GOTO_X;
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_MSG, SW_SHOW);
					break;
				}

				default:
				break;
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

		case VK_EXIT:
		case VK_MENU:
		{
			if(_GetMoveState() != MOVE_STOP)
			{
				_SetMoveState(MOVE_STOP);
			}
			MApi_DigiTuner_DiSEqC_GoSatPos(SatInfor.u8Position);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION, SW_HIDE);
			if(SatInfor.u8Position > 0)
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_EXIT, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_OK, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_SHOW);
				if(!IsUSALS(SatInfor))
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR_GREEN, SW_HIDE);
				}
			}
			else
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_HIDE);
			}

			MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DISHSETUP_SATLIST);
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_MOTOR);
			eRetval = bValidateKey = TRUE;
			break;
		}

		case VK_NUM_1:
		case VK_NUM_2:
		case VK_NUM_3:
		case VK_NUM_4:
		case VK_NUM_5:
		case VK_NUM_6:
		case VK_NUM_7:
		case VK_NUM_8:
		case VK_NUM_9:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP:
				case HWND_MENU_DISHSETUP_SETPOSITION_STEP:
				{
					_u8MoveSteps = key-VK_NUM_0;
					if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP)
					{
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP_TEXT, SW_SHOW);
					}
					else if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_SETPOSITION_STEP)
					{
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_STEP_TEXT, SW_SHOW);
					}
					break;
				}

				default:
					break;
			}
			eRetval = bValidateKey = TRUE;
			break;
		}

		default:
			eRetval = bValidateKey = TRUE;
			break;
	}

	return eRetval;
}

static BOOLEAN _DishSetup_HandleChannelSearchKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval         = FALSE;

	if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_RESETALLCHANNELS))
	{
		if(key == VK_SELECT)
			;
		else if(key == VK_EXIT)
			;
		else
			return TRUE;
		_GotoChannelSearch();
		return TRUE;
	}
	switch(key)
	{
		case VK_UP:
		case VK_DOWN:
		{
			break;
		}

		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{

            #if(ENABLE_S2_FAST_SCAN)
                case HWND_MENU_DISHSETUP_FAST_SCAN_TEXT:
                {
                    if(VK_RIGHT == key)
                    {
                        S2_FastScan_Type = (S2_FastScan_Type >= EN_SATEPF_SKYLINK_CS_LINK_SLOVAK?EN_SATEPF_CANALDIGITALAL_HD:S2_FastScan_Type + EN_SATEPF_M7_MIN);
                    }
                    else if(VK_LEFT == key)
                    {
                        S2_FastScan_Type = (S2_FastScan_Type <= EN_SATEPF_CANALDIGITALAL_HD?EN_SATEPF_SKYLINK_CS_LINK_SLOVAK:S2_FastScan_Type - EN_SATEPF_M7_MIN);
                    }
                    MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_FAST_SCAN_TEXT);
                    break;
                }
           #endif
				case HWND_MENU_DISHSETUP_CHANNELSERACH_MODE:
				{
					if(u8CurEditListType == TYPE_SATLIST)
					{
						MS_U8 u8Type=S2_enScanType;
						u8Type+=(key == VK_RIGHT?1:SCANTYPE_NUM-1);
						u8Type %= SCANTYPE_NUM;
						S2_enScanType = (SCAN_TYPE)u8Type;
					}
					else
					{
						if(S2_enScanType == SCAN_DEFAULT)
						{
							S2_enScanType = SCAN_NETWORK;
						}
						else
						{
							S2_enScanType = SCAN_DEFAULT;
						}
					}
#if(ASTRA_HD_ENABLE)
                    if(GetASTRA_HD_ENABLE())
                    {
                        if(S2_enScanType == SCAN_ASTRA_FAST)
                        {
                            //printf("MApp_Set_IsNITQuickScan(TRUE)\n");
                            MApp_Set_IsNITQuickScan(TRUE);
                        }
                        else
                        {
                            //Let it be Ture firstly
                            //printf("MApp_Set_IsNITQuickScan(FALSE)\n");
                            MApp_Set_IsNITQuickScan(TRUE);

                        }
                    }
#endif

					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_CHANNELSERACH_MODE_OPTION);
					break;
				}
				case HWND_MENU_DISHSETUP_CHANNELSERACH_PROG:
				{
					MS_U8 u8SaveType= (MS_U8)_eScanProgSaveType;

					u8SaveType += (key == VK_LEFT)?SCAN_SAVETYPE_NUM -1:1;
					u8SaveType %= SCAN_SAVETYPE_NUM;
					_eScanProgSaveType = (SCAN_SAVETYPE)u8SaveType;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_CHANNELSERACH_PROG_OPTION);
					break;
				}

				case HWND_MENU_DISHSETUP_CHANNELSEARCH_SERVICETYPE:
				{
					MS_U8 u8ServiceType= (MS_U8)_eScanServiceType;

					u8ServiceType += (key == VK_LEFT)?SCAN_SERVICETYPE_NUM -1:1;
					u8ServiceType %= SCAN_SERVICETYPE_NUM;
					_eScanServiceType = (SCAN_SERVICETYPE)u8ServiceType;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_CHANNELSEARCH_SERVICETYPE_OPTION);
					break;
				}
			}
			eRetval = TRUE;
			break;
		}

		case VK_MENU:
		case VK_EXIT:
		{
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_CHANNELSERACH, SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_FAST_SCAN, SW_HIDE);
			_ReturnBackToSatOrTPlist();
			eRetval = TRUE;
			break;
		}

		case VK_BLUE:
		case VK_SELECT:
		{
#if(ENABLE_S2_FAST_SCAN)
            if(SCAN_FAST == S2_enScanType && MApp_ZUI_API_GetFocus() != HWND_MENU_DISHSETUP_FAST_SCAN_TEXT)
            {
                MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_FAST_SCAN, SW_SHOW);
                MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_FAST_SCAN_TEXT);
            }
            else if(SCAN_FAST == S2_enScanType && MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_FAST_SCAN_TEXT)
            {
			_GotoChannelSearch();
                msAPI_SI_SetSatePlatform(S2_FastScan_Type);
                MApp_ZUI_ACT_ExecuteDishSetupMenuAction(EN_EXE_DISHSETUP_GOTO_SCAN);
            }
            else
#endif
            {
    			_GotoChannelSearch();
			MApp_ZUI_ACT_ExecuteDishSetupMenuAction(EN_EXE_DISHSETUP_GOTO_SCAN);
			}
			break;
		}

		default:
			eRetval = TRUE;
			break;
	}

	return eRetval;
}
extern MS_BOOL  _DigiTuner_SwitchSatellite(MS_SAT_PARAM stSATParam,MS_U8 u8Polarity,MS_BOOL bflagIsHiLOF);

static BOOLEAN _DishSetup_HandleDishSetupPageKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval         = FALSE;
	MS_BOOL bValidateKey    = FALSE;

	switch(key)
	{
		case VK_UP:
		{
			printf("KEY UP DOWN 20100702\n");
			if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_LNBTYPE&& SatInfor.u8Position > 0)
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_EXIT, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_OK, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_COVER, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_SHOW);
				if(!IsUSALS(SatInfor))
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR_GREEN, SW_HIDE);
				}
			}
			else
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_HIDE);
			}
			break;
		}

		case VK_DOWN:
		{
			if(MApp_ZUI_API_GetFocus() == HWND_MENU_DISHSETUP_DISEQC11&& SatInfor.u8Position > 0)
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_EXIT, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_OK, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_SHOW);
				if(!IsUSALS(SatInfor))
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR_GREEN, SW_HIDE);
				}
			}
			else
			{
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
				MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_HIDE);
			}
			break;
		}
		case VK_LEFT:
		case VK_RIGHT:
		{
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_LNBTYPE:
				{
					MApp_ZUI_ProcessKey(KEY_SELECT);
					break;
				}

				case HWND_MENU_DISHSETUP_LNBPOWER:
				{
					SatInfor.eLNBPwrOnOff = (MS_EN_LNBPWR_ONOFF)MApp_ZUI_ACT_DecIncValue_Cycle(key==VK_RIGHT, SatInfor.eLNBPwrOnOff, EN_LNBPWR_OFF, EN_LNBPWR_18V, 1);
					MApp_MenuChannel_SetLNBPower(SatInfor.eLNBPwrOnOff,CarrierParam.u8Polarity,SatInfor.bPorInvert);
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_LNBPOWER_OPTION);
					break;
				}

				case HWND_MENU_DISHSETUP_22K:
				{
					MS_U8 u8Temp =  SatInfor.e22KOnOff;
					u8Temp += (key==VK_RIGHT?1:(EN_22K_ONOFF_NUM-1));
					u8Temp %= EN_22K_ONOFF_NUM;
					SatInfor.e22KOnOff  = (MS_EN_22K_ONOFF)u8Temp;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_22K_OPTION);

					_DigiTuner_SwitchSatellite(SatInfor,CarrierParam.u8Polarity,FALSE);
					break;
				}

				case HWND_MENU_DISHSETUP_TONEBURST:
				{
					MS_U8 u8Port = SatInfor.eToneburstType;

					u8Port += (key==VK_RIGHT?1:EN_TONEBURST_TYPE_NUM-1);
					u8Port %= EN_TONEBURST_TYPE_NUM;
					SatInfor.eToneburstType = (MS_EN_TONEBURST_TYPE)u8Port;
					_u8ModifyParam = 1;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_TONEBURST_OPTION);
					_DigiTuner_SwitchSatellite(SatInfor,CarrierParam.u8Polarity,FALSE);
					break;
				}

				case HWND_MENU_DISHSETUP_DISEQC10:
				{
					MS_U8 u8Port = SatInfor.eSwt10Port;

					u8Port += (key==VK_RIGHT?1:EN_SWT_DISEQC10_PORT_NUM-1);
					u8Port %= EN_SWT_DISEQC10_PORT_NUM;
					SatInfor.eSwt10Port = (MS_EN_SWT_PORT)u8Port;
					if(EN_SWT_PORT_OFF == u8Port)
					{
						MApi_DigiTuner_DiSEqC_Reset();
						SatInfor.eDiseqcLevel=EN_DISEQC_LVL_OFF;
					}
                    else if(SatInfor.eSwt11Port != EN_SWT_PORT_OFF)
                    {
                        SatInfor.eDiseqcLevel = EN_DISEQC_LVL_MULTI;
                    }
					else
                    {               
						SatInfor.eDiseqcLevel = EN_DISEQC_LVL_10;
                    }

					_u8ModifyParam = 1;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_DISEQC10_OPTION);
					_DigiTuner_SwitchSatellite(SatInfor,CarrierParam.u8Polarity,FALSE);
					break;
				}

				case HWND_MENU_DISHSETUP_DISEQC11:
				{
					MS_U8 u8Port = SatInfor.eSwt11Port;

					u8Port += (key==VK_RIGHT?1:EN_SWT_PORT_NUM-1);
					u8Port %= EN_SWT_DISEQC11_PORT_NUM;
					SatInfor.eSwt11Port = (MS_EN_SWT_PORT)u8Port;
					if(EN_SWT_PORT_OFF == u8Port)
					{
						SatInfor.eDiseqcLevel=EN_DISEQC_LVL_OFF;
						MApi_DigiTuner_DiSEqC_Reset();
					}
                    else if(SatInfor.eSwt10Port != EN_SWT_PORT_OFF)
                    {
                        SatInfor.eDiseqcLevel = EN_DISEQC_LVL_MULTI;
                    }
					else
					{
						SatInfor.eDiseqcLevel=EN_DISEQC_LVL_11;
					}
					_u8ModifyParam = 1;
					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_DISEQC11_OPTION);
					_DigiTuner_SwitchSatellite(SatInfor,CarrierParam.u8Polarity,FALSE);
					break;
				}

				case HWND_MENU_DISHSETUP_MOTOR:
				{
					if(!_bIsValidSAT)
					{
						break;
					}

					if(SatInfor.u8Position == 0)
					{
						SatInfor.u8Position = _GetNextUnusedPosition();
						if(key == VK_LEFT)
						{
							SatInfor.u8Position |= DISEQC_USALS_BIT;
						}
					}
					else if(!IsUSALS(SatInfor))
					{
						SatInfor.u8Position |= DISEQC_USALS_BIT;
						if(key == VK_LEFT)
						{
							SatInfor.u8Position = 0;
						}
					}
					else
					{
						SatInfor.u8Position = 0;
						if(key == VK_LEFT)
						{
							SatInfor.u8Position = _GetNextUnusedPosition();
						}
					}
					if(SatInfor.u8Position==0)
						SatInfor.eDiseqcLevel=EN_DISEQC_LVL_OFF;
					else
						SatInfor.eDiseqcLevel=EN_DISEQC_LVL_12;
					_u8ModifyParam = 1;
					if(SatInfor.u8Position > 0)
					{
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_EXIT, SW_HIDE);
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_OK, SW_HIDE);
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE, SW_HIDE);
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_SHOW);
						if(!IsUSALS(SatInfor))
						{
							MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR_GREEN, SW_HIDE);
						}
					}
					else
					{
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR, SW_SHOW);
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR, SW_HIDE);
					}

					MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_MOTOR_OPTION);
					_SaveSatInfor(u8CurrentEditSATId);

					_DigiTuner_SwitchSatellite(SatInfor,CarrierParam.u8Polarity,FALSE);
					break;
				}

				default:
					break;
			}
			//bValidateKey = eRetval = TRUE;
			break;
		}

		case VK_SELECT:
		{
			printf("key select 20100702\n");
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_LNBTYPE:
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_LOFLIST, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOF, SW_HIDE);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_HIDE);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_LOFLIST_ITEM1);
					_Init_LOFlist();
					break;
				}

				case HWND_MENU_DISHSETUP_MOTOR:
				{
					if(SatInfor.u8Position>0)
					{
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION, SW_SHOW);
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_HIDE);
						MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO);
						if(!IsUSALS(SatInfor))
						{
							MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_GOTOX, SW_HIDE);
						}
					}
					break;
				}

				default:
				break;
			}

			bValidateKey = eRetval = TRUE;
			break;
		}

		case VK_MENU:
		case VK_EXIT:
		{
			if( _CheckCurrentSatChanged())
			{
				bNeedToSaveSatellite = TRUE;
				MApi_DB_SAT_UpdateSAT(u8CurrentEditSATId, &SatInfor);
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
			_ReturnBackToSatOrTPlist();
			bValidateKey = eRetval = TRUE;
			break;
		}

		case VK_RED:
		{
			if(MApp_ZUI_API_GetFocus()== HWND_MENU_DISHSETUP_MOTOR)
			{
				if(SatInfor.u8Position>0)
				{
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_HIDE);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE);
				}
			}
			bValidateKey = eRetval = TRUE;
			break;
		}

		case VK_GREEN:
		{
			if(MApp_ZUI_API_GetFocus()== HWND_MENU_DISHSETUP_MOTOR)
			{
				if(IsUSALS(SatInfor))
				{
					if(_u8pLocation == 0)
					{
						if(SetSATLocation[_u8pLocation].MyLongitude>=0)
						{
							_bLongitudeMinus = FALSE;
						}
						else
						{
							_bLongitudeMinus = TRUE;
						}
						if(SetSATLocation[_u8pLocation].MyLatitude>=0)
						{
							_bLatitudeMinus= FALSE;
						}
						else
						{
							_bLatitudeMinus= TRUE;
						}
					}
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLOCATION, SW_SHOW);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_HELP_BAR_BLUE,SW_HIDE);
					MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_SETLOCATION_LOCATION);
				}
			}
			bValidateKey = eRetval = TRUE;
			break;
		}

		case VK_BLUE:
		{
			if(_bIsValidSAT == FALSE)
			{
				break;
			}
			if( _CheckCurrentSatChanged())
			{
				bNeedToSaveSatellite = TRUE;
				_SaveSatInfor(u8CurrentEditSATId);
			}
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_DISEQC12_HELPBAR, SW_HIDE);
			_ReturnBackToSatOrTPlist();
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SATLIST_HELP_BAR,SW_HIDE);
			MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_CHANNELSERACH, SW_SHOW);
			S2_enScanType = SCAN_DEFAULT;
			MApp_ZUI_API_SetFocus(HWND_MENU_DISHSETUP_CHANNELSERACH_MODE);
			eRetval = bValidateKey = TRUE;
			break;
		}

		default:
		bValidateKey = eRetval = FALSE;
		break;
	}
	return eRetval;
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_HandleDishSetupMenuKey
///  [OSD page handler] global key handler for MENU application
///
///  @param [in]       key VIRTUAL_KEY_CODE      key code
///
///  @return BOOLEAN    true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_HandleDishSetupMenuKey(VIRTUAL_KEY_CODE key)
{
	MS_BOOL eRetval = FALSE;
	switch (key)
	{
		case VK_INPUT_SOURCE:
			MApp_ZUI_ACT_ExecuteDishSetupMenuAction(EN_EXE_SHOW_SOURCE_BANNER);
			eRetval = TRUE;
			break;
		case VK_POWER:
			MApp_ZUI_ACT_ExecuteDishSetupMenuAction(EN_EXE_POWEROFF);
			eRetval = TRUE;
			break;
		default:
		{
			if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_LOFLIST))
			{
				if(MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SETLOF))
				{
					eRetval = _DishSetup_HandleSetLOFKey(key);
				}
				else
				{
					eRetval =  _DishSetup_HandleLOFListKey(key);
				}
			}
			else if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SETLIMIT)
			||MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SETPOSITION))
			{
				eRetval =  _DishSetup_HandleSetLimitOrPositionKey(key);
			}
			else if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SETLOCATION))
			{
				eRetval =  _DishSetup_HandleSetLocationKey(key);
			}
			else if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SATELLITE_EDIT))
			{
				if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SOFTKEYBOARD))
				{
					eRetval =  _DishSetup_HandleSoftkeyboardkey(key);
				}
				else
				{
					eRetval =  _DishSetup_HandleSatelliteEditKey(key);
				}
			}
			else if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_TP_EDIT))
			{
				eRetval =  _DishSetup_HandleTPEditKey(key);
			}
			else if (MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_CHANNELSERACH))
			{
				eRetval =  _DishSetup_HandleChannelSearchKey(key);
			}
			else
			{
				switch(MApp_ZUI_API_GetParent(MApp_ZUI_API_GetFocus()))
				{
					case HWND_MENU_DISHSETUP_ITEMS:
					{
						eRetval =  _DishSetup_HandleDishSetupPageKey(key);
						break;
					}
					default:
					{
						eRetval =  _DishSetup_HandleSatelliteOrTPListKey(key);
						break;
					}
				}
			}
			break;
		}
	}
#if ENABLE_S2_QUALITY_DISPLAY_PERCENT
	if(_CheckCurrentSatChanged()
	&& !MApp_ZUI_API_IsWindowVisible(HWND_MENU_DISHSETUP_SATELLITE_EDIT))
	{
		_SaveSatInfor(u8CurrentEditSATId);
		if(u8CurEditListType == TYPE_SATLIST)
		{
			u16CurrentSatTpIndex = 0;
			u16SatTpDetectCount = 0;
		}
	}
	MApp_ZUI_API_SetTimer(HWND_MENU_DISHSETUP_QULITY, 0, DISHSETUP_SIGNAL_BAR_MONITOR_DURATION);  //for icon flash
#endif
	return eRetval;
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_TerminateDishSetupMenu
///  [OSD page handler] terminate MENU application
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void MApp_ZUI_ACT_TerminateDishSetupMenu(void)
{

}
///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_ExecuteMainMenuAction
///  [OSD page handler] execute a specific action in MENU application
///
///  @param [in]       act U16      action ID
///
///  @return BOOLEAN     true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteDishSetupMenuAction(U16 act)
{
	switch (act)
	{
		case EN_EXE_CLOSE_CURRENT_OSD:
		{
			MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
			break;
		}
		case EN_EXE_SHOW_SOURCE_BANNER:
			MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
			enDishSetupState = STATE_DISHSETUP_GOTO_INPUTSOURCE;
			return TRUE;

		case EN_EXE_DISHSETUP_GOTO_SCAN:
			MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
			enDishSetupState = STATE_DISHSETUP_GOTO_SCAN;
			return TRUE;

		case EN_EXE_EFFECT_SLIDEITEM:
		{
			HWND srchWnd = MApp_ZUI_API_GetFocus();
			MApp_ZUI_API_PostMessage(MApp_ZUI_API_GetFocus(), MSG_EFFECT_SLIDEITEM, srchWnd);
			return TRUE;
		}
		case EN_EXE_POWEROFF:
			MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
			enDishSetupState = STATE_DISHSETUP_GOTO_STANDBY;
			return TRUE;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}

static LPTSTR _DishSetup_softkeyboard_dynamictext(HWND hWnd)
{
	MS_U8 u8Str[2]={0};
	u8Str[0] = _softkeyboard_dispchar(hWnd);
	MApp_ZUI_API_StringBuffU8toU16( CHAR_BUFFER, (MS_U8*)u8Str,UTL_strlen1((char *)u8Str));
	return CHAR_BUFFER;
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetDishSetupMenuDynamicText
///  [OSD page handler] dynamic text content provider in MENU application
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return LPCTSTR     string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetDishSetupMenuDynamicText(HWND hwnd)
{
	MS_U8 nTempIndx = 0;

	if(hwnd >= HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_1 && hwnd <= HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_40)
	{
		return _DishSetup_softkeyboard_dynamictext(hwnd);
	}

	switch (hwnd)
	{
	#if(SUPPORT_UNICABLE)
		case HWND_MENU_DISHSETUP_SETHLOF_CHANNEL_VALUE:
		{
			MS_U8 u8str[2] = "";

			sprintf((char*)u8str, "%d", SatInfor.u8ChannelId);
			MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char *)u8str));
			return CHAR_BUFFER;
			break;
		}
		case HWND_MENU_DISHSETUP_SETHLOF_FREQ_VALUE:
		{
			MS_U8 freq[5] = "";

			SatInfor.u16IFreq = u16UnicableIFeq[SatInfor.u8ChannelId];
			sprintf((char*)freq ,"%04d",SatInfor.u16IFreq);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)freq,UTL_strlen1((char*)freq));
			return u16StringBuff;
			break;
		}
	#endif
		//satellite or tp list ------------------------------------start
		case HWND_MENU_DISHSETUP_SATLIST_TITLE:
		{
			if(u8CurEditListType == TYPE_SATLIST)
			{
				return MApp_ZUI_API_GetString(en_str_Satellite);
			}
			else
			{
				return MApp_ZUI_API_GetString(en_str_TransPonder);
			}
		}

		case HWND_MENU_DISHSETUP_SATLIST_ITEM8_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM7_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM6_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM5_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM4_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM3_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM2_TEXT:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM1_TEXT:
		{
			return _GetSatOrTpListTxt(nTempIndx);
			break;
		}

		case HWND_MENU_DISHSETUP_SATLIST_HELPBAR_GOTO_TEXT:
		{
			if(u8CurEditListType == TYPE_SATLIST)
			{
				return MApp_ZUI_API_GetString(en_str_TransPonder);
			}
			else
			{
				return MApp_ZUI_API_GetString(en_str_Satellite);
			}
			break;
		}

		case HWND_MENU_DISHSETUP_SATELLITE_NAME:
		{
			MS_U8 u8Str[100];

			_GetSatInforByID(u8CurrentEditSATId, &SatInfor);
			MS_U16 u16Angle = SatInfor.u16Angle;
			if(u16Angle > 1800)
			{
				u16Angle = 3600 -u16Angle;
				sprintf((char*)u8Str,"%03d.%dW ",u16Angle/10,u16Angle%10);
			}
			else
			{
				sprintf((char*)u8Str,"%03d.%dE ",u16Angle/10,u16Angle%10);
			}
			if(SatInfor.eLNBType == EN_LNBTYPE_C)
			{
				strcpy((char*)u8Str,(char*)"C_");
			}
			else
			{
				strcpy((char*)u8Str,(char*)"Ku_");
			}
			if(u8CurrentEditSATId == 1)
				strcat((char*)u8Str,"ASTRA 1H,1KR,1L,1M");
			else
				strcat((char*)u8Str,(char*)SatInfor.aSatName);
			MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8Str,UTL_strlen1((char *)u8Str));
			return CHAR_BUFFER;
		}

		case HWND_MENU_DISHSETUP_LNBTYPE_OPTION:
		{
			MS_U8 u8str[20] = "";
		#if(SUPPORT_UNICABLE)
			if(SatInfor.eLNBType == EN_LNBTYPE_UNICABLE)
			{
				strcpy((char*)u8str,(char*)"Unicable");
				MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char *)u8str));
				return CHAR_BUFFER;
				break;
			}
		#endif
			if(SatInfor.u16LoLOF != SatInfor.u16HiLOF)
			{
				sprintf((char*)u8str, "%05d/%05d", SatInfor.u16LoLOF, SatInfor.u16HiLOF);
			}
			else
			{
				sprintf((char*)u8str, "%05d", SatInfor.u16LoLOF);
			}
			MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char *)u8str));
			return CHAR_BUFFER;
			break;
		}

		case HWND_MENU_DISHSETUP_LNBPOWER_OPTION:
		{
			switch(SatInfor.eLNBPwrOnOff)
			{
				case EN_LNBPWR_OFF:
					return MApp_ZUI_API_GetString(en_str_Off);
				case EN_LNBPWR_13OR18V:
					MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8*)"13/18V",UTL_strlen1((char *)"13/18V"));
					return CHAR_BUFFER;
				case EN_LNBPWR_13V:
					MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8*)"13V",UTL_strlen1((char*)"13V"));
					return CHAR_BUFFER;
				case EN_LNBPWR_18V:
					MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8*)"18V",UTL_strlen1((char*)"18V"));
					return CHAR_BUFFER;
				default:
					return MApp_ZUI_API_GetString(en_str_Off);
			}
			break;
		}

		case HWND_MENU_DISHSETUP_22K_OPTION:
		{
			if (SatInfor.e22KOnOff == EN_22K_AUTO)
			{
				return MApp_ZUI_API_GetString(en_str_Auto);
			}
			else if (SatInfor.e22KOnOff == EN_22K_ON)
			{
				return MApp_ZUI_API_GetString(en_str_On);
			}
			else
			{
				return MApp_ZUI_API_GetString(en_str_Off);
			}
			break;
		}

		case HWND_MENU_DISHSETUP_TONEBURST_OPTION:
		{
			MS_U8 u8str[10] = "Burst";

			if(SatInfor.eToneburstType == EN_TONEBURST_0)
			{
				u8str[5]='A';
				u8str[6]='\0';
				MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char *)u8str));
				return CHAR_BUFFER;
			}
			else if(SatInfor.eToneburstType == EN_TONEBURST_1)
			{
				u8str[5]='B';
				u8str[6]='\0';
				MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char *)u8str));
				return CHAR_BUFFER;
			}
			return MApp_ZUI_API_GetString(en_str_None);
			break;
		}

		case HWND_MENU_DISHSETUP_DISEQC10_OPTION:
		{
			MS_U8 u8str[10] = "LNB";
			MS_U8 u8Port = 1;

			if(SatInfor.eSwt10Port != EN_SWT_PORT_OFF)
			{
				u8Port = SatInfor.eSwt10Port - EN_SWT_PORT_OFF;
				sprintf((char*)u8str+UTL_strlen1((char*)u8str), "%d", u8Port);
				MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char *)u8str));
				return CHAR_BUFFER;
			}
			return MApp_ZUI_API_GetString(en_str_None);
			break;
		}

		case HWND_MENU_DISHSETUP_DISEQC11_OPTION:
		{
			MS_U8 u8str[10] = "LNB";
			MS_U8 u8Port = 1;

			if(SatInfor.eSwt11Port != EN_SWT_PORT_OFF)
			{
				u8Port = SatInfor.eSwt11Port - EN_SWT_PORT_OFF;
				sprintf((char*)(u8str+UTL_strlen1((char*)u8str)), "%d", u8Port);
				MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8str,UTL_strlen1((char*)u8str));
				return CHAR_BUFFER;
			}
			return MApp_ZUI_API_GetString(en_str_None);
			break;
		}

		case HWND_MENU_DISHSETUP_MOTOR_OPTION:
		{
			if(!_bIsValidSAT)
			{
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(MS_U8*)"- - - - -",UTL_strlen1((char*)"- - - - -"));
				return u16StringBuff;
			}
			if(SatInfor.u8Position == 0)
			{
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(MS_U8*)"None",UTL_strlen1((char *)"None"));
			}
			else if(IsUSALS(SatInfor))
			{
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(MS_U8*)"DiSEqC1.3",UTL_strlen1((char *)"DiSEqC1.3"));
			}
			else
			{
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(MS_U8*)"DiSEqC1.2",UTL_strlen1((char *)"DiSEqC1.2"));
			}
			return u16StringBuff;
			break;
		}

		//dish set  -----------------------------------------  end
		//satellite edit  -----------------------------------------  start
		case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_NO_SET:
		{
			MS_U8 u8Str[10];

			if(_bAddSATOrTP)
			{
				sprintf((char*)u8Str,"%03d",u8SATNum+1);
			}
			else
			{
				sprintf((char*)u8Str,"%03d",u8CurrentEditSATId+1);
			}
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)u8Str,UTL_strlen1((char *)u8Str));
			return u16StringBuff;

			break;
		}

		case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_SATELLITENAME_SET:
		{
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)SatInfor.aSatName,UTL_strlen1((char *)(SatInfor.aSatName)));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_DERECT_SET:
		{
			if(SatInfor.u16Angle > 1800)
			{
				return MApp_ZUI_API_GetString(en_str_West);
			}
			else
			{
				return MApp_ZUI_API_GetString(en_str_East);
			}
			break;
		}

		case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_LONGITUDE_SET:
		{
			MS_U8 u8Str[10];
			MS_U16 u16Angle = SatInfor.u16Angle;
			if(u16Angle > 1800)
			{
				u16Angle = 3600 -u16Angle;
			}
			sprintf((char*)u8Str,"%03d.%1d",u16Angle/10,u16Angle%10);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)u8Str,UTL_strlen1((char *)u8Str));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SATELLITE_EDIT_ITMES_BOND_SET:
		{
			MS_U8 u8Str[10];
			if(SatInfor.eLNBType ==  EN_LNBTYPE_C)
				sprintf((char*)u8Str,"%s","C");
			else
				sprintf((char*)u8Str,"%s","Ku");
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)u8Str,UTL_strlen1((char *)u8Str));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SATELLITE_EDIT_M:
		case HWND_MENU_DISHSETUP_TP_EDIT_TITLE_M:
		{
			if(_bAddSATOrTP)
			{
				return MApp_ZUI_API_GetString(en_str_Add);
			}
			else
			{
				return MApp_ZUI_API_GetString(en_str_Edit);
			}
			break;
		}

		//satellite edit  -----------------------------------------  end
		//TP edit  -----------------------------------------  start
		case HWND_MENU_DISHSETUP_TP_EDIT_NUMBER_OPTION:
		{
			MS_U8 u8Str[10];
			if(_bAddSATOrTP)
			{
				sprintf((char*)u8Str,"%03d",_GetCurrentSatTPNum()+1);
			}
			else
			{
				sprintf((char*)u8Str,"%03d",u16CurrentEditSATTPPos+1);
			}
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)u8Str,UTL_strlen1((char*)u8Str));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_TP_EDIT_FREQ_OPTION:
		{
			MS_U8 u8Str[10];
			sprintf((char*)u8Str,"%05d",CarrierParam.u32S2Frequency);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)u8Str,UTL_strlen1((char*)u8Str));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_TP_EDIT_SYMBOLRATE_OPTION:
		{
			MS_U8 u8Str[10];
			sprintf((char*)u8Str,"%05d",CarrierParam.u16SymbolRate);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)u8Str,UTL_strlen1((char*)u8Str));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_TP_EDIT_POLARITY_OPTION:
		{
			if(CarrierParam.u8Polarity)
			{
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)"V",UTL_strlen1((char*)"V"));
			}
			else
			{
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)"H",UTL_strlen1((char*)"H"));
			}
			return u16StringBuff;
			break;
		}
		case HWND_MENU_DISHSETUP_MSG_TEXT:
		{
			if(USER_DEFINE_STRING == _enMsgTextID)
			{
				MS_U16 strEnd[5]={' ', '?', 0};

                //MApp_ZUI_API_StringBuffU8toU16(strEnd,(MS_U8*)" ?",UTL_strlen1((char *)(" ?")));
				if(_enSetLimtState == SET_WEST_LIMIT)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Set_West_Limit));
				}
				else if(_enSetLimtState == SET_EAST_LIMIT)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Set_East_Limit));
				}
				else if(_enSetLimtState == GOTO_REF)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Goto_Reference));
				}
				else if(_enSetLimtState == DISABLE_LIMIT)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Disable_Limit));
				}
				else if(_enSetLimtState == GOTO_X)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_GotoX));
				}
				else if(_enSetLimtState == GOTO_POSITON)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Goto_Positon));
				}
				else if(_enSetLimtState == STORE_POSITON)
				{
					UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Store_Positon));
				}
				wcscat1(u16StringBuff, strEnd);
				return u16StringBuff;
			}
			else
			{
				return MApp_ZUI_API_GetString(_enMsgTextID);
			}
			break;
		}
		case HWND_MENU_DISHSETUP_SOFTKEYBOARD_TITLE_M:
		{
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff, (MS_U8*)u8ProgName, UTL_strlen1((char *)u8ProgName));
			return u16StringBuff;
		}

		case HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_EXTEND:
		{
			return MApp_ZUI_API_GetString(bIsExtendChar?en_str_On:en_str_Extend);
		}

		case HWND_MENU_DISHSETUP_SOFTKEYBOARD_KEY_CAPSON:
		{
			return MApp_ZUI_API_GetString(bIsCaptalChar?en_str_Off:en_str_Caps_On);
		}
		case HWND_MENU_DISHSETUP_CHANNELSERACH_MODE_OPTION:
		{
			switch(S2_enScanType)
			{
				default:
				case SCAN_DEFAULT:
					return MApp_ZUI_API_GetString(en_str_Default);
				case SCAN_BLIND:
					return MApp_ZUI_API_GetString(en_str_Blind_Scan);
				case SCAN_NETWORK:
					return MApp_ZUI_API_GetString(en_str_Network);
            #if(ENABLE_S2_FAST_SCAN)
				case SCAN_FAST:
					return MApp_ZUI_API_GetString(en_str_FastScan);
            #endif
			}
			return MApp_ZUI_API_GetString(en_str_Default);
		}

		case HWND_MENU_DISHSETUP_CHANNELSERACH_PROG_OPTION:
		{
			if(_eScanProgSaveType == SCAN_SAVEALL)
			{
				return MApp_ZUI_API_GetString(en_str_All_Channels);
			}
			else
			{
				return MApp_ZUI_API_GetString(en_str_FTA_Channels);
			}
		}

		case HWND_MENU_DISHSETUP_CHANNELSEARCH_SERVICETYPE_OPTION:
		{
			switch(_eScanServiceType)
			{
				default:
				case SCAN_SERVICE_ALL:
					return MApp_ZUI_API_GetString(en_str_All);
				case SCAN_SERVICE_DTV:
					return MApp_ZUI_API_GetString(en_str_DTV);
				case SCAN_SERVICE_RADIO:
					return MApp_ZUI_API_GetString(en_str_Radio);
			}
			return MApp_ZUI_API_GetString(en_str_All);
		}

		case HWND_MENU_DISHSETUP_RESETALLCHANNELS_TEXT:
		{
			return MApp_ZUI_API_GetString(en_str_Delete_all_exist_channels_of_selected_satellites);
		}

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM7_TEXT:
			nTempIndx++;

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM6_TEXT:
			nTempIndx++;

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM5_TEXT:
			nTempIndx++;

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM4_TEXT:
			nTempIndx++;

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM3_TEXT:
			nTempIndx++;

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM2_TEXT:
			nTempIndx++;

		case HWND_MENU_DISHSETUP_LOFLIST_ITEM1_TEXT:
		{
			return _GetLOFListTxt(nTempIndx);
			break;
		}

		case HWND_MENU_DISHSETUP_SETLOF_LLOF_VALUE:
		{
			MS_U8 freq[6] = "";

			sprintf((char*)freq ,"%05d",stLOF[u8CurLofInListIdx].u16LLOF);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)freq,UTL_strlen1((char*)freq));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SETLOF_HLOF_VALUE:
		{
			MS_U8 freq[6] = "";
			sprintf((char*)freq ,"%05d",stLOF[u8CurLofInListIdx].u16HLOF );
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)freq,UTL_strlen1((char*)freq));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SETLOCATION_LOCATION_SET:
		{
			if(_u8pLocation >= LOCATION_NUM)
			{
				_u8pLocation=0;
			}
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,SetSATLocation[_u8pLocation].Location,strlen((char*)(SetSATLocation[_u8pLocation].Location)));
			return u16StringBuff;
			break;
		}
		case HWND_MENU_DISHSETUP_SETLOCATION_LONGITUDEDIRECTION_SET:
		{
			if(_u8pLocation!=0)
			{
				if(SetSATLocation[_u8pLocation].MyLongitude>=0)
					_bLongitudeMinus = FALSE;
				else
					_bLongitudeMinus = TRUE;
			}
			if(!_bLongitudeMinus)
				return MApp_ZUI_API_GetString(en_str_East);
			else
				return MApp_ZUI_API_GetString(en_str_West);
		}

		case HWND_MENU_DISHSETUP_SETLOCATION_LATITUDEDIRECTION_SET:
		{
			if(_u8pLocation!=0)
			{
				if(SetSATLocation[_u8pLocation].MyLatitude>=0)
					_bLatitudeMinus= FALSE;
				else
					_bLatitudeMinus = TRUE;
			}
			if(!_bLatitudeMinus)
				return MApp_ZUI_API_GetString(en_str_North);
			else
				return MApp_ZUI_API_GetString(en_str_South);
		}

		case HWND_MENU_DISHSETUP_SETLOCATION_MYLONGITUDE_SET:
		{
			MS_U8 num[10];
			MS_S16 n;
			if(SetSATLocation[_u8pLocation].MyLongitude>=0)
				n = SetSATLocation[_u8pLocation].MyLongitude;
			else
				n = -1*SetSATLocation[_u8pLocation].MyLongitude;
			sprintf((char*)num,"%03d.%d",n/10,n%10);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,num,strlen((char*)num));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SETLOCATION_MYLATITUDE_SET:
		{
			MS_U8 num[10];
			MS_S16 n;
			if(SetSATLocation[_u8pLocation].MyLatitude>=0)
				n = SetSATLocation[_u8pLocation].MyLatitude;
			else
				n = -1*SetSATLocation[_u8pLocation].MyLatitude;
			sprintf((char*)num,"%03d.%d",n/10,n%10);
			MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,num,strlen((char*)num));
			return u16StringBuff;
			break;
		}

		case HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE_SET:
		case HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP_SET:
		case HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_OPTION:
		case HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE_OPTION:
		case HWND_MENU_DISHSETUP_SETPOSITION_STEP_OPTION:
		{
			if(_s8MoveState == MOVE_STOP)
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8*)"STOP",UTL_strlen1((char *)("STOP")));
			else if(_s8MoveState == MOVE_WEST ||_s8MoveState == MOVE_WEST_STEP)
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)"WEST",UTL_strlen1((char *)("WEST")));
			else if(_s8MoveState == MOVE_EAST ||_s8MoveState == MOVE_EAST_STEP)
				MApp_ZUI_API_StringBuffU8toU16(u16StringBuff,(U8 *)"EAST",UTL_strlen1((char *)("EAST")));
			return u16StringBuff;
		}

		case HWND_MENU_DISHSETUP_SETPOSITION_STEP_TEXT:
		case HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP_TEXT:
		{
			MS_U8 u8Str[10] = {0}; // fix coverity 207485

			printf((char*)u8Str,"(%d)",_u8MoveSteps);
			UTL_wcscpy1(u16StringBuff,MApp_ZUI_API_GetString(en_str_Move_Step));
			MApp_ZUI_API_StringBuffU8toU16(&u16StringBuff[wcslen1(u16StringBuff)],(U8 *)u8Str,UTL_strlen1((char*)u8Str));
			return u16StringBuff;
		}

#if(ENABLE_S2_FAST_SCAN)
        case HWND_MENU_DISHSETUP_FAST_SCAN_TEXT:
        {
            switch(S2_FastScan_Type)
            {
                case EN_SATEPF_CANALDIGITALAL_HD:
                    return MApp_ZUI_API_GetString(en_str_CanalDigitalal_HD);
                case EN_SATEPF_CANALDIGITALAL_SD:
                    return MApp_ZUI_API_GetString(en_str_CanalDigitalal_SD);
                case EN_SATEPF_TV_VLAANDEREN_HD:
                    return MApp_ZUI_API_GetString(en_str_TV_VLAANDEREN_HD);
                case EN_SATEPF_TV_VLAANDEREN_SD :
                    return MApp_ZUI_API_GetString(en_str_TV_VLAANDEREN_SD);
                case EN_SATEPF_TELESAT_BELGIUM:
                    return MApp_ZUI_API_GetString(en_str_Telesat_Belgium);
                case EN_SATEPF_TELESAT_LUXEMBOURG:
                    return MApp_ZUI_API_GetString(en_str_Telesat_Luxembourg);
                case EN_SATEPF_HD_AUSTRIASAT:
                    return MApp_ZUI_API_GetString(en_str_HD_Austriasat);
                case EN_SATEPF_HELLO:
                    return MApp_ZUI_API_GetString(en_str_Hello);
                case EN_SATEPF_SKYLINK_CS_LINK_CZECH:
                    return MApp_ZUI_API_GetString(en_str_Skylink_Czech_Republic);
                case EN_SATEPF_SKYLINK_CS_LINK_SLOVAK:
                    return MApp_ZUI_API_GetString(en_str_Skylink_Slovak_Republic);

                default:
                    return MApp_ZUI_API_GetString(en_str_CanalDigitalal_SD);

            }
            return MApp_ZUI_API_GetString(en_str_CanalDigitalal_SD);
        }
#endif
		default:
		{
			ASSERT(0);
			break;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetDynamicValue_DishSetupMenu
///
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S16 MApp_ZUI_ACT_GetDynamicValue_DishSetupMenu(HWND hwnd)
{
	switch (hwnd)
	{
		case HWND_MENU_DISHSETUP_QULITY_BAR:
			return msAPI_Tuner_GetSignalQualityPercentage();

		default:
		{
			//ASSERT(0);
			return FALSE;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetDishSetupMenuDynamicText
///  [OSD page handler] dynamic text content provider in MENU application
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return LPCTSTR     string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
MS_U16 MApp_ZUI_ACT_GetDishSetupMenuDynamicBmp(HWND hwnd)
{
	MS_U8 nTempIndx = 0;
	switch(hwnd)
	{
		case HWND_MENU_DISHSETUP_SATLIST_ITEM8_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM7_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM6_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM5_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM4_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM3_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM2_SELICON:
			nTempIndx++;
		case HWND_MENU_DISHSETUP_SATLIST_ITEM1_SELICON:
		{
			return _GetSatSel_Bmp(nTempIndx);
		}

		case HWND_MENU_DISHSETUP_SATLIST_HELPBAR_GOTO:
		{
			return E_BMP_BMP_NINE;
		}
		default:
			ASSERT(0);
	}

	return ~0;
}
#endif


EN_RET MApp_DishSetup_Main(void)
{
    EN_RET enRetVal =EXIT_NULL;
    //printf("enDishSetupState =%d",enDishSetupState);
    switch(enDishSetupState)
    {
        case STATE_DISHSETUP_INIT:
        //printf("STATE_DISHSETUP_INIT start\r\n");
            MApp_ZUI_ACT_StartupOSD(E_OSD_MENU_DISHSETUP);
            enDishSetupState = STATE_DISHSETUP_WAIT;
            break;

        case STATE_DISHSETUP_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        case STATE_DISHSETUP_CLEAN_UP:
			MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            MApp_ZUI_ACT_ShutdownOSD();
            enDishSetupState = STATE_DISHSETUP_INIT;
            enRetVal =EXIT_CLOSE;
            break;

        case STATE_DISHSETUP_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal =EXIT_GOTO_STANDBY;
            break;
        case STATE_DISHSETUP_GOTO_INPUTSOURCE:
			MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            MApp_ZUI_ACT_ShutdownOSD();
            enDishSetupState = STATE_DISHSETUP_INIT;
            enRetVal = EXIT_GOTO_INPUTSOURCE;
            break;

        case STATE_DISHSETUP_GOTO_MENU:
			MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            MApp_ZUI_ACT_ShutdownOSD();
            enDishSetupState = STATE_DISHSETUP_INIT;
            enRetVal = EXIT_GOTO_MENU;
            break;

        case STATE_DISHSETUP_GOTO_SCAN:
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_ZUI_ACT_StartupOSD(E_OSD_AUTO_TUNING);
            enDishSetupState = STATE_DISHSETUP_INIT;
            enRetVal = EXIT_GOTO_DTVSCAN;
            break;
		default:
            enDishSetupState = STATE_DISHSETUP_WAIT;
            break;
    }
    return enRetVal;
}
#endif
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryDishItemStatus(HWND hwnd)
{
	switch(hwnd)
	{
		default:
		return EN_DL_STATE_NORMAL;
	}
	return EN_DL_STATE_NORMAL;
}

SCAN_SERVICETYPE MApp_GetScanServiceType(void)
{
	return _eScanServiceType;
}
SCAN_SAVETYPE MApp_GetScanCryptedType(void)
{
	return _eScanProgSaveType;
}

static void vDispSignalQuality(void)
{
	MS_SAT_PARAM TempSatInfor;
	DTVPROGRAMID_M TempTp;

    memset(&TempSatInfor, 0x00, sizeof(MS_SAT_PARAM)); // fix coverity 207492
    memset(&TempTp, 0x00, sizeof(DTVPROGRAMID_M)); // fix coverity 207493

	{
		if(MOVE_WEST_STEP == _s8MoveState || MOVE_EAST_STEP == _s8MoveState)
		{
			if(MOVE_TIME == _u8MoveTime)
			{
				_SetMoveState(MOVE_STOP);
				switch(MApp_ZUI_API_GetFocus())
				{
					case HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP:
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETLIMIT_MOVESTEP_SET, SW_SHOW);
						break;

					case HWND_MENU_DISHSETUP_SETPOSITION_STEP:
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_STEP_OPTION, SW_SHOW);
                        break; // Fix coverity!?

					case HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO:
						MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_OPTION, SW_SHOW);
						break;

					default:
						break;
					}
			}
			else
			{
				_u8MoveTime++;
			}
		}

		if(MOVE_WEST == _s8MoveState || MOVE_EAST == _s8MoveState)
		{
			HWND hdr = NULL,hdl = NULL;
			switch(MApp_ZUI_API_GetFocus())
			{
				case HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE:
				{
					hdl = HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE_LARROW;
					hdr = HWND_MENU_DISHSETUP_SETLIMIT_MOVECONTINUE_RARROW;
					break;
				}
				case HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO:
				{
					hdl = HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_LARROW;
					hdr = HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO_RARROW;
					break;
				}
				case HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE:
				{
					hdl = HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE_LARROW;
					hdr = HWND_MENU_DISHSETUP_SETPOSITION_CONTINUE_RARROW;
					break;
				}
				default:
					break;
			}
			if(2 == _u8MoveTime)
			{
				if(_GetMoveState() == MOVE_WEST)
					MApp_ZUI_API_ShowWindow(hdl,SW_HIDE);
				else if(_GetMoveState() == MOVE_EAST)
					MApp_ZUI_API_ShowWindow(hdr,SW_HIDE);
				_u8MoveTime++;
			}
			else if(4 == _u8MoveTime)
			{
				if(_GetMoveState() == MOVE_WEST)
				MApp_ZUI_API_ShowWindow(hdl,SW_SHOW);
				else if(_GetMoveState() == MOVE_EAST)
				MApp_ZUI_API_ShowWindow(hdr,SW_SHOW);
				_u8MoveTime = 0;
			}
			else
			{
				_u8MoveTime++;
			}
		}

		if(_u8ModifyParam >= FORCE_TUNE_COUNT_MAX )
		{
			_u8ModifyParam = 0;
			_s16QualityPercent = 0;

			if (_GetCurrentSatTPNum() == 0)
			{
				_s16QualityPercent = 0;
				MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_QULITY);
				return;
			}
			_GetSatInforByID(u8CurrentEditSATId, &TempSatInfor);
			_GetCarrierParam(u16CurrentEditSATTPPos, &TempTp);
			MApi_DigiTuner_Tune2RfCh(TempSatInfor, &TempTp, eAutoTune);
		}
		else if(_u8ModifyParam>0&&_u8ModifyParam < FORCE_TUNE_COUNT_MAX)
		{
			_u8ModifyParam ++;
		}
		else
		{
			MS_S16 s16CurQulity;
			if (MApi_DigiTuner_TPSGetLock() == TRUE)
			{
				s16CurQulity = MApi_DigiTuner_getCurRFSignalSNR_Persent();
			}
			else
			{
				s16CurQulity = 0;
			}

			if((_s8MoveState == MOVE_WEST || _s8MoveState == MOVE_EAST)
			&&MApp_ZUI_API_GetFocus() ==  HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO)
			{
				if(_s16QualityPercent >s16CurQulity)
				{
					_s8MoveState = (_s8MoveState == MOVE_WEST)?MOVE_EAST_STEP:MOVE_WEST_STEP;
					_SetMoveStep(_s8MoveState,10);
					MApp_ZUI_API_ShowWindow(HWND_MENU_DISHSETUP_SETPOSITION_MOVEAUTO, SW_SHOW);
					_u8MoveTime = 0;
				}
			}
			_s16QualityPercent = s16CurQulity;
			MApp_ZUI_API_InvalidateWindow(HWND_MENU_DISHSETUP_QULITY);
		}
		return;
	}
}

#if(ENABLE_DELETE_SCREMBAL_PROGRAM)
SCAN_SAVETYPE Get_Scan_Savetype(void)
{
	return _eScanProgSaveType;
}
SCAN_SERVICETYPE Get_Scan_ServiceType(void)
{
	return _eScanServiceType;
}
#endif

#if ENABLE_S2_QUALITY_DISPLAY_PERCENT
S32 MApp_ZUI_ACT_DISHSETUP_WINPROC(HWND hwnd, PMSG msg)
{
	switch(msg->message)
	{
		case MSG_CREATE:
		{
			MApp_ZUI_API_SetTimer(HWND_MENU_DISHSETUP_QULITY, 0, DISHSETUP_SIGNAL_BAR_MONITOR_DURATION);
		}
		break;

		case MSG_TIMER:
		{
			switch(msg->wParam)
			{
				case 0:
				default:
					vDispSignalQuality();
					break;
			}
		}
		break;

		default:
			break;
	}
	return DEFAULTWINPROC(hwnd, msg);
}
#endif

#endif
#undef MAPP_ZUI_ACTDISHSETUP_C

