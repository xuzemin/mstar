/*
 *           Copyright 2012 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be 
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


///$Date: 2012-3-8 21:47 $
///
#ifndef IBlindScanAPI_h_h
	#define IBlindScanAPI_h_h

	#include "avl_dvbsx.h"
	#include "ITuner.h"
	#include "IBlindScan.h"

	#ifdef AVL_CPLUSPLUS
extern "C" {
	#endif

	/// 
	/// Defines the status of blind scan process.
	enum AVL_DVBSx_BlindScanAPI_Status
	{	
		AVL_DVBSx_BS_Status_Init = 0,							///< = 0 Indicates that the blind scan process is initializing the parameters.
		AVL_DVBSx_BS_Status_Start = 1,							///< = 1 Indicates that the blind scan process is starting to scan.
		AVL_DVBSx_BS_Status_Wait = 2,							///< = 2 Indicates that the blind scan process is waiting for the completion of scanning.
		AVL_DVBSx_BS_Status_Adjust = 3,							///< = 3 Indicates that the blind scan process is reading the channel info which have scanned out.
		AVL_DVBSx_BS_Status_User_Process = 4,					///< = 4 Indicates that the blind scan process is in custom code. Customer can add the callback function in this stage such as adding TP information to TP list or lock the TP for parsing PSI.
		AVL_DVBSx_BS_Status_Cancel = 5,							///< = 5 Indicates that the blind scan process is cancelled or the blind scan have completed.
		AVL_DVBSx_BS_Status_Exit = 6							///< = 6 Indicates that the blind scan process have ended.
	};

	/// 
	/// Defines the blind scan mode.
	enum AVL_DVBSx_BlindScanAPI_Mode
	{
		AVL_DVBSx_BS_Fast_Mode = 0,								///< = 0 Indicates that the blind scan frequency step is automatic settings.
		AVL_DVBSx_BS_Slow_Mode = 1								///< = 1 Indicates that the blind scan frequency step can be setting by user. The default value is 10MHz.
	};

	/// 
	/// Stores the blind scan configuration parameters.
	struct AVL_DVBSx_BlindScanAPI_Setting
	{
		AVL_uint16  m_uiScan_Min_Symbolrate_MHz;				///< The minimum symbol rate to be scanned in units of MHz. The minimum value is 1000 kHz.
		AVL_uint16  m_uiScan_Max_Symbolrate_MHz;				///< The maximum symbol rate to be scanned in units of MHz. The maximum value is 45000 kHz.
		AVL_uint16  m_uiScan_Start_Freq_MHz;					///< The start scan frequency in units of MHz. The minimum value depends on the tuner specification.
		AVL_uint16  m_uiScan_Stop_Freq_MHz;						///< The stop scan frequency in units of MHz. The maximum value depends on the tuner specification.
		AVL_uint16  m_uiScan_Next_Freq_100KHz;					///< The start frequency of the next scan in units of 100kHz.
		AVL_uint16  m_uiScan_Progress_Per;						///< The percentage completion of the blind scan process. A value of 100 indicates that the blind scan is finished.
		AVL_uint16  m_uiScan_Bind_No;							///< The number of completion of the blind scan procedure.
		AVL_uint16  m_uiTuner_MaxLPF_100kHz;					///< The max low pass filter bandwidth of the tuner.
		AVL_uint16  m_uiScan_Center_Freq_Step_100KHz;			///< The blind scan frequency step. The value is only valid when BS_Mode set to AVL_DVBSx_BS_Slow_Mode and would be ignored when BS_Mode set to AVL_DVBSx_BS_Fast_Mode.
		AVL_uint16  m_uiScaning_Flag;							///< The flag whether in blind scan progress.
		enum AVL_DVBSx_BlindScanAPI_Mode  BS_Mode;				///< The blind scan mode. \sa ::AVL_DVBSx_IBlindScanAPI_Mode.
		
		AVL_uint16  m_uiChannelCount;							///< The number of channels detected thus far by the blind scan operation.  The Availink device can store up to 120 detected channels.
		struct AVL_DVBSx_Channel  channels[128];				///< Stores the channel information that all scan out results. 
		struct AVL_DVBSx_Channel  channels_Temp[16];			///< Stores the channel information temporarily that scan out results by the blind scan procedure.

		struct AVL_DVBSx_BlindScanPara  bsPara;					///< Stores the blind scan parameters each blind scan procedure.
		struct AVL_DVBSx_BlindScanInfo  bsInfo;					///< Stores the blind scan status information each blind scan procedure.
		enum AVL_DVBSx_SpectrumPolarity  m_eSpectrumMode;		///< Defines the device spectrum polarity setting.  \sa ::AVL_DVBSx_SpectrumPolarity.
	};

	/// Initializes the blind scan parameters.
	/// 
	/// @param pBSsetting  A pointer to the blind scan configuration parameters.
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK after all the member of the pBSsetting is configured with the default value.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Initialize(struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting );

	/// Configures the device to indicate whether the tuner inverts the received signal spectrum.
	/// 
	/// @param pBSsetting A pointer to the ::AVL_DVBSx_IBlindScanAPI_Setting object for which the spectrum polarity is being configured.
	/// @param SpectrumMode Indicates whether the tuner inverts the received signal spectrum. 
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK after the spectrum polarity is configured with the desired value.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetSpectrumMode(struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting, enum AVL_DVBSx_SpectrumPolarity SpectrumMode);

	/// Sets the blind scan mode.
	/// 
	/// @param pBSsetting A Pointer to the ::AVL_DVBSx_IBlindScanAPI_Setting for which the blind scan mode is being retrieved.
	/// @param Scan_Mode The blind scan mode on which the device is being placed.
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK after the blind scan mode has been retrieved.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetScanMode(struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting, enum AVL_DVBSx_BlindScanAPI_Mode Scan_Mode);

	/// Sets the start frequency and stop frequency.
	/// 
	/// @param pBSsetting A Pointer to the ::AVL_DVBSx_IBlindScanAPI_Setting for which the frequency range is being retrieved.
	/// @param StartFreq_MHz The start scan frequency in units of MHz.
	/// @param EndFreq_MHz The stop scan frequency in units of MHz.
	///
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK after the frequency range has been retrieved.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetFreqRange(struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting, AVL_uint16 StartFreq_MHz, AVL_uint16 EndFreq_MHz );

	/// Sets the max low pass filter bandwidth of the tuner.
	/// 
	/// @param pBSsetting A Pointer to the ::AVL_DVBSx_IBlindScanAPI_Setting for which the max LPF is being retrieved.
	/// @param MaxLPF The tuner LPF bandwidth setting in units of 100 kHz.
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK after the max LPF has been retrieved.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetMaxLPF(struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting, AVL_uint16 MaxLPF );

	/// Performs a blind scan operation. Call the function ::AVL_DVBSx_IBlindScan_GetScanStatus to check the status of the blind scan operation.
	/// 
	/// @param pAVLChip A pointer to the ::AVL_DVBSx_Chip object on which blind scan is being performed.
	/// @param pTuner A Pointer to the ::AVL_Tuner object on which to lock tuner at a proper frequency point.
	/// @param pBSsetting A Pointer to blind scan configuration parameters.
	///
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK if the scan command is successfully sent to the Availink device.
	/// Return ::AVL_DVBSx_EC_I2CFail if there is an I2C communication problem.
	/// Return ::AVL_DVBSx_EC_Running if the scan command could not be sent because the Availink device is still processing a previous command.
	/// Return ::AVL_DVBSx_EC_GeneralFail if the device is not in the blind scan functional mode or the parameters are wrong.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Start(struct AVL_DVBSx_Chip *pAVLChip, struct AVL_Tuner *pTuner, struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting );

	/// Queries the blind scan status.
	/// 
	/// @param pAVLChip A pointer to Pointer to the ::AVL_DVBSx_Chip object for which the blind scan status is being queried.
	/// @param pBSsetting A Pointer to a variable in which to store the blind scan status.
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK if the blind scan status has been retrieved.
	/// Return ::AVL_DVBSx_EC_I2CFail if there is an I2C communication problem.
	/// Return ::AVL_DVBSx_EC_Running if the scan command could not be sent because the Availink device is still processing a previous command.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_GetCurrentScanStatus(struct AVL_DVBSx_Chip *pAVLChip ,struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting );

	/// Reads the channels found during a particular scan from the firmware and stores the new channels found in the scan and filters out the duplicate ones.
	/// 
	/// @param pAVLChip A pointer to the AVL_DVBSx_Chip object on which read channel operation is being performed.
	/// @param pBSsetting A pointer to a structure that stores the new channels found in the scan.
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK if the blind scan status has been retrieved.
	/// Return ::AVL_DVBSx_EC_I2CFail if there is an I2C communication problem.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Adjust(struct AVL_DVBSx_Chip *pAVLChip ,struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting );

	/// Stops blind scan process.
	/// 
	/// @param pAVLChip A pointer to the ::AVL_DVBSx_Chip object on which blind scan is being stopped.
	/// @param pBSsetting A Pointer to blind scan configuration parameters.
	/// 
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK if the functional mode has been set. 	
	/// Return ::AVL_DVBSx_EC_I2CFail if there is an I2C communication problem.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Exit(struct AVL_DVBSx_Chip *pAVLChip, struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting );

	/// Gets the progress of blind scan process based on current scan step's start frequency.
	/// 
	/// @param pBSsetting A pointer to the ::AVL_DVBSx_IBlindScanAPI_Setting object for which store the blind scan process.
	/// 
	/// @return ::AVL_uint16, 
	/// Return ::The progress of blind scan process based on current scan step's start frequency.
	AVL_uint16 AVL_DVBSx_IBlindscanAPI_GetProgress(struct AVL_DVBSx_BlindScanAPI_Setting *pBSsetting );

	/// Gets the num of  TP found in current  blind scan process .
	/// 
	/// @param pBSsetting A pointer to the ::AVL_DVBSx_IBlindScanAPI_Setting object for which store the blind scan process.
	/// 
	/// @return ::AVL_uint16, 
	/// Return ::he num of  TP found in current  blind scan process.
	AVL_uint16 AVL_DVBSx_IBlindscanAPI_GetTPCount(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting);

	/// Gets the paramenters of TP found in current blindscan process
	/// 
	/// @param pBSsetting .A Pointer to blind scan configuration parameters.
	/// @param uiStartIndex.The blind scan results are stored in an array internal to the Availink device. This parameter tells the function the array index at which to retrieve the results.
	/// @param uiNum. The number of channel results to be retrieved.  The function updates this value with the actual number of channel results that are reported.
	/// @pChannel. A Pointer to an object in which the blind scan results are to be stored.
	///
	/// @return ::AVL_DVBSx_ErrorCode, 
	/// Return ::AVL_DVBSx_EC_OK if the scan command is successfully sent to the Availink device.
	/// Return ::AVL_DVBSx_EC_GeneralFail if uiStartIndex is large than total TP real found in current blindscan process.
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindscanAPI_GetTP(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting, AVL_uint16 uiStartIndex, AVL_puint16 uiNum, struct AVL_DVBSx_Channel *pChannel);

	#ifdef AVL_CPLUSPLUS
}
	#endif

#endif


