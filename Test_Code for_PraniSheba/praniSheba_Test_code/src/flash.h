#ifndef FLASH_H
#define FLAH_H

void flashBegin();
void flashCheck(int command) ;
void flashCheckAuto();


void read(bool automation = false);
bool write(bool automation = false);
void eraseSector(bool automation = false);
void eraseAllChip(bool automation = false);


#endif // !FLASH_H
