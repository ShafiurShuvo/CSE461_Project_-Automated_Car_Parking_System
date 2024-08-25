# [CSE461_Project - Introduction to Robotics]
# RFID_Based_Automated_Toll_Collection_System_&_Car_Parking_System_Using_Arduino

__Group Members :__ <br><br>
[MD. Shafiur Rahman](https://github.com/ShafiurShuvo) | [Faisal Ahmed](https://github.com/FaisalAhmed21) | [Nazia Mumtahina](https://github.com/NaziaMumtahina) | [Kazi Abrab Hossain](https://github.com/AbrabOme) | [Maria Hossain Tuli]()

## Video Demonstration

[![Watch the video](https://ytcards.demolab.com/?id=GiGhQvBfyNY&title=RFID-Based+Automated+Parking+Management+System&lang=en&timestamp=1724539200&background_color=%230d1117&title_color=%23ffffff&stats_color=%23dedede&max_title_lines=1&width=250&border_radius=5&duration=697 "RFID-Based Automated Parking Management System")](https://youtu.be/GiGhQvBfyNY)

## Components

- **Arduino Uno**
- **16x2 LCD Display**
- **20x4 LCD Display**
- **2 I2C Modules**
- **2 Servo Motors**
- **6 IR Sensors**
- **RFID Reader Module with RFID Card**
- **Additional RFID Cards (if needed)**
- **Breadboard**
- **Jumper Wires**
- **Female Header and Male Header**

## Purpose

The RFID-Based Automated Parking Management System is designed to streamline and enhance the efficiency of parking facilities by automating the process of identifying vehicles upon entry, categorizing them based on predefined criteria, determining applicable fees, and facilitating seamless entry and exit for authorized vehicles.

## Functionality Breakdown

This system simplifies car entry by quickly recognizing RFID tags when a vehicle arrives. The following steps outline the process:

1. **RFID Detection**: As a vehicle approaches, the system detects the RFID tag associated with the vehicle.
2. **Vehicle Identification**: Here each vehicle is unique because each RFID card has a unique card address. So the system identifies the vehicle and retrieves the relevant information.
3. **Fee Calculation**: Based on predefined criteria, the system estimates the applicable parking fees.
4. **LCD Display**: The calculated amount is instantly displayed on the 16x2 or 20x4 LCD screen.
5. **Balance Check**:
   - **Sufficient Balance**: If the RFID card has a sufficient balance, the parking gate opens automatically.
   - **Insufficient Balance**: If the balance is insufficient, the gate remains closed, and an error message "Insufficient Balance" is displayed on the screen.
6. **Unauthorized Vehicles**: The gate will remain closed for unauthorized vehicles.
7. **Parking Lot Full**: If the parking lot is full, the gate remains closed, and the message "No Space" is displayed.

This system ensures efficient and secure management of parking facilities, reducing the need for manual intervention and enhancing user experience.

## Circuit and Schematic Views

### Schematic View
![Schematic View](Schematic%20Part-01%2602.png)

### Circuit View
![Circuit View](Circuit%20Part-01%2602.png)
