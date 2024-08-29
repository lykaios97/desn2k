
# Lab Timer User Guide

  
  

<!--- Group info -->

  

<p align="center">

  

UNSW DESN2000 24T2 (COMP)

  

</p>

  

<p align="center">

  

Group: "G"

  

</p>

  

<p align="center">

  

Members: Aditya Muthukattu, Linfeng Cai, Kavisha Chandraratne

  
  

</p>

  

<!--- Group info -->

  
  

---

<div style="page-break-before:always"></div>

## Table of Contents

- [Lab Timer User Guide](#lab-timer-user-guide)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Getting Started](#getting-started)
    - [Installation](#installation)
    - [User Interface Overview](#user-interface-overview)
  - [Standard Clock navigation and Alarm instructions](#standard-clock-navigation-and-alarm-instructions)
    - [Normal Operation and Alarm deactivation (with snooze)](#normal-operation-and-alarm-deactivation-with-snooze)
      - [Display](#display)
      - [User Actions](#user-actions)
    - [Setting the Date and Time](#setting-the-date-and-time)
      - [Input Date](#input-date)
      - [Setting Time](#setting-time)
      - [Input Time](#input-time)
    - [Setting the Alarm](#setting-the-alarm)
      - [Enter Alarm Setting Mode](#enter-alarm-setting-mode)
      - [Input Alarm Time](#input-alarm-time)
      - [Confirm Alarm Time](#confirm-alarm-time)
      - [Input Alarm Day](#input-alarm-day)
      - [Confirm Alarm Day](#confirm-alarm-day)
      - [Cancel Alarm Setting](#cancel-alarm-setting)
    - [Alarm Activation](#alarm-activation)
      - [Snooze Prompt](#snooze-prompt)
      - [Deactivate Alarm](#deactivate-alarm)
    - [Syncing Time via UART](#syncing-time-via-uart)
      - [Sync Time](#sync-time)
      - [Upon Successful Sync](#upon-successful-sync)
  - [Summary of Keypad Controls](#summary-of-keypad-controls)
    - [Sync time from UART](#sync-time-from-uart)
      - [Set Date and Time:](#set-date-and-time)
      - [Set Alarm:](#set-alarm)
      - [Snooze Alarm:](#snooze-alarm)
    - [Standard Timer](#standard-timer)
      - [Keypad Button Functions](#keypad-button-functions)
      - [LCD Display](#lcd-display)
    - [Stopwatch](#stopwatch)
  - [Scientific Timer initialisation and operation](#scientific-timer-initialisation-and-operation)
  - [Additional Resources](#additional-resources)

<div style="page-break-before:always"></div>

## Introduction

  
  

Thank you for your purchase of the Custom Clock with Laboratory Timer (CCLT). The CCLT seamlessly integrates parallel timer functionality with standard clock features, as well as additional features tailored specifically to enhance the efficiency and accuracy of lab operations. This document serves to familiarise the user with the device, its user interface and functionality

  
  

## Features

  

The Custom Clock with Laboratory Timer (CCLT) is a versatile device that combines the functionality of a standard clock with a laboratory timer. The key features of the CCLT include:

- Two operating modes: Standard Clock and Laboratory Timer

- Standard Clock mode displays the current time, date and day of the week

- Additional clock functionality including and alarm, stopwatch and countdown timer are also present

-

- Laboratory Timer mode allows users to set multiple timers with custom labels

- The user may setup up to 4 timers with custom labels

- These timers can be started, paused and reset independently

- They can also be started simultaneously

  

Additional Features:

- Standard Clock time sync via UART

  

## Getting Started

  

### Installation

The CCLT firmware can be installed on the STM32F303RET6 microcontroller using the STM32CubeIDE platform. Simply plug the device into your computer, open the project in STM32CubeIDE, and upload the firmware to the microcontroller.

  

Once the firmware is on the device, it should display a boot message and load into the Standard Clock mode, displaying the date, time and day of the week.

  

### User Interface Overview

  

![User Interface Design](https://lh7-rt.googleusercontent.com/docsz/AD_4nXcB9Po1JI1LpL2d_Cxo4AsU5UJKQhk3yj3_9_acUQ3jZhIsfwiEOYWOUCgDm8IDPVXR2y2EurYWlQvKoHEHhsZIFoaYfSi3-6Q7BC-_5x_zm9uT5yb3IU6qlGxkYcqMMsL3Mlbth2xcKbzWBBZAb3YN54e-?key=CCTEQPQ62lXGHUiHtNA4aA)

  

The CCLT’s user interface can be traversed using the mode and function buttons on the keypad (A and B respectively). The mode button switches between the Standard Clock and Laboratory Timer modes, while the function button is used to navigate through the different functions within each mode. While in the Standard Clock mode, the function button can be pressed repeatedly to cycle through the different functions (clock, alarm, stopwatch, countdown timer). In the Laboratory Timer mode, the function button is used to cycle through the different timers.

  

The direct buttons SW1-SW4 can be used to start, and pause the timers 1 to 4 from any mode, and the direct LEDs can be used to indicate the status of the timers (slow blinking = ready, solid = running, fast blinking = completed, off = timer not active). The switch B1 is used to start all timers simultaneously, and the switch B2 is used to reset the entire device.

  

The LED Bar across the bottom is used to indicate the progress of the shortest remaining timer, giving the user a visual indicator of the time remaining.

  
  

## Standard Clock navigation and Alarm instructions

  

Keypad Controls

- D: Cancel current setting or deactivate alarm.
    
- C: Confirm current input.
    
- #: Syncs time from UART.
    
- ``*``: Enters date setting mode.
    
- Numeric keys (0-9): Input date and time values.
    

### Normal Operation and Alarm deactivation (with snooze)

#### Display

Line 1: Displays the date and weekday in DD/MM/YYYY Weekday format.

Line 2: Displays the time in hh:mm:ss AM/PM format.

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfxpmXBCoADN25_LSiu0YdLZz7_Fl825cD0oNriuj5RciGQc6UH2zeVXqv5VhhnlBuXp3lF-5V1AY7RubxA52oNlEpTBopUnYYtkG9-zQyoz_9Ycq6Hc9BTMgmZQHgTnsyUeQJHFl5NtE6UjOskQof9vGd6?key=CCTEQPQ62lXGHUiHtNA4aA)

#### User Actions

Press D: Prompts for snooze when alarm is active.

Display:

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXcGMSkR2lKMJarfAlqKkqCYjmghMhy0U1OjfjiXgkRplbg8riWiCb-DoUtX8rW5ezv4RBUroQHcezxafDHpwXY0QmztXzxriNPv0QnluZhjhdbAgkAjumoQYAyaS2NG7YlwcARRwiMx-YMV_Hsxo7zIluyR?key=CCTEQPQ62lXGHUiHtNA4aA)Press #: Syncs time from UART.

Press `*`: Enters date setting mode.

Display:

Line 1: "Set Date(DDMMYY)"

Line 2: User input

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXezhVFXoyfnIkxeWEOmqk9KYD2kH0-Kp7IVywDLFHMp10dhCKzwGaznjvBEZ4HsYB_U_uw-nnqg6W1JJpwigexp1toEdnoH8TwtRgoFAxpuigM3pAARuVkUhqecHZSYvcJhaUf2dmW8sbexPIuFmDDW_LoO?key=CCTEQPQ62lXGHUiHtNA4aA)

### Setting the Date and Time

Enter Date Setting Mode

Press `*`: Enters date setting mode.

Display:

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfypJOR87bhBnVxqOdSfovd0KbKUL7c-S4Mtkl8bE_7av-4Ap4u7Vr07DfTCqNxHfm-P97u6DqWwbznsP8QbccCLpXWcfwL34_Cjac2X1OfqUl3y51Bk6VCCgNEZz_V3eGw2XMXc7JH72YkMf3vyBHkFiE6?key=CCTEQPQ62lXGHUiHtNA4aA)
#### Input Date

Use numeric keys (0-9) to input the date in DDMMYY format. The entered date will be displayed on Line 2. 

Note: YY represents the last 2 digit of year after 2000. E.g. 24 represents 2024, 12 represents 2012, etc.

Confirm Date

Press C to confirm the date input and proceed to time setting mode.
#### Setting Time



Display:

Line 1: "Set Time(HHMMSS)"

Line 2: ""

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfJ2SgKjQobQcj3tNDdMQHK3KHLaSV7-IxEcBY6SLTZ92HyxF4h7DNyBSnxUKug5JuK-dwCYBqukVQWcNl8QgcgThv_Bq9iKAYgPlAOeVKVvaWLdcOvDiTOERSBqlpMTXguzfsRD8y0X4LDbb77unvl1q8?key=CCTEQPQ62lXGHUiHtNA4aA)

#### Input Time

Use numeric keys (0-9) to input the time in HHMMSS format. The entered time will be displayed on Line 2.

Display:

Line 2: "HHMMSS"

Confirm Time

Press C to confirm the time input and return to the normal operation display.

Cancel Setting

Press D at any point to cancel the current setting and return to the normal operation display the original time (before the start of the time setting process) remain unchanged.

### Setting the Alarm

#### Enter Alarm Setting Mode

Press C in normal operation mode.

Display:

Line 1: "Set Time(HHMM)"

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXf04gMzhKNuLZLi8PuP9-cQdIk9hNIVbA_1MacqJIZXXNBEmaMVRQj4MjzJX-vbUlKiwJz3bFsQkriKIFvPzWOlospZOPQPWQLUm4PHRauaBN7i8nXvnysqSHleao_hVRRwJOlmgA3dUT2zEQ4uDTX2de6P?key=CCTEQPQ62lXGHUiHtNA4aA)

#### Input Alarm Time

Use numeric keys (0-9) to input the alarm time in HHMM format. The entered time will be displayed on Line 2.

Display:

Line 2: "HHMM"

#### Confirm Alarm Time

Press C to confirm the alarm time input and proceed to day setting mode.

Display:

Line 1: "Set Day (1-7)"![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfUEon-cMgZNuBqjQneikD8EjA8aAA5a2FSPT9GmVy0IMZUw95gk-evxOBmMNdcrYIeDQYLMwhUu7fKV9_OUN_7LJ-P0sYO4kmoXNmlyrTu-kmFSH6htVk0Z_C8IDGQhZNEV3P0nWN4mdNWcC_zlkWlfeP2?key=CCTEQPQ62lXGHUiHtNA4aA)

#### Input Alarm Day

Use numeric keys (0-9) to input the day (1=Monday, 7=Sunday). The entered day will be displayed on Line 2.

#### Confirm Alarm Day

Press C to confirm the day input and set the alarm. (Returns to primary time display)

#### Cancel Alarm Setting

Press D at any point to cancel the current setting and return to the normal operation display. (Returns to primary time display)

### Alarm Activation

Alarm Event

When the alarm time is reached, the microcontroller will activate the alarm by setting the respective GPIO pins high. (from initial example it is set to light up all direct LED) Can be customized.

#### Snooze Prompt

Press D when the alarm is active to prompt for snooze.

Display:

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXcGMSkR2lKMJarfAlqKkqCYjmghMhy0U1OjfjiXgkRplbg8riWiCb-DoUtX8rW5ezv4RBUroQHcezxafDHpwXY0QmztXzxriNPv0QnluZhjhdbAgkAjumoQYAyaS2NG7YlwcARRwiMx-YMV_Hsxo7zIluyR?key=CCTEQPQ62lXGHUiHtNA4aA)Snooze Alarm

Press C to snooze the alarm for 1 minute. (Customizable to any duration)

Display:

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXdZmHDLfoosHz18xcCCVSdrcRo5Asq_Nu07DrnLk2wm76QLnL9yXwcOu3V8Qikrni9HiBEGhW4q6E8msSocrbshUe6LZ5TcIVLOBuYMEYagsOfv3K6ZUotPJKOwXNrCU6xHmLSCMZEyfZzSIRTHUWzXT2Qc?key=CCTEQPQ62lXGHUiHtNA4aA)

After 1 second:

Returns to primary time display.

#### Deactivate Alarm

Press D to deactivate the alarm. (Returns to primary display)

### Syncing Time via UART

#### Sync Time

Press # to sync the time from UART. The received time will be displayed temporarily for debugging.

Display:

#### ![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXeLTh6oPq86EVXG7wvHbUvlay7v8juNd-egtfyHuIMMWDzCl1Z6oumP9x_OLkWZcORPaAFKiBNf2v4M7vdNQWdceD-jip_MmN8Lu9DOGqCekwVPahNIe5jTtAsJefcZPVEwBRFH2_PjdsEsXIRLWTjyAtes?key=CCTEQPQ62lXGHUiHtNA4aA)Upon Successful Sync

Returns to primary time and date display

## Summary of Keypad Controls

| Key | Action                             | Display             |
| --- | ---------------------------------- | ------------------- |
| D   | Cancel setting or deactivate alarm | Normal display  |
| C   | Confirm input or enter alarm       | Setting mode        |

### Sync time from UART

`*` Enter date setting mode "Set Date(DDMMYY)" for date setting

0-9 Input date/time values Display input values on Line 2 during setting

Example Usage

#### Set Date and Time:

- Press `*` to enter date setting mode.
    
- Input date using numeric keys and press C.
    
- Input time using numeric keys and press C.
    
- Normal display resumes with updated date and time.
    

#### Set Alarm:

- Press C in normal display to enter alarm setting mode.
    
- Input alarm time using numeric keys and press C.
    
- Input alarm day using numeric keys and press C.
    
- Normal display resumes with alarm set.
    

#### Snooze Alarm:

- When alarm is active, press D to prompt for snooze.
    
- Press C to snooze for 1 minute or D to deactivate the alarm.
    

This user guide provides a comprehensive overview of the functionality and usage of the STD_CLK library from the user's perspective, with clear explanations of the display and keypad controls.

### Standard Timer

#### Keypad Button Functions

- 'C' Button (Set Timer)
- Press 'C' to enter timer setting mode.
- The display will show "Set Timer(HHMMSS)".
- Enter the timer duration in HHMMSS format (e.g., 012345 for 1 hour, 23 minutes, and 45 seconds).
- Press 'C' again to confirm the entered time.
- 'D' Button (Cancel/End)

In setting mode, press 'D' to cancel the timer setting process and exit setting mode.

In normal mode, press 'D' to cancel the running timer and reset the timer to 00:00:00.

When the timer ends, the display will show "Timer Ended".

'#' Button (Start Timer)

Press '#' to start the countdown of the timer if it is set and not already running.

'`*`' Button (Pause Timer)


Press '`*`' to pause the countdown of the timer if it is running.

#### LCD Display

The LCD display will show relevant information based on the current mode:

Setting Mode:

Line 1: "Set Timer(HHMMSS)"

Line 2: Current input for the timer in HHMMSS format.

Normal Mode:

Line 1: "Timer:" followed by the current timer value (HH:MM) if the timer is set and not running.

Line 1: "Timer Ended" when the timer reaches 00:00:00.

Line 2: The current timer value in HH:MM format when the timer is running or paused.

When user first start the timer the following is what the user sees

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfkWDROSa-u2qlrY7SfM9MdOuaQcLjMnNMnnLdaKgQo6uan-x0VK3DvpYRIXYOnzoJA0VLdsi3Bx0NI71XxQ6Dgvx-0awGqdtqkeIdzsI6T7A-aIXOnb0B5J_1pjcO5J5FEU0sQoRAySGETHw8LfzsZen9g?key=CCTEQPQ62lXGHUiHtNA4aA)

Timer in line 1 and the remaining duration in line2

By pressing ‘C’ user can enter the timer setting mode as shown below.  
![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfqSSH9SnzsC-8FsX8Eq0Gdn1KY8uZnwZBsn5OJDrl6U3WsJEqJ7aRkYkWXvukYYCwG6RSbCbZ-yY-1M4aNGFfj-gF3HLYZHcZg8mu6MoF_6jHVhNP6wUVblBhkjY0pgQTy494mnB0CaJVkM2ALVOFUcch3?key=CCTEQPQ62lXGHUiHtNA4aA)

Entering the duration of the timer in the format of HHMMSS and pressing “C” again completes the setting process, and the user will return to the main display of the timer.

Pressing ‘D’ at any point of the setting process will cancel the timer setting.

At this point the timer is set and ready to start.  
Press ‘#’ key to start the timer.

When the timer is running press ‘`*`’ will pause the timer. When paused although pressing ‘C’ will bring up the setting menu but setting with an already running timer is invalid. 

User needs to press ‘D’ to reset the current time to revert to the below state.

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXfkWDROSa-u2qlrY7SfM9MdOuaQcLjMnNMnnLdaKgQo6uan-x0VK3DvpYRIXYOnzoJA0VLdsi3Bx0NI71XxQ6Dgvx-0awGqdtqkeIdzsI6T7A-aIXOnb0B5J_1pjcO5J5FEU0sQoRAySGETHw8LfzsZen9g?key=CCTEQPQ62lXGHUiHtNA4aA)

Now the user can set a new timer.

When the timer completes its count down a timer complete message will appear on screen. At this point a new timer can also be set.

### Stopwatch

Given the simple nature of the stop watch there will only be 1 display as can be seen below that simply shows the time elapsed since the start.

![](https://lh7-rt.googleusercontent.com/docsz/AD_4nXeM2vqt0vZp5ijw4uzQqXLau6MSnFrHNLSUOthrfBxSetVx3eskgLQ7aqhAH7F0Tpy3X2rySBJi1v-Db-bQsplAj_8b2m-jxzSVNvMAqvrSxD1cSfk_ysOEcqwKhZ5kNQG4lWib2RhtGQd_-Zbst4xM72Z8?key=CCTEQPQ62lXGHUiHtNA4aA)

Pressing ‘C’ will start the timer if the time displays 00:00:00 and will pause upon pressing ‘C’ again. This process repeats itself every time ‘C’ is pressed. By pressing D the stopwatch will stop and reset the time to 00:00:00.

## Scientific Timer initialisation and operation

The scientific timer mode allows for the operation of up to 4 precise timers. 

Upon entering Scientific timer mode for the first time, the user is prompted to select how many timers they would like to use. The user can select between 1 and 4 timers. The user can then set the time for each timer in the format HH:MM:SS. After completing the setup routine, the user can start and pause, each timer independently using the direct buttons SW1-SW4. They may also start all timers simultaneously using the B1 switch. They can reconfigure the timers individually by pressing the function button and selecting the timer they wish to modify, before pressing the set key (C) on the keypad. This will take them to an edit screen where they can modify the time for that timer. They may also initiate the initial configuration routine to pick a new number of timers and set them all at once again by pressing the reset key (D) on the keypad.


The direct switches SW1-SW4 allow for starting and pausing the timers from anywhere in the UI, even in standard clock mode. This allows for procedures than involve lining up a timer with the real time of day, or a stopwatch for example. The direct LEDs adjacent to each switch correspond to each timer as well, and indicate the timer status (slow blinking = ready, solid = running, fast blinking = completed, off = timer not active)

  

## Additional Resources

 