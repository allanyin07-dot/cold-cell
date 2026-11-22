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

---
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

---
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

---
## S1 — C from Python, Part 1        Date: 2026-11-15        Time: 7:30-10:30

**Goal:** Write, compile and run five small C programs, and explain how C's types and integer division differ from Python's.

**Requirements touched:** None directly. Foundation for R1 and R2 firmware (ntc.c Nov 28, INA219 driver Dec 29).

**Predictions (write these BEFORE you start):**
- sizeof(int) will print 4
- 5 / 2 will print 2, and 5.0 / 2 will print 2.5
- A uint8_t holding 255, plus 1, will become 0
- Converting 3156 ADC counts with counts / 4095 * 3.3 will print 0.000 V

**Setup:** Laptop only. Compiler: gcc (Ubuntu 15.2.0-16ubuntu1) 15.2.0. Route A (WSL). Files: practice/c/s1/p1–p5. Firmware commit: n/a.

**What I did:**
1. Installed gcc in WSL. First attempt at `apt install build-essential` hit 404 errors until I ran `apt update` first. Now on Route A.
2. Beej reading, chapters 2–4, 6 (skim), 14, 37; I read through the textbook about coding in C. Built my Python-vs-C table and type-size table.
3. hello.c; to practice setting stdio.h and print hello world in main function. Typed `studio.h` instead of `stdio.h`; the error at 2:11 caused a knock-on `printf` error. Fixed, prints "Hello, World!".
4. p1_float.c; to practice setting floats and printing them. Heater current and power printed with %f, %.2f and %.1f. Learned `%%` prints a literal %. Used the given printf lines for 3d.
5. p2_sizes.c; to practice printing out sizes of variables. `long` = 8 bytes on WSL (4 on STM32). uint8_t 255 + 1 = 0. 0xFFF6 = 65526 unsigned, −10 as int16_t.
6. p3_divider.c; to practice setting a function and calling it. `divider_vout()` gave #3 = 1.0551 V and #10 = 2.5431 V, both matching D1.
7. p4_loop.c; to practice creating for loops and using the loop and functions to sort through information. Three arrays + a for loop over all ten D1 dividers; all rows match the answer key.
8. p5_division.c; to practice and learn how C reads floats and integer division. `5%%2` failed to compile (%% only works inside quotes); `%d` with 5.0/2 gave a -Wformat warning, fixed with %f. counts/4095*3.3f = 0.000 V vs counts*3.3f/4095 = 2.543 V.

