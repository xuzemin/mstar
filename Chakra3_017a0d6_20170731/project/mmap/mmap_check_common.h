
#ifndef _MMAP_CHECK_COMMON_H_
#define _MMAP_CHECK_COMMON_H_


//==================================================================
#if (MEMORY_MAP == MMAP_128MB)
    #if( MIU_DRAM_LEN != 0x0008000000 )
        #error "MIU_DRAM_LEN != 0x0008000000"
    #endif

#elif (MEMORY_MAP == MMAP_64MB)
    #if( MIU_DRAM_LEN != 0x0004000000 )
        #error "MIU_DRAM_LEN != 0x0004000000"
    #endif
#elif (MEMORY_MAP == MMAP_128_128MB)
    #if( MIU_DRAM_LEN != 0x0010000000 )
        #error "MIU_DRAM_LEN != 0x0010000000"
    #endif
#elif (MEMORY_MAP == MMAP_128_256MB)
    #if( MIU_DRAM_LEN != 0x0018000000 )
        #error "MIU_DRAM_LEN != 0x0018000000"
    #endif

#endif

//==================================================================
// Check VDEC_BITSTREAM
#if( defined(VDEC_BITSTREAM_SD_ADR) )
    #if( VDEC_BITSTREAM_ADR != VDEC_BITSTREAM_SD_ADR )
        #error "VDEC_BITSTREAM_ADR != VDEC_BITSTREAM_SD_ADR"
    #endif
#endif

#if( defined(VDEC_BITSTREAM_SD_LEN) )
    #if( VDEC_BITSTREAM_SD_LEN != VDEC_BITSTREAM_LEN )
        #error "VDEC_BITSTREAM_SD_LEN != VDEC_BITSTREAM_LEN"
    #endif
#endif

//==================================================================
// Check VDEC_FRAMEBUFFER
#if( defined(VDEC_FRAMEBUFFER_SD_ADR) )
    #if( VDEC_FRAMEBUFFER_SD_ADR != VDEC_FRAMEBUFFER_ADR )
        #error "VDEC_FRAMEBUFFER_SD_ADR != VDEC_FRAMEBUFFER_ADR"
    #endif
#endif

//==================================================================

#define IS_BUF_IN_RANGE(a,x,y)  ( ((x) <= (a)) && ((a) < (y)) )

#define IS_BUF_OVERLAY(a,b,x,y) (\
      ( IS_BUF_IN_RANGE( (x),(a),(b) ) )\
    ||( IS_BUF_IN_RANGE( (y),(a),(b) ) )\
    ||( IS_BUF_IN_RANGE( (a),(x),(y) ) )\
    )


// Check PVR&MHEG Co-Buffer
#if( ENABLE_PVR && MHEG5_ENABLE )

    #define MHEG5_BUFFER_ADR_END        (MHEG5_BUFFER_ADR + MHEG5_BUFFER_LEN)
    #define PVR_WRITE_SDRAM_ADR_END     (PVR_WRITE_SDRAM_ADR + PVR_WRITE_SDRAM_LEN)
    #define PVR_WRITE_METADATA_ADR_END  (PVR_WRITE_METADATA_BUFFER_ADR + PVR_WRITE_METADATA_BUFFER_LEN)
    #define PVR_BROWSER_BUFFER_ADR_END  (PVR_BROWSER_BUFFER_ADR + PVR_BROWSER_BUFFER_LEN)


    // PVR_WRITE_SDRAM can't co-buffer with MHEG5_BUFFER
    #if( IS_BUF_OVERLAY(MHEG5_BUFFER_ADR, MHEG5_BUFFER_ADR_END, PVR_WRITE_SDRAM_ADR, PVR_WRITE_SDRAM_ADR_END) )
        #error "PVR_WRITE_SDRAM is overlay with MHEG5_BUFFER!!"
    #endif

    // PVR_WRITE_METADATA can't co-buffer with MHEG5_BUFFER
    #if( IS_BUF_OVERLAY(MHEG5_BUFFER_ADR, MHEG5_BUFFER_ADR_END, PVR_WRITE_METADATA_BUFFER_ADR, PVR_WRITE_METADATA_ADR_END) )
        #error "PVR_WRITE_METADATA is overlay with MHEG5_BUFFER!!"
    #endif

    // PVR_BROWSER_BUFFER can't co-buffer with MHEG5_BUFFER
    #if( IS_BUF_OVERLAY(MHEG5_BUFFER_ADR, MHEG5_BUFFER_ADR_END, PVR_BROWSER_BUFFER_ADR, PVR_BROWSER_BUFFER_ADR_END) )
        #error "PVR_BROWSER_BUFFER is overlay with MHEG5_BUFFER!!"
    #endif

#endif

//==================================================================
#endif // _MMAP_CHECK_COMMON_H_

