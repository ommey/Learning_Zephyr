#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

static const struct device *dev = 
  DEVICE_DT_GET(DT_NODELABEL(gpio0));

int main() 
{
  if (!device_is_ready(dev)) {
    printk("Device %s is not ready\n", dev->name);
    return;
  }
  int ret = gpio_pin_configure(dev, 25, GPIO_OUTPUT_ACTIVE);


  while (1){
    printf("Hello, World!! from: ");
    printf(CONFIG_BOARD);
    printf("\n");

// ret = gpio_pin_set_raw(dev, 25, 1);
    if (ret != 0) {
      return;
    }
    k_msleep(1000);

    ret = gpio_pin_set_raw(dev, 25, 0);
    if (ret != 0) {
      return;
    }
    k_msleep(1000);
  }
  return 0;
}