**Notes:**
**How a C program runs (3 steps):**
1. Edit: write or change the `.c` file in VS Code and save it.
2. Compile: `wsl gcc -std=c11 -Wall -Wextra -o hello.out hello.c` turns the source into a program (`hello.out`). You can combine multiple .c files and -std=c11 tells it what C version to run
3. Run: `wsl ./hello.out` runs the compiled program, not the `.c` file.
Recompile after every edit, or I'll run the old version.
4. `#include <stdio.h>`: pulls in the standard input/output library so I can use `printf`. Roughly like `import` in Python. (Typing `studio.h` broke it today.)
5. `int main(void)`: where the program starts running. Python runs a script top to bottom; C always starts at `main`. `return 0;` at the end means "finished OK".
6. In C, setting variables requires you to identify the type of variable first before defining it
- Eg. int A = 1, float B = 2.5f (if the float has a decimal, it needs an f suffix at the end), char C = 'c', char * D = "Hello"
- Booleans are the same as python like 0 is false except anything else is true; bool needs #include <stdbool.h>
- If i is a variable, i ++ adds 1 to i and i -- subtracts 1 from i
- To print the size of a variable or expression, use %zu then sizeof()
- If and else statements --> if (condition) { code }
- Python: for i in range(10): → C for (int i = 0; i < 10; i++). This is the same as: while (i < 10)
7. C copies each argument into the parameter, so the function only changes its own copy.
8. C reads top to bottom, so a function must be defined or declared (with a prototype) above the line that calls it.
9. Empty parameter lists: write `(void)` for "no arguments", e.g. `int main(void)`. Before C23 we use C11, `()` means "unknown arguments" and the compiler won't check calls.
10. Function defining example in C: float heater_power(float v, float r)
11. Signed int vs Unsigned int: signed types hold negatives and positives; unsigned types hold only 0 and up, but reach twice as high. Going past an unsigned type's max wraps around to 0.
12. short / long: C doesn't fix their sizes; they depend on the machine. `long` is 8 bytes on my laptop (WSL) but 4 on the STM32.
13. Fixed-width types (`#include <stdint.h>`): `uint8_t`, `uint16_t`, `int16_t`, `uint32_t`. The number is the number of bits (8 bits = 1 byte); `u` = unsigned. Same size on every machine, which is why firmware uses them.
### Python vs C Table
| Concept | Python | C |
| --- | --- | --- |
| Declare a variable | `x = 5` | `int x = 5;` |
| Decimal number | `b = 2.4` | `float b = 2.4f` |
| Divide two whole numbers | `7 / 2` → 3.5 | `7 / 2` → 3 |
| Floor division | `7 // 2` → 3 |  N/A It starts a comment |
| Remainder | `7 % 2` → 1 | `7 % 2` → 1 |
| Counting loop | `for i in range(10):` | `for (int i = 0; i < 10; i++)` |
| Print with 2 decimals | `print(f"{v:.2f}")` | `printf("%.2f\n", v);` |
| Comment | `# text` | `// text` |
| Function changes its argument? | No (for numbers) | No — it gets a copy |
| Print signed whole number | `print(n)` | `printf("%d\n", n);` |
| Print unsigned whole number | `print(n)` | `printf("%u\n", n);` |
| Print float | `print(f"{v:.2f}")` | `printf("%.2f\n", v);` |
| Print a sizeof result | `print(len(x))` | `printf("%zu\n", sizeof(x));` |
| Print hex | `print(hex(n))` | `printf("%X\n", n);` |
### Type sizes
| Type | Predicted bytes | Measured bytes (WSL) | Range |
| --- | --- | --- | --- |
| `char` | 1 | 1 | - |
| `int` | 1 | 4 | −2,147,483,648 to 2,147,483,647 |
| `long` | 8 (WSL) / 4 (STM32) | 4 | depends on the machine |
| `float` | 4 | 4 | about 7 sig figs |
| `double` | 8 | 8 | about 15 sig figs |
| `uint8_t` | 1 | 1 | 0 to 255 |
| `uint16_t` | 2 | 2 | 0 to 65,535  |
| `int16_t` | 2 | 2 | −32,768 to 32,767 |
| `uint32_t` | 4 | 4 | 0 to 4,294,967,295 |
**Predictions:**
- Wraparound: a `uint8_t` at 255, plus 1, will print **0** (it passes its max of 255 and wraps to 0). Max is 2^bits − 1 (2^8 − 1 = 255)
- Sign test: `uint16_t raw = 0xFFF6` will print 65526 as unsigned and −10 as `(int16_t)raw`.
- 5/2 = 2
- 5%2 = 1
- 5.0/2 = 2.5
- (float)5 = 2 = 2.5
- (float)(5/2) = 2.0
- uint16_t counts = 3156;: counts / 4095 * 3.3f -> 0
- same counts: counts * 3.3f / 4095 -> 2.5432
**What I observed:**
- Heater: R = 5.0 ohm, I = 0.74 A
- P (%f)   = 2.738000 W
- P (%.2f) = 2.74 W
- P (%.1f) = 2.7 W
- Divider #3 = 1.0551 V, Divider #10 = 2.5431 V.

Program 2 (p2_sizes.c):
```
char:     1 bytes
int:      4 bytes
long:     8 bytes
float:    4 bytes
double:   8 bytes
uint8_t:  1 bytes
uint16_t: 2 bytes
int16_t:  2 bytes
uint32_t: 4 bytes
u: 0
raw: 65526
int16_t raw: -10
```

Program 5 (p5_division.c):
```
2
1
2.500000
2.500000
2.000000
0.000 Vbad, 2.543 Vgood
```

