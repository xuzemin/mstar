//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_ATVSystem.h
/// This file includes MStar ATV System Application interface
/// @brief API for ATV control
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#include "Utl.h"
#include "Tuner.h"
#include "msAPI_ATVSystem.h"
#if ENABLE_ISDB_DOUBLE_RF_INPUT
#include "drvGPIO.h"        // for Panel VCC control
#endif

static BYTE             _u8CATVPRIndexTable[MAX_CATVPROGRAM];
static BYTE             _u8CATVPRTableMap[MAX_CATV_PRTABLEMAP];
static EN_ANT_TYPE      _bAntenna;

//------------------------------------------------------------------------------
/// -This function will init ATV Data manager (for TV/AV)
//------------------------------------------------------------------------------
void msAPI_ATV_InitATVDataManager(void)
{
    BYTE i;

    if ( _u16Identification != DATA_IDENTIFICATION )
    {
        for ( i = 0 ; i < 5 ; i++ )
        {
            if ( TRUE == _GetNVRAM(BASEADDRESS_IDENT, (BYTE *)&_u16Identification, sizeof(_u16Identification)) )
            {
                if ( _u16Identification == DATA_IDENTIFICATION )
                {
                    break;
                }
            }
        }

        #if 0
        if ( i >= 5 )
        {
            ATV_MSG("ATV data structure is cleard", 0);
        }
        #endif
    }
    else
    {
        _u8PastProgramNumber = _u8CurrentProgramNumber;

        return;
    }

    if ( _u16Identification != DATA_IDENTIFICATION )
    {
        msAPI_ATV_ResetATVDataManager();

        _u16Identification = DATA_IDENTIFICATION;

        _SetNVRAM(BASEADDRESS_IDENT, (BYTE *)&_u16Identification, sizeof(_u16Identification));
    }

    //if(_bAntenna == ANT_AIR)
    {
        _GetNVRAM(BASEADDRESS_PR_ATVPRINDEXTABLE, _u8ATVPRIndexTable, sizeof(_u8ATVPRIndexTable));
        _GetNVRAM(BASEADDRESS_PR_ATVPRTABLEMAP, _u8PRTableMap, sizeof(_u8PRTableMap));
    }
    //else
    {
        _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRINDEXTABLE, _u8CATVPRIndexTable, sizeof(_u8CATVPRIndexTable));
        _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLEMAP, _u8CATVPRTableMap, sizeof(_u8CATVPRTableMap));
    }

    if(stGenSetting.stScanMenuSetting.u8Antenna == ANT_AIR)
    {
        _bAntenna = ANT_AIR;
    }
    else
    {
        _bAntenna = ANT_CATV;
    }

    _CorrectDuplication();
    _CorrectMapping();

     _u8CurrentProgramNumber = _LoadProgramNumber();

    _u8PastProgramNumber = _u8CurrentProgramNumber;

}

//------------------------------------------------------------------------------
/// -This function will reset ATV Channel Data (for TV/AV)
//------------------------------------------------------------------------------
void msAPI_ATV_ResetAntennaChannelData(void)
{
    BYTE i;

#if ENABLE_SBTVD_ATV_SYSTEM
    msAPI_Reset_Tuner_GetNumberOfChBeFound_WhileAutoScan();
#endif

    _SaveProgramNumber(DEFAULT_LASTPROGRAM);

    if(_bAntenna == ANT_AIR)
    {
        _u8PastProgramNumber = DEFAULT_LASTPROGRAM;

        for ( i = 0; i < MAX_PRTABLEMAP; i++ )
        {
            _u8PRTableMap[i] = 0xFF;
        }

        _SetNVRAM(BASEADDRESS_PR_ATVPRTABLEMAP, (BYTE *)&_u8PRTableMap, sizeof(_u8PRTableMap));

        for ( i = 0; i < MAX_ATVPROGRAM; i++ )
        {
            _SetPRIndexTable(i, i);
            _FillPREntityWithDefault(i);
        }
    }
    else
    {
        for ( i = 0; i < MAX_CATV_PRTABLEMAP; i++ )
        {
            _u8CATVPRTableMap[i] = 0xFF;
        }

        _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLEMAP, (BYTE *)&_u8CATVPRTableMap, sizeof(_u8CATVPRTableMap));

        for ( i = 0; i < MAX_CATVPROGRAM; i++ )
        {
            _SetPRIndexTable(i, i);
            _FillPREntityWithDefault(i);
        }
    }
}

void msAPI_ATV_ResetChannelData(void)
{
    if(_bAntenna == ANT_AIR)
        _bAntenna = ANT_CATV;
    else
        _bAntenna = ANT_AIR;

    msAPI_ATV_ResetAntennaChannelData();

    if(_bAntenna == ANT_AIR)
        _bAntenna = ANT_CATV;
    else
        _bAntenna = ANT_AIR;

    msAPI_ATV_ResetAntennaChannelData();
}

//------------------------------------------------------------------------------
/// -This function will get first favorite Program
/// @return BYTE: First Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetFirstFavoriteProgramNumber(void)
{
    BYTE u8ProgramNumber;

    for (u8ProgramNumber = ATV_FIRST_PR_NUM; u8ProgramNumber < msAPI_ATV_GetChannelMax(); u8ProgramNumber++)
    {
        if ( TRUE == _IsIndexActive(u8ProgramNumber) &&
             TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            break;
        }
    }

    return u8ProgramNumber;
}


