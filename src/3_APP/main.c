/*********************************************************************
 * @file        item.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
// ********************************************************************
// *                      Defines
// ******************************************************************** 

// ********************************************************************
// *                      Prototypes
// ********************************************************************
    
// ********************************************************************
// *                      Variables
// ********************************************************************

//********************************************************************************
//                      main
//********************************************************************************
int main(void)
{
    // code running once
    APPSYS_Init();

    while (True)
    {
        // code running every APPSYS_ELAPSED_TIME_CYCLIC ms
        APPSYS_Cyclic();
    }
    return 0;
}
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