**Results:**
- All 9 measured sizes matched my predictions; `long` is 8 bytes on WSL (vs 4 on STM32).
- p3: #3 = 1.0551 V, #10 = 2.5431 V, both exact matches with D1.
- p4 reproduced all ten D1 dividers; largest difference from the answer key: none (all rows matched).
- p5: integer division gave 0.000 V for the ADC conversion; reordering to multiply by 3.3f first gave the correct 2.543 V.
**Anomalies:**
- gcc wasn't installed in WSL. `apt install build-essential` failed with 404 errors (stale package list); fixed by running `apt update` first.
- hello.c: typed `studio.h` instead of `stdio.h`. The first error (line 2, col 11) caused a knock-on "implicit declaration of printf" error. Lesson: fix the first error first.
- p2: ran `./p2.out` before compiling → "No such file or directory". Must compile before running, and recompile after every edit.
- p2: `long` measured 8 bytes on WSL, but it's 4 on the STM32. Code that assumes a size can work on the laptop and break on the board → use stdint.h types in firmware.
- p5: wrote `5%%2` in code; `%%` only works inside a format string, so it didn't compile. Fixed to `5%2`.
- p5: used `%d` for `5.0/2` (a double) → -Wformat warning. Fixed with `%f`. -Wall caught it before it printed garbage.
- p5: `counts / 4095 * 3.3f` silently gives 0.000 V with no warning from gcc. Real firmware risk for the ADC conversion.
- Session ran well past the 90-minute limit (setup and compiler install took most of the extra time).
**Checkpoint:**
- Explained why 5/2 is 2 in C and how to get 2.5: PASS
- Why 2: 5 and 2 are both integers, so C does integer division and truncates the decimal.
- How to get 2.5: make one operand a decimal: `5.0/2`, `5/2.0` or `(float)5/2`.
- Why `(float)(5/2)` gives 2.0: the brackets run first, so 5/2 is already 2 before the cast turns it into 2.0.

**Conclusion:**
- C makes number types explicit, unlike Python. Integer division and type sizes are the traps that matter for firmware: ordering the ADC conversion wrong silently gives 0 V.

**Next Action:** 
- Weekday career slots Mon–Fri. D2 Thu Nov 19 (datasheets, 30 min). D3 Sat Nov 21 (thermistor and ADC, 2 h). S2 Sun Nov 22 (C part 2, 90 min).

**Explain-back:**
- In C, 5/2 is 2 because they are both integers, and to get 2.5, one of them has to be a float. On my laptop int is 4 bytes and long is 8 (but long is 4 on the STM32), which is why firmware uses fixed-width types like uint16_t and int16_t: they're the same size on every machine.Converting ADC counts with counts / 4095 * 3.3 gives 0 because counts / 4095 is integer division and truncates to 0 first, so the fix is to multiply by 3.3f first (counts * 3.3f / 4095).

## Weekly review — week of Nov 11–15        Date: 2026-11-15
Done: D1 (PASS), S1 (PASS), gcc installed; Everything Done
Slipped (and where it moved): Nothing
Next week's sessions: D3 Sat Nov 21 (2 h), S2 Sun Nov 22 (90 min)
Conflicts next week: Midterm Wednesday
One thing I learned this week: integer division silently zeroes the ADC conversion; type order matters.
Reminder set: Google Task for Wed Nov 18, book co-op coordinator meeting.

## D2 · How to read a datasheet: Fri Nov 20, 11:10–11:45

### Video notes (A3)

**Source:** <EEVblog / Phil's Lab — video title>, watched 11:12–11:22

**Usual section order (TI-style datasheet):**
Features → Applications → Description → Pin configuration → Specifications
(Absolute max → ESD → Recommended operating conditions → Thermal → Electrical
characteristics → Typical characteristics graphs) → Detailed description
(block diagram, functional modes, programming, register map) → Application and
implementation → Power supply recommendations → Layout → Package/mechanical

**Absolute Maximum Ratings vs Recommended Operating Conditions:**
- Absolute max = limits where the part may be *damaged*. Not a place to operate;
  nothing is guaranteed there.
- Recommended operating conditions = the range where the part is *guaranteed* to
  meet its electrical characteristics. Design inside this range, with margin.

**How to read a spec table:**
- Only MIN/MAX values are guaranteed. TYP is "usually", so never design to TYP.
- Every number is only valid under the test conditions in its column
  (supply voltage, temperature, load). Check them before quoting a value.
- Typical-characteristics graphs show trends, not guarantees.
- Read the footnotes: they often change what a number means.

**How I'll use a datasheet:** go in with a specific question, use Ctrl+F to find
the section, record the number *with its conditions and units*, and cite the
page/table in the notebook.

### Overview:
**What it is:** The INA219 is a current and power monitor that talks over I²C.
It measures the small voltage across a shunt resistor (to get current) and the
bus supply voltage, then calculates power internally.

**Key facts from page 1:**
- Senses buses from 0 to 26 V; the chip itself runs on a 3.0–5.5 V supply
- Reports shunt voltage, bus voltage, current and power over I²C
- 12-bit ADC, with a programmable gain on the shunt input
  (full-scale ±40, ±80, ±160 or ±320 mV)
- 16 selectable I²C addresses (set by the A0/A1 pins)
- Works high-side or low-side
- Current and power only read correctly once the Calibration register is set