//------------------------------------------------------------------------------
/// -This function will get Previous favorite Program
/// @param cBaseProgramNumber \b IN: Base program number
/// @return BYTE: Previous Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetPreviousFavoriteProgramNumber(BYTE u8BaseProgramNumber)
{
    BYTE u8ProgramNumber;

    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        u8ProgramNumber--;

        if (u8ProgramNumber < ATV_FIRST_PR_NUM)
        {
            u8ProgramNumber = (msAPI_ATV_GetChannelMax() -1);
        }

        if ( TRUE == _IsIndexActive(u8ProgramNumber) &&
             TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            break;
        }
    } while ( u8ProgramNumber != u8BaseProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get next favorite Program
/// @param cBaseProgramNumber \b IN: Base program number
/// @return BYTE: Next Favorite Program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetNextFavoriteProgramNumber(BYTE u8BaseProgramNumber)
{
    BYTE u8ProgramNumber;

    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        u8ProgramNumber++;

        if (u8ProgramNumber >= msAPI_ATV_GetChannelMax())
        {
            u8ProgramNumber = ATV_FIRST_PR_NUM;
        }

        if ( TRUE == _IsIndexActive(u8ProgramNumber) && TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            break;
        }
    } while ( u8ProgramNumber != u8BaseProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get total favorite Program numbers
/// @return BYTE: Total Program numbers
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetTotalFavoriteProgramCount(void)
{
    BYTE u8FavoriteProgramCount = 0;
    BYTE u8ProgramNumber;

    for ( u8ProgramNumber = ATV_FIRST_PR_NUM; u8ProgramNumber < msAPI_ATV_GetChannelMax(); u8ProgramNumber++ )
    {
        if ( TRUE == _IsIndexActive(u8ProgramNumber) && TRUE == msAPI_ATV_IsProgramFavorite(u8ProgramNumber) )
        {
            u8FavoriteProgramCount++;
        }
    }

    return u8FavoriteProgramCount;
}

//------------------------------------------------------------------------------
/// -This function will set Current Program number
/// @param cProgramNumber \b IN: Current program number
//------------------------------------------------------------------------------
void msAPI_ATV_SetCurrentProgramNumber(BYTE u8ProgramNumber)
{
    if ( u8ProgramNumber < msAPI_ATV_GetChannelMax() )
    {
        _u8PastProgramNumber = _u8CurrentProgramNumber;

        _u8CurrentProgramNumber = u8ProgramNumber;

        _SaveProgramNumber(_u8CurrentProgramNumber);
    }
}

//------------------------------------------------------------------------------
/// -This function will get Next Program number
/// @param cBaseProgramNumber \b IN: base program number
/// @param bIncludeSkipped \b IN: Include skpped program or not
/// - TURE: Include
/// - FALSE: Don't include skipped program
/// @return BYTE: Next program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetNextProgramNumber(BYTE u8BaseProgramNumber, BOOLEAN bIncludeSkipped)
{
    BYTE u8ProgramNumber;

    #if 1 //(!ENABLE_SBTVD_CM_APP)
    bIncludeSkipped = FALSE;
    #endif

    //u8ProgramNumber = _u8CurrentProgramNumber;
    if(u8BaseProgramNumber < ATV_FIRST_PR_NUM)
    {
        u8BaseProgramNumber = ATV_FIRST_PR_NUM;
    }
    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        u8ProgramNumber++;

        if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
        {
            u8ProgramNumber = ATV_FIRST_PR_NUM;
        }

        #if 0 //ENABLE_SBTVD_CM_APP
        if(bIncludeSkipped == TRUE)
        {
            if(TRUE == _IsIndexActive(u8ProgramNumber))
                break;
        }
        else
        #endif
        if ( TRUE == _IsIndexActive(u8ProgramNumber) && FALSE == msAPI_ATV_IsProgramSkipped(u8ProgramNumber) )
        {
            break;
        }

        if( u8ProgramNumber == u8BaseProgramNumber)
            break;

    } while (u8ProgramNumber <= msAPI_ATV_GetChannelMax());//( u8ProgramNumber != _u8CurrentProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will get Previous Program number
/// @param cBaseProgramNumber \b IN: base program number
/// @param bIncludeSkipped \b IN: Include skpped program or not
/// - TURE: Include
/// - FALSE: Don't include skipped program
/// @return BYTE: Previous program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetPrevProgramNumber(BYTE u8BaseProgramNumber, BOOLEAN bIncludeSkipped)
{
    BYTE u8ProgramNumber;

    bIncludeSkipped = FALSE;
    UNUSED(bIncludeSkipped);

    //u8ProgramNumber = _u8CurrentProgramNumber;
    if(u8BaseProgramNumber < ATV_FIRST_PR_NUM)
    {
        u8BaseProgramNumber = ATV_FIRST_PR_NUM;
    }
    u8ProgramNumber = u8BaseProgramNumber;

    do
    {
        if (u8ProgramNumber == ATV_FIRST_PR_NUM)
        {
            u8ProgramNumber = msAPI_ATV_GetChannelMax();
        }

            u8ProgramNumber--;

        if ( TRUE == _IsIndexActive(u8ProgramNumber) && FALSE == msAPI_ATV_IsProgramSkipped(u8ProgramNumber) )
        {
            break;
        }

        if( u8ProgramNumber == u8BaseProgramNumber)
            break;

    } while ( u8ProgramNumber != _u8CurrentProgramNumber );

    return u8ProgramNumber;
}

//------------------------------------------------------------------------------
/// -This function will increase current Program number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IncCurrentProgramNumber(void)
{
    if ( _u8CurrentProgramNumber >= (msAPI_ATV_GetChannelMax() - 1) )
    {
        return FALSE;
    }

    _u8PastProgramNumber = _u8CurrentProgramNumber;

    _u8CurrentProgramNumber++;

    _SaveProgramNumber(_u8CurrentProgramNumber);

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get Program PLL data
/// @param cProgramNumber \b IN: program number
/// @return WORD: PLL Data
//------------------------------------------------------------------------------
WORD msAPI_ATV_GetProgramPLLData(BYTE u8ProgramNumber)
{
    WORD wPLL = 0;

    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return DEFAULT_PLL;
    }

    if(TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&wPLL, PRDATA_PLL_PARAM))
        return wPLL;

    return DEFAULT_PLL;
}

//------------------------------------------------------------------------------
/// -This function will set Program PLL data
/// @param cProgramNumber \b IN: program number
/// @param wPLL: PLL Data
//------------------------------------------------------------------------------
void msAPI_ATV_SetProgramPLLData(BYTE u8ProgramNumber, WORD wPLL)
{
    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return;
    }

    if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&wPLL, PRDATA_PLL_PARAM))
    {
        __ASSERT(0);
     }
}

