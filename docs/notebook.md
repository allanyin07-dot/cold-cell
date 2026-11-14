# Cold Cell Design Notebook
Entries go newest at the bottom.

---

# Session Entry Template
Copy this for every session.

## <Session code> — <title>        Date:        Time: start-end

Goal:

Requirements touched: R__

Predictions (write these BEFORE you start):

Setup: (photo filename, firmware commit)

What I did: (numbered steps, exactly)

What I observed: (numbers with units; data file names)

Results: (computed values with uncertainty)

Did it match my prediction? (by how much, and why not)

Anomalies:

Conclusion (1-2 sentences):

Next action:

Explain-back (3 sentences from memory, no notes):

---
## SETUP — Toolchain and repo        Date: 2026-11-11        Time: 10:00-11:30

Goal: Set up the toolchain and the project repo.

Requirements touched: None (setup session)

Predictions (write these BEFORE you start): None (setup session)

Setup: No photo (software only). Repo commit: [937555a --oneline -1]. No firmware yet.

What I did:
1. Installed Python with numpy, pandas, matplotlib, pyserial.
2. Installed WSL with Ubuntu, then build-essential (gcc), git, and gh.
3. Installed STM32CubeIDE and LTspice.
4. Authenticated GitHub from Ubuntu with gh auth login, entering the device code in my Windows browser because WSL has no browser.
5. Set my git identity (user.name and user.email).
6. In the existing cold-cell repo, created the blueprint folder structure, the five docs files, .gitkeep placeholders, and a .gitignore.
7. Resolved a rebase conflict on docs/notebook.md after a rejected push, then pushed.
8. Reset docs/notebook.md with the session template and pushed again.
9. Built the co-op application tracker with 13 target companies.

What I observed:
- Two pushes were rejected with "fetch first" (GitHub had commits my laptop lacked).
- git pull --rebase stopped on a conflict in docs/notebook.md.
- First successful push: b0d3807..4846450 main -> main.
- Tracker has 13 companies (5 Tier A, 4 Tier B, 4 Tier C).
- No data files today.

Results: Repo synced with GitHub, working tree clean. Toolchain installed and verified. No measured values, so no uncertainty.

Did it match my prediction? No predictions written. The blueprint estimated 40 min for setup; it took 1.5 hours because of WSL, authentication, and merge problems.

Anomalies:
- "sudo: not recognized" because I was in PowerShell, not Ubuntu.
- Browser failed to open during gh auth login (WSL has no browser).
- Stuck in a heredoc after pasting commands together.
- "Author identity unknown" on the first commit.
- Two rejected pushes and one notebook.md merge conflict.
- Ran commands from my home folder instead of the repo several times.

Conclusion: The toolchain and repo are ready for D1 on Saturday. Most of the time went on Git and WSL problems rather than installation.

Next action: Thu Nov 12: check the five Tier A careers pages, set job alerts, and read E1 chapter 1. Verify the careers-page links in the tracker.

Explain-back: sudo and apt only exist in Ubuntu, so PowerShell said "not recognized," and WSL has no browser, so I entered the gh login code manually at github.com/login/device. My pushes were rejected because GitHub already had commits my laptop lacked, and git pull --rebase then stopped on a conflict because notebook.md had changed on both sides, so I chose which version to keep and ran git rebase --continue. I also kept running commands from my home folder instead of cold-cell, so I should check pwd first.

## R0 — E1 Chapter 1: Basic concepts of electricity        Date: 2026-11-12

Goal: Refresh charge, voltage, current, and resistance before D1 (Sat Nov 14).

Requirements touched: none (foundation reading, module M1)

Key ideas (one line each, my own words):
- Voltage: Voltage is the amount of energy per unit charge required to move charge from one point to another point.
- Current: Current is the rate of change flow past a point; in wires it is carried by electrons
- Resistance: Resistance is the how strongly a material opposes the flow of electrons, AKA the current
- Closed circuit: A closed circuit is a circuit that has no breaks in it and allows current to flow
- Conventional vs electron flow: Conventional flow is the direction a positive charge would move from + to - and electron flow is the opposite as a negative charge would move from - to +

Project connection:
- The heater path is a closed loop: Cell+ -> fuse -> INA219 -> thermostat -> heater -> MOSFET -> Cell-. Opening the fuse, thermostat, or MOSFET stops the current. This is why each one works as an independent safety layer (Section 2.7).

Anything unclear (re-check before D1):
-Current isn’t used up by resistors; it’s the same all around a series loop.

Explain-back (3 sentences from memory, no notes):
Voltage is the amount of energy per unit charge required to move a charge between two points. Current is the rate of charge flow past a certain point while resistance is how strongly a material opposes the current. These three all relate to each other as passing through a material consumes voltage and decreases the overall current in the circuit. The difference between conventional current and electron flow is that conventional current models the direction of a positive charge moving from + to - while electron flow goes in the direction of electrons which is - to +. In schematics, conventional current is typically utilized. For the cold cell, current only flows in a closed loop so the cell's energy only reaches the heater when the loop is complete, and opening the fuse, thermostat, or MOSFET anywhere in the loop will shut the heater off

## R0 — D1 Chapter 1: Circuits you can trust       Date: 2026-11-14

Goal: The goal of today is to build the habit of predicting circuit values by hand, and confirm them in LTspice within 2%."

