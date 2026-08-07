// JTW 24 BIT BISS-C encoders

#include "Renishaw19bit.h"

#ifdef HAS_RENISHAW_19BIT

#define ENC_BISSC_NAME "REN19"

#include <stdio.h>

// initialize BiSS-C encoder
Ren19::Ren19(int16_t axis, int16_t maPin, int16_t sloPin) {
  if (axis < 1 || axis > 9) return;

  this->axis = axis;

  this->maPin = maPin;
  this->sloPin = sloPin;

  snprintf(encoderName, sizeof(encoderName), "RENISHAW_19BIT Ax%d", axis);
  encoderBits = 19;
  encoderMultiTurnBits = 0;
}

// Designed according protocol description found in as38-H39e-b-an100.pdf and
// Renishaw application note E201D02_02

// BiSS-C 6-bit CRC of 21 bit data (19 position + 2 err/wrn)
uint8_t Ren19::crc6(uint64_t data) {
  uint8_t crc;
  uint64_t idx;
  crc = ((data >> 18) & 0b111111);
  crc = ((data >> 12) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = ((data >> 6) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = (data & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = CRC6[idx];
  return (~crc & 0b111111);
}

#endif