//------------------------------------------------------------------------------
/// -This function will check if AFT is needed
/// @param cProgramNumber \b IN: Program number
/// @return BOOLEAN: needed or not
/// - TRUE: Yes
/// - FALSE: NO
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsAFTNeeded(BYTE u8ProgramNumber)
{
    ATV_MISC Misc;

    memset(&Misc,0,sizeof(ATV_MISC));
    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return TRUE;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( Misc.bAFT == FALSE )
        {
            return FALSE;
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get Medium and Channel Number
/// @param cProgramNumber \b IN: Program number
/// @param *peMedium \b IN: pointer to Medium for return
/// -@see MEDIUM
/// @param *pcChannelNumber \b IN: pointer to Channel number for return
//------------------------------------------------------------------------------
void msAPI_ATV_GetMediumAndChannelNumber(BYTE u8ProgramNumber, MEDIUM * peMedium, BYTE * pcChannelNumber)
{
    ATV_MISC Misc;
    memset(&Misc,0,sizeof(ATV_MISC));

    WORD wPLL;

    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        if ( peMedium != NULL )
        {
            *peMedium = DEFAULT_MEDIUM;
        }

        if ( pcChannelNumber != NULL )
        {
            *pcChannelNumber = DEFAULT_CHANNELNUMBER;
        }

        return;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( TRUE == msAPI_CFT_IsValidMediumAndChannel((MEDIUM)Misc.eMedium, Misc.u8ChannelNumber) )
        {
            if ( peMedium != NULL )
            {
                *peMedium = (MEDIUM)Misc.eMedium;
            }

            if ( pcChannelNumber != NULL )
            {
                *pcChannelNumber = Misc.u8ChannelNumber;
            }

            return;
        }
    }

    wPLL = msAPI_ATV_GetProgramPLLData(u8ProgramNumber);

    if ( peMedium != NULL )
    {
        *peMedium = msAPI_CFT_GetMedium(wPLL);
    }

    if ( pcChannelNumber != NULL )
    {
        *pcChannelNumber = msAPI_CFT_GetChannelNumber(wPLL);
    }
}

//------------------------------------------------------------------------------
/// -This function will get Medium and Channel Number
/// @param cProgramNumber \b IN: Program number
/// @param eMedium \b IN: Medium type
/// -@see MEDIUM
/// @param cChannelNumber \b IN: Channel number
//------------------------------------------------------------------------------
void msAPI_ATV_SetMediumAndChannelNumber(BYTE u8ProgramNumber, MEDIUM eMedium, BYTE cChannelNumber)
{
    ATV_MISC Misc;
    WORD wPLL;

    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM) )
    {
        if ( TRUE == msAPI_CFT_IsValidMediumAndChannel(eMedium, cChannelNumber) )
        {
            Misc.eMedium = eMedium;
            Misc.u8ChannelNumber = cChannelNumber;
        }
        else
        {
            wPLL = msAPI_ATV_GetProgramPLLData(u8ProgramNumber);

            Misc.eMedium = msAPI_CFT_GetMedium(wPLL);;
            Misc.u8ChannelNumber = msAPI_CFT_GetChannelNumber(wPLL);
        }

        if(TRUE != _SetPRTable(u8ProgramNumber, (BYTE *)&Misc, PRDATA_MISC_PARAM))
        {
            __ASSERT(0);
         }
    }
}

