#
# Copyright (C) 2026 The Android Open Source Project
#
# SPDX-License-Identifier: Apache-2.0
#

DEVICE_PATH := device/nubia/NX809J

# Inherit from device.mk configuration
$(call inherit-product, $(DEVICE_PATH)/device.mk)

## Device identifier
PRODUCT_NAME    := twrp_NX809J
PRODUCT_BRAND   := REDMAGIC
PRODUCT_MANUFACTURER := nubia
PRODUCT_MODEL := NX809J
PRODUCT_DEVICE  := NX809J

# Theme
TW_STATUS_ICONS_ALIGN   := center
