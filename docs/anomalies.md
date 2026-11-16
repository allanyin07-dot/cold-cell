## R0 — D1 Chapter 1: Circuits you can trust       Date: 2026-11-14
Anomaly:
- Blueprint warm-up estimate (120 mAh) exceeds ideal calculation (68 mAh). This implies about 56% heating efficiency and will be measured in V2." The heater-overhead experiment on Sun Feb 28 (V2) measures the real number.

## S1 — C from Python, Part 1        Date: 2026-11-15        Time: 7:30-9:30
Anomaly:
- `long` is 8 bytes on WSL but 4 on the STM32F401. Use stdint.h fixed-width types (uint16_t, int16_t, uint32_t) in all firmware.
- Integer division trap: `counts / 4095 * 3.3f` = 0 V with no compiler warning. Always make one operand float before dividing (e.g. `counts * 3.3f / 4095`). Check this in ntc.c (Nov 28).
