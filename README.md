# DeskElf

<!-- > X, X & X    -->

> Indoor Environment Quality sensing & Pomodoro Technique



## Background

With the blend work model prevailing, office workers spend most of their time inside the buildings as they did before–– but now stay in their homes more than offices. It is proved that indoor environmental quality has a significant influence on staffs’ productivity, health and wellbeing (U.S. Green Building Council, 2014). Unlike commercial buildings, most of the residential buildings have a lack of large-scale IT infrastructure and building-wise environmental controls which makes it hard to deploy state-of-the-art sensors in the building (Graham Coulby et al., 2020).

However, this problem provides a great opportunity to develop a lightweight and portable indoor environmental sensor for people who adopt a flexible working model. DeskElf is born for this need and manages to offer a desktop device helping workers keep productive and healthy at the same time. Besides, DeskElf can serve as an extended service of corporates’ wellbeing programmes, taking care of employees’ working environment just like what they do at the office.



## Functionality

![image](https://user-images.githubusercontent.com/52306317/148701829-f9fcba65-2176-401c-a164-cf4280552ae3.png)


## Building Process
To make DeskElf portable and keep flexible for data application, the data captured by sensors will be sent to the network server–– The Things Network via LoRa gateway. So, The Things Uno board is used, and it is designed based on the Arduino Leonardo board with a microchip LoRa module (RN2483).

![image](https://user-images.githubusercontent.com/52306317/148701854-4642581e-4618-4db5-80a3-ab0b893a9a54.png)

![image](https://user-images.githubusercontent.com/52306317/148701870-8969084e-1560-45bb-ac0f-9fe0b78a13ff.png)

<img width="705" alt="Screenshot 2022-01-09 at 21 41 01" src="https://user-images.githubusercontent.com/52306317/148702054-2eee4d73-17b4-4f72-a1f3-df2eccce02e3.png">

The building process of DeskElf consists of 4 stages from hardware setup, Arduino IDE code, The Things Network setup and the enclosure design and 3d printing.

![image](https://user-images.githubusercontent.com/52306317/148702085-f42d80ba-289f-4661-ae6b-371e62355e51.png)


### 1. Hardware setup
The reason for choosing The Things Uno (Arduino Leonardo) board is due to the data communication concern. Since DeskElf should work functionally wherever users work, its function must be low-power consumption and long-range coverage to reduce users’ hassle in charging and reconnecting. Therefore, the LoRa network, which can deliver a 2 to 3 km-wide coverage from its gateways in the urban area, becomes a feasible choice.
For indoor environmental quality sensing, LCD is used to display real-time readings of each sensor which allows users to get updated information and take immediate action if they want. Besides, SGP30 and TCS34725 both are connected to The Things Uno board through I2C communication by occupying the SCL/SDA set and pins 2 and 3.
For Pomodoro Technique, the LDR will trigger the countdown timer function when users start working (In this case: Users will plug the FOCUS signage on the lid, changing the amount of light that LDR receives) and the LED will remind users that the working time is up, and it is time to take a break. All components are wired up as below schematic.

![image](https://user-images.githubusercontent.com/52306317/148702099-e1fd7d39-2c12-4a52-a8e7-1c4af027d282.png)


### 2. Arduino IDE code




### 3. Communicating over LoRa

### 4. Enclosure Design for 3D Printing
* https://www.hubs.com/knowledge-base/enclosure-design-3d-printing-step-step-guide/

### 5. Sensor Data Visualization and Interaction





## Reflection

### 1.	Hardware setup
During the hardware setup process, different sensors can be considered to capture indoor environmental quality, for example, PM2.5 is also a good indicator of air quality. Besides, there are various solutions to trigger the Pomodoro technique as well such as RFID or light sensor; However, the choice of solution should be based on its purpose.

### 2.	LoRa setup
During the LoRa setup process, the transmitting interval should be considered to make the most of the resources. It is possible to update data with a longer interval or set up a certain threshold that leads to transmitting sensor value (The Things Network, 2021a).

### 3.	Future extension
DeskElf's mobile App can be used to allow users to set up their comfort settings and it will automatically send alerts when the environment needs to be adjusted. What’s more, sensor data should be analyzed and visualized in a long-term way, making users understand or find out the pattern or potential issue of the quality of their working environment.


## Reference
* Arduino (no date) Arduino - Serial. Available at: https://www.arduino.cc/en/reference/serial&gt (Accessed: 15 December 2021).
* Desining Buildings (2021) Indoor environmental quality. https://www.designingbuildings.co.uk. Available at: https://www.designingbuildings.co.uk/wiki/Indoor_environmental_quality (Accessed: 3 January 2022).
* Graham Coulby et al. (2020) ‘A Scoping Review of Technological Approaches to Environmental Monitoring’, International Journal of Environmental Research and Public Health, (International Journal of Environmental Research and Public Health), p. 25.
* John Rampton (2020) The Benefits of the Pomodoro Technique, The Benefits of the Pomodoro Technique. Available at: https://www.calendar.com/blog/the-benefits-of-the-pomodoro-technique/ (Accessed: 29 December 2021).
* Kat Boogaard (no date) The Pomodoro Technique Really Works for Productivity | The Muse. Available at: https://www.themuse.com/advice/take-it-from-someone-who-hates-productivity-hacksthe-pomodoro-technique-actually-works (Accessed: 1 January 2022).
* LoRa-Developers (2021) LoRa best practices Packet Optimisation Introduction | DEVELOPER PORTAL. Available at: https://lora-developers.semtech.com/documentation/tech-papers-and-guides/the-book/intr/ (Accessed: 29 December 2021).
* Michael Contreras, M. (2022) arduino-timer - library for delaying function calls. Available at: https://github.com/contrem/arduino-timer (Accessed: 1 January 2022).
* The Things Network (2021a) Limitations, The Things Network. Available at: https://www.thethingsnetwork.org/docs/lorawan/limitations/ (Accessed: 12 December 2021).
* The Things Network (2021b) Quick Start, The Things Network. Available at: https://www.thethingsnetwork.org/docs/devices/uno/quick-start/ (Accessed: 5 December 2021).
* The Things Network (2021c) TTN Mapper, TTN Mapper. Available at: https://ttnmapper.org/heatmap/ (Accessed: 29 December 2021).
* The Things Network (2021d) Working with Bytes, The Things Network. Available at: https://www.thethingsnetwork.org/docs/devices/bytes/ (Accessed: 10 December 2021).
* U.S. Green Building Council (2014) Green Building 101: What is indoor environmental quality? Available at: https://www.usgbc.org/articles/green-building-101-what-indoor-environmental-quality (Accessed: 3 January 2022).
