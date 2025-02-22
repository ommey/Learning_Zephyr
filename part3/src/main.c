#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

#define DEBOUNCE_DELAY_MS 200  // Adjust debounce time as needed

static struct gpio_callback button_cb_data;
static struct k_timer debounce_timer;

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(blinking_led), gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_NODELABEL(button), gpios);

// Flag to indicate button press
volatile bool button_pressed_flag = false;

// Timer callback (executed after debounce delay)
void debounce_timer_handler(struct k_timer *timer_id) {
    if (button_pressed_flag) {
        gpio_pin_toggle_dt(&led);  // Toggle LED after debounce
        button_pressed_flag = false;
    }
}

// Button interrupt handler
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    // Set flag and start debounce timer
    button_pressed_flag = true;
    k_timer_start(&debounce_timer, K_MSEC(DEBOUNCE_DELAY_MS), K_NO_WAIT);
}

int main() 
{
    if (!device_is_ready(led.port)) {
        return 0;
    }
    if (!device_is_ready(button.port)) {
        return 0;
    }

    // Configure LED (ensure it starts OFF)
    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret != 0) {
        return 0;
    }

    // Configure button as input
    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0) {
        return 0;
    }

    // Configure button interrupt (trigger on press)
    ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
        return 0;
    }

    // Initialize debounce timer
    k_timer_init(&debounce_timer, debounce_timer_handler, NULL);

    // Attach callback
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    while (1) {
        k_msleep(1000);
    }

    return 0;
}
