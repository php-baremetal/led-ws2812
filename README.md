# led-ws2812

The WS2812 driver for [ext-led](package:php-baremetal/ext-led): it adds `Baremetal\Led\Driver\Ws2812`, a class
for WS2812 and WS2812B addressable RGB LEDs (strips, rings, and the single RGB LED many boards carry). Three
channels, GRB byte order by default.

## Install

In a project created with `phpbm init`:

```bash
composer require php-baremetal/led-ws2812
```

The package requires ext-led, so this line is enough; conductor adds the LED-strip HAL for your platform
(`esp32-ledstrip-hal` on ESP32).

## Example

```php
<?php
use Baremetal\Led\Driver\Ws2812;

$strip = new Ws2812(pin: 5, count: 8);   // GRB, cleared on construction
$strip->fill(0, 0, 32);                  // dim blue into the buffer
$strip->hsv(0, 0, 255, 64);              // first pixel red
$strip->show();

$onboard = new Ws2812(48, 1, Ws2812::RGB);   // Waveshare ESP32-S3-Zero: on-board LED, RGB order
$onboard->set(0, 8, 0);
```

## The class

| Item | Value |
| --- | --- |
| Class | `Baremetal\Led\Driver\Ws2812`, extends `Baremetal\Led\Device`, implements `Baremetal\Output\Led` |
| Constructor | `new Ws2812(int $pin, int $count = 1, ?int $order = null)` |
| Constants | `Ws2812::GRB` (0, default), `Ws2812::RGB` (1) |
| Methods | `pixel()`, `fill()`, `hsv()`, `set()`, `show()`, `off()`, `count()`, all from `Device` |
| LED model | WS2812 timing |

`$order` accepts only `GRB` and `RGB`; anything else throws `\ValueError`. Standard strips are GRB; if red and
green come out swapped, pass `Ws2812::RGB`. The methods, their errors and the limits are documented in
[ext-led](package:php-baremetal/ext-led#docs/usage/device.md).

## Registration

The package is a `bm-lib` with one C file. It registers the descriptor `ws2812_driver_desc` into ext-led's
`led_drivers` registry (`extra.baremetal.register`); at startup ext-led turns it into the class above. To add
another chip the same way, see
[Writing a driver](package:php-baremetal/ext-led#docs/drivers/writing-a-driver.md).

## License

MIT.
