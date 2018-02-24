 



typedef enum {
  SR_44100 = 0,		 
  SR_32000 = 1,
  SR_24000 = 2,
  SR_22050 = 3,
  SR_16000 = 4,
  SR_12000 = 5,
  SR_11025 = 6,
  SR_8000  = 7
} SAMPLE_RATE_SEL;


int mst_rsrc_get_sram_size(int sample_rate_index, int inblock_size, int *outblock_size);
void* mst_rsrc_init (void *heap, SAMPLE_RATE_SEL sample_rate_index, int *delay); 
int mst_rsrc_process(void *  isrc, short * in, short *  out, int inputSize); 
int mst_rsrc_get_output_size(void *isrc, int inputSize);
int mst_rsrc_get_input_size(void *isrc, int outputSize);
 
