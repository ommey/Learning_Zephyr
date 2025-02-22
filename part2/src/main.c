#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

static const struct gpio_dt_spec led = 
  GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);

int main() 
{
  if (!device_is_ready(led.port)) {
    return;
  }
//  int ret = gpio_pin_configure(led.port, led.pin, led.dt_flags);
int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
if (ret != 0) {
  return;
}


  while (1){
    printf("Hello, World! from: ");
    printf(CONFIG_BOARD);
    printf("\n");

    //ret = gpio_pin_set_dt(&led, 1);
    ret = gpio_pin_toggle_dt(&led);

    if (ret != 0) {
      return;
    }
    k_msleep(1000);
}
  return 0;
}