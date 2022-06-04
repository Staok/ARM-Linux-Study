/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MCIMX6Y2xxx08
package_id: MCIMX6Y2CVM08
mcu_data: i_mx_2_0
processor_version: 9.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "iomux_config.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'false', coreID: ca7}
- pin_list:
  - {pin_num: P10, peripheral: GPIO5, signal: 'gpio_io, 3', pin_signal: SNVS_TAMPER3, direction: OUTPUT, HYS: ENABLED}
  - {pin_num: L17, peripheral: GPIO1, signal: 'gpio_io, 3', pin_signal: GPIO1_IO03, direction: OUTPUT, HYS: ENABLED, DSE: OHM_60}
  - {pin_num: M16, peripheral: GPIO1, signal: 'gpio_io, 4', pin_signal: GPIO1_IO04, direction: OUTPUT, HYS: ENABLED, DSE: OHM_60}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {                                /*!< Function assigned for the core: Cortex-A7[ca7] */
  /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 register modification value */
  IOMUXC_BASE_PTR->SW_MUX_CTL_PAD[9U] = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5U);
  /* IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04 register modification value */
  IOMUXC_BASE_PTR->SW_MUX_CTL_PAD[10U] = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5U);
  /* IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 register modification value */
  IOMUXC_BASE_PTR->SW_PAD_CTL_PAD[9] = 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(4U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK;
  /* IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO04 register modification value */
  IOMUXC_BASE_PTR->SW_PAD_CTL_PAD[10] = 
                        IOMUXC_SW_PAD_CTL_PAD_DSE(4U) |
                        IOMUXC_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SW_PAD_CTL_PAD_HYS_MASK;
  /* IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 register modification value */
  IOMUXC_SNVS_BASE_PTR->SW_MUX_CTL_PAD[5U] = IOMUXC_SNVS_SW_MUX_CTL_PAD_MUX_MODE(5U);
  /* IOMUXC_SNVS_SW_PAD_CTL_PAD_SNVS_TAMPER3 register modification value */
  IOMUXC_SNVS_BASE_PTR->SW_PAD_CTL_PAD[10] =
                        IOMUXC_SNVS_SW_PAD_CTL_PAD_DSE(4U) |
                        IOMUXC_SNVS_SW_PAD_CTL_PAD_SPEED(2U) |
                        IOMUXC_SNVS_SW_PAD_CTL_PAD_PKE_MASK |
                        IOMUXC_SNVS_SW_PAD_CTL_PAD_HYS_MASK;
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