//------------------------------------------------------------------------------
/// -This function will get Station name
/// @param cProgramNumber \b IN: Program number
/// @param *sName \b IN: pointer to station name for return
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_GetStationName(BYTE u8ProgramNumber, BYTE *sName)
{
    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    if ( TRUE == _GetPRTable(u8ProgramNumber, sName, PRDATA_NAME_PARAM) )
    {
        return TRUE;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will sort program
/// @param cStart \b IN: start program
/// @param cStop \b IN: stop
//------------------------------------------------------------------------------
void msAPI_ATV_SortProgram(BYTE u8Start, BYTE u8Stop)
{
    BYTE i, j;
    BYTE u8MinValue = 0 ;
    BYTE u8MinIndex;
    BYTE u8Value = 0 ;

    if ( IS_CH_NAME_ENABLED == FALSE )
    {
        return;
    }

    if ( u8Start >= u8Stop || u8Stop >= msAPI_ATV_GetChannelMax() )
    {
        return;
    }

    for ( i = u8Start; i < u8Stop; i++ )
    {
        u8MinIndex = i;

        if(TRUE == _GetPRTable(i, &u8MinValue, PRDATA_SORT_PARAM))
        {
            for ( j = i+1; j <= u8Stop; j++ )
            {
                if(TRUE == _GetPRTable(j, &u8Value, PRDATA_SORT_PARAM))
                {
                    if ( u8MinValue > u8Value )
                    {
                        u8MinValue = u8Value;
                        u8MinIndex = j;
                    }
                }
            }
        }

        if ( i != u8MinIndex )
        {
            _MovePRTable(u8MinIndex, i);
        }
    }
}

//------------------------------------------------------------------------------
/// -This function will check if the program number is active or not
/// @param cProgramNumber \b IN: Program number
/// @return BOOLEAN: Active or not
/// - TRUE: Active
/// - FALSE: Not active
//------------------------------------------------------------------------------
BOOLEAN msAPI_ATV_IsProgramNumberActive(BYTE u8ProgramNumber)
{
    BYTE u8PRIndex;

    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8ProgramNumber);

    return _IsPREntityActive(u8PRIndex);
}

BOOLEAN msAPI_ATV_IsProgramEmpty(void)
{
    int i;

    if(_bAntenna == ANT_AIR)
    {
        for ( i = 0; i < MAX_PRTABLEMAP; i++ )
        {
            if ( _u8PRTableMap[i] != 0 )
            {
                return FALSE;
            }
        }
    }
    else
    {
        for ( i = 0; i < MAX_CATV_PRTABLEMAP; i++ )
        {
            if ( _u8CATVPRTableMap[i] != 0 )
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will get first program number
/// @param bIncludeSkipped \b IN: include skipped program or not
/// - TRUE: include
/// - FALSE: don't include
/// @return BYTE: The first program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetFirstProgramNumber(BOOLEAN bIncludeSkipped)
{
    BYTE u8ProgramNumber;

    bIncludeSkipped = FALSE;
    UNUSED(bIncludeSkipped);

    for (u8ProgramNumber = ATV_FIRST_PR_NUM; u8ProgramNumber < msAPI_ATV_GetChannelMax(); u8ProgramNumber++)
    {
        if ( TRUE == _IsIndexActive(u8ProgramNumber) )
        {
            return u8ProgramNumber;
        }
    }

    return msAPI_ATV_GetChannelMin();
}

//------------------------------------------------------------------------------
/// -This function will get active program count
/// @return BYTE: active program count
//------------------------------------------------------------------------------
BYTE msAPI_ATV_GetActiveProgramCount(void)
{
    BYTE count;
    int i;

    count = 0;

    for ( i = ATV_FIRST_PR_NUM; i < msAPI_ATV_GetChannelMax(); i++ )
    {
        if ( _IsIndexActive(i) )
        {
            ++count;
        }
    }

    return count;
}

//------------------------------------------------------------------------------
/// -This function will convert program number to ordinal number
/// @return BYTE: ordinal number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_ConvertProgramNumberToOrdinalNumber(BYTE u8ProgramNumber)
{
    BYTE i;
    BYTE u8OrdinalNumber = 0;

    if (u8ProgramNumber < msAPI_ATV_GetChannelMax())
    {
        for ( i = ATV_FIRST_PR_NUM; i <= u8ProgramNumber; i++ )
        {
            if ( _IsIndexActive(i) )
            {
                ++u8OrdinalNumber;
            }
        }
    }

    if(u8OrdinalNumber > 0)
        u8OrdinalNumber--;

    //printf("u8ProgramNumber %bu => u8OrdinalNumber %bu\n", u8ProgramNumber, u8OrdinalNumber);

    return u8OrdinalNumber;
}

//------------------------------------------------------------------------------
/// -This function will convert ordinal number to program number
/// @return BYTE: program number
//------------------------------------------------------------------------------
BYTE msAPI_ATV_ConvertOrdinalNumberToProgramNumber(WORD wOrdinalNumber)
{
    BYTE i;
    BYTE u8ProgramNumber = 0;

    if (wOrdinalNumber < msAPI_ATV_GetChannelMax())
    {
        for ( i = ATV_FIRST_PR_NUM; i < msAPI_ATV_GetChannelMax(); i++ )
        {
            if ( _IsIndexActive(i))
            {
                if(wOrdinalNumber == u8ProgramNumber)
                {
                    u8ProgramNumber = i;
                    break;
                }

                ++u8ProgramNumber;
            }
        }
    }

    //printf("wOrdinalNumber %bu => u8ProgramNumber %bu\n", wOrdinalNumber, u8ProgramNumber);

    return u8ProgramNumber;
}
//------------------------------------------------------------------------------
// Locals
//------------------------------------------------------------------------------

static void _CorrectDuplication(void)
{
    BYTE u8DuplicationMap[MAX_CATV_PRTABLEMAP];//it's because MAX_CATV_PRTABLEMAP > MAX_PRTABLEMAP
    BYTE i;
    BYTE u8PRIndex;
    BYTE u8MaxPRTableMap;

    if(_bAntenna == ANT_AIR)
        u8MaxPRTableMap = MAX_PRTABLEMAP;
    else
        u8MaxPRTableMap = MAX_CATV_PRTABLEMAP;

    for ( i = 0; i < u8MaxPRTableMap; i++ )
    {
        u8DuplicationMap[i] = 0x00;
    }

    for ( i = 0; i < msAPI_ATV_GetChannelMax(); i++ )
    {
        u8PRIndex = _GetPRIndexTable(i);

        if ( u8PRIndex >= msAPI_ATV_GetChannelMax() )
        {
            continue;
        }

        if ( (u8DuplicationMap[u8PRIndex/8] & (0x01 << (u8PRIndex%8))) == TRUE )
        {
            _SetPRIndexTable(i, PR_NOTHING);

            ATV_MSG("ATV: Channel Duplication", 0);
        }
        else
        {
            u8DuplicationMap[u8PRIndex/8] =  u8DuplicationMap[u8PRIndex/8] | (0x01 << (u8PRIndex%8));
        }
    }
}

static void _CorrectMapping(void)
{
    BYTE u8PRIndex;
    BYTE i;
    BYTE u8IndexCount;
    BYTE u8MapCount;

    u8IndexCount = 0;

    for ( i = 0; i < msAPI_ATV_GetChannelMax(); i++ )
    {
        u8PRIndex = _GetPRIndexTable(i);

        if ( u8PRIndex >= msAPI_ATV_GetChannelMax() )
        {
            continue;
        }

        u8IndexCount++;

        if ( _IsPREntityActive(u8PRIndex) == FALSE )
        {
            _SetPRIndexTable(i, PR_NOTHING);

            u8IndexCount--;

            ATV_MSG("ATV: Mapping error", 0);
        }
    }

    u8MapCount = 0;

    for ( i = 0; i < msAPI_ATV_GetChannelMax(); i++ )
    {
        if ( _IsPREntityActive(i) == TRUE )
        {
            u8MapCount++;
        }
    }

    if ( u8MapCount != u8IndexCount )
    {
        ATV_MSG("ATV: Count is different", 0);

        for ( i = 0; i < msAPI_ATV_GetChannelMax(); i++ )
        {
            _ActivePREntity(i, FALSE);
        }

        for ( i = 0; i < msAPI_ATV_GetChannelMax(); i++ )
        {
            u8PRIndex = _GetPRIndexTable(i);

            if ( u8PRIndex >= msAPI_ATV_GetChannelMax() )
            {
                continue;
            }

            _ActivePREntity(u8PRIndex, TRUE);
        }
    }
}

static BOOLEAN _GetPRTable(BYTE u8Index, BYTE * pu8Buffer, BYTE u8Param)
{
    ATVPROGRAMDATA AtvProgramData;
    ATVPROGRAMDATA * pAtvProgramData = &AtvProgramData;
    ATV_MISC AtvMisc;
    ATV_MISC * pAtvMisc = &AtvMisc;
    WORD wPLL;
    BYTE u8PRIndex,u8Sort;
    BOOLEAN b_IsPREntityActive;
    S8 s8FineTune;

    if ( u8Index >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8Index);

    b_IsPREntityActive = _IsPREntityActive(u8PRIndex);

    if(_bAntenna == ANT_AIR)
    {
        switch ( u8Param )
        {
        case PRDATA_ALL_PARAM:
            if ( b_IsPREntityActive == TRUE )
            {
                _GetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)),
                        pu8Buffer, sizeof(ATVPROGRAMDATA));
            }
            else
            {
                pAtvProgramData->wPLL = DEFAULT_PLL;
                pAtvProgramData->Misc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
                pAtvProgramData->Misc.bSkip = DEFAULT_SKIP_VALUE;
                pAtvProgramData->Misc.bAFT = DEFAULT_AFT_VALUE;
                pAtvProgramData->Misc.eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
                pAtvProgramData->Misc.eAudioMode = DEFAULT_TV_AUDIOMODE;
                pAtvProgramData->Misc.bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
                pAtvProgramData->Misc.bIsFavorite = DEFAULT_FAVORITE_VALUE;
                pAtvProgramData->Misc.eMedium = DEFAULT_MEDIUM;
                pAtvProgramData->Misc.bIsLock = DEFAULT_LOCK_VALUE;
                pAtvProgramData->Misc.bIsSearched = DEFAULT_SEARCHED_VALUE;
                pAtvProgramData->Misc.u8ChannelNumber = DEFAULT_CHANNELNUMBER;
                pAtvProgramData->Misc.bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;

                pAtvProgramData->s8FineTune = DEFAULT_FINETUNE;
                _StringCopy(pAtvProgramData->sName, sNullStationName, MAX_STATION_NAME);
                memcpy(pu8Buffer,pAtvProgramData,sizeof(ATVPROGRAMDATA));
            }
            return TRUE;

        case PRDATA_PLL_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, wPLL)),
                        pu8Buffer, sizeof(WORD));
            }
            else
            {
                wPLL = DEFAULT_PLL;
                memcpy(pu8Buffer,&wPLL,sizeof(WORD));
            }

            return TRUE;

        case PRDATA_MISC_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                        pu8Buffer, sizeof(ATV_MISC));
            }
            else
            {
                pAtvMisc->eAudioStandard = DEFAULT_AUDIOSTANDARD;
                pAtvMisc->bSkip = DEFAULT_SKIP_VALUE;
                pAtvMisc->bAFT = DEFAULT_AFT_VALUE;
                pAtvMisc->eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
                pAtvMisc->eAudioMode = DEFAULT_TV_AUDIOMODE;
                pAtvMisc->bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
                pAtvMisc->bIsFavorite = DEFAULT_FAVORITE_VALUE;
                pAtvMisc->eMedium = DEFAULT_MEDIUM;
                pAtvMisc->bIsLock = DEFAULT_LOCK_VALUE;
                pAtvMisc->bIsSearched = DEFAULT_SEARCHED_VALUE;
                pAtvMisc->bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;
                pAtvMisc->u8ChannelNumber = DEFAULT_CHANNELNUMBER;

                memcpy(pu8Buffer,pAtvMisc,sizeof(ATV_MISC));
            }
            return TRUE;

        case PRDATA_FINETUNE_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, s8FineTune)),
                        pu8Buffer, sizeof(BYTE));
            }
            else
            {
                s8FineTune = (BYTE)DEFAULT_FINETUNE;
                memcpy(pu8Buffer,&s8FineTune,sizeof(S8));
            }
            return TRUE;

        case PRDATA_SORT_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8Sort)),
                        pu8Buffer, sizeof(BYTE));
            }
            else
            {
                u8Sort = (BYTE)LOWEST_SORTING_PRIORITY;
                memcpy(pu8Buffer,&u8Sort,sizeof(BYTE));
            }
            return TRUE;

        case PRDATA_NAME_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, sName)),
                        pu8Buffer, sizeof(BYTE)*MAX_STATION_NAME);
            }
            else
            {
                _StringCopy(pu8Buffer, sNullStationName, MAX_STATION_NAME);
            }
            return TRUE;
        }
    }
    else//ANT_CATV
    {
        switch ( u8Param )
        {
        case PRDATA_ALL_PARAM:
            if ( b_IsPREntityActive == TRUE )
            {
                _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)),
                        pu8Buffer, sizeof(ATVPROGRAMDATA));
            }
            else
            {
                pAtvProgramData->wPLL = DEFAULT_PLL;
                pAtvProgramData->Misc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
                pAtvProgramData->Misc.bSkip = DEFAULT_SKIP_VALUE;
                pAtvProgramData->Misc.bAFT = DEFAULT_AFT_VALUE;
                pAtvProgramData->Misc.eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
                pAtvProgramData->Misc.eAudioMode = DEFAULT_TV_AUDIOMODE;
                pAtvProgramData->Misc.bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
                pAtvProgramData->Misc.bIsFavorite = DEFAULT_FAVORITE_VALUE;
                pAtvProgramData->Misc.eMedium = DEFAULT_MEDIUM;
                pAtvProgramData->Misc.bIsLock = DEFAULT_LOCK_VALUE;
                pAtvProgramData->Misc.bIsSearched = DEFAULT_SEARCHED_VALUE;
                pAtvProgramData->Misc.bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;
                pAtvProgramData->Misc.u8ChannelNumber = DEFAULT_CHANNELNUMBER;

                pAtvProgramData->s8FineTune = DEFAULT_FINETUNE;
                _StringCopy(pAtvProgramData->sName, sNullStationName, MAX_STATION_NAME);

                memcpy(pu8Buffer,pAtvProgramData,sizeof(ATVPROGRAMDATA));
            }
            return TRUE;

        case PRDATA_PLL_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, wPLL)),
                        pu8Buffer, sizeof(WORD));
            }
            else
            {
                wPLL = DEFAULT_PLL;
                memcpy(pu8Buffer,&wPLL,sizeof(WORD));
            }

            return TRUE;

        case PRDATA_MISC_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                        pu8Buffer, sizeof(ATV_MISC));
            }
            else
            {
                pAtvMisc->eAudioStandard = DEFAULT_AUDIOSTANDARD;
                pAtvMisc->bSkip = DEFAULT_SKIP_VALUE;
                pAtvMisc->bAFT = DEFAULT_AFT_VALUE;
                pAtvMisc->eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
                pAtvMisc->eAudioMode = DEFAULT_TV_AUDIOMODE;
                pAtvMisc->bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
                pAtvMisc->bIsFavorite = DEFAULT_FAVORITE_VALUE;
                pAtvMisc->eMedium = DEFAULT_MEDIUM;
                pAtvMisc->bIsLock = DEFAULT_LOCK_VALUE;
                pAtvMisc->bIsSearched = DEFAULT_SEARCHED_VALUE;
                pAtvMisc->bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;

                pAtvMisc->u8ChannelNumber = DEFAULT_CHANNELNUMBER;

                memcpy(pu8Buffer,pAtvMisc,sizeof(ATV_MISC));
            }

            return TRUE;

        case PRDATA_FINETUNE_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, s8FineTune)),
                        pu8Buffer, sizeof(BYTE));
            }
            else
            {
                s8FineTune = (BYTE)DEFAULT_FINETUNE;
                memcpy(pu8Buffer,&s8FineTune,sizeof(S8));
            }
            return TRUE;

        case PRDATA_SORT_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8Sort)),
                        pu8Buffer, sizeof(BYTE));
            }
            else
            {
                u8Sort = (BYTE)LOWEST_SORTING_PRIORITY;
                memcpy(pu8Buffer,&u8Sort,sizeof(BYTE));
            }
            return TRUE;

        case PRDATA_NAME_PARAM:
            if (b_IsPREntityActive == TRUE)
            {
                _GetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                        (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, sName)),
                        pu8Buffer, sizeof(BYTE)*MAX_STATION_NAME);
            }
            else
            {
                _StringCopy(pu8Buffer, sNullStationName, MAX_STATION_NAME);
            }
            return TRUE;
        }
    }

    return FALSE;
}

