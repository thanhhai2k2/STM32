/* File name: stm32f401re_syscfg.c
 *
 * Description: API for SYSCFG
 *
 * Last Changed By:  $Author: $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $April 15, 2022
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "stm32f401re_rcc.h"
#include "stm32f401re_syscfg.h"
#include "typedefs.h"

/******************************************************************************/
/*                     PRIVATE TYPES and DEFINITIONS                         */
/******************************************************************************/
/** @defgroup SYSCFG 
  * @brief SYSCFG driver modules
  * @{
  */ 
/* ------------ RCC registers bit address in the alias region ----------- */
#define SYSCFG_OFFSET             (SYSCFG_BASE - PERIPH_BASE)
/* ---  MEMRMP Register ---*/ 
/* Alias word address of UFB_MODE bit */ 
#define MEMRMP_OFFSET             SYSCFG_OFFSET 
#define UFB_MODE_BitNumber        ((u8_t)0x8) 
#define UFB_MODE_BB               (PERIPH_BB_BASE + (MEMRMP_OFFSET * 32) + (UFB_MODE_BitNumber * 4)) 
    
/* ---  PMC Register ---*/ 
/* Alias word address of MII_RMII_SEL bit */ 
#define PMC_OFFSET                (SYSCFG_OFFSET + 0x04) 
#define MII_RMII_SEL_BitNumber    ((u8_t)0x17) 
#define PMC_MII_RMII_SEL_BB       (PERIPH_BB_BASE + (PMC_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4)) 
    
/* ---  CMPCR Register ---*/ 
/* Alias word address of CMP_PD bit */ 
#define CMPCR_OFFSET              (SYSCFG_OFFSET + 0x20) 
#define CMP_PD_BitNumber          ((u8_t)0x00) 
#define CMPCR_CMP_PD_BB           (PERIPH_BB_BASE + (CMPCR_OFFSET * 32) + (CMP_PD_BitNumber * 4)) 

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

/** @defgroup SYSCFG_Private_Functions
  * @{
  */ 

/**
  * @brief  Deinitializes the Alternate Functions (remap and EXTI configuration)
  *   registers to their default reset values.
  * @param  None
  * @retval None
  */
void SYSCFG_DeInit(void)
{
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);
   RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, DISABLE);
}

/**
  * @brief  Changes the mapping of the specified pin.
  * @param  SYSCFG_Memory: selects the memory remapping.
  *         This parameter can be one of the following values:
  *            @arg SYSCFG_MemoryRemap_Flash:       Main Flash memory mapped at 0x00000000  
  *            @arg SYSCFG_MemoryRemap_SystemFlash: System Flash memory mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_FSMC:        FSMC (Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000 for STM32F405xx/407xx, STM32F415xx/417xx and STM32F413_423xx devices. 
  *            @arg SYSCFG_MemoryRemap_FMC:         FMC (Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000 for STM32F42xxx/43xxx devices. 
  *            @arg SYSCFG_MemoryRemap_ExtMEM:      External Memory mapped at 0x00000000 for STM32F446xx/STM32F469_479xx devices. 
  *            @arg SYSCFG_MemoryRemap_SRAM:        Embedded SRAM (112kB) mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SDRAM:       FMC (External SDRAM)  mapped at 0x00000000 for STM32F42xxx/43xxx devices.            
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(u8_t SYSCFG_MemoryRemap)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_MEMORY_REMAP_CONFING(SYSCFG_MemoryRemap));

  SYSCFG->MEMRMP = SYSCFG_MemoryRemap;
}

/**
  * @brief  Enables or disables the Internal FLASH Bank Swapping.
  *   
  * @note   This function can be used only for STM32F42xxx/43xxx devices. 
  *
  * @param  NewState: new state of Internal FLASH Bank swapping.
  *          This parameter can be one of the following values:
  *            @arg ENABLE: Flash Bank2 mapped at 0x08000000 (and aliased @0x00000000) 
  *                         and Flash Bank1 mapped at 0x08100000 (and aliased at 0x00100000)   
  *            @arg DISABLE:(the default state) Flash Bank1 mapped at 0x08000000 (and aliased @0x0000 0000) 
                            and Flash Bank2 mapped at 0x08100000 (and aliased at 0x00100000)  
  * @retval None
  */
void SYSCFG_MemorySwappingBank(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) UFB_MODE_BB = (u32_t)NewState;
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx : selects the GPIO port to be used as source for
  *          EXTI lines where x can be (A..K) for STM32F42xxx/43xxx devices, (A..I) 
  *          for STM32F405xx/407xx and STM32F415xx/417xx devices or (A, B, C, D and H)
  *          for STM32401xx devices.  
  *            
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  *           This parameter can be EXTI_PinSourcex where x can be (0..15, except
  *           for EXTI_PortSourceGPIOI x can be (0..11) for STM32F405xx/407xx
  *           and STM32F405xx/407xx devices and for EXTI_PortSourceGPIOK x can   
  *           be (0..7) for STM32F42xxx/43xxx devices. 
  *             
  * @retval None
  */
void SYSCFG_EXTILineConfig(u8_t EXTI_PortSourceGPIOx, u8_t EXTI_PinSourcex)
{
  u32_t tmp = 0x00;

  /* Check the parameters */
  assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
  assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));

  tmp = ((u32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (u8_t)0x03));
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((u32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (u8_t)0x03)));
}


/**
  * @brief  Enables or disables the I/O Compensation Cell.
  * @note   The I/O compensation cell can be used only when the device supply
  *         voltage ranges from 2.4 to 3.6 V.  
  * @param  NewState: new state of the I/O Compensation Cell.
  *          This parameter can be one of the following values:
  *            @arg ENABLE: I/O compensation cell enabled  
  *            @arg DISABLE: I/O compensation cell power-down mode  
  * @retval None
  */
void SYSCFG_CompensationCellCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CMPCR_CMP_PD_BB = (u32_t)NewState;
}

/**
  * @brief  Checks whether the I/O Compensation Cell ready flag is set or not.
  * @param  None
  * @retval The new state of the I/O Compensation Cell ready flag (SET or RESET)
  */
FlagStatus SYSCFG_GetCompensationCellStatus(void)
{
  FlagStatus bitstatus = RESET;
    
  if ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY ) != (u32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}
/*****END OF FILE****/
