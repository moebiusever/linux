// ############################################################################
// #             Copyright (C), NXP Semiconductors                            #
// #                       (C), NXP B.V. of Eindhoven                         #
// #                                                                          #
// # All rights are reserved. Reproduction in whole or in part is prohibited  #
// # without the written consent of the copyright owner.                      #
// # NXP reserves the right to make changes without notice at any time.       #
// # NXP makes no warranty, expressed, implied or statutory, including but    #
// # not limited to any implied warranty of merchantibility or fitness for    #
// # any particular purpose, or that the use will not infringe any third      #
// # party patent, copyright or trademark. NXP must not be liable for any     #
// # loss or damage arising from its use.                                     #
// ############################################################################

#ifndef _ROOT_H_
#define _ROOT_H_

/*!
 * @addtogroup a100x
 * @{
 */

/*! @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "app.h"

#define hostUIDsize (sizeof(HOST_UID) - 1)

/*!
 * @name Constants
 * @{
 */

/*!
 * @brief NXP root CA public key for test samples.
 *
 * Uncompressed NIST-P224 (secp224r1) public key as uncompressed (x, y) coordinates, in little endian encoding and right
 * zero padded. Must be specified as 32-bit unsigned int for correct allignment.
 */
const uint32_t testRootPub[] = {0x19BD7FEE, 0x64DAF9DD, 0x6940EBE7, 0xEFC1CF82, 0x1C51B388, 0x3F2F754F, 0x321553F2,
                                0x0D41D6B4, 0x74773EEE, 0x2E468820, 0x229D400B, 0x2CBBE5C4, 0x96F57258, 0x2ECB5539};

/*!
 * @brief NXP root CA public key for production devices.
 *
 * Uncompressed NIST-P224 (secp224r1) public key as uncompressed (x, y) coordinates, in little endian encoding and right
 * zero padded. Must be specified as 32-bit unsigned int for correct allignment.
 */
const uint32_t prodRootPub[] = {0x4BBA911B, 0x3E3CF675, 0x972C8450, 0x5DEC45F2, 0xBEB4FA70, 0x3197ED8D, 0x25D04121,
                                0x717306EC, 0xC0BB9C7A, 0xBAA611C1, 0x266C80B8, 0xC99F95C3, 0xEA3685F5, 0x6935C983};

/*! @brief Diversified host UID */
const uint8_t *hostUID = (uint8_t *)HOST_UID;

/*! @}*/

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif // _ROOT_H_