static BOOLEAN _SetPRTable(BYTE u8Index, BYTE * pu8Buffer, BYTE u8Param)
{
    BYTE u8PRIndex;
    BYTE u8NewPREntity;

    if ( u8Index >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8Index);

    if ( TRUE != _IsPREntityActive(u8PRIndex) )
    {
        u8NewPREntity = _GetEmptyPREntity();

        if (u8NewPREntity >= msAPI_ATV_GetChannelMax() || u8NewPREntity == PR_NOTHING)
        {
            _CorrectDuplication();

            _CorrectMapping();

            u8NewPREntity = _GetEmptyPREntity();

            if ( u8NewPREntity >= msAPI_ATV_GetChannelMax() || u8NewPREntity == PR_NOTHING )
            {
                ATV_MSG("ATV: FATAL ERROR", 0);
                return FALSE;
            }
        }

        _FillPREntityWithDefault(u8NewPREntity);

        u8PRIndex = u8NewPREntity;

        _SetPRIndexTable(u8Index, u8PRIndex);

        _ActivePREntity(u8PRIndex, TRUE);
    }

    if(_bAntenna == ANT_AIR)
    {
        switch ( u8Param )
        {
        case PRDATA_PLL_PARAM:
            _SetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, wPLL)),
                    pu8Buffer, sizeof(WORD));

            return TRUE;

        case PRDATA_MISC_PARAM:
            _SetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                    pu8Buffer, sizeof(ATV_MISC));

            return TRUE;

        case PRDATA_FINETUNE_PARAM:
            _SetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, s8FineTune)),
                    pu8Buffer, sizeof(BYTE));

            return TRUE;

        case PRDATA_SORT_PARAM:
            _SetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8Sort)),
                    pu8Buffer, sizeof(BYTE));

            return TRUE;

        case PRDATA_NAME_PARAM:
            _SetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, sName)),
                    pu8Buffer, sizeof(BYTE)*MAX_STATION_NAME);

            return TRUE;

        case PRDATA_ALL_PARAM:
            _SetNVRAM(BASEADDRESS_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)),
                    pu8Buffer, sizeof(ATVPROGRAMDATA));

            return TRUE;
        }

    }
    else//ANT_CATV
    {
        switch ( u8Param )
        {
        case PRDATA_PLL_PARAM:
            _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, wPLL)),
                    pu8Buffer, sizeof(WORD));

            return TRUE;

        case PRDATA_MISC_PARAM:
            _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, Misc)),
                    pu8Buffer, sizeof(ATV_MISC));

            return TRUE;

        case PRDATA_FINETUNE_PARAM:
            _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, s8FineTune)),
                    pu8Buffer, sizeof(BYTE));

            return TRUE;

        case PRDATA_SORT_PARAM:
            _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, u8Sort)),
                    pu8Buffer, sizeof(BYTE));

            return TRUE;

        case PRDATA_NAME_PARAM:
            _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)+offsetof(ATVPROGRAMDATA, sName)),
                    pu8Buffer, sizeof(BYTE)*MAX_STATION_NAME);

            return TRUE;

        case PRDATA_ALL_PARAM:
            _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLE+
                    (u8PRIndex*sizeof(ATVPROGRAMDATA)),
                    pu8Buffer, sizeof(ATVPROGRAMDATA));

            return TRUE;
        }

    }

    return FALSE;
}

