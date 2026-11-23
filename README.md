# hypharos_minibot_STM32
STM32F103C8T6 firmware for the MiniBot, ported by NCU Mathematical Robotics Lab (MRL) to the new WHEELTEC C03C + S28A + TB6612 hardware.
Built with Keil MDK 5. For the original HyphaROS firmware, see the `v1` branch.

## Versions
| Branch | Description |
|---|---|
| `v1` | Original HyphaROS MiniBot firmware (Keil MDK 4 project) |
| `v2` (`main`) | Ported to the new WHEELTEC hardware by NCU MRL (Keil MDK 5 project) |

### Changes in v2
- **New hardware**: the original modules are discontinued, so v2 targets their WHEELTEC replacements:
  - Core board: WHEELTEC C03C (STM32F103C8T6)
  - Adapter board: WHEELTEC S28A (STM32 adapter board)
  - Motor driver: TB6612
- **MPU6050 moved to the Raspberry Pi**: the IMU is now read by the Raspberry Pi instead of the MCU, so the MPU6050 driver, DMP, I²C driver and IMU filter were removed.
- **Removed unused modules**: Bluetooth (USART2) and DataScope debug output.
- Migrated the project from `.uvproj` (MDK 4) to `.uvprojx` (MDK 5).

## Build
Open `HyphaROS_MiniBot_STM32/USER/Minibalance.uvprojx` with Keil MDK 5 and press **Build (F7)**.
The output is `HyphaROS_MiniBot_STM32/OBJ/Minibalance.hex`.

## Flash
A prebuilt `HyphaROS_MiniBot_STM32/OBJ/Minibalance.hex` is included.
Flash it over USB-serial with FlyMcu
(unzip `FlyMcu.zip` in this repo, or download it from the [official site](http://www.mcuisp.com/)):

1. Click **EnumPort** and select the COM port (bps: `115200`).
2. Select `HyphaROS_MiniBot_STM32/OBJ/Minibalance.hex` as the code file.
3. Check **Verify** and **Run After ISP complete**.
4. Set the bottom option to **Reset@DTR Low(<-3V), ISP@RTS High**.
5. Click **Start ISP(P)**.

![FlyMcu configuration](docs/images/flymcu_config.png)

## Credits
Developed by NCU Mathematical Robotics Lab (MRL), based on the sample code
provided by WHEELTEC with the C03C / S28A / TB6612 modules.
For the original firmware from [HyphaROS MiniBot](https://github.com/Hypha-ROS/hypharos_minibot) by HaoChih Lin, see the `v1` branch.
