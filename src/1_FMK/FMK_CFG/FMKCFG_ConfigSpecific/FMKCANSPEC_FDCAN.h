
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCAN_ConfigPublic.h"
#include "stm32g4xx_hal.h"


#ifdef FMKCAN_PROTOCOL_FDCAN

typedef struct
{
    FDCAN_HandleTypeDef bspNode_s;
    bool isConfigured_b;
} t_sFMKCAN_NodeInfo;

#endif