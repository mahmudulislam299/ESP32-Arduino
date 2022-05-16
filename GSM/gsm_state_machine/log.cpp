#include "log.h"





String create_payload()
{
    String payload = "[[22,{\"id\":\"B2008\",\"ts\":\"";
    uint32_t time = getUnixTime();
    payload = payload + String(time);
    payload = payload + String("\",\"data\":[80,80,80,80,80,80,80,80,80,80]}]]");

    Serial.println(payload);
    return payload;
}
