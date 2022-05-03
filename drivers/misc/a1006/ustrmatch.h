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

#ifndef _USTRMATCH_H_
#define _USTRMATCH_H_
#include "common.h"
/*!
 * @addtogroup ustrmatch
 * @{
 * @brief Wildcard '*' & '?' unsigned character string matching.
 */

/*! @file */

/*!
 * @name Module version
 * @{
 * @brief Version 1.0.0
 */
#define USTRMATCH_VERSION \
    (((USTRMATCH_VERSION_MAJOR) << 16) | ((USTRMATCH_VERSION_MINOR) << 8) | (USTRMATCH_VERSION_REVISION))
#define USTRMATCH_VERSION_MAJOR 1
#define USTRMATCH_VERSION_MINOR 0
#define USTRMATCH_VERSION_REVISION 0
/*! @} */

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Matches the specified string against a null terminated pattern which may contain path-like wildcard
 * characters: '*' and '?'.
 *
 * @param upattern  Null-terminated pattern which may contain path-like wildcard characters: '*' and '?'
 * @param ustr      String to match against the pattern
 * @param ustrlen   Length of the string to match against the pattern (excluding optional null character)
 *
 * @return 0 on match\n
 *         != 0 on mismatch
 */
uint32_t ustrmatch(const uint8_t *upattern, const uint8_t *ustr, const uint32_t ustrlen);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif // _USTRMATCH_H_
