# Electric Heater System 🔥❄️

This project implements an embedded system for an **Electric Heater** that can both heat and cool based on temperature readings from sensors. Built using **ATmega32**, it demonstrates a solid understanding of low-level embedded programming, driver development, and EEPROM data management.

---

## 🔧 Features

- **Temperature Monitoring:** Uses an **LM35 temperature sensor** to read ambient temperature.
- **Cooling & Heating Control:** Interfaces with heating and cooling elements using thermocouples.
- **Display System:** Shows temperature readings on a **7-segment display**.
- **Data Logging:** Stores readings in an **External EEPROM** via the **I2C protocol**.
- **Time-Based Updates:** Utilizes **Timers** to periodically save temperature data.

---

## 🛠️ Technologies Used

- **ATmega32 Microcontroller**
- **C Language**
- **LM35 Temperature Sensor**
- **7-Segment Display**
- **I2C Protocol (for EEPROM)**
- **Timers (for scheduled EEPROM writes)**

---

## How It Works
1. Reads temperature via LM35
2. Displays it on 7-segment
3. Periodically stores value to EEPROM using Timer and I2C

## Future Improvements
- Add LCD for more detailed UI
- Implement UART to send logs to PC


## Author
Mohamed Omar 
[GitHub Profile](https://github.com/MohamdOmar)
