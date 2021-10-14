/*  -*- tab-width: 4; c-basic-offset: 4; c-file-style: "linux"; indent-tabs-mode: nil; -*-
 */

#include "hal.h"
#include "simpleserial.h"
#include "bigint.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

uint32_t binary_exp (uint32_t message, uint32_t exponent, uint32_t modulus)
{
    trigger_high();
    uint32_t res = 1;
    while (exponent)
    {
        if (exponent & 1)
        {
            res = (res * message);
        }

        message = (message * message) % modulus;
        exponent >>= 1;
    }
    trigger_low();
    return res;
}

void bigint_exp(bigint_t *result, const bigint_t *message, const bigint_t *exponent, const bigint_t *modulus)
{
    trigger_high();
    bigint_expmod_u(result, message, exponent, modulus);
    trigger_low();
}

uint8_t rsa(uint8_t *input)
{
    bigint_t message = {
        .length_B = 4,
        .info = 0,
        .wordv = alloca(4),
    };
    memcpy(message.wordv, input, message.length_B);

    bigint_t exponent = {
        .length_B = 4,
        .info = 0,
        .wordv = alloca(4),
    };
    memcpy(exponent.wordv, input + 4, exponent.length_B);

    bigint_t modulus = {
        .length_B = 4,
        .info = 0,
        .wordv = alloca(4),
    };
    memcpy(modulus.wordv, input + 8, modulus.length_B);

    bigint_t result = {
        .length_B = 4,
        .info = 0,
        .wordv = alloca(4),
    };
    memset(result.wordv, 0, 4);

    bigint_exp(&result, &message, &exponent, &modulus);

    uint8_t *serial_result = alloca(2 + 4);
    *(uint16_t *)serial_result = result.length_B;
    memcpy(serial_result + 2, result.wordv, 4);
    simpleserial_put('r', 6, serial_result);


    /* uint32_t message = ((uint32_t *)input)[0], */
    /*     exponent = ((uint32_t *)input)[1], */
    /*     modulus = ((uint32_t *)input)[2]; */
    /* uint32_t result = binary_exp(message, exponent, modulus); */

    return 0;
}

uint8_t rsa2(uint8_t *input)
{
    uint8_t message= input[0],
        exponent = input[1],
        modulus = input[2];

    trigger_high();
    uint16_t tmp;
    uint8_t res = 1;
    while (exponent)
    {
        if (exponent & 1)
        {
            tmp = res * message;
            res = tmp % modulus;
        }

        tmp = message * message;
        message = tmp % modulus;
        exponent >>= 1;
    }
    trigger_low();

    simpleserial_put('r', 1, &res);
    return 0;
}

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    simpleserial_init();
    /* simpleserial_addcmd('r', 3 * sizeof(uint32_t), rsa); */
    simpleserial_addcmd('r', 3, rsa2);
    while(1)
        simpleserial_get();
}
