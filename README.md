# Smart Dynamic Traffic Light System (PoC)

## Overview

This project is a Proof of Concept (PoC) for a low-cost dynamic traffic light system intended for Smart City use cases, particularly temporary roadworks.
The system replaces fixed-timer traffic lights with an adaptive solution that reacts to real vehicle presence, improving traffic flow and reducing unnecessary waiting times.

![Hardware setup](/images/electronicSchema.png)

## Problem

Temporary traffic lights are usually based on static timing, even when one side of the road is empty. This leads to long waits, traffic congestion, driver frustration, and increased pollution due to idling vehicles.

## Solution

The proposed system is built around an Arduino UNO R4 WiFi acting as a central controller. Ultrasonic sensors detect vehicles on each side of the road, allowing the traffic lights to switch dynamically based on real demand rather than fixed cycles.

Green light duration is calculated using parameters such as road distance and allowed speed. These parameters can be configured through a simple web interface, hosted directly on the Arduino via its Wi-Fi access point. This makes the system easy to deploy and adjust on-site, without additional infrastructure.

![Web interface](/images/webInterface.png)

## System Logic

The algorithm is based on a state machine that ensures safe transitions between red, amber, and green phases. Minimum green and amber durations are enforced, while still allowing priority to the side where vehicles are detected.

The logic was first designed using a pseudo-code structogram to cover all traffic scenarios, then implemented in C++ on the Arduino.

![Algorithm pseudo-code](/images/TrafficLightsAlgorithm.png)

## Hardware

The PoC uses affordable and widely available components, including :
- 1 Arduino UNO R4 WiFi
- 2 traffic light LED modules
- 2 HC-SR04 ultrasonic distance sensors
- 10 standard jumper wires.

![List of Hardware](/images/hardware.png)
