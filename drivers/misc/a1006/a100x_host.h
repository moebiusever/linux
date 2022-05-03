// ############################################################################
// #             Copyright (C), NXP Semiconductors                            #
// #                       (C), NXP B.V. of Eindhoven                         #
// #                                                                          #
// # All rights are reserved. Reproduction in whole or in part is prohibited  #
// # without the written consent of the copyright owner.                      #
// # NXP reserves the right to make changes without notice at any time.       #
// # NXP makes no warranty, expressed, implied or statutory, including but    #
// # not limited to any implied warranty of merchantability or fitness for    #
// # any particular purpose, or that the use will not infringe any third      #
// # party patent, copyright or trademark. NXP must not be liable for any     #
// # loss or damage arising from its use.                                     #
// ############################################################################

#ifndef _A100X_HOST_H_
#define _A100X_HOST_H_

#include "common.h"
#include <linux/i2c.h>
#include "a1006.h"

/*!
 * @addtogroup a100x
 * @{
 * @brief A100x host routines to decompress and validate A100x certificates, as well as to generate A100x authentication
 * challenge and validate response. The module needs to be initialized before any of the other functions can be used.
 */

/*! @file */

/*!
 * @name Module version
 * @{
 * @brief Version 1.1.1
 */
#define A100X_VERSION (((A100X_VERSION_MAJOR) << 16) | ((A100X_VERSION_MINOR) << 8) | (A100X_VERSION_REVISION))
#define A100X_VERSION_MAJOR 1
#define A100X_VERSION_MINOR 1
#define A100X_VERSION_REVISION 1
/*! @} */

/*! @brief Minimum size of interface buffer when reading UID. */
#define IFBUF_UID_SIZE 18
/*! @brief Minimum size of interface buffer when downloading root certificate. */
#define IFBUF_DLCERT_SIZE 148 /* 148=(16+128)+2*2 */
/*! @brief Minimum size of interface buffer when uploading root certificate. */
#define IFBUF_ULCERT_SIZE 216 /* 216=(16+128)/4*6 */
/*! @brief Minimum size of interface buffer for challenge response validation. */
#define IFBUF_AUTH_SIZE 47 /* 47=max(47,46)    */

/*! @brief Wake-up values for A100x powerDown mode. */
typedef enum
{
    a100x_wake_on_i2c = 0x01,
    a100x_wake_on_owi_low_pulse = 0x02,
    a100x_wake_on_owi_high_pulse = 0x04,
} A100x_powerDown_parameter;

/*! @brief Structure to hold certificate. */
typedef struct
{
    uint8_t uid[8], certz[128];
} a100x_host_certData_t;

/*! @brief Structure to hold authentication data. */
typedef struct
{
    uint8_t random[21], challenge[44], response[44];
    uint32_t timing;
} a100x_host_authData_t;

#ifdef __cplusplus
extern "C" {
#endif

int a100x_host_init(uint8_t *entBuf, uint32_t entBufSize);

int a100x_host_uid(a1006_dev_t *dev, const uint32_t userRead, uint8_t *ifBuf);

int a100x_host_cert(a1006_dev_t *dev,
                         const uint32_t userRead,
                         const uint32_t *rootPub,
                         uint8_t *ifBuf,
                         uint8_t *cert,
                         a100x_host_certData_t *certData);

int a100x_host_auth(a1006_dev_t *dev,
                         const uint8_t *hostUID,
                         const uint32_t hostUIDsize,
                         const uint8_t *pubKey,
                         uint8_t *ifBuf,
                         a100x_host_authData_t *authData);

int a100x_host_cipher_check(a1006_dev_t *dev);
int a100x_host_write_cipher(a1006_dev_t *dev);
int a100x_host_iclock(a1006_dev_t *dev);

int a100x_host_ic(a1006_dev_t *dev);

int a100x_host_changeAddr(a1006_dev_t *dev, const uint32_t newAddr);

int a100x_host_softReset(void);

int a100x_host_powerDown(a1006_dev_t *dev, const A100x_powerDown_parameter wakeupSrc);

void a100x_host_wakeUp(a1006_dev_t *dev);

int a100x_host_writeData(a1006_dev_t *dev,
                              const uint32_t memoryAddr,
                              const uint8_t *data,
                              const uint32_t dataSize);

int a100x_host_readData(a1006_dev_t *dev,
                             const uint32_t memoryAddr,
                             uint8_t *data,
                             const uint32_t dataSize);

int a100x_host_status(a1006_dev_t *dev);

/*! @}*/

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif // _A100X_HOST_H_
