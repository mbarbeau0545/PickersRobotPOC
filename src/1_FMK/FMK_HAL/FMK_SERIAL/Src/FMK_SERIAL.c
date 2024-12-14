/*********************************************************************
 * @file        FMK_SERIAL.c
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    FMKSRL_SERIAL_LINE_CFG_UART = 0x00, 
    FMKSRL_SERIAL_LINE_CFG_USART,

    FMKSRL_SERIAL_LINE_CFG_NB,
} t_eFMKSRL_SerialLineCfg;

typedef enum 
{
    FMKSRL_SERIAL_LINE_1 = 0x00,
    FMKSRL_SERIAL_LINE_2,
    FMKSRL_SERIAL_LINE_3,
} t_eFMKSRL_SerialLine;

typedef union 
{
    UART_HandleTypeDef  UartIstc_s;
    USART_HandleTypeDef UsartIstc_s;
} t_uFMKSRL_SerialType;

typedef struct 
{
    t_uFMKSRL_SerialType *bspInit_pu;
    t_eFMKSRL_SerialLineCfg bspSrlCfg_e;
    t_bool isLineConfigured;
} t_sFMKSRL_SerialInfo;

USART_HandleTypeDef g_bspUsart_s[3];
UART_HandleTypeDef g_bspUart_s[3];
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//

t_sFMKSRL_SerialInfo g_SerialInfo_s;
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
typedef HAL_StatusTypeDef (t_cbFMKSRL_bspSerialInit)(void * bspHandle);
typedef HAL_StatusTypeDef (t_cbFMKSRL_bspSerialDeInit)(void * bspHandle);

typedef struct 
{
    t_cbFMKSRL_bspSerialInit   *bspSrlInit;
    t_cbFMKSRL_bspSerialDeInit *bspSrlDeInit;
} t_sFMKSRl_BspSrlFunc;
// ********************************************************************
// *                      Prototypes
// ********************************************************************
// Tableau de fonctions pour l'initialisation
// Déclaration des fonctions d'initialisation pour UART et USART
t_sFMKSRl_BspSrlFunc bspSerialInit_apf[FMKSRL_SERIAL_LINE_CFG_NB] = {
    {(HAL_StatusTypeDef (*)(void *))HAL_UART_Init, (HAL_StatusTypeDef (*)(void *))HAL_UART_DeInit},
    {(HAL_StatusTypeDef (*)(void *))HAL_USART_Init, (HAL_StatusTypeDef (*)(void *))HAL_USART_DeInit}
    
      // Cast pour USART
};

t_eReturnCode s_FMKSRL_Init(void);
// ********************************************************************
// *                      Variables
// ********************************************************************
t_eReturnCode s_FMKSRL_Init(void)
{
    // Sélection de la configuration de la ligne série (UART ou USART)
    t_eFMKSRL_SerialLineCfg idxInit_e = g_SerialInfo_s.bspSrlCfg_e;

    // Initialisation du handle en fonction de la configuration
    if (idxInit_e == FMKSRL_SERIAL_LINE_CFG_UART) {
        // Si UART est sélectionné
        g_SerialInfo_s.bspInit_pu = (t_uFMKSRL_SerialType *)&g_bspUart_s[0];
    } else {
        // Si USART est sélectionné
        g_SerialInfo_s.bspInit_pu = (t_uFMKSRL_SerialType *)&g_bspUsart_s[0];
    }

    // Appel de la fonction d'initialisation appropriée (UART ou USART)
    HAL_StatusTypeDef status = bspSerialInit_apf[idxInit_e].bspSrlInit(g_SerialInfo_s.bspInit_pu);

    return RC_OK;
}
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
           
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
