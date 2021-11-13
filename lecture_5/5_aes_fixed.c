/*  -*- tab-width: 4; c-basic-offset: 4; c-file-style: "linux"; indent-tabs-mode: nil; -*-
 */

#include "hal.h"
#include "simpleserial.h"
#include "aes-independant.h"
#include <stdint.h>
#include <string.h>

static uint8_t aes_key[16] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
};

uint8_t aes(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    trigger_high();

	aes_indep_enc(buf);
	trigger_low();
    return 0;
}

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    aes_indep_init();
    aes_indep_key(aes_key);

    simpleserial_init();
    simpleserial_addcmd(0x01, 16, aes);
    while(1)
        simpleserial_get();
}
