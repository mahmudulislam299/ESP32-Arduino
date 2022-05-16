#ifndef _RADIO_H_
#define _RADIO_H_

#include "nRF24.h"
#include "nRF24_Client.h"
#include "nRF24_Qry_Common.h"

void txIsr(void);
void rxIsr(void);
void maxRtIsr(void);

void radio_begin();
void radioStart();
uint32_t millis_esp32();
uint32_t second();


extern nrfNodeConfig_t nrfConfig;
extern pong_t pong;
#endif
