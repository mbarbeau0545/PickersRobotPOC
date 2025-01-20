/**
 * @file        LIBRamp.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef LIBRAMP_H_INCLUDED
#define LIBRAMP_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "./LIBRamp ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        LIBRAMP_MODE_LINEAR = 0x00,              /**< Compute Ramp based on linear calculation */
        LIBRAMP_MODE_EXPONENTIAL,               /**< Compute Ramp based on exponentional calculation */
        LIBRAMP_MODE_SIGMOIDALE,
        LIBRAMP_MODE_NB
    } t_eLIBRamp_Mode;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_float32 maxSlope_u32;             /**< Max slope allow for a step */
        t_uint32 updatePeriod_u32;          /**< Update period imposed by sotware, for instance in the framework it is APPSYS_ELAPSED_TIME_CYCLIC*/
        
    } t_sLIBRamp_LinearCfg;

    typedef struct 
    {
        t_float32 expFactor_f32;            /**< Exponential factor */
        t_float32 smoothingFactor_f32;      /**< Whenever this value is passed, target is the value return */

    } t_sLIBRamp_ExpCfg;

    typedef struct 
    {
        t_float32 midPoint_f32;             /**< Value where the signal will have the higher slope
                                                    To calculate it, take your target */

    } t_sLIBRamp_SigmoidaleCfg;

    typedef union 
    {
        t_sLIBRamp_LinearCfg        linearCfg_s;
        t_sLIBRamp_ExpCfg           expCfg_s;
        t_sLIBRamp_SigmoidaleCfg    sigmoidaleCfg_s;
    } t_uLIBRamp_RampCfg;

    typedef struct 
    {
        t_eLIBRamp_Mode rampMode_e;       /**< Specifies the mode of the ramp.  */
        t_float32 startValue_f32;
        t_uint32 maxDuration_u32;         /**< the maximum rate of change allowed for the ramp value. */
        t_uLIBRamp_RampCfg rampModeCfg_u;
    } t_sLIBRamp_RampCfg;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBRamp_Init(t_sLIBRamp_RampCfg f_rampCfg_s, t_uint8 *f_rampID_pu8);
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBRamp_Compute(  t_uint8 f_rampID_u8, 
                                    t_float32 f_rawValue_f32,
                                    t_float32 * f_computeValue_pf32);


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // LIBRAMP_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[in]
 *	 
 *
 *
 */
