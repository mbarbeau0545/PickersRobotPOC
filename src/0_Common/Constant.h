/*****************************************************************************
 * @file        Constant.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
#include "TypeCommon.h"
#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

    #define CST_MHZ_TO_HZ           ((t_uint32)1000000)             // Number of Hz in 1MHz
    #define CST_MAX_UINT_16BIT      ((t_uint32)0xFFFF)              // Max Number 32 bits
    #define CST_MAX_UINT_32BIT      ((t_uint32)0xFFFFFFFF)          // Max Number 16 bits
    #define CST_MSEC_TO_SEC         ((t_uint32)1000)
    #ifndef M_PI
        #define M_PI ((t_float32)3.14159265358979323846)
    #endif
#endif //CONSTANT_H_INCLUDED