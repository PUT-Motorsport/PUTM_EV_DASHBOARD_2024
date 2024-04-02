# Dashboard

A next-gen racing car dashboard powered by TouchGFX.

<img width="500" src="https://github.com/PUT-Motorsport/PUTM_EV_DASHBOARD_2024/assets/28950897/880ac114-cadb-45ca-99b1-776ad6b42841">

The dashboard presents the following information:
- speed,
- SOC,
- RPM,
- power,
- distance traveled,
- estimated range,
- current, last and the best lap duration,
- lap pace,
- battery, inverter, oil and coolant temperature,
- oil and coolant pressure.

## Prerequisites

Follow the [TouchGFX Installation Guide](https://support.touchgfx.com/docs/introduction/installation) to set up the environment.

Make sure you have the following programs installed and updated:

- TouchGFX Designer (Windows required),
- STM32CubeIDE (or optionally STM32CubeMX),
- STM32CubeProgrammer.

> [!IMPORTANT]
> Don't change the default installation paths, or things will break.

## Setup

1. Clone the repository: `git clone --recurse-submodules 'git@github.com:PUT-Motorsport/PUTM_EV_DASHBOARD_2024.git'`.

> [!IMPORTANT]
> Make sure that the project path is short and contains no special characters or spaces.

2. Open the project using the TouchGFX Designer: click on the open button, then select the `TouchGFX/Dashboard.touchgfx` file.

> [!NOTE]
> To update the project to a new TouchGFX version (if needed), follow the [Updating to a new TouchGFX Version](https://support.touchgfx.com/docs/miscellaneous/updating-to-a-new-touchgfx-version) guide.

3. Generate the code: `Code` → `Generate Code`.
4. Import the project into the STM32CubeIDE: `File` → `Open Project from Filesystem…` and select the `STM32CubeIDE` directory.

You can now work on the project.

To flash the firmware, build it and program the target either using TouchGFX or STM32CubeIDE.


## Icons

#### Google Material Library

Some icons used in this project are sourced from Google Material Icons library, which is provided under the Apache License, Version 2.0 (the "License"). You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.

For specific details about the Material Icons license, please refer to the following link: https://github.com/google/material-design-icons/blob/master/LICENSE

#### Flaticon

The following icons have been created using images obtained from <https://flaticon.com>:

- [Battery](https://www.flaticon.com/free-icon/battery_1626494),
- [Inverter](https://www.flaticon.com/free-icon/thunder_2682835),
- [Oil temperature](https://www.flaticon.com/free-icon/hot-water_11590055),
- [Oil pressure](https://www.flaticon.com/free-icon/pressure-gauge_15322629),
- [Coolant temperature](https://www.flaticon.com/free-icon/engine-coolant_95134),
- [Coolant pressure](https://www.flaticon.com/free-icon/pressure-gauge_7808070).

## License

    Copyright 2024 Ignacy Kajdan

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
