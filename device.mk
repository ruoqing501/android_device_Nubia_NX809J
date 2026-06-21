#
# Copyright (C) 2026 The Android Open Source Project
# Copyright (C) 2026 SebaUbuntu's TWRP device tree generator
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := device/nubia/NX809J

# Base product configuration
$(call inherit-product, $(SRC_TARGET_DIR)/product/base.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit_only.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/emulated_storage.mk)
$(call inherit-product, vendor/twrp/config/common.mk)

# Shipping API level
BOARD_SHIPPING_API_LEVEL := 36
PRODUCT_SHIPPING_API_LEVEL := 36
PRODUCT_TARGET_VNDK_VERSION := 36

# Dynamic partitions
PRODUCT_USE_DYNAMIC_PARTITIONS := true

# Fastbootd
PRODUCT_PACKAGES += \
    fastbootd

# Wi-Fi
PRODUCT_PACKAGES += \
    wpa_cli_recovery \
    wpa_supplicant_recovery

# Otacert
PRODUCT_EXTRA_RECOVERY_KEYS += \
    $(DEVICE_PATH)/security/releasekey

# Kernel
PRODUCT_OTA_ENFORCE_VINTF_KERNEL_REQUIREMENTS   := false
PRODUCT_ENABLE_UFFD_GC                          := true
PRODUCT_CHECK_PREBUILT_MAX_PAGE_SIZE            := false
