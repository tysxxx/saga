#ifndef __TLS1401_H
#define __TLS1401_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef TLS1401_CONTROL
	#define TLS1401_EXTERN	extern
#else
	#define TLS1401_EXTERN 
#endif
	
#include "global.h"

//TSL1401
    //SI
#define TSL1401_SI_PIN									GPIO_Pin_2
#define TSL1401_SI_GPIO_PORT                            GPIOC
#define TSL1401_SI_SET()                                GPIO_SetBits(TSL1401_SI_GPIO_PORT, TSL1401_SI_PIN)
#define TSL1401_SI_RESET()                              GPIO_ResetBits(TSL1401_SI_GPIO_PORT, TSL1401_SI_PIN)
    //CLK
#define TSL1401_CLK_PIN									GPIO_Pin_1
#define TSL1401_CLK_GPIO_PORT                           GPIOC
#define TSL1401_CLK_SET()                               GPIO_SetBits(TSL1401_CLK_GPIO_PORT, TSL1401_CLK_PIN)
#define TSL1401_CLK_RESET()                             GPIO_ResetBits(TSL1401_CLK_GPIO_PORT, TSL1401_CLK_PIN)   
 
#define TSL1401_GPIO_PORT   GPIOC      

#define TSL1401_SIZE 128
    
#define ABS(x) (((x) > 0) ? (x) : (-(x)))

typedef struct VALIDFLAG_T
{
    uint8_t startPos; //有效标记点的位置
    uint8_t width; //宽度
}VALIDFLAG_YTPE;

typedef struct HEIDIAN_T
{
    uint8_t pos[128]; //各黑点的位置
    uint8_t sum; //总黑点数目
    uint8_t num; //有效的连续黑点数目
    uint8_t startPos; //有效连续黑点起始位置
    uint8_t validPoint[2][128+1]; //最后一个用于存放数目
}HEIDIAN_YTPE;

typedef enum
{
    TSL1401_SAMPLE_START_FLAG,  //采集开始标志     
    TSL1401_SAMPLE_FINISH_FLAG, //采集完成标志
}TSL1401_SAMPLE_FLAG; 

//TLS1401_EXTERN uint8_t  oldAverage;
//TLS1401_EXTERN uint8_t  max[TSL1401_SIZE];
//TLS1401_EXTERN uint8_t  avg[TSL1401_SIZE];
TLS1401_EXTERN uint8_t  tls1401DataBuf[TSL1401_SIZE];
//TLS1401_EXTERN uint8_t  tls1401DiffBuf[TSL1401_SIZE];
TLS1401_EXTERN uint8_t  tls1401BinBuf[TSL1401_SIZE];
TLS1401_EXTERN uint8_t  tls1401SampleBuf[TSL1401_SIZE];
//TLS1401_EXTERN TSL1401_SAMPLE_FLAG tsl1401SampleFlag;
//TLS1401_EXTERN TSL1401STATUS_TYPE tsl1401Status;
TLS1401_EXTERN VALIDFLAG_YTPE validFlagInfo;
TLS1401_EXTERN HEIDIAN_YTPE heiDian;
TLS1401_EXTERN BOOL f_sampleHandler;

void TSL1401_SI(uint8_t state);
void TSL1401_CLK(uint8_t state);
void TSL1401Init();
void TSL1401Sample(void);
void tsl1401Reset();
void tsl1401GetImg(void);
void maxvar(uint8_t *buf, uint16_t len, uint8_t maxval);
void abs_diff(uint8_t *dst,uint8_t *src,uint16_t len,uint8_t * maxval,uint8_t * avgval);
void bin(uint8_t *bin,uint8_t * img,uint8_t * difimg,uint16_t len,uint8_t maxdif);
void tsl1401Bin();
void filterBin(void);
void judgeValidFlag();
void adjustHandler(uint8_t* midPos);





















#ifdef __cplusplus
}
#endif
#endif
