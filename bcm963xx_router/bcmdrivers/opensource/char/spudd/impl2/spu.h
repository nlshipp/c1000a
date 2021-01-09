/*
<:copyright-BRCM:2007:DUAL/GPL:standard

   Copyright (c) 2007 Broadcom Corporation
   All Rights Reserved

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
//**************************************************************************
// File Name  : spu.h
//
// Description: 
//               
//**************************************************************************
#ifndef __SPU_H__
#define __SPU_H__

#define MAX_MSG_LEN     256
#define MAX_LINE_LEN    16
#define  SWAP_BLOCK(x,size)

#define SPU_MD5_HAMC_BLOCK_SIZE 64

#define  CTX_COPY(x,y,z)  do { memcpy((void*)(x), (void*)(y), z);\
                SWAP_BLOCK((uint32_t *)(x), z);} while(0)

#define ECH_SIZE              4
#define OUT_HDR_OFST          9
#define AUTH_FRAG_SIZE        20
#define STATUS_FRAG_SIZE      4
#define BCT_FRAG_SIZE         (2*16)
#define SPSV4_FRAG_SIZE       sizeof(SPSV4_FIELD)
#define SPSV6_FRAG_SIZE       sizeof(SPSV6_FIELD)
#define SUPDT_FRAG_SIZE       sizeof(SCTX_INSAU)

#define RX_MSG_HDR_SIZE       12 /* CCH(1 word)+ECH(1 word)+BD(1 word)+PAD(1 word) */
#define RX_STS_SIZE           4

#define BCM_XTRA_DMA_HDR_SIZE         256 

#define SPU_MAX_KEY_SIZE		64
#define SPU_MAX_AUTH_SIZE		32
#define SPU_MAX_IV_LENGTH		16 /* max of AES_BLOCK_SIZE, DES3_EDE_BLOCK_SIZE */

#define MD5_DIGEST_SIZE                 16

#define SPU_MAX_DATA_LEN 65535

#define SPU_CHAIN_SIZE                  4032

#define BCM_DESC_ENCR_ALG_NONE    0x00000001
#define BCM_DESC_ENCR_ALG_NULL    0x00000002
#define BCM_DESC_ENCR_ALG_DES     0x00000004
#define BCM_DESC_ENCR_ALG_3DES    0x00000008
#define BCM_DESC_ENCR_ALG_AES     0x00000010
#define BCM_DESC_ENCR_ALG_AES_CTR 0x00000020

#define BCM_DESC_ENCR_KEYLEN_AES128    0x00000100
#define BCM_DESC_ENCR_KEYLEN_AES192    0x00000200
#define BCM_DESC_ENCR_KEYLEN_AES256    0x00000400

#define BCM_DESC_AUTH_ALG_NONE    0x00001000
#define BCM_DESC_AUTH_ALG_SHA1    0x00002000
#define BCM_DESC_AUTH_ALG_MD5     0x00004000

#define BCM_DESC_IPSEC_ESP        0x00010000
#define BCM_DESC_IPSEC_AH         0x00020000

#define SPU_CRA_PRIORITY		3000


struct spu_pkt_frag
{
	u8 *buf;
	int len;
	struct spu_pkt_frag *next;
};

/**
 * spu_request - descriptor submission request
 * @callback: whom to call when descriptor processing is done
 * @context: caller context (optional)
 */
struct spu_trans_req
{
#define SPU_TRANS_TYPE_IPSEC          1
#define SPU_TRANS_TYPE_ENCYPT         2
#define SPU_TRANS_TYPE_DECRYPT        3
    int type;                 /* transaction type */
    int dir;                  /* direction */
    void (*callback) (struct spu_trans_req *trans_req);
    void *context;
    void *cmd_buf;
    struct spu_pkt_frag *sfrags_list;
    int slen;
    int sfrags;
    unsigned char *dbuf;
    unsigned char *dStatus;
    struct spu_pkt_frag *dfrags_list;
    int dlen;
    int dfrags;
    int alloc_buff_spu;
    int headerLen;
    int err;
};

struct spu_info
{
    /* list of registered algorithms */
    struct list_head alg_list;

    /* hwrng device */
    struct hwrng rng;
};

struct spu_ctx
{
    u8 iv[SPU_MAX_IV_LENGTH];
    u8 crypt_key[SPU_MAX_KEY_SIZE];
    u8 auth_key[SPU_MAX_AUTH_SIZE];

    unsigned int cryptkeylen;
    unsigned int authkeylen;
    unsigned int authsize;
    __be32 desc_hdr_template;
};

#endif /* __SPU_H__ */
