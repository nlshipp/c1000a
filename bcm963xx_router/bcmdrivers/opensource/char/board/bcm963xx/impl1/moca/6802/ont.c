#include <linux/kernel.h>
#include "../../bbsi/bbsi.h"
#include "../../bbsi/bbsiExecSeq.h"
#include "bcm6802_map.h"

void board_mocaInit(void);



// Needs to be inited from board.c

// Enable RGMII_0 to MOCA. 1Gbps
// Enable RGMII_1 to GPHY. 1Gbps
cmdElem ontInitSeq[] = {
                            { CMD_WRITE, SUN_TOP_CTRL_PIN_MUX_CTRL_0, 0x11110000 }, // pinmux
                            { CMD_WRITE, SUN_TOP_CTRL_PIN_MUX_CTRL_1, 0x11111111 },
                            { CMD_WRITE, SUN_TOP_CTRL_PIN_MUX_CTRL_2, 0x11111111 },                        
                            { CMD_WRITE, SUN_TOP_CTRL_PIN_MUX_CTRL_2, 0x00001111 },    
                            { CMD_WRITE, SUN_TOP_CTRL_PIN_MUX_CTRL_6, 0x00001100 }, //mdio, mdc
                            
                            { CMD_WRITE, SUN_TOP_CTRL_GENERAL_CTRL_NO_SCAN_0, 0x11 }, // Use 2.5V for rgmii
                            
                            { CMD_WRITE, EPORT_REG_EMUX_CNTRL, 0x0  }, // Reset
                            { CMD_WAIT,  1000,                 0x0  },                           
                            { CMD_WRITE, EPORT_REG_EMUX_CNTRL, 0x12 }, // Select port mode. Activate both GPHY and MOCA phys. 
                            
                            { CMD_WRITE, EPORT_REG_RGMII_0_CNTRL,  0x9 }, // Enable rgmii and disable internal TX delay.
                            { CMD_WRITE, EPORT_REG_RGMII_0_RX_CLOCK_DELAY_CNTRL,  0xC0 }, // Disable RX delay. We set up the 
                            { CMD_WRITE, EPORT_REG_RGMII_1_CNTRL,  0x9 },                 // only on the CPE chips side.
                            { CMD_WRITE, EPORT_REG_RGMII_1_RX_CLOCK_DELAY_CNTRL,  0xC0 },                                                 
                            
                            { CMD_WRITE, EPORT_REG_GPHY_CNTRL, 0x02A4C000 | 0x200 }, // Reset Gphy
                            { CMD_WAIT,  100,                 0x0         },                            
                            { CMD_WRITE, EPORT_REG_GPHY_CNTRL, 0x02A4C000 },                           
                            
                            { CMD_END,  0, 0 }                  
                       };


void board_mocaInit(void)
{
    printk("Initializing the 6802 moca ont board\n");
   
    kerSysBcmSpiSlaveInit();    
    bbsiExecuteCommandSequence(ontInitSeq);
}

