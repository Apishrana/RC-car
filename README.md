# ESP-NOW RC Car

## What This Project Is

This is a RC car built around two ESP32 boards. One ESP32 will act as the handheld controller and read a joystick, and the second ESP32 sits on the car and drives the motors based on commands sent by second ESP32 using ESP-NOW protocol.

The current repository includes:

- ESP32 code for the [remote](src/car.txt) and the [car](./src/car.txt)
- A helper sketch for reading an ESP32 MAC address
- A [Fritzing](https://fritzing.org/) design for wiring in `design.fzz`
- A Fusion360 design of car

## Why I Made It

The main goal was to learn how to use joystick input, ESP-NOW communication and motor control into one complete system that I could keep improving.

## Features

- ESP32-to-ESP32 wireless communication using ESP-NOW
- Joystick-based steering and drive input
- Simple motor driver control for forward, left, right, and stop states
- MAC address utility sketch to pair the boards

## How It Works

### Remote

The remote firmware is in [src/remote](/src/remote.txt). It:

- reads joystick X and Y values
- decides whether the car should stop, move, or turn
- sends the command over ESP-NOW to the car

### Car

The car firmware is in [src/car](src/car.txt). It:

- listens for incoming ESP-NOW packets
- decodes movement and reverse data
- controls four output pins connected to the motor driver to execute the commands

### MAC Address Utility

The helper sketch in [src/getMac](src/getMac.txt) prints the ESP32 MAC address so the remote can be paired with the car.

## Wiring

The current wiring diagram is stored as [design.fzz](design.fzz).

Main control connections used in firmware right now:

- Remote joystick Y: GPIO 4
- Remote joystick X: GPIO 2
- Car motor driver pins: GPIO 21, 19, 18, 5 (check code for specific pins)

### Car

- Breadboard

![img](https://stasis.hackclub-assets.com/images/1773430597750-0fhsbx.png)

- Schematic

![img](https://stasis.hackclub-assets.com/images/1773430631847-jm5mvs.png)

### Remote

- Breadboard

![img](https://stasis.hackclub-assets.com/images/1773430667547-ovxi41.png)

- Schematic

![img](https://stasis.hackclub-assets.com/images/1773430693120-3m29mq.png)

## Build Photos

to be added latter

## 3D Model

the car 3d model can be found in [cad/](cad/)

also on fusion [here](https://a360.co/4bC1af7)

### Side

![Side](https://stasis.hackclub-assets.com/images/1773825379975-kyb7a6.png)

### Front

![Front](https://stasis.hackclub-assets.com/images/1773825389459-n9o9y4.png)

### Top

![Top](https://stasis.hackclub-assets.com/images/1773825404753-ic3u4r.png)

### Bottom

![Bottom](https://stasis.hackclub-assets.com/images/1773825465453-5ogmvj.png)

## PCB

This project currently uses wiring-based electronics using a breadboard, not a PCB design.

## Repository Structure

```text
.
├── BOM.csv
├── cad
├── design.fzz
├── images
│   └── bill.png
├── include
│   └── README
├── JOURNAL.md
├── lib
│   └── README
├── platformio.ini
├── README.md
├── src
│   ├── car.txt
│   ├── getMac.txt
│   ├── main.cpp
│   └── remote.txt
└── test
    └── README
```

## How to setup your own car

- Paste the code form [getMac](src/getMac.txt) to `main.cpp` and upload to get mac of car ESP32
- Replace the placeholder broadcast MAC address in the [remote](src/remote.txt) firmware with the actual car ESP32 MAC address and upload the code through `main.cpp`
- Upload the [car](src/car.txt) code to car ESP32
- Replicate the wiring in [design.fzz](design.fzz)

## BOM

The full CSV BOM is in [BOM.csv](BOM.csv). Current estimated total: **2,131.00 + taxes => 2,514.58**.
![bill.png](./images/bill.png)

| Name                                                                     | Purpose                                            | Cost Per Item (USD) | Quantity | Total (USD) | Link                                                                                                                          | Distributor          |
| --- | --- | --- | --- | --- | --- | --- |
| XL6009 Step Up Down Buck Boost Converter Module                          | power supply for esp32                             | 1.50                | 1        | 1.50        | [link](https://quartzcomponents.com/products/xl6009-step-up-down-buck-boost-converter-module?_pos=4&_sid=666e76809&_ss=r)          | quartzcomponents.com |
| 12V 300RPM Geared DC Motor                                               | motor to drive the car                             | 1.57                | 4        | 6.28        | [link](https://quartzcomponents.com/products/12v-300rpm-geared-dc-motor?variant=44881938972906)                                    | quartzcomponents.com |
| USB to micro-USB Cable                                                   | programing/power cable for esp                     | 0.28                | 2        | 0.56        | [link](https://quartzcomponents.com/products/raspberry-pi-cable-for-charging?_pos=2&_psq=micro+usb&_ss=e&_v=1.0)                   | quartzcomponents.com |
| L293D Motor Driver Module                                                | Motor Driver to controll motors                    | 0.75                | 1        | 0.75        | [link](https://quartzcomponents.com/products/l293d-motor-driver-module?variant=31898009927815)                                     | quartzcomponents.com |
| 18650 Li-ion 2500mAh Rechargeable Battery Copy                           | battery to power the car                           | 0.53                | 3        | 1.59        | [link](https://quartzcomponents.com/products/18650-li-ion-2500mah-rechargeable-battery?variant=37862622036152)                     | quartzcomponents.com |
| 3 Cell 18650 Lithium Battery Holder                                      | battert to power the car                           | 0.30                | 1        | 0.30        | [link](https://quartzcomponents.com/products/3-cell-18650-lithium-battery-holder?variant=44216406802666)                           | quartzcomponents.com |
| Lithium Battery Capacity Indicator - Battery Level Indicator / Voltmeter | Battery %age Indicator                             | 0.74                | 1        | 0.74        | [link](https://quartzcomponents.com/products/1s-18650-li-po-lithium-battery-capacity-indicator-module?variant=42987409539306)      | quartzcomponents.com |
| Dual Axis XY Joystick Module                                             | Joystick for remote controller                     | 0.35                | 1        | 0.35        | [link](https://quartzcomponents.com/products/dual-axis-xy-joystick-module?variant=31898099449991)                                  | quartzcomponents.com |
| Male to Female Connecting Wires / Jumper Wires (Set of 10)               | wiring                                             | 0.13                | 3        | 0.39        | [link](https://quartzcomponents.com/products/male-to-female-connecting-wires-jumper-wires-set-of-10?variant=32115365216391)        | quartzcomponents.com |
| Male to Male Connecting Wires / Jumper wires (Set of 10)                 | wiring                                             | 0.15                | 3        | 0.45        | [link](https://quartzcomponents.com/products/male-to-male-jumper-wire-set?variant=31898123894919)                                  | quartzcomponents.com |
| Female to Female Connecting Wires / Jumper Wires (Set of 10)             | wiring                                             | 0.13                | 1        | 0.13        | [link](https://quartzcomponents.com/products/female-to-female-connecting-wires-jumper-wires-set-of-10?variant=32116354285703)      | quartzcomponents.com |
| Small Breadboard / Mini Solderless Board - 400 points                    | wiring the car                                     | 0.37                | 1        | 0.37        | [link](https://quartzcomponents.com/products/small-breadboard-mini-solderless-board?variant=33254289539207)                        | quartzcomponents.com |
| 170 points Mini Breadboard - Solderless breadboard                       | wiring the remote                                  | 0.15                | 1        | 0.15        | [link](https://quartzcomponents.com/products/syb-170-mini-solderless-prototype-experiment-test-breadboard-1?variant=35140715413657)| quartzcomponents.com |
| Robot Car Wheel 70mm x 40mm for BO Motors                                | wheel for the car                                  | 0.48                | 4        | 1.92        | [link](https://quartzcomponents.com/products/robot-car-wheel-70mm-x-40mm-for-bo-motors?variant=44188075393258)                     | quartzcomponents.com |
| ESP32 30 Pin CP2102 Development Board with Wi-Fi and Bluetooth           | one esp for controlling the car one for the remote | 3.74                | 2        | 7.48        | [link](https://quartzcomponents.com/products/esp32-30-pin-development-board-with-wi-fi-and-bluetooth?variant=45080070455530)       | quartzcomponents.com |
