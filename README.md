# Arduino Traffic Light with Pedestrian Button & Countdown

This project simulates a real-life traffic light system with a pedestrian crossing button.

## Features
- Red and green traffic lights
- Pedestrian button input
- Buzzer for crossing signal
- 4-digit 7-segment countdown display
- Green light blinks near the end of countdown

## How it works
- By default, the light stays red for cars to pass
- When the button is pressed:
  - Red blinks as warning
  - Green turns on + buzzer beeps, allowing the pedestrians to cross the road
  - Countdown starts on 7-seg display
  - LCD Display shows Countdown aswell as current status of light
  - Near the end, green starts blinking
  - System returns to red

## Hardware Used
- Arduino 
- LEDs (Red, Green)
- LCD I2C Display (16x2)
- Buzzer
- Push button
- 4-digit 7-segment display
- Resistors & wires (220/330 ohm)

## Demo Video
