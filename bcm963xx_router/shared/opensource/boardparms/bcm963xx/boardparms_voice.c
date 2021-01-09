/*
    Copyright 2000-2010 Broadcom Corporation

    <:label-BRCM:2011:DUAL/GPL:standard
    
    Unless you and Broadcom execute a separate written software license
    agreement governing use of this software, this software is licensed
    to you under the terms of the GNU General Public License version 2
    (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
    with the following added to such license:
    
       As a special exception, the copyright holders of this software give
       you permission to link this software with independent modules, and
       to copy and distribute the resulting executable under terms of your
       choice, provided that you also meet, for each linked independent
       module, the terms and conditions of the license of that module.
       An independent module is a module which is not derived from this
       software.  The special exception does not apply to any modifications
       of the software.
    
    Not withstanding the above, under no circumstances may you combine
    this software in any way with any other Broadcom software provided
    under a license other than the GPL, without Broadcom's express prior
    written consent.
    
:>
*/                       

/**************************************************************************
* File Name  : boardparms_voice.c
*
* Description: This file contains the implementation for the BCM63xx board
*              parameter voice access functions.
*
***************************************************************************/

/* ---- Include Files ---------------------------------------------------- */

#include "boardparms_voice.h"
#include <bcm_map_part.h>

#if !defined(_CFE_)
#include <linux/kernel.h>
#endif

/* ---- Public Variables ------------------------------------------------- */

/* ---- Private Constants and Types -------------------------------------- */

/*
 * -------------------------- Daughter Boards ------------------------------
 */ 
 
VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE88506 = 
{
   VOICECFG_LE88506_STR,     /* szBoardId */
   2,             /* numFxsLines */
   0,             /* numFxoLines */
   {
      /* voiceDevice0 parameters */
      {
         /* Device type */
         BP_VD_ZARLINK_88506,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */

         /* Channel description */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
      /* Always end the device list with BP_NULL_DEVICE */
      BP_NULL_DEVICE_MACRO_NEW,
   },
   /* SLIC Device Profile */
   BP_VD_FLYBACK,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE88264_TH = 
{
   VOICECFG_LE88264_TH_STR,   /*Daughter Card ID*/
   2,   /*Number of FXS Lines*/
   0,   /*Number of FXO Lines*/
   {
      {
         /* Device Type */
         BP_VD_ZARLINK_88264,
         BP_SPI_SS_B1, /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1,   /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               3,
               3
             }
         }
      },
   
    BP_NULL_DEVICE_MACRO_NEW 
   },
   /* SLIC Device Profile */
   BP_VD_FLYBACK_TH, 
   /* General-purpose flags */
   ( BP_FLAG_THALASSA_SUPPORT )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32261 =
{
   VOICECFG_SI32261_STR,   /* daughter card ID */
   2,   /* FXS number is 2 */
   0,   /* FXO number is 0 */
   {  /* voiceDevice0 parameters */
      {
         /* Device Type */
         BP_VD_SILABS_32261,
         BP_SPI_SS_B1,   /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1,  /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         {
         /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
         /* Channel 1 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
  
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FLYBACK,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE88266 = 
{
   VOICECFG_LE88266_STR,   /* Daughter Board ID */
   2,   /*Number of FXS Lines */
   0,   /*Number of FXO Lines */ 
   {   /* Voice Device 0 */
      {
         /* Device Type */
         BP_VD_ZARLINK_88266,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
         /* Channel 0 on device 0 */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
         /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            },
         }
      },
      
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_MASTERSLAVE_FB,
   /* General-purpose flags */
   ( 0 )
}; 

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32267 = 
{
   VOICECFG_SI32267_STR,   /*Daughter board ID */ 
   2,   /*Number of FXS Lines */
   0,   /*Number of FXO Lines */ 
   {
      {
         /* Device Type */
         BP_VD_SILABS_32267,  
         BP_SPI_SS_NOT_REQUIRED,   /* ISI SPI CS handled internally. It is mapped by the zsiChipMap list. */
         BP_RESET_FXS1,    
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },

      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FB_TSS_ISO,   
   /* General-purpose flags */
   ( BP_FLAG_ISI_SUPPORT ) 
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI3217x = 
{
   VOICECFG_SI3217X_STR,   /*Daughter Card ID */
   2,   /*Number of FXS Lines */
   1,   /*Number of FXO Lines */ 
   {
      {
         /* Device Type */
         BP_VD_SILABS_32176,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            {
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            }
         }
      },
      {
         /* Device Type 2 */
         BP_VD_SILABS_32178,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            },
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            }
         }
      },
     
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FLYBACK,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_VE890_INVBOOST =
{
   VOICECFG_VE890_INVBOOST_STR,   /* daughter card ID */
   2,   /* FXS number is 2 */
   1,   /* FXO number is 1 */    
   {   /* voiceDevice0 parameters */
      {
         /* Device Type */ 
         BP_VD_ZARLINK_89116,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            {
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            }
         }
      },
      {
         /* Device Type 2 */ 
         BP_VD_ZARLINK_89316,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            },
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            }
         }
      },
      
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_INVBOOST,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE88266x2_LE89010 = 
{
   VOICECFG_LE88266x2_LE89010_STR,   /* Daughter Card ID */
   4,   /* Number of FXS Lines */
   1,   /* Number of FXO Lines */
   {
      {
         /* Device Type */
         BP_VD_ZARLINK_88266,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device 0 */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
      {
         /* Device Type 2 */
         BP_VD_ZARLINK_88266,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device 0 */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               3,
               3
            },
         }
      },
      {
         /* Device Type 3 */
         BP_VD_ZARLINK_89010,
         BP_SPI_SS_B3,  /* Device uses SPI_SS_B3 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXO,  /* Device uses FXO reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               4,
               4
            },
            /* There is no second channel on Le89010 so mark it as inactive */
            {  
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            },
         }
      },

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_MASTERSLAVE_FB,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32260x2 =
{
   VOICECFG_SI32260x2_STR,   /*Daughter Card ID*/
   4,   /*Number of FXS Lines*/
   0,   /*Number of FXO Lines*/
   {   /* voiceDevice0 Parameters */
      {
         /* Device Type */
         BP_VD_SILABS_32261,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1, 
               1
            }
         }
      },
      {
         /* Device Type 2*/
         BP_VD_SILABS_32261,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               3,
               3
            }
         }
      },

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FB_TSS,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE88536_ZSI = 
{
   VOICECFG_LE88536_ZSI_STR,   /* Daughter Board ID */
   2,   /* Number of FXS Lines */
   0,   /*Number of FXO Lines */ 
   {   /* Voice Device 0 Parameters */ 
      {
         BP_VD_ZARLINK_88536,   /* Device Type */
         BP_SPI_SS_NOT_REQUIRED,   /* ZSI SPI CS handled internally. It is mapped using the zsiMapList. */
         BP_RESET_FXS1,
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               3,
               3
            },
         }
      }, 

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW 
   },
   /* SLIC Device Profile */
   BP_VD_INVBOOST, 
   /* General-purpose flags */
   ( BP_FLAG_ZSI_SUPPORT )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_ZL88601 = 
{
   VOICECFG_ZL88601_STR,   /* szBoardId */
   2,   /* Number of FXS Lines */
   0,   /* Number of FXO Lines */ 
   {
      {
         /* Device Type */
         BP_VD_ZARLINK_88601,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel Description */
         {
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */ 
   BP_VD_FLYBACK,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE89116 = 
{
   VOICECFG_LE89116_STR,   /* Daughter Card ID */
   1,   /*Number of FXS Lines */
   0,   /*Number of FXO Lines */
   {
      {
         /* Device Type */
         BP_VD_ZARLINK_89116,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device 0 */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* There is no second channel on 89116 so mark it as inactive */
            {  
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID},
            }
      },

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_INVBOOST,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI3217x_NOFXO = 
{
   VOICECFG_SI3217X_NOFXO_STR,   /* Daughter Card ID */
   2,   /* Number of FXS Lines */
   0,   /*Number of FXO Lines */
   {
      {  
         /* Device type */
         BP_VD_SILABS_32176,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 Reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* There is no second channel on 89116 so mark it as inactive */
            {  
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            }
         }
      },
      {
         /* Device Type */
         BP_VD_SILABS_32178,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            }
         }
      },

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FLYBACK,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32176 = 
{
   VOICECFG_SI32176_STR,   /* Daughter Board ID */
   1,   /* Number of FXS Lines */
   0,   /* Number of FXO Lines */
   {
      {
         /* Device Type */
         BP_VD_SILABS_32176,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* There is no second channel on 89116 so mark it as inactive */
            { 
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            },
         }
      },
 
      /* Always end device list with this macro. */ 
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FLYBACK,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_VE890HV = 
{
   VOICECFG_VE890HV_STR,   /*Daughter Card ID */
   2,   /*Number of FXS Lines */
   1,   /*Number of FXO Lines */
   {
      {
         /* Device type */
         BP_VD_ZARLINK_89136,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device 0 */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* There is no second channel on 89116 so mark it as inactive */
            { 
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            },
         }
      },
      {
         /* Device type 2 */
         BP_VD_ZARLINK_89336,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device 0 */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
         }
      },

      /* Always end the device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_INVBOOST,
   /* General-purpose flags */
   ( 0 )	
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE89316 = 
{
   VOICECFG_LE89316_STR,   /* Daughter Card ID */
   1,   /*Number of FXS Lines */
   1,   /*Number of FXO Lines */
   {
      {
         /* Device Type */
         BP_VD_ZARLINK_89316,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device 0 */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },

      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_INVBOOST,
   /* General-purpose flags */
   ( 0 )

};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32178 = 
{
   VOICECFG_SI32178_STR,   /* Daughter Board ID */
   1,   /* Number of FXS Lines */
   1,   /* Number of FXO Lines */
   {
      { 
         /* Device Type */
         BP_VD_SILABS_32178,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
   
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   
   /* SLIC Device Profile */
    BP_VD_FLYBACK,
    /* General-purpose flags */
    ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_NOSLIC = 
{
   VOICECFG_NOSLIC_STR, /*Daughter Board ID */ 
   0,   /*Number of FXS Lines */
   0,   /*Number of FXO Lines */
   {
      BP_NULL_DEVICE_MACRO_NEW
   },

   /* SLIC Device Profile */
   BP_NOT_DEFINED,   
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32267_NTR = 
{
   VOICECFG_SI32267_NTR_STR,   /* Daughter Board ID */ 
   2,   /*Number of FXS Lines */
   0,   /*Number of FXO Lines */
   {
      {
         /* Device Type */
         BP_VD_SILABS_32267,
         BP_SPI_SS_NOT_REQUIRED, /* ISI SPI CS handled internally. It is mapped by the zsiChipMap list. */
         BP_RESET_FXS1,          /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            },
         }
      },

      /* Always end the device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FB_TSS_ISO,   
   /* General-purpose flags */
   ( BP_FLAG_ISI_SUPPORT )
}; 

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI32260x2_SI3050 = 
{
   VOICECFG_SI32260x2_SI3050_STR,   /*Daughter card ID */
   4,   /* Number of FXS Lines */
   1,   /* Number of FXO Lines */
   {
      {
         /* Device Type */
         BP_VD_SILABS_32261,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
      {
         /* Device Type 2 */
         BP_VD_SILABS_32261,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               3,
               3
            },
         }
      }, 
      {
         /* Device Type 3 */
         BP_VD_SILABS_3050,
         BP_SPI_SS_B3,  /* Device uses SPI_SS_B3 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXO,  /* Device uses FXO reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               4,
               4
            },
            /* There is no second channel on Si3050 so mark it as inactive */
            {  
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            },
         }
      },
      
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_VD_FB_TSS,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE88266x2 = 
{
   VOICECFG_LE88266x2_STR,   /* Daughter card ID */
   4,   /*Number of FXS Lines */
   0,   /* Number of FXO Lines*/
   {
      {
         /* Device Type */
         BP_VD_ZARLINK_88266,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */ 
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
      {
         /* Device Type 2 */
         BP_VD_ZARLINK_88266,
         BP_SPI_SS_B2,  /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS2, /* Device uses FXS2 reset pin. Pin on base board depends on base board parameters. */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               2,
               2
            },
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               3,
               3
            }
         }
      },
         
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },

   /* SLIC Device Profile */
   BP_VD_MASTERSLAVE_FB,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_6368MVWG = 
{
   VOICECFG_6368MVWG_STR,   /*Daughter board ID */
   2,   /*Number of FXS Lines */
   1,   /*Number of FXO Lines */
   {
      {   
         /*Voice device 0 */
         BP_VD_ZARLINK_89116, /*Device type */ 
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         
         /* Channel description */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               4,
               4
            },
            /* There is no second channel on 89116 so mark it as inactive */
            { 
               BP_VOICE_CHANNEL_INACTIVE,
               BP_VCTYPE_NONE,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            },
         }
      },
      {   
         /*Voice Device 1 */ 
         BP_VD_ZARLINK_89316,
         BP_SPI_SS_B2,           /* Device uses SPI_SS_B2 pin. Pin on base board depends on base board parameters. */
         BP_RESET_NOT_REQUIRED,  /* Device does not need reset. */
         
         /* Channel description */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               5,
               5
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_DAA,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               6,
               6
            },
         }
      },
      
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
      
   /* SLIC Device Profile */
   BP_VD_BUCKBOOST,
   /* General-purpose flags */
   ( 0 )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE9530 =
{
   VOICECFG_LE9530_STR,   /* daughter card ID */
   2,   /* FXS number is 2 */
   0,   /* FXO number is 0 */
   {  /* voiceDevice0 parameters */
      {
         /* Device Type */
         BP_VD_ZARLINK_9530,
         BP_SPI_SS_B1,           /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_NOT_REQUIRED,  /* Device does not require a reset pin. */
         {
            /* Channel 0 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
  
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_NOT_DEFINED,
   /* General-purpose flags */
   ( BP_FLAG_DSP_APMHAL_ENABLE )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE9530_WB =
{
   VOICECFG_LE9530_WB_STR,	/* daughter card ID */
   2,   /* FXS number is 2 */
   0,   /* FXO number is 0 */
   {   /* voiceDevice0 parameters */
      {
         /* Device Type */
         BP_VD_ZARLINK_9530,
         BP_SPI_SS_B1,           /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_NOT_REQUIRED,  /* Device does not require a reset pin. */
         {
            /* Channel 0 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_WIDEBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            },
            /* Channel 1 on device */
            { 
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_WIDEBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               BP_TIMESLOT_INVALID,
               BP_TIMESLOT_INVALID
            }
         }
      },
     
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW 
   },
   /* SLIC Device Profile */
   BP_NOT_DEFINED,
   /* General-purpose flags */
   ( BP_FLAG_DSP_APMHAL_ENABLE )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_SI3239 =
{
   VOICECFG_SI3239_STR,   /* daughter card ID */
   2,   /* FXS number is 2 */
   0,   /* FXO number is 0 */
   {   /* voiceDevice0 parameters */
      {
         /* Device type */
         BP_VD_SILABS_3239,
         BP_SPI_SS_B1,           /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_NOT_REQUIRED,  /* Device does not require a reset pin. */
         {
            /* Channel 0 on device */
            {
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               0,
               0
            },
            /* Channel 1 on device */
            {  
               BP_VOICE_CHANNEL_ACTIVE,
               BP_VCTYPE_SLIC,
               BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
               BP_VOICE_CHANNEL_NARROWBAND,
               BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
               BP_VOICE_CHANNEL_ENDIAN_BIG,
               1,
               1
            }
         }
      },
      
      /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
   /* SLIC Device Profile */
   BP_NOT_DEFINED,
   /* General-purpose flags */
   ( BP_FLAG_DSP_APMHAL_ENABLE )
};

VOICE_DAUGHTER_BOARD_PARMS g_voiceBoard_LE9530_LE88506 = {
   VOICECFG_LE9530_LE88506_STR,   /* Daughter board ID*/
   4,   /*Num FXS Lines */
   0,   /*Num FXO Lines */ 
   {   /*voiceDevice0 Params */ 
      {
         /* Device Type */
         BP_VD_ZARLINK_88506,
         BP_SPI_SS_B1,  /* Device uses SPI_SS_B1 pin. Pin on base board depends on base board parameters. */
         BP_RESET_FXS1, /* Device uses FXS1 reset pin. Pin on base board depends on base board parameters. */
         /* Channel description */
            {
               /* Channel 0 on device */
               { 
                  BP_VOICE_CHANNEL_ACTIVE,
                  BP_VCTYPE_SLIC,
                  BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
                  BP_VOICE_CHANNEL_NARROWBAND,
                  BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
                  BP_VOICE_CHANNEL_ENDIAN_BIG,
                  0,
                  0
               },
               /* Test a single channel on 88506 */
               {  
                  BP_VOICE_CHANNEL_ACTIVE,
                  BP_VCTYPE_SLIC,
                  BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
                  BP_VOICE_CHANNEL_NARROWBAND,
                  BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
                  BP_VOICE_CHANNEL_ENDIAN_BIG,
                  1,
                  1
               }
         }
      },
      {
         /* Device Type 2 */
         BP_VD_ZARLINK_9530,
         BP_SPI_SS_B1,           /*The 9530 chips are actually internal, device ID is always 0. */
         BP_RESET_NOT_REQUIRED,  /* Device does not require a reset pin. */
         /* Channel description */
            {
               /* Channel 0 on device */
               {  
                  BP_VOICE_CHANNEL_ACTIVE,
                  BP_VCTYPE_SLIC,
                  BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
                  BP_VOICE_CHANNEL_NARROWBAND,
                  BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
                  BP_VOICE_CHANNEL_ENDIAN_BIG,
                  BP_TIMESLOT_INVALID,
                  BP_TIMESLOT_INVALID
               },
               /* Channel 1 on device */
               { 
                  BP_VOICE_CHANNEL_ACTIVE,
                  BP_VCTYPE_SLIC,
                  BP_VOICE_CHANNEL_PCMCOMP_MODE_NONE,
                  BP_VOICE_CHANNEL_NARROWBAND,
                  BP_VOICE_CHANNEL_SAMPLE_SIZE_16BITS,
                  BP_VOICE_CHANNEL_ENDIAN_BIG,
                  BP_TIMESLOT_INVALID,
                  BP_TIMESLOT_INVALID
               }
            }
      },

     /* Always end device list with this macro. */
      BP_NULL_DEVICE_MACRO_NEW
   },
 
   /* SLIC Device Profile */
   BP_VD_FLYBACK,    
   /* General-purpose flags */
   ( BP_FLAG_DSP_APMHAL_ENABLE )
};

/* End of Daughter Card Definitions */

#if defined(_BCM96328_) || defined(CONFIG_BCM96328)

VOICE_BOARD_PARMS_NEW g_voice_bcm96328AVNGR = 
{
   "96328avngr",   /*Base Board ID*/
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_2, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_6, BP_DEDICATED_PIN }    /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */
   },
   {
      BP_GPIO_29_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_NOT_CONNECTED, /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to FXO reset pin on daughter board. */
   }, 

   BP_NOT_CONNECTED, /* DECT reset GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */

   BP_DECT_NOT_SUPPORTED,  /* Dect is not supported on this board. */
 
   /* List of daughter boards supported by this base board. */
   {
      &g_voiceBoard_SI32176,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE89116,   
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_LE88264_TH,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_SI32267,
      0
   }
};

/* List of base boards in this family of chips. */
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[] =
{
   &g_voice_bcm96328AVNGR,
   0
};

#endif

#if defined(_BCM96362_) || defined(CONFIG_BCM96362)

VOICE_BOARD_PARMS_NEW g_voice_bcm96361I2 = 
{
   "96361I2",   /*Base Board ID*/
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   }, 
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_29_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 

   BP_GPIO_29_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_10_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */

   /* DECT is not supported */
   BP_DECT_NOT_SUPPORTED,
 
   /* List of supported daughter cards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88266,   
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88266x2_LE89010,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96362RPVT = {
   "96362RPVT",   /*Base Board ID*/
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_26_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
   
   BP_GPIO_29_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_35_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
   
   /* Dect is supported. */ 
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter cards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88266,   
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96361XF = 
{
   "96361XF",   /*Base Board ID*/
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_DEFINED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
 
   BP_NOT_CONNECTED,   /* DECT reset GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */

   /* DECT not supported on this board. */
   BP_DECT_NOT_SUPPORTED,
 
   /* List of supported daughter cards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88506,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96362ADVN2XH = 
{
   "96362ADVN2xh",   /*Base Board ID*/
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_26_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
 
   BP_GPIO_30_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_44_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
 
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88506,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96362RAVNGR2 = 
{
   "96362RAVNGR2",   /*Base Board ID*/
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_DEFINED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
 
   BP_GPIO_29_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_35_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
 
   /* Dect is supported*/
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88266,  
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96362ADVNGR2 = 
{
   "96362ADVNgr2",   /*Base Board ID*/
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_DEFINED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
 
   BP_GPIO_29_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_44_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
  
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88266,   
      &g_voiceBoard_VE890_INVBOOST,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96362ADVNgr = 
{
   "96362ADVNgr",   /*Base Board ID*/ 
   {
      { SPI_DEV_0, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_1, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin. */
      { SPI_DEV_2, BP_GPIO_9_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_28_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_31_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_DEFINED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
 
   BP_GPIO_29_AL,    /* DECT reset GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
 
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_NOSLIC,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_SI32176,
      &g_voiceBoard_SI32178,
      &g_voiceBoard_SI3217x_NOFXO,   
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE89116,
      &g_voiceBoard_LE89316,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88264_TH,
#ifdef SI32261ENABLE
      &g_voiceBoard_SI32261,
#endif
#ifdef SI32267ENABLE
      &g_voiceBoard_SI32267,
#endif
      &g_voiceBoard_VE890HV,
      &g_voiceBoard_LE88266,
      0
   }
};

/* List of base boards in this family of chips. */
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   &g_voice_bcm96361I2,
   &g_voice_bcm96362RPVT,
   &g_voice_bcm96361XF,
   &g_voice_bcm96362ADVN2XH,
   &g_voice_bcm96362RAVNGR2,
   &g_voice_bcm96362ADVNGR2,
   &g_voice_bcm96362ADVNgr,
   0
};

#endif

#if defined(_BCM963268_) || defined(CONFIG_BCM963268)

VOICE_BOARD_PARMS_NEW g_voice_bcm963268SV = 
{
   "963268SV1",   /*Base Board ID */
   {
      { SPI_DEV_1, BP_DEDICATED_PIN }, /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_4, BP_GPIO_16_AL },    /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */
      { SPI_DEV_3, BP_DEDICATED_PIN }  /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */
   },
   {
      BP_GPIO_14_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
 
   BP_GPIO_35_AL,    /* DECT reset GPIO pin. */
   BP_GPIO_8_AH,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
 
   BP_DECT_INTERNAL,  /* Internal DECT Config */ 
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,	
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963268MBV = 
{
   "963268MBV",   /*Base Board ID */
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */
      { SPI_DEV_3, BP_DEDICATED_PIN }    /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */
   },
 
   {
      BP_GPIO_14_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
 
   BP_GPIO_35_AL,    /* DECT reset GPIO pin. */
   BP_GPIO_8_AH,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */

   BP_DECT_INTERNAL,  /* Internal DECT Config */
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266, 
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963268V30A = 
{
   "963268V30A",   /*Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */
      { SPI_DEV_5, BP_GPIO_17_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with a dthe GPIO_17_AL pin. */
   },
   {
      BP_GPIO_14_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_50_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
 
   BP_GPIO_51_AL,    /* DECT reset GPIO pin. */
   BP_GPIO_39_AH,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
 
   BP_DECT_INTERNAL,  /* Internal DECT Config */
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88264_TH,
      &g_voiceBoard_SI32260x2,    
      &g_voiceBoard_ZL88601,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168MBV_17A_302 = 
{
   "963168MBV17A302",
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */ 
      { SPI_DEV_7, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_14_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_10_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_GPIO_35_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_8_AH,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */

   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266, 
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168MBV_30A_302 = 
{
   "963168MBV30A302",   /* Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */ 
      { SPI_DEV_7, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_10_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
  
   BP_GPIO_35_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_8_AH,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
 
   BP_DECT_INTERNAL,  /* Internal DECT Config */
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266, 	
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168MBV_17A = 
{
   "963168MBV_17A",   /* Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_7, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */ 
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_23_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
 
   BP_GPIO_35_AL,    /* DECT reset GPIO pin. */
   BP_GPIO_8_AH,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */

   BP_DECT_INTERNAL,  /* Internal DECT Config */ 
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266, 
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168MBV_30A = 
{
   "963168MBV_30A",   /* Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */  
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_7, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */ 
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_23_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
 
   BP_GPIO_35_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_8_AH,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
 
   BP_DECT_INTERNAL,  /* Internal DECT Config */
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266, 
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168XH = 
{
   "963168XH",   /*Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */  
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_7, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */  
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_21_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_GPIO_35_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_39_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
   
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST, 
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88266,
      0 
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168MP = 
{
   "963168MP",   /*Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */  
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_7, BP_GPIO_9_AL }        /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_9_AL pin. */  
   },
   {
      BP_GPIO_14_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_GPIO_19_AL,   /* DECT reset GPIO pin. */
   BP_GPIO_39_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */
   
   BP_DECT_INTERNAL,  /* Internal DECT Config */
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST, 
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88266,
      0      
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168VX = 
{
   "963168VX",   /* Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */  
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_5, BP_GPIO_17_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_17_AL pin. */  
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_9_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,  /* DECT reset GPIO pin. */ 
   BP_GPIO_8_AH,      /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
   
   /*Dect not supported on this board. */
   BP_DECT_NOT_SUPPORTED,
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963168VX_P400 = 
{
   "963168VX_P400",   /* Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */  
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_5, BP_GPIO_17_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_17_AL pin. */  
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_9_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,  /* DECT reset GPIO pin. */ 
   BP_GPIO_8_AH,      /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
   
   /*Dect not supported on this board. */
   BP_DECT_NOT_SUPPORTED,
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266,
      0
   }
};

#if defined(SUPPPORT_GPL)
VOICE_BOARD_PARMS_NEW g_voice_bcm963168VX_C2000A = 
{
   "C2000A",   /* Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */  
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */  
      { SPI_DEV_5, BP_GPIO_17_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_17_AL pin. */  
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_9_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,  /* DECT reset GPIO pin. */ 
   BP_GPIO_8_AH,      /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
   
   /*Dect not supported on this board. */
   BP_DECT_NOT_SUPPORTED,
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_SI32261,
      0
   }
};
#endif

VOICE_BOARD_PARMS_NEW g_voice_bcm963268BU = 
{
   "963268BU",   /*Base Board ID */
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */ 
      { SPI_DEV_5, BP_GPIO_17_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_17_AL pin. */ 
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_18_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_GPIO_19_AL,   /* DECT reset GPIO pin. */  
   BP_GPIO_39_AH,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,  /* Relay 2 GPIO pin. */

   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST, 
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88266,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm963268BU_P300 = 
{
   "963268BU_P300",   /*Base Board ID */ 
   {
      { SPI_DEV_1, BP_DEDICATED_PIN },   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      { SPI_DEV_4, BP_GPIO_16_AL },      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */ 
      { SPI_DEV_5, BP_GPIO_17_AL }       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_17_AL pin. */ 
   }, 
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_18_AL    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   }, 
   
   BP_GPIO_19_AL,    /* DECT reset GPIO pin. */ 
   BP_GPIO_39_AH,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
   
   BP_DECT_INTERNAL,  /* Internal DECT Config */   
   /* Supported Daughter Cards */
   {   
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_VE890_INVBOOST, 
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88266,  
      0
   }
}; 

/* List of base boards in this family of chips. */
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   &g_voice_bcm963268BU_P300,
   &g_voice_bcm963268BU,
   &g_voice_bcm963168VX,
   &g_voice_bcm963168VX_P400,
   &g_voice_bcm963268SV,
   &g_voice_bcm963268MBV,
   &g_voice_bcm963268V30A,
   &g_voice_bcm963168MBV_17A,
   &g_voice_bcm963168MBV_30A,
   &g_voice_bcm963168XH,
   &g_voice_bcm963168MP,
   &g_voice_bcm963168VX,
   &g_voice_bcm963168MBV_17A_302,
   &g_voice_bcm963168MBV_30A_302,
#if defined(SUPPPORT_GPL)
   &g_voice_bcm963168VX_C2000A,
#endif
   0
};

#endif

#if defined(_BCM96368_) || defined(CONFIG_BCM96368)

VOICE_BOARD_PARMS_NEW g_voice_bcm96368MVWG =
{
   "96368MVWG",
   {
      {SPI_DEV_2, BP_GPIO_28_AL},   /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3, BP_GPIO_29_AL},   /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_29_AL pin. */ 
      {SPI_DEV_4, BP_NOT_CONNECTED} /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */ 
   },
   {
      BP_GPIO_10_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_10_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,  /* DECT reset GPIO pin. */ 
   BP_GPIO_3_AH,      /* Relay 1 GPIO pin. */
   BP_GPIO_13_AH,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */ 
   
   /* List of supported daughter cards. */
   {
      &g_voiceBoard_6368MVWG,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96368MB2G = 
{
   "96368MB2G",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3, BP_GPIO_29_AL}       /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */ 
   },
   
   {
      BP_GPIO_3_AL,      /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_16_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,  /* DECT reset GPIO pin. */ 
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 3 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE89116,
      &g_voiceBoard_LE89316,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_SI32176,
      &g_voiceBoard_SI32178,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96368RMVNg = 
{
   "96368RMVNg NOR",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3, BP_GPIO_29_AL}      /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */  
   },
   
   {
      BP_GPIO_16_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_17_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_4_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_DEFINED,  /* DECT reset GPIO pin. */ 
   BP_GPIO_8_AH,    /* Relay 1 GPIO pin. */
   BP_GPIO_13_AH,   /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI32261,
      &g_voiceBoard_SI32260x2,
      &g_voiceBoard_SI32260x2_SI3050,
      &g_voiceBoard_LE88266x2,
      &g_voiceBoard_LE88266x2_LE89010,
      &g_voiceBoard_SI3217x,
      0
   }   
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96368MVNgr = 
{
   "96368MVNgr",   /*Board ID */
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3, BP_GPIO_29_AL}      /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */   
   },
   {
      BP_GPIO_16_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_17_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_4_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_DEFINED,   /* DECT reset GPIO pin. */ 
   BP_NOT_DEFINED,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
   
   /* Channel description */
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI32176,
      &g_voiceBoard_SI32178,
      &g_voiceBoard_SI3217x_NOFXO,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE89116,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE89316,
      &g_voiceBoard_VE890HV,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88264_TH,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96368MVNgrP2 = 
{
   "96368MVNgrP2",   /*Board ID*/
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */
      {SPI_DEV_3, BP_GPIO_29_AL}      /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */ 
   },
   {
      BP_GPIO_16_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_17_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_4_AL     /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_DEFINED,   /* DECT reset GPIO pin. */  
   BP_NOT_DEFINED,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {   
      &g_voiceBoard_SI32176,
      &g_voiceBoard_SI32178,
      &g_voiceBoard_SI3217x_NOFXO,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE89116,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE89316,
      &g_voiceBoard_VE890HV,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88264_TH,
      0
   }
};

/* List of base boards in this family of chips. */
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   &g_voice_bcm96368MVWG,
   &g_voice_bcm96368RMVNg,
   &g_voice_bcm96368MVNgrP2,
   &g_voice_bcm96368MVNgr,
   &g_voice_bcm96368MB2G,
   0
};

#endif

#if defined(_BCM96816_) || defined(CONFIG_BCM96816)

VOICE_BOARD_PARMS_NEW g_voice_bcm96816PVWM =
{
   "96816PVWM",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3, BP_GPIO_29_AL}      /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */ 
   },
   {
      BP_GPIO_14_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_16_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_DEFINED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset GPIO pin. */ 
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530_LE88506,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96816SV = 
{
   "96816SV",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN}, /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_NOT_CONNECTED}, /* No connection for this SPI Device. */ 
      {SPI_DEV_3, BP_NOT_CONNECTED}  /* No connection for this SPI Device. */ 
   },
   {
      BP_NOT_DEFINED,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_NOT_CONNECTED,   /* FXS2 reset pin, no connection on this board. */
      BP_NOT_CONNECTED   /* FXO reset pin, no connection on this board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset GPIO pin. */ 
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3239,       
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96818RG = 
{
   "96818RG",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3, BP_GPIO_29_AL}      /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */ 
   },
   {
      BP_GPIO_14_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_16_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board.  */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset GPIO pin. */ 
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE88506,
      0
   }
};

/* List of base boards in this family of chips. */
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   &g_voice_bcm96816SV,
   &g_voice_bcm96816PVWM,
   &g_voice_bcm96818RG,
   0
};

#endif

#if defined(_BCM96818_) || defined(CONFIG_BCM96818)

VOICE_BOARD_PARMS_NEW g_voice_bcm96818G_RG =
{
   "96818G_RG",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2,  BP_GPIO_28_AL},    /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3,  BP_GPIO_29_AL}     /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */   
   },
   {
      BP_GPIO_14_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_16_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */   
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset pin, 6818G_RG doesn't support DECT */
   BP_NOT_DEFINED,   /* Relay1 control pin, 6818G_RG doesn't support relay */
   BP_NOT_DEFINED,   /* Repay2 control pin, 6818G_RG doesn't support relay */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_LE9530,
      &g_voiceBoard_SI32261,      
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88506,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96818GR_ONT =
{
   "96818GR_ONT",
   {
      {SPI_DEV_1, BP_NOT_DEFINED},   /*Only uses built-in Le9530 daughter board */
      {SPI_DEV_2, BP_NOT_DEFINED},
      {SPI_DEV_3, BP_NOT_DEFINED}
      },
   {
      BP_NOT_DEFINED,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_NOT_DEFINED,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXSO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset pin */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */ 
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */ 
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_LE9530,
      0
   }
};


VOICE_BOARD_PARMS_NEW g_voice_bcm96818SV =
{
   "96818SV",
   {
      {SPI_DEV_1,  BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_3,  BP_GPIO_29_AL}      /* This SPI Device ID is mapped to SPI_SS_B3 with the GPIO_29_AL pin. */               
   },
   {
      BP_GPIO_11_AL,   /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_12_AL,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_GPIO_13_AL   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset pin */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_SI3239,     
      &g_voiceBoard_LE88506,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI32267,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_LE88266x2_LE89010,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96818EGG = 
{
   "96818EGG",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},   /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */ 
      {SPI_DEV_2, BP_GPIO_16_AL},      /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */ 
      {SPI_DEV_3, BP_NOT_CONNECTED}    /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */ 
   },
   {
      BP_GPIO_28_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_5_AL,      /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset pin */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI32267,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96818GRRG = 
{
   "96818GRRG",
   {
      {SPI_DEV_3, BP_GPIO_21_AL},     /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_21_AL pin. */ 
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */ 
      {SPI_DEV_7, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */ 
   },
   {
      BP_GPIO_16_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset pin */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */ 
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_SI3239,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_VE890_INVBOOST,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_SI32267,	
      &g_voiceBoard_ZL88601,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96818GRRG_BOSA = 
{
   "96818GRRG_BOSA",
   {
      {SPI_DEV_3, BP_GPIO_21_AL},     /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_21_AL pin. */
      {SPI_DEV_2, BP_GPIO_28_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_28_AL pin. */
      {SPI_DEV_7, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin. */
   },
   {
      BP_GPIO_16_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_15_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,   /* DECT reset pin */
   BP_NOT_DEFINED,     /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,     /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */ 
   
   /* The list of supported daughter boards. */
   {
       &g_voiceBoard_SI3239,
       &g_voiceBoard_LE88506,
       &g_voiceBoard_VE890_INVBOOST,
       &g_voiceBoard_LE88536_ZSI,
       &g_voiceBoard_LE88266,
       &g_voiceBoard_SI32261,
       &g_voiceBoard_SI32267,   
       0   
   }
};

/* The list of daughter boards in this family of chips. */
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   &g_voice_bcm96818G_RG,
   &g_voice_bcm96818SV,
   &g_voice_bcm96818EGG,
   &g_voice_bcm96818GRRG,
   &g_voice_bcm96818GRRG_BOSA,
   &g_voice_bcm96818GR_ONT,
   0
};

#endif

#if defined(_BCM96828_) || defined(CONFIG_BCM96828)

VOICE_BOARD_PARMS_NEW g_voice_bcm96828EGG =
{
   "96828EGG", 
   {
      {SPI_DEV_1, BP_DEDICATED_PIN },  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. */
      {SPI_DEV_4, BP_GPIO_16_AL },     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */
      {SPI_DEV_3, BP_NOT_CONNECTED }     /* This SPI Device ID is not connected */  
   },
   {
      BP_GPIO_17_AL,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_22_AL,    /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED  /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },

   BP_NOT_CONNECTED, /* DECT reset pin */
   BP_NOT_DEFINED,   /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,   /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */

   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE9530_LE88506, 
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,
      &g_voiceBoard_ZL88601,
      0
   }
}; 

VOICE_BOARD_PARMS_NEW g_voice_bcm96828HGW =
{
   "96828HGW",
   {
      { SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin. This is the mapping for P202 and later versions of this board. */
      { SPI_DEV_4, BP_GPIO_16_AL},    /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_16_AL pin. */
      { SPI_DEV_3, BP_NOT_CONNECTED}  /* This SPI Device ID is not connected. */ 
   },
   {
      BP_GPIO_17_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */   
      BP_GPIO_22_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */  
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
   
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
   
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88266,    
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE9530_LE88506,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,    
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96821GF_SFU_F11 = 
{
   "96821GF_SFU_F11",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin.  */
      {SPI_DEV_2, BP_NOT_CONNECTED},  /* This SPI Device ID is not connected. */
      {SPI_DEV_3, BP_NOT_CONNECTED}   /* This SPI Device ID is not connected. */
   },
   {
      BP_NOT_DEFINED,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */ 
      BP_NOT_CONNECTED,  /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */ 
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */ 
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
    
   /* List of supported daughter cards */ 
   {
      &g_voiceBoard_SI3239,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96821GF_SFU_G11 = 
{
   "96821GF_SFU_G11",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin.  */
      {SPI_DEV_2, BP_NOT_CONNECTED},  /* This SPI Device ID is not connected.  */
      {SPI_DEV_3, BP_NOT_CONNECTED}   /* This SPI Device ID is not connected.  */
      },
   {
      BP_NOT_DEFINED,    /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_NOT_CONNECTED,  /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
    
   /* List of supported daughter cards. */ 
   {
      &g_voiceBoard_SI3239,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96821GF_SFU_F21 = 
{
   "96821GF_SFU_F21",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin.  */
      {SPI_DEV_2, BP_NOT_CONNECTED},  /* This SPI Device ID is not connected.  */
      {SPI_DEV_3, BP_NOT_CONNECTED}   /* This SPI Device ID is not connected.  */
   },
   {
      BP_NOT_DEFINED,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_NOT_CONNECTED,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_SI3239,
    0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96821GF_SFU_G21 = 
{
   "96821GF_SFU_G21",
   {
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B1 with a dedicated pin.  */
      {SPI_DEV_2, BP_NOT_CONNECTED},  /* This SPI Device ID is not connected.  */
      {SPI_DEV_3, BP_NOT_CONNECTED}   /* This SPI Device ID is not connected.  */
   },
   {
      BP_NOT_DEFINED,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_NOT_CONNECTED,   /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED    /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED, /* Internal DECT configuration */
    
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI3239,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96828HGW_F42 =
{
   "96828HGW_F42",
   {
      { SPI_DEV_4, BP_GPIO_16_AL},    /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_16_AL pin.  */
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin.  */
      {SPI_DEV_3, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin.  */
   },
   {
      BP_GPIO_17_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_22_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
    
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96828HGW_G42 =
{
   "96828HGW_G42",
   {
      {SPI_DEV_4, BP_GPIO_16_AL},     /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_16_AL pin.  */
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin.  */
      {SPI_DEV_3, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin.  */
   },
   {
      BP_GPIO_17_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_22_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
    
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96828HGW_F21 =
{
   "96828HGW_F21",
   {
      {SPI_DEV_4, BP_GPIO_16_AL},     /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_16_AL pin.  */
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin.  */
      {SPI_DEV_3, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin.  */
   },
   {
      BP_GPIO_17_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_22_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
   
   /* List of supported daughter boards. */ 
   {
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,
      0
    }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96828HGW_G21 =
{
   "96828HGW_G21",
   {
      {SPI_DEV_4, BP_GPIO_16_AL},     /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_16_AL pin.  */
      {SPI_DEV_1, BP_DEDICATED_PIN},  /* This SPI Device ID is mapped to SPI_SS_B2 with a dedicated pin.  */
      {SPI_DEV_3, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin.  */
   },
   {
      BP_GPIO_17_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_22_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
    
   /* List of supported daughter boards. */
   {
      &g_voiceBoard_SI32267,
      &g_voiceBoard_LE88536_ZSI,
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_SI32261,
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE9530,
      &g_voiceBoard_LE9530_WB,
      0
   }
};

VOICE_BOARD_PARMS_NEW g_voice_bcm96828SV = 
{
   "96828SV",
   {
      {SPI_DEV_4, BP_GPIO_16_AL},     /* This SPI Device ID is mapped to SPI_SS_B1 with the GPIO_16_AL pin.  */
      {SPI_DEV_5, BP_GPIO_17_AL},     /* This SPI Device ID is mapped to SPI_SS_B2 with the GPIO_17_AL pin.  */
      {SPI_DEV_3, BP_DEDICATED_PIN}   /* This SPI Device ID is mapped to SPI_SS_B3 with a dedicated pin.  */
   },
   {
      BP_GPIO_36_AL,     /* FXS1 reset pin, mapped to the FXS1 reset pin on daughter board. */
      BP_GPIO_37_AL,     /* FXS2 reset pin, mapped to the FXS2 reset pin on daughter board. */
      BP_NOT_CONNECTED   /* FXO reset pin, mapped to the FXO reset pin on daughter board. */
   },
    
   BP_NOT_CONNECTED,  /* DECT reset pin */
   BP_NOT_DEFINED,    /* Relay 1 GPIO pin. */
   BP_NOT_DEFINED,    /* Relay 2 GPIO pin. */
    
   BP_DECT_NOT_SUPPORTED,  /* Internal DECT Config */
    
   /* List of supported daughter boards */
   {
      &g_voiceBoard_SI3217x,
      &g_voiceBoard_SI3239, 
      &g_voiceBoard_LE88506,
      &g_voiceBoard_LE88266,
      &g_voiceBoard_LE88536_ZSI,
      0
   }
};

/* List of base boards in this family of chips. */ 
static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   &g_voice_bcm96828HGW,
   &g_voice_bcm96828EGG,
   &g_voice_bcm96821GF_SFU_F11,
   &g_voice_bcm96821GF_SFU_G11,
   &g_voice_bcm96821GF_SFU_F21,
   &g_voice_bcm96821GF_SFU_G21,
   &g_voice_bcm96828HGW_F42,
   &g_voice_bcm96828HGW_G42,
   &g_voice_bcm96828HGW_F21,
   &g_voice_bcm96828HGW_G21,
   &g_voice_bcm96828SV,
   0
};

#endif

#if !defined(_BCM963268_) && !defined(CONFIG_BCM963268) && !defined(_BCM96362_) && !defined(CONFIG_BCM96362) && !defined(_BCM96328_) && !defined(CONFIG_BCM96328) && !defined(_BCM96368_) && !defined(CONFIG_BCM96368) && !defined(_BCM96816_) && !defined(CONFIG_BCM96816) && !defined(_BCM96828_) && !defined(CONFIG_BCM96828) && !defined(_BCM96818_) && !defined(CONFIG_BCM96818)

static PVOICE_BOARD_PARMS_NEW g_VoiceBoardParms_new[]=
{
   0
};

#endif

static VOICE_BOARD_PARMS voiceBoard_Current;
static PVOICE_BOARD_PARMS_NEW g_pCurrentVoiceBp = 0;
static PVOICE_DAUGHTER_BOARD_PARMS g_pCurrentVoiceDc = 0;
static int g_BpDectPopulated = 1; 

static void bpmemcpy( void* dstptr, const void* srcptr, int size );
static char * bpstrcpy( char* dest, const char* src ); 

static void bpmemcpy( void* dstptr, const void* srcptr, int size )
{
   char* dstp = dstptr;
   const char* srcp = srcptr;
   int i;
   for( i=0; i < size; i++ )
   {
      *dstp++ = *srcp++;
   }
} 

static char * bpstrcpy( char* dest, const char* src)
{
   while(*src)
   {
      *dest++ = *src++; 
   }
   
   *dest = '\0'; 
   
   return dest; 
}

/*****************************************************************************
 * Name:          BpGetZSISpiDevID()  
 * 
 * Description:     This function returns the SPI Device ID for the ZSI daughter
*                   boards based on the current chip.  
 *
 * Parameters:    Nothing 
 *
 * Returns:       SPI Dev ID for ZSI Daughter Boards
 *     
 *****************************************************************************/ 
unsigned int BpGetZSISpiDevID( void )
{
#ifdef ZSI_SPI_DEV_ID
   return ZSI_SPI_DEV_ID; 
#else
   return BP_NOT_DEFINED; 
#endif
}

/*****************************************************************************
 * Name:          BpSetDectPopulatedData()  
 * 
 * Description:     This function sets the g_BpDectPopulated variable. It is
 *                used for the user to specify in the board parameters if the 
 *                board DECT is populated or not (1 for populated, 0 for not). 
 *
 * Parameters:    int BpData - The data that g_BpDectPopulated will be set to. 
 *
 * Returns:       Nothing 
 *     
 *****************************************************************************/ 
void BpSetDectPopulatedData( int BpData ) 
{
   g_BpDectPopulated = BpData; 
}

/*****************************************************************************
 * Name: 	      BpGetVoiceDectNum()  
 * 
 * Description:	  This function returns the number of DECT channels. It is
 *                used to fill the old board parameters structure with DECT 
 *                data. If the user specifies that DECT is not populated on the 
 *                board, it will return that there are zero DECT lines.  
 *
 * Parameters:    ppBpVoice - The voice board parameters structure.
 *                 
 * Returns:       The number of DECT lines in passed-in board.  
 *   			
 *****************************************************************************/ 
unsigned int BpGetVoiceDectNum(PVOICE_BOARD_PARMS_NEW *ppBpVoice)
{
   unsigned int iCnt=0;
                
   while ( (*ppBpVoice)->dectChDes[iCnt].status != BP_VOICE_CHANNEL_NONE )
   {
      iCnt++;
   }
   
   if(BpDectPopulated() == BP_DECT_NOT_POPULATED)
   {
      return 0; 
   }
        
   return iCnt;
}


/*****************************************************************************
 * Name: 	      BpDectPopulated()  
 * 
 * Description:	  This function is used to determine if DECT is populated on
 * 				  the board.   
 *
 * Parameters:    None
 *                 
 * Returns:       BP_DECT_POPULATED if DECT is populated, otherwise it will 
 *                return BP_DECT_NOT_POPULATED. 
 *   			
 *****************************************************************************/ 
int BpDectPopulated( void )
{
   return (g_BpDectPopulated ? BP_DECT_POPULATED:BP_DECT_NOT_POPULATED);
}

/*****************************************************************************
 * Name:          BpGetVoiceParms()  
 * 
 * Description:     Finds the voice parameters based on the daughter board and 
 *                base board IDs and fills the old parameters structure with 
 *                information.   
 *
 * Parameters:    pszBoardId - The daughter board ID that is being used.
 *                voiceParms - The old voice parameters structure that must be 
 *                             filled with data from the new structure.
 *                pszBaseBoardId - The base board ID that is being used.
 *                 
 * Returns:       If the board is not found, returns BP_BOARD_ID_NOT_FOUND. 
 *                If everything goes properly, returns BP_SUCCESS. 
 *    
 *****************************************************************************/ 
int BpGetVoiceParms( char* pszBoardId, VOICE_BOARD_PARMS* voiceParms, char* pszBaseBoardId )
{
   int nRet = BP_BOARD_ID_NOT_FOUND;
   int relayCount = 0; 
   int i = 0;
   int nDeviceCount = 0;
   PVOICE_BOARD_PARMS_NEW *ppBp;
   PVOICE_DAUGHTER_BOARD_PARMS *ppDc; 
   VOICE_BOARD_PARMS currentVoiceParms; 

   /* Must first go through the list of base boards and find one that matches */
   for( ppBp = g_VoiceBoardParms_new; *ppBp; ppBp++ )
   {
      if( (0 == bpstrcmp((*ppBp)->szBaseBoardId, pszBaseBoardId)))
      {
         /* Found the matching board */
         break;
      }
   }
   
   if(!(*ppBp))
   {
      /* No matching base board found */
      return nRet;  
   }
   
   /* Found matching base board; now, must iterate through supported daughter cards to find a match. */
   for(ppDc = (*ppBp)->pDcParms; *ppDc; ppDc++) 
   {
      if( (0 == bpstrcmp((*ppDc)->szBoardId, pszBoardId)))
      {
         /*Succesfully found base board + daughter card combination
         Must now fill the currentVoiceParms structure with data and copy to voiceParms 
         First set base board and daughter board strings */
         bpmemcpy(currentVoiceParms.szBoardId, (*ppDc)->szBoardId, BP_BOARD_ID_LEN);
         bpmemcpy(currentVoiceParms.szBaseBoardId, (*ppBp)->szBaseBoardId, BP_BOARD_ID_LEN);  
            
         /*Set the FXS and FXO line numbers. */
         currentVoiceParms.numFxsLines = (*ppDc)->numFxsLines;
         currentVoiceParms.numFxoLines = (*ppDc)->numFxoLines; 
            
         /*Set the number of DECT Lines. */
         currentVoiceParms.numDectLines = BpGetVoiceDectNum(ppBp); 
            
         /*This prevents the total number of channels from being greater than 7. */
         if(currentVoiceParms.numFxsLines + currentVoiceParms.numFxoLines + currentVoiceParms.numDectLines > 7)
         {
            return BP_MAX_CHANNELS_EXCEEDED; /* Return a failure. */ 
         }
         
         /*Set the relay GPIO pins*/
         currentVoiceParms.pstnRelayCtrl.relayGpio[0] = (*ppBp)->relay1CtrlGpio;
         currentVoiceParms.pstnRelayCtrl.relayGpio[1] = (*ppBp)->relay2CtrlGpio; 
            
         if((*ppBp)->relay1CtrlGpio != BP_NOT_DEFINED)
         {
            relayCount++;
         }
         
         if((*ppBp)->relay2CtrlGpio != BP_NOT_DEFINED)
         {
            relayCount++; 
         }
         
         currentVoiceParms.numFailoverRelayPins = relayCount; 
            
         /*Set DECT UART to Not Defined always for now. */
         currentVoiceParms.dectUartControl.dectUartGpioTx = BP_NOT_DEFINED; 
         currentVoiceParms.dectUartControl.dectUartGpioRx = BP_NOT_DEFINED; 
            
         /* Set the device profile */
         currentVoiceParms.deviceProfile = (*ppDc)->deviceProfile; 
            
         /*Set the flags*/
         currentVoiceParms.flags = (*ppDc)->flags; 
            
         /*Set DECT*/
         if(currentVoiceParms.numDectLines)
         {
            currentVoiceParms.voiceDevice[nDeviceCount].voiceDeviceType = currentVoiceParms.voiceDevice[nDeviceCount+1].voiceDeviceType = BP_VD_IDECT1;
            currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiDevId = currentVoiceParms.voiceDevice[nDeviceCount+1].spiCtrl.spiDevId = 0;
            currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiGpio = currentVoiceParms.voiceDevice[nDeviceCount+1].spiCtrl.spiGpio = BP_NOT_DEFINED;
            currentVoiceParms.voiceDevice[nDeviceCount].requiresReset = currentVoiceParms.voiceDevice[nDeviceCount+1].requiresReset = 1;
            currentVoiceParms.voiceDevice[nDeviceCount].resetGpio = currentVoiceParms.voiceDevice[nDeviceCount+1].resetGpio = (*ppBp)->dectRstGpio;
                
            switch(currentVoiceParms.numDectLines)
            {
               case 2:
               {
                  bpmemcpy(&currentVoiceParms.voiceDevice[nDeviceCount].channel[nDeviceCount],&(*ppBp)->dectChDes[0],sizeof(BP_VOICE_CHANNEL)*currentVoiceParms.numDectLines);
                  nDeviceCount++;
               }
               break;
               case 4:
               {
                  bpmemcpy(&currentVoiceParms.voiceDevice[nDeviceCount].channel[nDeviceCount], &(*ppBp)->dectChDes[0], sizeof(BP_VOICE_CHANNEL)*2);
                  bpmemcpy(&currentVoiceParms.voiceDevice[nDeviceCount+1].channel[nDeviceCount],&(*ppBp)->dectChDes[1],sizeof(BP_VOICE_CHANNEL)*2);
                  nDeviceCount+=2;
               }
               break;
               default:
               {
                  /* Return a failure */
                  return BP_MAX_CHANNELS_EXCEEDED; 
               }
               break;
            }
         }
    
         while(i < BP_MAX_VOICE_DEVICES && (*ppDc)->voiceDevice[i].nDeviceType != BP_VD_NONE)
         {
            /*Loop through the voice devices and copy to currentVoiceParms*/

            currentVoiceParms.voiceDevice[nDeviceCount].voiceDeviceType = (*ppDc)->voiceDevice[i].nDeviceType; 
                
            if((*ppDc)->voiceDevice[i].nRstPin == BP_RESET_NOT_REQUIRED || (*ppBp)->fxsoRstGpio[(*ppDc)->voiceDevice[i].nRstPin] == BP_RESET_NOT_REQUIRED)
            {
               currentVoiceParms.voiceDevice[nDeviceCount].requiresReset = 0; 
               currentVoiceParms.voiceDevice[nDeviceCount].resetGpio = BP_NOT_DEFINED;
            }
            else
            {
               currentVoiceParms.voiceDevice[nDeviceCount].requiresReset = 1;
               currentVoiceParms.voiceDevice[nDeviceCount].resetGpio = (*ppBp)->fxsoRstGpio[(*ppDc)->voiceDevice[i].nRstPin];
            }
    
            currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiDevId = (*ppBp)->voiceSpiPortCs[(*ppDc)->voiceDevice[i].nSPI_SS_Bx].numSpiPort; 
            currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiGpio  = ((*ppBp)->voiceSpiPortCs[(*ppDc)->voiceDevice[i].nSPI_SS_Bx].numGpio == BP_DEDICATED_PIN) ? BP_NOT_DEFINED : (*ppBp)->voiceSpiPortCs[(*ppDc)->voiceDevice[i].nSPI_SS_Bx].numGpio;
            
            /* Handle the ZSI devices */
            if((*ppDc)->voiceDevice[i].nSPI_SS_Bx == BP_SPI_SS_NOT_REQUIRED) 
            {
               /* Current device is a ZSI device. */
               currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiDevId = BpGetZSISpiDevID(); 
               
               if(currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiDevId == BP_NOT_DEFINED)
               {
                  /* Failure - Tried to use a ZSI/ISI chip on a board which does not support it*/
                  return BP_NO_ZSI_ON_BOARD_ERR; 
               }
               
               currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiGpio = BP_NOT_DEFINED; 
            }
            
            /* Handle Le9530 and Si3239, which are internal devices */
            switch(currentVoiceParms.voiceDevice[nDeviceCount].voiceDeviceType)
            {
               case BP_VD_ZARLINK_9530:
               {
                  currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiDevId = 0; 
                  currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiGpio = BP_NOT_DEFINED;
               } 
               break;
               case BP_VD_SILABS_3239:
               {
                  currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiDevId = 1; 
                  currentVoiceParms.voiceDevice[nDeviceCount].spiCtrl.spiGpio = BP_NOT_DEFINED;
               }
               default:
               break;
            }
                     
            bpmemcpy(&currentVoiceParms.voiceDevice[nDeviceCount].channel[0], &((*ppDc)->voiceDevice[i].channel[0]), sizeof(BP_VOICE_CHANNEL)*2); 
                
            i++; 
            nDeviceCount++;
         }
            
         /*Add a NULL Device*/
         currentVoiceParms.voiceDevice[nDeviceCount].voiceDeviceType=BP_VD_NONE;
                        
         voiceBoard_Current = currentVoiceParms;
         g_pCurrentVoiceBp = *ppBp; 
         g_pCurrentVoiceDc = *ppDc; 
         bpmemcpy( voiceParms, &currentVoiceParms, sizeof(VOICE_BOARD_PARMS) );
         nRet = BP_SUCCESS; 

         break;
      }
   }
   
   return( nRet );
}

/**************************************************************************
* Name       : BpSetVoiceBoardId
*
* Description: This function find the BOARD_PARAMETERS structure for the
*              specified board id string and assigns it to a global, static
*              variable.
*
* Parameters : [IN] pszBoardId - Board id string that is saved into NVRAM.
*
* Returns    : BP_SUCCESS - Success, value is returned.
*              BP_BOARD_ID_NOT_FOUND - Error, board id input string does not
*                  have a board parameters configuration record.
***************************************************************************/
int BpSetVoiceBoardId( char *pszBoardId )
{
   int nRet = BP_BOARD_ID_NOT_FOUND;
   PVOICE_DAUGHTER_BOARD_PARMS *ppDc;
   PVOICE_BOARD_PARMS_NEW *ppBpVoice;

   for( ppBpVoice = g_VoiceBoardParms_new; *ppBpVoice; ppBpVoice++ )
   {
      for(ppDc = (*ppBpVoice)->pDcParms; *ppDc; ppDc++)
      {
         if( 0 == bpstrcmp((*ppDc)->szBoardId, pszBoardId) )
         {
            bpmemcpy(voiceBoard_Current.szBoardId,pszBoardId,BP_BOARD_ID_LEN);
            g_pCurrentVoiceDc = *ppDc;
            nRet = BP_SUCCESS;
                
            return nRet; 
         }
      }
    }
    
    return( nRet );
} /* BpSetVoiceBoardId */


/**************************************************************************
* Name       : BpGetVoiceBoardId
*
* Description: This function returns the current board id strings.
*
* Parameters : [OUT] pszBoardIds - Address of a buffer that the board id
*                  string is returned in.
*
* Returns    : BP_SUCCESS - Success, value is returned.
***************************************************************************/

int BpGetVoiceBoardId( char *pszBoardId )
{
   int i;

   if (g_pCurrentVoiceDc == 0)
   {
      return -1;
   }
   
   for (i = 0; i < BP_BOARD_ID_LEN; i++)
   {
      pszBoardId[i] = g_pCurrentVoiceDc->szBoardId[i];
   }
   
   return 0;
}


/**************************************************************************
* Name       : BpGetVoiceBoardIds
*
* Description: This function returns all of the supported voice board id strings.
*
* Parameters : [OUT] pszBoardIds - Address of a buffer that the board id
*                  strings are returned in.  Each id starts at BP_BOARD_ID_LEN
*                  boundary.
*              [IN] nBoardIdsSize - Number of BP_BOARD_ID_LEN elements that
*                  were allocated in pszBoardIds.
*              [IN] pszBaseBoardId - Name of base Board ID to associate Voice
*                  Board ID with.
*
* Returns    : Number of board id strings returned.
***************************************************************************/
int BpGetVoiceBoardIds( char *pszBoardIds, int nBoardIdsSize, char *pszBaseBoardId )
{
   PVOICE_BOARD_PARMS_NEW *ppBp;
   PVOICE_DAUGHTER_BOARD_PARMS *ppDc; 
   int i;
   char *src;
   char *dest;

   for( i = 0, ppBp = g_VoiceBoardParms_new; *ppBp; ppBp++)
   {
      if( 0 == bpstrcmp((*ppBp)->szBaseBoardId, pszBaseBoardId))
      {
         break;
      }
   }
    
   if(!(*ppBp))
   {
      return 0; 
   }
    
   for( i = 0, ppDc = (*ppBp)->pDcParms; *ppDc && nBoardIdsSize; ppDc++)
   {
      dest = pszBoardIds;
      
      src = (*ppDc)->szBoardId; 
      
      bpstrcpy(dest, src); 
      
      i++;
      pszBoardIds += BP_BOARD_ID_LEN;
      nBoardIdsSize--;
   }
    
   return( i );
} /* BpGetVoiceBoardIds */

/**************************************************************************
* Name       : BpGetVoiceDectType
*
* Description: This function returns whether or not Dect is supported on a given board.
*
* Parameters : [IN] pszBoardId - Name of the base Board ID
*              
* Returns    : Status indicating if the base board supports dect. 
***************************************************************************/
int BpGetVoiceDectType( char *pszBoardId )
{
   PVOICE_BOARD_PARMS_NEW *ppBp; 
   int dectStatus = BP_VOICE_NO_DECT; 
    
   for(ppBp = g_VoiceBoardParms_new; *ppBp; ppBp++)
   {
      if( 0 == bpstrcmp((*ppBp)->szBaseBoardId, pszBoardId))
      {
         break; 
      }
   }
    
   if(!(*ppBp))
   {
        return dectStatus; 
   }
    
   if((*ppBp)->dectChDes[0].status != BP_VOICE_CHANNEL_NONE)
   {
      dectStatus = BP_VOICE_INT_DECT;
   }
    
   return dectStatus;
}