/*
 * Copyright (C) 2022-2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <unordered_map>
#include <string>
#include <fstream>
#include <sys/mount.h>
#include <unistd.h>

using android::base::GetProperty;

struct ModelInfo {
    const char* brand;
    const char* device;
    const char* manufacturer;
    const char* model;
    const char* twversion;
};

const std::unordered_map<std::string, ModelInfo> kModelInfoMap = {
    {"NX741J", {"nubia","PQ85A01","nubia","NX741J","Nubia-NX741J"}},
    {"NX809J", {"REDMAGIC", "NX809J", "nubia", "NX809J", "Nubia-NX809J"}},
};

void OverrideProperty(const char* name, const char* value) {
    size_t valuelen = strlen(value);
    prop_info* pi = (prop_info*)__system_property_find(name);
    if (pi != nullptr) {
        __system_property_update(pi, value, valuelen);
    } else {
        __system_property_add(name, strlen(name), value, valuelen);
    }
}

void SetupModelProperties(const ModelInfo& info) {
    struct PropPair {
        const char* key;
        const char* value;
    } props[] = {
        {"ro.product.brand",                info.brand},
        {"ro.product.device",               info.device},
        {"ro.product.manufacturer",         info.manufacturer},
        {"ro.product.model",                info.model},
        {"ro.product.name",                 info.model},
        {"ro.product.system.device",        info.device},
        {"ro.product.system.model",         info.model},
        {"ro.product.product.device",       info.device},
        {"ro.product.product.model",        info.model},
        {"ro.product.system_ext.device",    info.device},
        {"ro.product.system_ext.model",     info.model},
        {"ro.product.vendor.device",        info.device},
        {"ro.product.vendor.model",         info.model},
        {"ro.product.odm.device",           info.device},
        {"ro.product.odm.model",            info.model},
        {"ro.twrp.device_version",          info.twversion},
        {"ro.build.date.utc",               "0"},
    };

    for (const auto& p : props) {
        OverrideProperty(p.key, p.value);
    }
}

static std::string ReadBuildPropKey(const std::string& path, const std::string& key) {
    std::ifstream file(path);
    if (!file.is_open()) return "";

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(key + "=") == 0) {
            return line.substr(key.length() + 1);
        }
    }
    return "";
}

static std::string DetectDeviceFromVendor() {
    bool mounted = false;
    if (mount("/dev/block/by-name/vendor", "/vendor", "ext4", MS_RDONLY, "") == 0) {
        mounted = true;
    } else if (mount("/dev/block/by-name/vendor", "/vendor", "erofs", MS_RDONLY, "") == 0) {
        mounted = true;
    } else if (mount("/dev/block/by-name/vendor", "/vendor", "f2fs", MS_RDONLY, "") == 0) {
        mounted = true;
    }

    if (!mounted && access("/vendor/build.prop", F_OK) != 0) {
        return "NX809J";
    }

    std::string model = ReadBuildPropKey("/vendor/build.prop", "ro.product.model");
    if (model.empty()) {
        model = ReadBuildPropKey("/vendor/build.prop", "ro.product.vendor.model");
    }

    if (model.find("NX741J") != std::string::npos) {
        return "NX741J";
    }
    if (model.find("NX809J") != std::string::npos) {
        return "NX809J";
    }

    return "NX809J";
}

void vendor_load_properties() {
    std::string sku = DetectDeviceFromVendor();
    auto model_info = kModelInfoMap.find(sku);
    SetupModelProperties(model_info->second);
}
