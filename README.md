# TWRP device tree for REDMAGIC NX809J

## Supported devices

- REDMAGIC 11 Pro
- ZTE Z80 Ultra

## Build

```shell

mkdir twrp && cd twrp

repo init --depth=1 -u https://github.com/TWRP-Test/platform_manifest_twrp_aosp.git -b twrp-16.0

repo sync

git clone --depth=1 https://github.com/ruoqing501/android_device_Nubia_NX809J.git device/nubia/NX809J

source build/envsetup.sh

export ALLOW_MISSING_DEPENDENCIES=true

lunch twrp_NX809J-bp2a-eng

m recoveryimage

```

If there is no error, `recovery.img` will be generated at:

```text
out/target/product/NX809J/recovery.img
```

## Features

Works:

- [X] ADB
- [X] Display
- [X] Decryption
- [X] Fastbootd
- [X] Flashing
- [X] Haptic feedback / vibration
- [X] MTP
- [X] ADB sideload mode
- [X] Touchscreen
- [X] USB OTG
- [X] Wi-Fi
- [X] WPA2-PSK connection
- [X] DHCP / DNS / internet access from TWRP
