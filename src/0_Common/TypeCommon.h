/*****************************************************************************
 * @file        TypeCommon.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */


#ifndef TYPECOMMON_H_INCLUDED
#define TYPECOMMON_H_INCLUDED

    #define true	      ((t_uint8)1)
    #define false	      ((t_uint8)0)
    #define True          ((t_uint8)1)
    #define False         ((t_uint8)0)
    #define NULL_FONCTION ((void *)0)

    #ifndef NULL
        #define NULL ((void *)0)
    #endif // NULL
    /**
     * @brief Get a bit from a flag macro
     */
    #ifndef GETBIT
        #define GETBIT(flag, bit) ((flag >> (bit)) & 1)
    #endif
    /**
     * @brief Set a bit in a 16 bit flag
     */
    #ifndef SETBIT_16B
        #define SETBIT_16B(flag, bit) ((flag) |= (t_uint16)1 << (bit))
    #endif
    /**
     * @brief Set a bit in a 32 bit flag
     */
    #ifndef SETBIT_32B
        #define SETBIT_32B(flag, bit) ((flag) |= (t_uint32)1 << (bit))
    #endif
    /**
     * @brief Reset a bit in a 16 bit flag
     */
    #ifndef RESETBIT_16B
        #define RESETBIT_16B(flag, bit) ((flag) &= ~(t_uint16)1 << (bit))
    #endif
    /**
     * @brief Reset a bit in a 32 bit flag
     */
    #ifndef RESETBIT_32B
        #define RESETBIT_32B(flag, bit) ((flag) &= ~(t_uint32)1 << (bit))
    #endif
    /**
     * @brief Bit in a 16 bit flag is set
     */
    #ifndef BIT_IS_SET_16B 
        #define BIT_IS_SET_16B ((t_uint16)1)
    #endif
    /**
     * @brief Bit in a 16 bit flag is reset
     */
    #ifndef BIT_IS_RESET_16B 
        #define BIT_IS_RESET_16B ((t_uint16)0)
    #endif
    /**
     * @brief Bit in a 32 bit flag is set
     */
    #ifndef BIT_IS_SET_32B 
        #define BIT_IS_SET_32B ((t_uint32)1)
    #endif
    /**
     * @brief Bit in a 32 bit flag is reset
     */
     #ifndef BIT_IS_RESET_32B 
        #define BIT_IS_RESET_32B ((t_uint32)0)
    #endif

    /**
     * @brief Bit in a 16 bit flag is set
     */
    #ifndef BIT_IS_SET_8B 
        #define BIT_IS_SET_8B ((t_uint8)1)
    #endif
    /**
     * @brief Bit in a 16 bit flag is reset
     */
    #ifndef BIT_IS_RESET_8B 
        #define BIT_IS_RESET_8B ((t_uint8)0)
    #endif
     #ifndef SETBIT_8B
        #define SETBIT_8B(flag, bit) ((flag) |= (t_uint8)1 << (bit))
    #endif
    /**
     * @brief Enum for return function
     */
    typedef enum __t_eReturnCode
    {
        RC_ERROR_INSTANCE_NOT_INITIALIZED = -18, /**< The Instance or Structure should be initialized before use the function */
        RC_ERROR_ALREADY_CONFIGURED = -17,        /**< The operation is not accepted because the instance has already been configured */
        RC_ERROR_COPY_FAILED = -16,               /**< The copy between two variables failed */
        RC_ERROR_PTR_NULL = -15,                  /**< At least one of the pointers is null */
        RC_ERROR_PARAM_INVALID = -14,             /**< At least one of the parameters is not in the allowed range */
        RC_ERROR_PARAM_NOT_SUPPORTED = -13,       /**< At least one of the parameters is not supported */
        RC_ERROR_WRONG_STATE = -12,               /**< The function cannot succeed in the current state */
        RC_ERROR_MODULE_NOT_INITIALIZED = -11,    /**< The module must be initialized before calling the function */
        RC_ERROR_MISSING_CONFIG = -10,            /**< Some configuration is missing */
        RC_ERROR_WRONG_CONFIG = -9,               /**< The configuration is not consistent */
        RC_ERROR_UNDEFINED = -8,                  /**< An undefined error has occurred */
        RC_ERROR_NOT_SUPPORTED = -7,              /**< The function is not supported */
        RC_ERROR_BUSY = -6,                       /**< Process busy, task not accepted */
        RC_ERROR_TIMEOUT = -5,                    /**< The operation timed out */
        RC_ERROR_NOT_ALLOWED = -4,                /**< Not allowed to perform the requested operation */
        RC_ERROR_WRONG_RESULT = -3,               /**< The operation has succeeded, but the result is incorrect */
        RC_ERROR_LIMIT_REACHED = -2,              /**< The operation cannot be done because a limit has been reached */
        RC_ERROR_NOT_ENOUGH_MEMORY = -1,          /**< The operation cannot be done because there is not enough memory */
        RC_OK = 0,                                /**< Process finished successfully */
        RC_WARNING_NO_OPERATION = 1,              /**< No error occurred, but there was no operation to execute */
        RC_WARNING_BUSY = 2,                      /**< The operation is not accepted but the program could continue */
        RC_WARNING_WRONG_CONFIG = 3,              /**< The configuration is not consistent */
        RC_WARNING_MISSING_CONFIG = 4,            /**< Some configuration is missing */
        RC_WARNING_INIT_PROBLEM = 5,              /**< No initialization done, process performed as default mode */
        RC_WARNING_PENDING = 6,                   /**< Operation accepted and started, but the result is not immediate */
        RC_WARNING_NOT_ALLOWED = 7,               /**< Not allowed to perform the requested operation */
        RC_WARNING_LIMIT_REACHED = 8,             /**< The operation cannot be done because a limit has been reached */
        RC_WARNING_WRONG_RESULT = 9,              /**< The operation has succeeded, but the result is incorrect */
        RC_WARNING_MEM_FAILED = 10                /**< The operation to copy an element has failed */
    } t_eReturnCode;
    
    /**
     * @brief Enum for Cyclic function management
     */
    typedef enum __t_eCyclicModState
    {
        STATE_CYCLIC_CFG = 0x00U,     /**< The module is making configuration to run properly */
        STATE_CYCLIC_PREOPE,          /**< The module needs to make actions before the operational state */
        STATE_CYCLIC_OPE,             /**< The module performs operational cyclic action */
        STATE_CYCLIC_BUSY,            /**< The module is busy doing other things, cyclic operations are not executed */
        STATE_CYCLIC_WAITING,         /**< The module is waiting ready to operate and waiting for a system signal */
        STATE_CYCLIC_ERROR            /**< The module is in error state, Deprecated mode */
    } t_eCyclicModState;

    typedef unsigned char t_bool;   /**< Boolean type */
    typedef unsigned char t_uint8;  /**< Unsigned 8-bit type */
    typedef signed char t_sint8;    /**< Signed 8-bit type */
    typedef unsigned short t_uint16; /**< Unsigned 16-bit type */
    typedef signed short t_sint16;   /**< Signed 16-bit type */
    typedef unsigned long t_uint32;  /**< Unsigned 32-bit type */
    typedef signed long t_sint32;    /**< Signed 32-bit type */
    typedef float t_float32;         /**< 32-bit float type */
    typedef char t_char;             /**< Character type */
    ;
    /* 0x000000FFUL*/
    // bit management 
    #define Mu8ExtractByte0fromU16 (Mu16Value)     (t_uint8)((t_uint16)(Mu16Value)        )
    #define Mu8ExtractByte1fromU16 (Mu16Value)     (t_uint8)((t_uint16)(Mu16Value) >> 8   )
    
    #define Mu8ExtractByte0fromU32 (Mu32Value)     (t_uint8)((t_uint32)(Mu32Value)        )
    #define Mu8ExtractByte1fromU32 (Mu32Value)     (t_uint8)((t_uint32)(Mu32Value) >> 8   )
    #define Mu8ExtractByte2fromU32 (Mu32Value)     (t_uint8)((t_uint32)(Mu32Value) >> 16  )
    #define Mu8ExtractByte3fromU32 (Mu32Value)     (t_uint8)((t_uint32)(Mu32Value) >> 24  )
    
    #define Ms8ExtractByte0fromU16 (Ms16Value)     (t_sint8)((t_sint16)(Ms16Value)        )  
    #define Ms8ExtractByte1fromU16 (Ms16Value)     (t_sint8)((t_sint16)(Ms16Value) >> 8   )  
    
    #define Ms8ExtractByte0fromU32 (Ms32Value)     (t_sint8)((t_sint32)(Ms32Value)        )
    #define Ms8ExtractByte1fromU32 (Ms32Value)     (t_sint8)((t_sint32)(Ms32Value) >> 8   )
    #define Ms8ExtractByte2fromU32 (Ms32Value)     (t_sint8)((t_sint32)(Ms32Value) >> 16  )
    #define Ms8ExtractByte3fromU32 (Ms32Value)     (t_sint8)((t_sint32)(Ms32Value) >> 24  )
    

    #define Mu16BuildFromByte (Mu8ValueB0, Mu8ValueB1) \
    (((t_uint16)(Mu8ValueB0))            /* 0x00FFUL*/ | \
    (((t_uint16)(Mu8ValueB1)) << 8)     /* 0xFF00UL*/   )



    #define Ms32BuildFromByte (Ms8ValueB0, Ms8ValueB1, Ms8ValueB2, Ms8ValueB3) \
    (((t_sint32)(Ms8ValueB0)          )       /* 0x000000FFUL*/ | \
    ((t_sint32)(Ms8ValueB1) << 8     )       /* 0x0000FF00UL*/ | \
    ((t_sint32)(Ms8ValueB2) << 16    )       /* 0x00FF0000UL*/ | \
    ((t_sint32)(Ms8ValueB3) << 24    )       /* 0xFF000000UL*/ )


    #define Ms16BuildFromByte (Ms8ValueB0, Ms8ValueB1)  \
    (((t_sint16)(Ms8ValueB0))            /* 0x00FFUL*/ | \
    (((t_sint16)(Ms8ValueB1)) << 8   )      /* 0xFF00UL*/)

    #define Mu32BuildFromByte (Mu8ValueB0, Mu8ValueB1, Mu8ValueB2, Mu8ValueB3) \
    (((t_uint32)(Mu8ValueB0)         )       /* 0x000000FFUL*/ | \
    ((t_uint32)(Mu8ValueB1) << 8     )       /* 0x0000FF00UL*/ | \
    ((t_uint32)(Mu8ValueB2) << 16    )       /* 0x00FF0000UL*/ | \
    ((t_uint32)(Mu8ValueB3) << 24    )       /* 0xFF000000UL*/)
    
#endif //TYPECOMMON_H_INCLUDED