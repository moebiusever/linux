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

#ifndef _APP_H_
#define _APP_H_

#define I2C_SLAVE_ADDR  0x50 /* 8-bit slave address of A1006 */
#define CERTORG_PATTERN "NXP *CA"
#define CERTCN_PATTERN "*Device*"
#define CERT_SLOT 0     /* 0 for NXP, 1 for user */
#define ENTROPY_SIZE 64 /* Must be power of 2 */
/* Define below symbol for verbose output of interface messaging, crypto objects, etc. */
#define ENABLE_SHOW_DUMP
//typedef unsigned char uint8_t;
//typedef unsigned char u8;
//typedef unsigned char uchar;
//typedef unsigned int uint32_t;

/* Define below symbol for verbose output on the certificate */
#define ENABLE_SHOW_CERT_DETAILS

/* Define below symbol to enable A1006 OWI interface. Defaults to I2C when not defined */
//#define ENABLE_A100X_INTERFACE_OWI

/* Define below symbol to enable support for legacy test CA. Test/production CA selection based on UID if enabled */
#define ENABLE_A100X_TEST_CA_SUPPORT

/* Replace with diversified Host UID (up to 16 bytes) */
#define HOST_UID "A1006 Host UID"

/*******************************************************************************
 * resources for softTimer module                                              *
 *******************************************************************************/
#define SOFTTIMER_TIMER LPC_TIMER32_1
#define SOFTTIMER_TIMER_IRQn TIMER_32_1_IRQn
#define SOFTTIMER_TIMER_IRQ_HANDLER TIMER32_1_IRQHandler

/*******************************************************************************
 * resources for entropy module                                                *
 *******************************************************************************/
//#define ENTROPY_PORT 1
//#define ENTROPY_PIN 1
//#define ENTROPY_IOCON_OFFSET IOCON_PIO1_1
//#define ENTROPY_IOCON_VALUE (FUNC2)
//#define ENTROPY_ADC_CHANNEL ADC_CH2

/*******************************************************************************
 * resources for A100x module                                                  *
 *******************************************************************************/
/* I2C */
#define A100X_INTERFACE_I2C I2C0
#define A100X_INTERFACE_I2C_RESET RESET_I2C0
#define A100X_INTERFACE_I2C_IRQn I2C0_IRQn
#define A100X_INTERFACE_I2C_IRQ_HANDLER I2C_IRQHandler
#define A100X_INTERFACE_I2C_SCL_PORT 0
#define A100X_INTERFACE_I2C_SCL_PIN 4
#define A100X_INTERFACE_I2C_SCL_IOCON_OFFSET IOCON_PIO0_4
#define A100X_INTERFACE_I2C_SCL_IOCON_VALUE (IOCON_FUNC1)
#define A100X_INTERFACE_I2C_SDA_PORT 0
#define A100X_INTERFACE_I2C_SDA_PIN 5
#define A100X_INTERFACE_I2C_SDA_IOCON_OFFSET IOCON_PIO0_5
#define A100X_INTERFACE_I2C_SDA_IOCON_VALUE (IOCON_FUNC1)
/* OWI */
#define A100X_INTERFACE_OWI_PORT 1
#define A100X_INTERFACE_OWI_PIN 10
#define A100X_INTERFACE_OWI_IOCON_OFFSET IOCON_PIO1_10
#define A100X_INTERFACE_OWI_IOCON_VALUE (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN | IOCON_OPENDRAIN_EN)
#define A100X_INTERFACE_OWI_TIMER LPC_TIMER16_1
#define A100X_INTERFACE_OWI_TIMER_IRQn TIMER_16_1_IRQn

#endif /* _APP_H_ */
