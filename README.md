# CLN-SimpleFOC

This repository contains the firmware for the [CLN closed-loop stepper motor drivers](https://github.com/creapunk/CLN-ClosedLoopNemaDriver). This firmware is based on [SimpleFOC](https://github.com/simplefoc/Arduino-FOC). Currently, only the **CLN V2.0** hardware is supported

## Safety information

Please be attentive when interacting with the CLN. It is a good idea to occasionally check the temperature of the DRV8844 (even with your finger) to make sure it is not overheating. In addition, for the first tests, it is a very good idea to use a laboratory power supply that can limit the current. 1 Ampere should be quite enough to start with. If tested irresponsibly, **WHITE SMOKE MAY ESCAPE** 🤣 

## How to use

1. You need the CLN V2.0 driver mounted on a motor. Ideally, you should connect it to your computer via the [SWD over USB Type-C](https://hackaday.io/project/192857-swd-over-usb-type-c-new-way-of-programming-boards) adapter. If you don't have it, you can probably use the standard ST-Link V2 to do the job too, but it's a little more complicated
1. Download the project and open it in [PlatformIO](https://platformio.org/)
1. Open the [src/config.h](https://github.com/AntonEvmenenko/CLN-SimpleFOC/blob/main/src/config.h) and **make sure that `POWER_SUPPLY_VOLTAGE` corresponds to your power supply voltage**. Also, **make sure that all the motor parameters listed in the `Motor` section correspond to your motor**
1. Use PlatformIO to build and upload the project
1. On first power-up, the motor performs a self-calibration and stores the parameters in the MCU’s “EEPROM” (actually the last page of FLASH). On subsequent startups, calibration is skipped. To force calibration, hold down SW1 while powering on the CLN. **The motor shaft must be free to rotate during calibration**
1. By default the motor works in position control mode. You can control the motor by sending the commands via the Serial interface, which by default works via the MCU's USB. See [here](https://docs.simplefoc.com/commander_motor) for a list of the available commands. For example, you can use the following command to change the position (shaft's angle) setpoint to PI radians:

```
M3.14
```

## Additional useful information

1. Attach the magnet to the motor shaft so that it is as close to the PCB as possible. You may need to use a spacer
1. You could easily change the motion control mode by modifying the first lines of the `initMotorParameters()` function
1. By default the motor current is set to 1.5A. You could change that by modifying the corresponding line in the `initMotorParameters()` function
1. The CLN's LED displays the firmware's status. Red (🟥) means that initialization is in progress. Blue (🟦) means that calibration is in progress. Green (🟩) means that the firmware is working normally
1. The firmware prints logs via Serial during startup. If something is wrong, check the logs first
1. I recommend doing any debugging and interaction with the servo via the [MCUViewer V1.1.0](https://github.com/klonyyy/MCUViewer/releases/tag/v1.0.1). You can find the corresponding configuration file in the project's root. A bunch of variables have already been added there. You can also easily tweak any PID/LPF/etc coefficients via the MCUViewer

## Information for developers

1. The latest SimpleFOC code is not compatible with CLN. I am currently trying to make the necessary changes to SimpleFOC to fix this, the discussion is [here](https://community.simplefoc.com/t/low-side-current-sensing-for-stepper-motors/7235), the draft PR is [here](https://github.com/simplefoc/Arduino-FOC/pull/472)