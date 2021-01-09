/***********************************************************************
 *
 *  Copyright (c) 2007  Broadcom Corporation
 *  All Rights Reserved
 *
 * <:label-BRCM:2011:DUAL/GPL:standard
 * 
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed
 * to you under the terms of the GNU General Public License version 2
 * (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
 * with the following added to such license:
 * 
 *    As a special exception, the copyright holders of this software give
 *    you permission to link this software with independent modules, and
 *    to copy and distribute the resulting executable under terms of your
 *    choice, provided that you also meet, for each linked independent
 *    module, the terms and conditions of the license of that module.
 *    An independent module is a module which is not derived from this
 *    software.  The special exception does not apply to any modifications
 *    of the software.
 * 
 * Not withstanding the above, under no circumstances may you combine
 * this software in any way with any other Broadcom software provided
 * under a license other than the GPL, without Broadcom's express prior
 * written consent.
 * 
:>
 *
 ************************************************************************/


#ifndef __CMS_FIL_H__
#define __CMS_FIL_H__

#define KILOBYTE 1024

/*!\file cms_fil.h
 * \brief Header file for file and directory utilities functions.
 */


/** Return true if the filename exists.
 *
 * @param filename (IN) full pathname to the file.
 *
 * @return TRUE if the specified file exists.
 */
UBOOL8 cmsFil_isFilePresent(const char *filename);



/** Return the size of the file.
 *
 * @param filename (IN) full pathname to the file.
 *
 * @return -1 if the file does not exist, otherwise, the file size.
 */
SINT32 cmsFil_getSize(const char *filename);



/** Copy the contents of the file to the specified buffer.
 *
 * @param filename (IN) full pathname to the file.
 * @param buf     (OUT) buffer that will hold contents of the file.
 * @bufSize    (IN/OUT) On input, the size of the buffer, on output
 *                      the actual number of bytes that was copied
 *                      into the buffer.
 *
 * @return CmsRet enum.
 */
CmsRet cmsFil_copyToBuffer(const char *filename, UINT8 *buf, UINT32 *bufSize);


/** Write the specified string into the specified proc file.
 *
 * @param procFile (IN) Name of the proc file.
 * @param s        (IN) String to write into the proc file.
 *
 * @return CmsRet enum.
 */
CmsRet cmsFil_writeToProc(const char *procFilename, const char *s);


/** Write the buffer into the specified file.
 *
 * @param filename (IN) Name of the file.
 * @param buf      (IN) Buffer to write.
 * @param bufLen   (IN) Length of buffer.
 *
 * @return CmsRet enum.
 */
CmsRet cmsFil_writeBufferToFile(const char *filename, const UINT8 *buf, UINT32 bufLen);


/** Remove specified directory.  If there are any files or sub-dirs in the
 * directory, they will be silently removed.
 *
 * @param dirname (IN) Name of the directory to remove.
 *
 * @return CmsRet enum.
 */
CmsRet cmsFil_removeDir(const char *dirname);


/** Create the specified directory.
 *
 * @param dirname (IN) Name of the directory to create.
 *
 * @return CmsRet enum.
 */
CmsRet cmsFil_makeDir(const char *dirname);


/** convert the size into KiloBytes 
 *
 * @param nblks (IN) number of blocks.
 * @param blkSize (IN) size of each block in bytes.
 *
 * @return UINT32 (size in Kilo Bytes)
 */

UINT32 cmsFil_scaleSizetoKB(long nblks, long blkSize);
#endif /* __CMS_FIL_H__ */
