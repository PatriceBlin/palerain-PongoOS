/* 
 * pongoOS - https://checkra.in
 * 
 * Copyright (C) 2019-2023 checkra1n team
 *
 * This file is part of pongoOS.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */
#include <pongo.h>

static bool s8003_probe(struct hal_platform_driver* device_driver, struct hal_platform* device) {
    if (device->cpid == 0x8003) {
        return true;
    }
    return false;
}

static struct usb_regs s8003_usb_regs = {
    .reg1 = 0x0e080250,
    .reg2 = 0x0e080258,
    .reg3 = 0x0e080290,
    .otg_irq = 214
};

static bool s8003_get_platform_value(const char* name, void* value, size_t* size) {
    if (strcmp(name, "usb_regs") == 0 && *size == sizeof(struct usb_regs)) {
        memcpy(value, &s8003_usb_regs, sizeof(struct usb_regs));
        return true;
    }
    return false;
}

static struct hal_platform_driver s8003_plat = {
    .name = "Apple A9 (S8003, TSMC)",
    .context = NULL,
    .probe = s8003_probe,
    .get_platform_value = s8003_get_platform_value
};

static void s8003_init(struct driver* driver) {
    hal_register_platform_driver(&s8003_plat);
}

REGISTER_DRIVER(s8003, s8003_init, NULL, DRIVER_FLAGS_PLATFORM);