**Why it's in Cold Cell:** 
-It measures the cell's current and voltage
through a shunt (tiny resistor), so the firmware can track charge/discharge and calculate
capacity lost in the cold.
**Shunt:** 
-Small precise resistor in the current path; INA219 reads the voltage across it and uses V = IR to get current
**Bus voltage:** 
-Voltage of the monitored supply line to ground
  (in Cold Cell ≈ the cell voltage)
### Register Map:
Source: INA219 datasheet p.21–23 (register descriptions)

| Addr | Register      | Access     | LSB                    |
|------|---------------|------------|------------------------|
| 00h  | Configuration | Read/write | —                      |
| 01h  | Shunt voltage | Read-only  | 10 µV (signed)         |
| 02h  | Bus voltage   | Read-only  | 4 mV (shift right 3)   |
| 03h  | Power         | Read-only  | 20 × Current_LSB       |
| 04h  | Current       | Read-only  | Current_LSB (I set it) |
| 05h  | Calibration   | Read/write | —                      |

**LSB = value of one count; real value = raw × LSB**
- Bus voltage value sits in bits 15–3; low bits are flags
  (CNVR = conversion ready, OVF = math overflow)
- I only write two registers: Configuration and Calibration
- Config and Calibration are written once at startup (Config first, then Cal),
and again after any reset, since Cal resets to 0 and Current/Power read 0**
### Calibration Equation:
Source: INA219 datasheet p.12, Programming the Calibration Register (Eq. 1–3)

1. Current_LSB = Max Expected Current / 2^15            [A/bit]
2. Cal = trunc( 0.04096 / (Current_LSB × R_shunt) )     [R_shunt in Ω]
3. Power_LSB = 20 × Current_LSB                          [W/bit]

- Round Current_LSB *up* to a convenient number to make conversion easier
- The Calibration register scales the shunt reading into the Current register;
  without it, Current and Power read 0
- Worked example on p.26: 15 A max → 457.78 µA/bit → rounded to 1 mA/bit

### Accuracy:
Source: INA219 datasheet p.5, Electrical Characteristics
(at 25 °C, VS = 3.3 V, PGA /1 unless noted). Design to MAX, not TYP.

| Parameter                   | INA219A MAX | INA219B MAX | Over −25 to 85 °C |
|-----------------------------|-------------|-------------|-------------------|
| Shunt offset (PGA /1)       | ±100 µV     | ±50 µV      | drift 0.1 µV/°C   |
| Current measurement error   | ±0.5%       | ±0.3%       | A ±1%, B ±0.5%    |
| Bus voltage error           | ±0.5%       | ±0.5%       | ±1% (both)        |

- Shunt offset grows with gain: PGA /8 → A ±200 µV, B ±100 µV
- Recommended operating temp: −25 to 85 °C. Cold Cell's −18 °C test is inside
  this range, so the INA219 itself stays within spec in the cold.
- Absolute max: supply 6 V, inputs 26 V

### Explain-Back:
1. The INA219's current reading depends on the Calibration register, which I
   calculate from the Current_LSB (max expected current / 2^15) and the shunt
   resistance (resistance of the tiny resistor on path). LSB (least significant bit) is the real-world value of one
   count, so real value = raw counts × LSB.
2. Absolute Maximum ratings differ from recommended operating conditions because those are the ratings at which the device can break or have a reduced lifespan whereas recommended operating conditions are the range where the part is guaranteed to meet its electrical characteristics, so I design inside those.
3. To find a part's accuracy, I go to the electrical characteristics page on the data sheet and check the values at the specific voltage and temperature

## D3 — The thermistor and the ADC        Date: 2026-11-21        Time: 18:00-19:30

Goal: Build a table of thermistor resistance and ADC counts from -20 to +60 °C, check it by hand, and use a sensitivity plot to justify the fixed-resistor value.

Requirements touched: R1 (cell temperature within ±1.0 °C over -20 to +60 °C; out-of-range readings flagged as faults)

Constants: T0 = 298.15 K, R0 = 10 kΩ, B = 3950, 12-bit ADC (0-4095), NTC on the bottom of the divider.

Predictions (written BEFORE computing):

| Question | Prediction | Actual | Match? |
| --- | --- | --- | --- |
| Counts at 25 °C | 2048 (first guess 4095) | 2047.5 | ✓ after correcting |
| Counts at 0 °C | 3000 | 3156.2 | ✓ close (5% low) |
| Counts at -20 °C | 4000 | 3740.1 | ~ 7% high; counts flatten near 4095 |
| Colder → counts up or down? | Up (first guess Down) | Up | ✓ after correcting |
| Most sensitive R_fixed, -20 to +10 °C | 47 k | 47 k (mean 53 counts/°C); 22 k 48; 10 k 33 | ✓ |
| Unplugged thermistor reads | 0 | 4095 | ✗ (0 = shorted, not open) |