static BOOLEAN _DeletePRTable(BYTE u8Index)
{

    BYTE u8PRIndex;

    if ( u8Index >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    u8PRIndex = _GetPRIndexTable(u8Index);

    msAPI_ATV_SetSearchedProgram(u8PRIndex, FALSE);

    return TRUE;
}

static BOOLEAN _MovePRTable(BYTE u8From, BYTE u8To)
{
    BYTE u8PRIndex;
    BYTE u8TempPRIndex;
    BYTE i;

    if ( u8From >= msAPI_ATV_GetChannelMax() || u8To >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    if ( u8From == u8To )
    {
        return TRUE;
    }

    if ( u8From > u8To )
    {
        u8TempPRIndex = _GetPRIndexTable(u8From);

        for ( i = u8From; i > u8To; i-- )
        {
            u8PRIndex = _GetPRIndexTable(i-1);

            _SetPRIndexTable(i, u8PRIndex);
        }

        _SetPRIndexTable(u8To, u8TempPRIndex);
    }
    else
    {
        u8TempPRIndex = _GetPRIndexTable(u8From);

        for ( i = u8From; i < u8To; i++ )
        {
            u8PRIndex = _GetPRIndexTable(i+1);

            _SetPRIndexTable(i, u8PRIndex);
        }

        _SetPRIndexTable(u8To, u8TempPRIndex);
    }

    return TRUE;
}

static BOOLEAN _SwapPRTable(BYTE u8Index1, BYTE u8Index2)
{
    BYTE u8PRIndex;
    BYTE u8TempPRIndex;

    if (( u8Index1 >= msAPI_ATV_GetChannelMax() || u8Index1 <= msAPI_ATV_GetChannelMin())
        || ( u8Index2 >= msAPI_ATV_GetChannelMax() || u8Index2 <= msAPI_ATV_GetChannelMin()))
    {
        return FALSE;
    }

    if ( u8Index1 == u8Index2 )
    {
        return TRUE;
    }

    u8TempPRIndex = _GetPRIndexTable(u8Index1);
    u8PRIndex = _GetPRIndexTable(u8Index2);
    _SetPRIndexTable(u8Index1, u8PRIndex);
    _SetPRIndexTable(u8Index2, u8TempPRIndex);

    return TRUE;
}

static BYTE _GetPRIndexTable(BYTE u8Index)
{
    BYTE u8PRIndex;

    if ( u8Index >= msAPI_ATV_GetChannelMax() )
    {
        return PR_INVALID_INDEX;
    }

    if(_bAntenna == ANT_AIR)
        u8PRIndex = _u8ATVPRIndexTable[u8Index];
    else
        u8PRIndex = _u8CATVPRIndexTable[u8Index];

    return u8PRIndex;
}

static void _SetPRIndexTable(BYTE u8Index, BYTE u8PRIndex)
{
    if ( u8Index >= msAPI_ATV_GetChannelMax() )
    {
        return;
    }

    if(_bAntenna == ANT_AIR)
    {
        _u8ATVPRIndexTable[u8Index] = u8PRIndex;

        _SetNVRAM(BASEADDRESS_PR_ATVPRINDEXTABLE+u8Index, &u8PRIndex, sizeof(u8PRIndex));
    }
    else
    {
        _u8CATVPRIndexTable[u8Index] = u8PRIndex;

        _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRINDEXTABLE+u8Index, &u8PRIndex, sizeof(u8PRIndex));
    }
}

static BOOLEAN _IsPREntityActive(BYTE u8PRIndex)
{
    if ( u8PRIndex >= msAPI_ATV_GetChannelMax() )
    {
        return FALSE;
    }

    if(_bAntenna == ANT_AIR)
        return ( (_u8PRTableMap[u8PRIndex/8] & (0x01 << (u8PRIndex%8))) ? TRUE : FALSE );
    else
        return ( (_u8CATVPRTableMap[u8PRIndex/8] & (0x01 << (u8PRIndex%8))) ? TRUE : FALSE );
}

static void _ActivePREntity(BYTE u8PRIndex, BOOLEAN bActive)
{
    BYTE u8Temp;

    if ( u8PRIndex >= msAPI_ATV_GetChannelMax() )
    {
        return;
    }

    u8Temp = u8PRIndex/8;

    if(_bAntenna == ANT_AIR)
    {
        if ( TRUE == bActive )
        {
            _u8PRTableMap[u8Temp] =  _u8PRTableMap[u8Temp] | (0x01 << (u8PRIndex%8));
        }
        else
        {
            _u8PRTableMap[u8Temp] =  _u8PRTableMap[u8Temp] & ~(0x01 << (u8PRIndex%8));
        }

        _SetNVRAM(BASEADDRESS_PR_ATVPRTABLEMAP+u8Temp, &(_u8PRTableMap[u8Temp]), sizeof(BYTE));
    }
    else
    {
        if ( TRUE == bActive )
        {
            _u8CATVPRTableMap[u8Temp] =  _u8CATVPRTableMap[u8Temp] | (0x01 << (u8PRIndex%8));
        }
        else
        {
            _u8CATVPRTableMap[u8Temp] =  _u8CATVPRTableMap[u8Temp] & ~(0x01 << (u8PRIndex%8));
        }

        _SetNVRAM(BASEADDRESS_CATV_PR_ATVPRTABLEMAP+u8Temp, &(_u8CATVPRTableMap[u8Temp]), sizeof(BYTE));
    }
}

static BOOLEAN _IsIndexActive(BYTE u8Index)
{
    BYTE u8PRIndex;

    u8PRIndex = _GetPRIndexTable(u8Index);

    if(msAPI_ATV_GetDirectTuneFlag() == FALSE)
    {
        if(msAPI_ATV_IsProgramSearched(u8Index) == FALSE)
            return FALSE;
    }

    return _IsPREntityActive(u8PRIndex);
}

static BYTE _GetEmptyPREntity(void)
{
    BYTE i;

    for ( i = 0; i < msAPI_ATV_GetChannelMax(); i++ )
    {
        if ( FALSE == _IsPREntityActive(i) )
        {
            return i;
        }
    }

    return PR_NOTHING;
}

static void _FillPREntityWithDefault(BYTE u8PRIndex)
{
    ATVPROGRAMDATA PRData;

    PRData.wPLL = msAPI_ATV_MapChanToFreq(u8PRIndex+1);//DEFAULT_PLL
    PRData.Misc.eAudioStandard = DEFAULT_AUDIOSTANDARD;
    PRData.Misc.bSkip = DEFAULT_SKIP_VALUE;
    PRData.Misc.bAFT = DEFAULT_AFT_VALUE;
    PRData.Misc.eVideoStandard = DEFAULT_VIDEOSTANDARD_OF_PROGRAM;
    PRData.Misc.eVideoStandard_User = DEFAULT_USER_VIDEOSTANDARD_OF_PROGRAM;
    PRData.Misc.eAudioMode = DEFAULT_TV_AUDIOMODE;
    PRData.Misc.bWasDualAudioSelected = DEFAULT_DUAL_AUDIO_SELECTION;
    PRData.Misc.bIsFavorite = DEFAULT_FAVORITE_VALUE;
    PRData.Misc.eMedium = DEFAULT_MEDIUM;
    PRData.Misc.bIsLock = DEFAULT_LOCK_VALUE;
    PRData.Misc.bIsSearched = DEFAULT_SEARCHED_VALUE;
    PRData.Misc.bIsAutoColorSystem=DEFAULT_IS_AUTO_COLOR_SYSTEM;
    PRData.Misc.u8ChannelNumber = DEFAULT_CHANNELNUMBER;
    PRData.s8FineTune = DEFAULT_FINETUNE;

    _StringCopy(PRData.sName, sNullStationName, MAX_STATION_NAME);

    if(_bAntenna == ANT_AIR)
        _SetNVRAM( BASEADDRESS_PR_ATVPRTABLE+(u8PRIndex*sizeof(ATVPROGRAMDATA)),
                   (BYTE *)(&PRData), sizeof(PRData) );
    else
        _SetNVRAM( BASEADDRESS_CATV_PR_ATVPRTABLE+(u8PRIndex*sizeof(ATVPROGRAMDATA)),
                   (BYTE *)(&PRData), sizeof(PRData) );
}

static BYTE _LoadProgramNumber(void)
{
    BYTE u8ProgramNumber;

    if(_bAntenna == ANT_AIR)
        //_GetNVRAM(BASEADDRESS_PR_LASTPRNUMBER, &u8ProgramNumber, sizeof(u8ProgramNumber));
        u8ProgramNumber = stGenSetting.stTvSetting.u8ATVProgramNumber;
    else
        //_GetNVRAM(BASEADDRESS_CATV_PR_LASTPRNUMBER, &u8ProgramNumber, sizeof(u8ProgramNumber));
        u8ProgramNumber = stGenSetting.stTvSetting.u8ATVProgramNumber_CATV;

    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        u8ProgramNumber = DEFAULT_LASTPROGRAM;

        _SaveProgramNumber(u8ProgramNumber);
    }

    return u8ProgramNumber;
}

