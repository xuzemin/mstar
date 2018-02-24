
#ifndef   _Si21XXC_PROPERTY_DUMP_H_
#define   _Si21XXC_PROPERTY_DUMP_H_

#if defined( __cplusplus )
extern "C"                     /* Use "C" external linkage                  */
{
#endif
unsigned char Si21XXC_L1_DUMP_TUNER_STATUS(L1_Si21XXC_Context *api,unsigned char   mode,
                                               unsigned long   freq,unsigned char cmdByteBuffer[]);

unsigned char DumpProperty(L1_Si21XXC_Context *api,int prop,unsigned char cmdByteBuffer[]);
unsigned char Si21XXC_DumpProperties(L1_Si21XXC_Context *api);
unsigned char Si21XXC_DumpAllToMem(L1_Si21XXC_Context *api,unsigned long *ddrTunerDataAddr, unsigned long *ddrTunerDataSize );
unsigned char Si21XXC_RestoreFromMem(L1_Si21XXC_Context *api);

#if defined( __cplusplus )
}
#endif
#endif /*_Si21XXC_PROPERTY_DUMP_H_                     */
