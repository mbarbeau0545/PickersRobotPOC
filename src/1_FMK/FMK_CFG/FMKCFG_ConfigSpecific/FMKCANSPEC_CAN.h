
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCAN_ConfigPublic.h"
#include "stm32g4xx_hal.h"


#ifdef FMKCAN_PROTOCOL_CAN


typedef struct
{
    uint16_t vv;
    uint16_t bb;
} CAN_HandleTypeDef;

typedef struct
{
    CAN_HandleTypeDef bspNode_s;
    bool isConfigured_b;
} t_sFMKCAN_NodeInfo;

#endif