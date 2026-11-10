# Cold Cell Design Notebook

-When a lithium ion battery enters sub-zero temperatures, the internal resistance increases. While a lithium ion battery itself already exhibits an amount of internal resistance, entering lower temperatures slows down the chemical processes and slows the movement of ions between the anode and cathode, thereby increasing the internal resistance. By Ohm's Law, a greater internal resistance combined with the same amount of current will result in a greater amount of voltage drop inside the colder cell.  Furthermore, since the terminal voltage of the system is seen as the open circuit voltage minus the voltage drop which is current times internal resistance, the increase in internal resistance, which in turn increases the voltage drop and forces the output voltage (terminal voltage) to the 3.0V low-voltage safety threshold earlier, even though there is still useable energy in the cell. As a result, the battery cell will seem to have less power for your power bank in colder conditions when in reality, the amount of power is the same however, it is just unable to extract the power since the increased internal resistance lowers the output voltage to the safety threshold.\
-To prove if the resistance heater is worth it in the battery pack, I calculated the total resistance of the heaters first. Since they are in parallel, the total resistance of two 10 ohm resistors is 5 ohms. Next, I calculated the power output of the battery at its nominal voltage of 3.7V. Take the voltage squared divided by the resistance and that gives a power of 2.74W. Now say I am running the device for ten minutes, I can calculate the time in watt hours by multiplying the power by 10/60 hours which gives me 0.457 Wh. Then, converting that to amp-hours gives me 0.123Ah which is 123 mAh. Now in a standard battery pack with 3400 mAh, this heater would only consume (123/3400)*100 percent which is around 3.6% of the total battery pack. Based of the information, this proves that the heater is worth it because the heater will only consume a small fraction of the total energy of the battery which makes it worth it since it will decrease the internal resistance in the battery and allow the battery to maximize its stored energy towards charging.\
## System Requirements (R1–R7)

| ID | Requirement Name | Target Specification & Operating Condition |
| :--- | :--- | :--- |
| **R1** | Thermal Sensing Range | Measure cell temperature from **–20 °C to +60 °C** with **±1 °C** accuracy using an NTC thermistor. |
| **R2** | Charge Lockout | Inhibit battery charging when cell temperature is **$< 3\ ^\circ\text{C}$** or **$> 43\ ^\circ\text{C}$** to prevent lithium plating and thermal runaway. |
| **R3** | Thermal Control Loop | Maintain cell temperature at **$10\ ^\circ\text{C} \pm 1\ ^\circ\text{C}$** using a PID-driven PWM heater control algorithm. |
| **R4** | Sensor Fault Protection | Trigger immediate safety lockout and disable heating if an NTC sensor open or short circuit is detected. |
| **R5** | Hardware Fail-Safe | Enforce Independent Watchdog (**IWDG**) timer timeout to safely cut power to the heater if firmware execution stalls. |
| **R6** | Current Sense Accuracy | Measure bidirectional pack current up to **$\pm 5\,\text{A}$** within **±2%** accuracy for power and energy tracking. |
| **R7** | Telemetry Logging | Transmit system states, temperatures, heater duty cycle, and safety flags via UART CSV log at **1 Hz**. |/
## System Architecture & Pin Allocation

### Firmware Architecture Layers
The firmware is structured into three distinct layers to ensure portability, testability, and clean separation of concerns[cite: 1]:
1. **Layer 3 (Application):** Manages the main control loop, 1 Hz control ticks, telemetry logging, and independent watchdog (IWDG) refreshes[cite: 1].
2. **Layer 2 (Pure C Logic):** Contains hardware-independent modules (`ntc.c`, `pid.c`, `fsm.c`, `ina219_decode.c`, `coulomb.c`) that can be unit-tested directly on a PC host[cite: 1].
3. **Layer 1 (Drivers / HAL Wrappers):** Interfaces directly with STM32 HAL peripherals (ADC reads, PWM generation, I2C/UART communication, and GPIO toggling)[cite: 1].

### Hardware Pin Map & Rationale

| Pin | Peripheral / Function | Target Component / Connection | Why We Need It (Rationale) |
| :--- | :--- | :--- | :--- |
| **PA0** | `ADC1_IN0` | Cell NTC Thermistor | Monitors cell temperature via a 10 kΩ voltage divider to prevent sub-zero charging and feed the PID heater control loop. |
| **PA1** | `ADC1_IN1` | Ambient NTC Thermistor | Tracks ambient environmental temperature to provide baseline thermal context relative to the cell pack. |
| **PA6** | `TIM3_CH1` (PWM) | Heater MOSFET Gate (`IRLZ44N`) | Outputs a 1 kHz PWM signal to precisely regulate power delivery to the 5 Ω resistive heater via PID control. |
| **PB0** | `GPIO_Output` | Charger Switch Gate (`BSS138`) | Controls the high-side P-MOSFET charger switch; defaults low to enforce a fail-safe charging lockout until explicitly enabled. |
| **PB1** | `GPIO_Input` | USB Power Sense Divider | Detects the presence of an external 5 V USB power source to trigger operational state machine transitions. |
| **PB6** | `I2C1_SCL` | INA219 Current Sensor (SCL) | Provides the I2C clock signal for communicating with the INA219 bidirectional current and bus voltage sensor. |
| **PB7** | `I2C1_SDA` | INA219 Current Sensor (SDA) | Provides the I2C data line for transmitting configurations and reading back telemetry registers from the INA219. |
| **PA2** | `USART2_TX` | Host Serial / USB Debug VCP | Transmits 1 Hz CSV telemetry logs and diagnostic print statements to the host computer over virtual COM. |
| **PA3** | `USART2_RX` | Host Serial / USB Debug VCP | Receives incoming serial commands or debug configuration flags from the host computer. |
| **PA5** | `GPIO_Output` | Status LED | Acts as a visual heartbeat indicator to verify that the main firmware execution loop is running normally. |
