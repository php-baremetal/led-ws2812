/*
   +----------------------------------------------------------------------+
   | php-baremetal: led-ws2812                                            |
   +----------------------------------------------------------------------+
   | Copyright (c) 2026 Gianfrancesco Aurecchia                           |
   +----------------------------------------------------------------------+
   | This source file is subject to the MIT license, that is bundled with |
   | this package in the file LICENSE.                                    |
   +----------------------------------------------------------------------+
   | Authors: Gianfrancesco Aurecchia <gianfri@aurecchia.com>             |
   +----------------------------------------------------------------------+
*/

/* WS2812 addressable RGB LED (3-channel, GRB on the wire). Some onboard LEDs are WS2812s in
 * RGB order -- pass order: Ws2812::RGB for them. */
#include "php_led.h"

extern const led_driver_desc_t ws2812_driver_desc;

ZEND_BEGIN_ARG_INFO_EX(arginfo_ws2812_ctor, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, pin, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, count, IS_LONG, 0, "1")
    ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, order, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

PHP_METHOD(Ws2812, __construct)
{
    led_ctor(INTERNAL_FUNCTION_PARAM_PASSTHRU, &ws2812_driver_desc);
}

static const zend_function_entry ws2812_methods[] = {
    PHP_ME(Ws2812, __construct, arginfo_ws2812_ctor, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

const led_driver_desc_t ws2812_driver_desc = {
    .name = "ws2812",
    .php_class = "Ws2812",
    .model = BM_LED_MODEL_WS2812,
    .channels = 3,
    .default_order = LED_ORDER_GRB,
    .methods = ws2812_methods,
};