Setup: Laptop only, no hardware. Script: sim/ntc_table.py. Outputs: data/processed/ntc_table.csv, data/processed/ntc_sensitivity.png. Firmware commit: n/a.

What I did:
1. Learned the Beta equation and solved it for R: R = R0 · exp[B·(1/T - 1/T0)], T in kelvin.
2. Divider to counts (NTC on the bottom): counts = 4095 × R_ntc / (R_fixed + R_ntc).
3. Wrote sim/ntc_table.py: ntc_resistance() and adc_counts(), applied to -20…60 °C in 5 °C steps, printed and saved to CSV.
4. Hand-checked 0, 25 and -20 °C on a calculator: all within 1 count of the script.
5. Sensitivity for 4.7 k, 10 k, 22 k, 47 k: np.gradient of counts vs temperature on a 0.5 °C grid, plotted and saved.
6. Fixes along the way: typo 'pands' → 'pandas'; numpy missing, installed with python -m pip; VS Code used a different interpreter than PowerShell, so ran from PowerShell.

What I observed (data/processed/ntc_table.csv):

| T (°C) | R_ntc (Ω) | Counts |
| --- | --- | --- |
| -20 | 105385 | 3740.1 |
| -15 | 77898 | 3629.1 |
| -10 | 58246 | 3495.0 |
| -5 | 44026 | 3337.0 |
| 0 | 33621 | 3156.2 |
| 5 | 25925 | 2955.1 |
| 10 | 20175 | 2737.9 |
| 15 | 15837 | 2510.1 |
| 20 | 12535 | 2277.9 |
| 25 | 10000 | 2047.5 |
| 30 | 8037 | 1824.7 |
| 35 | 6506 | 1614.0 |
| 40 | 5301 | 1418.8 |
| 45 | 4348 | 1241.0 |
| 50 | 3588 | 1081.4 |
| 55 | 2978 | 939.8 |
| 60 | 2486 | 815.4 |

Hand check: 0 °C 33621 Ω / 3156.2; 25 °C 10000 Ω / 2047.5; -20 °C 105385 Ω / 3740.1. Difference from script: 0 counts.

Sensitivity (counts per °C, simulated):

| R_fixed | -20 °C | 0 °C | 25 °C | 60 °C | Best region |
| --- | --- | --- | --- | --- | --- |
| 4.7 kΩ | 10.4 | 23.3 | 39.6 | 33.1 | Warm, peak near 35 °C |
| 10 kΩ | 20.2 | 38.3 | 45.5 | 23.4 | Room temp, peak near 18.5 °C |
| 22 kΩ | 36.4 | 51.8 | 39.1 | 13.4 | Near 0 °C, peak near 2.5 °C |
| 47 kΩ | 54.0 | 52.7 | 26.3 | 7.0 | Cold, peak near -11 °C |

Results: Checkpoint 3156.2 counts at 0 °C and 2047.5 at 25 °C. 10 kΩ's worst case in range is 20 counts/°C (about 0.05 °C per count), 20× finer than R1 needs.

Did it match my prediction? Mostly after correcting the divider direction before computing. Wrong first: counts fall when colder (the NTC is the bottom resistor, so more resistance gives more counts), and unplugged reads 0 (it reads 4095; 0 means a short).

Anomalies: sensitivity peaks sit where R_ntc ≈ 1.3 × R_fixed, a few °C colder than the R_ntc = R_fixed rule of thumb, because the thermistor itself changes faster in the cold.

M2 exit test: An unplugged thermistor reads near 4095 because, with no thermistor, no current flows through the fixed resistor, so it drops 0 volts and the pin sits at the full 3.3 V. It must be a fault because 4095 is what an infinitely cold thermistor would read, which never happens in real use, and if the firmware believed it, it would heat the cell forever.

Checkpoint: PASS (3156.2 and 2047.5).

Conclusion: The divider model gives about 3156 counts at 0 °C and 2048 at 25 °C, confirmed by hand. 10 kΩ isn't the most sensitive choice in the cold, but at 0.05 °C per count it is far finer than R1 needs, so it stays (provisional, see decisions.md ADR-02).

Next action: S2 · C from Python, part 2, Sun Nov 22 (90 min) + weekly review. ntc.c on Sat Nov 28 uses this table as test data.

Explain-back (3 sentences from memory, no notes): TODO — write before S2 on Nov 22.
1.
2.
3.