Requirements touched: None directly. This is foundation work for R1 (temperature measurement), which depends on the thermistor divider.

Predictions (write these BEFORE you start): I believe that my calculations and the results from LTspice will be within 5% of each other because the equations utilized are the same. Furthermore, I think the heater will draw about 0.74A and dissipate around 2.7W at 3.7V. Lastly, I think that warming the cell by 20 degrees celsius will only cost under 5% of the battery capacity.

Setup: (photo filename, firmware commit): No hardware, LTspice v26.1.1

What I did: (numbered steps, exactly):
-Read through Allaboutcircuits chapters 1-6
-Voltage out, the voltage in the node between R1 and R2 = Voltage in x R2/(R1+R2)
-Using LTspice, I calculated the voltage out by hand before comparing the results with the measurement from LTspice
-I calculated how much power a resistor with a 5W rating would take in this circuit
-Finally, I calculated the percentage of power that this heater would take from a normal 18650 cell

What I observed: (numbers with units; data file names):
-Hand Calculations:
| # | V_in (V) | R1 | R2 | V_out (V) | I (mA) |
|---|---|---|---|---|---|
| 1 | 5 | 10 kΩ | 10 kΩ | 2.5 | 0.25 |
| 2 | 3.3 | 10 kΩ | 10 kΩ | 1.65 | 0.165 |
| 3 | 3.3 | 10 kΩ | 4.7 kΩ | 1.06 | 0.224 |
| 4 | 3.3 | 10 kΩ | 22 kΩ | 2.27 | 0.103 |
| 5 | 5 | 1 kΩ | 2.2 kΩ | 3.44 | 1.56 |
| 6 | 12 | 100 kΩ | 15 kΩ | 1.57 | 0.104 |
| 7 | 4.2 | 100 kΩ | 100 kΩ | 2.10 | 0.021 |
| 8 | 3.3 | 220 Ω | 1 kΩ | 2.70 | 2.70 |
| 9 | 3.7 | 15 kΩ | 10 kΩ | 1.48 | 0.148 |
| 10 | 3.3 | 10 kΩ | 33.6 kΩ | 2.54 | 0.0757 |
-LTspice calculations and Hand Calculations: File names: d1_div3, d1_div6, d1_div10
| Divider | Hand V_out (V) | LTspice V(vout) (V) | Error (%) | Within 2%? |
|---|---|---|---|---|
| #3 | 1.0551 | 1.0551 | < 0.01 | Yes |
| #6 | 1.5652 | 1.5652 | < 0.01 | Yes |
| #10 | 2.5431 | 2.5431 | < 0.01 | Yes |

Heater Numbers/Calculations for rating %:
-Using resistors that have a 5W wattage rating, there are two resistors. Each resistor is 10 Ω. 
Parallel Resistance: R = ((1/10) + (1/10))^(-1) = 5Ω
Current: I = V/R = 3.7V/5Ω = 0.74A
Power of Battery: P = IV = 3.7V * 0.74A = 2.738 ≈ 2.7W, P = I^2R = (0.74A)^2 * 5Ω ≈ 2.7W
Since circuits are in parallel, each resistor will only have 0.74/2 = 0.37A going through
-Therefore, power each circuit will receive = (0.37^2)*10 = 1.37W
-Each resistor will only use (1.37/5)*100 = 27.4% of rating

Energy Consumption Calculations:
Q = C(deltaT), C ≈ 45 J/K, deltaT = 20K
Q = 457J/K * 20K = 900J
1 Wh = 3600 J --> 900/3600 = 0.25 Wh
Energy = voltage * charge --> charge = Energy/voltage = 900/3.7 = 243C
1 mAh = 3.6C --> 243C/3.6C = 67.6 mAh
Fraction of cell's power: (67.6/3400)*100 = 2%
Double check: 3.4 Ah * 3.7V = 12.6 Wh --> 0.25/12.6 = 2%

Results: (computed values with uncertainty):
-From calculations, the heater will only draw 2% of the cell's battery power. However, this calculation is based in an ideal scenario
-In real world, heat may leak into the air, causing more power to be drawn.
-In this case, if we double the amount to around 120 mAh, this corresponds to 1600J of energy being drawn from the cell (120 * 3.6 * 3.7)
-This implies that only around 56% of the heater's energy reaches the cell while the rest leaks into the air
-This is more realistic since in a real world, heat will escape

Did it match my prediction? (by how much, and why not):
All predicitions were matched

Anomalies:
None
Conclusion (1-2 sentences): The energy that the heater will take from the battery was successfully calculated to be within a reasonable range. Furthermore, all calculations for the wattage resistor was calculated and found to be below the max threshold.
Next action: S1 tomorrow (Sun Nov 15, 90 min): C types, variables and functions. Then the weekly review.
Explain-back (3 sentences from memory, no notes):
A voltage divider gives V_out = V_in * (R2/(R1+R2)), and this is because it only depends on the ratio of resistors 1 and 2. If both resistor values were doubled, the voltage out would remain the same. My hand calculations and LTspice agreed within 1% for dividers #3, #6 and #10, which makes sense because they utilize the same formula. The heater draws 0.74A and dissipates 1.37 W per resistor, and warming the cell by 20 K costs about 2% of its capacity, though it will likely be greater in a real world scenario

