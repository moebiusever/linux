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

#ifndef _A100X_INTERFACE_H_
#define _A100X_INTERFACE_H_

/*!
 * @addtogroup a100x_interface
 * @{
 * @brief A100x interface routines to communicate with the A100x over OWI or I2C.
 */

/*! @file */
#include "common.h"
#include <linux/i2c.h>
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Send data to and receive data from A100x.
 *
 * @param addr      A100x slave address
 * @param sendbuf   Buffer containing data to send to A100x
 * @param sendsize  Length of transmit data
 * @param recvbuf   Buffer to store information when reading. Can be null when recvsize == 0
 * @param recvlen   Pointer where to store number of bytes read. Can be null when recvsize == 0
 * @param recvsize  Specifies number of bytes to read, can be 0 when only transmitting
 *
 * @return 0 on success\n
 *         != 0 on error
 */
uint32_t a100x_interface_sendrecv(struct udevice *dev,
				  uint8_t *sendbuf,
                                  const uint32_t sendsize,
                                  uint8_t *recvbuf,
                                  const uint32_t recvsize);
/*! @}*/

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif // _A100X_INTERFACE_H_
