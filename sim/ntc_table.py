import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


R0 = 10000
T0_K = 298.15
BETA = 3950
R_FIXED = 10000
ADC_MAX = 4095

def ntc_resistance(temp_c):
    t_k = temp_c + 273.15
    return R0 * np.exp(BETA * (1/t_k - 1/T0_K))

def adc_counts(r_ntc, r_fixed=R_FIXED):
    return ADC_MAX * r_ntc / (r_fixed + r_ntc)

temps = np.arange(-20, 61, 5)
r = ntc_resistance(temps)
counts = adc_counts(r)
temps_fine = np.arange(-20, 60.5, 0.5)
for rf in [4700, 10000, 22000, 47000]:
    counts_rf = adc_counts(ntc_resistance(temps_fine), r_fixed=rf)
    sens = np.abs(np.gradient(counts_rf, temps_fine))
    plt.plot(temps_fine, sens, label=f"{rf/1000:g}k")
    print(rf, np.interp([-20, 0, 25, 60], temps_fine, sens).round(1))
plt.xlabel("Temperature (°C)")
plt.ylabel("Sensitivity (counts per °C)")
plt.title("NTC divider sensitivity vs fixed resistor")
plt.legend()
plt.grid(True)
plt.axvspan(-20, 10, alpha=0.1)
plt.savefig("data/processed/ntc_sensitivity.png", dpi=150)
plt.show()
df = pd.DataFrame({"temp_c": temps, "r_ntc_ohm": r.round(0), "counts": counts.round(1)})
print(df.to_string(index=False))
df.to_csv("data/processed/ntc_table.csv", index=False)