static void _SaveProgramNumber(BYTE u8ProgramNumber)
{
    if ( u8ProgramNumber >= msAPI_ATV_GetChannelMax() )
    {
        return;
    }

    if(_bAntenna == ANT_AIR)
        //_SetNVRAM(BASEADDRESS_PR_LASTPRNUMBER, &u8ProgramNumber, sizeof(u8ProgramNumber));
        stGenSetting.stTvSetting.u8ATVProgramNumber = u8ProgramNumber;
    else
        //_SetNVRAM(BASEADDRESS_CATV_PR_LASTPRNUMBER, &u8ProgramNumber, sizeof(u8ProgramNumber));
        stGenSetting.stTvSetting.u8ATVProgramNumber_CATV = u8ProgramNumber;
}

EN_ANT_TYPE msAPI_ATV_GetCurrentAntenna(void)
{
    return _bAntenna;
}

void msAPI_ATV_SetCurrentAntenna(EN_ANT_TYPE bAntenna)
{
    _bAntenna = bAntenna;

    #if ENABLE_ISDB_DOUBLE_RF_INPUT
    if (_bAntenna == ANT_AIR)
    {
        RF_Switch_To_Air();
    }
    else
    {
        RF_Switch_To_Cable();
    }
    #endif
}

BYTE msAPI_ATV_GetChannelMax(void)
{
    BYTE u8ProgramNumber;
    if(_bAntenna == ANT_AIR)
        u8ProgramNumber = (BYTE)(ATV_CHAN_AIR_MAX);
    else
        u8ProgramNumber = (BYTE)(ATV_CHAN_CATV_MAX);

    return u8ProgramNumber;
}

BYTE msAPI_ATV_GetChannelMin(void)
{
    BYTE u8ProgramNumber;
    if(_bAntenna == ANT_AIR)
        u8ProgramNumber = (BYTE)(ATV_CHAN_AIR_MIN);
    else
        u8ProgramNumber = (BYTE)(ATV_CHAN_CATV_MIN);

    return u8ProgramNumber;
}

