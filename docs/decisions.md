

ADR-02 (D3, 2026-11-21): NTC divider fixed resistor = 10 kΩ (provisional)
- Forced by: R1 needs ±1 °C from -20 to +60 °C; the critical range is -20 to +10 °C (charge lockout at 3 °C), and the 40 °C over-temperature cutoff also needs good resolution.
- Options: 4.7 k, 10 k, 22 k, 47 kΩ (simulated sensitivity in the D3 notebook entry and data/processed/ntc_sensitivity.png).
- Chose: 10 kΩ. Worst case 20 counts/°C at -20 °C (0.05 °C per count), 20× finer than R1. Matches R0; keeps 37 counts/°C at 40 °C vs 15 for 47 k. 22 k is the strongest alternative (36-52 cold, 26 at 40 °C).
- Makes harder: about 40% less cold-range resolution than 22 k. Revisit if W3 (Dec 26) shows ADC noise above a few counts.
