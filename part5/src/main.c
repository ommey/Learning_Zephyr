#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <zephyr/logging/log.h>
#include "photos.h"
#include <stdint.h>
#include <zephyr/drivers/display.h>


LOG_MODULE_REGISTER(display);
static const struct device *display = DEVICE_DT_GET(DT_NODELABEL(ssd1306));

void main(void)
{
    if (display == NULL)
    {
        LOG_ERR("Device not found");
        return;
    }

    if (!device_is_ready(display))
    {
        LOG_ERR("Device not ready");
        return;
    }

    int ret;
 /*   ret = cfb_framebuffer_init(display);
    if (ret < 0)
    {
        LOG_ERR("Framebuffer initialization failed");
        return;
    }

    ret = cfb_print(display, "Hello World", 0, 0);
    if (ret < 0)
    {
        LOG_ERR("Print failed");
        return;
    }

    ret = cfb_framebuffer_finalize(display);
    if (ret < 0)
    {
        LOG_ERR("Framebuffer finalization failed");
        return;
    }

    LOG_INF("Display initialized");
   */ 

   struct display_capabilities capabilities;
   display_get_capabilities(display, &capabilities);

    LOG_INF("x_resolution: %d", capabilities.x_resolution);
    LOG_INF("y_resolution: %d", capabilities.y_resolution);
    LOG_INF("supported_pixel_formats: %d", capabilities.supported_pixel_formats);
    LOG_INF("sceen_info: %d", capabilities.screen_info);
    LOG_INF("current_pixel_format: %d", capabilities.current_pixel_format);
    LOG_INF("current_orientation: %d", capabilities.current_orientation);

   const struct display_buffer_descriptor buf_desc = {
        .buf_size = capabilities.x_resolution * capabilities.y_resolution,
        .width = capabilities.x_resolution,
        .height = capabilities.y_resolution,
        .pitch = 128,
    };

    if (display_write(display, 0, 0, &buf_desc, omar) != 0)
    {
        LOG_ERR("Failed to write to display");
        return;
    }

    if (display_set_contrast(display, 0) != 0)
    {
        LOG_ERR("Failed to set contrast");
        return;
    }

    size_t ms_sleep = 10;

    while (1)
    {
        for (size_t i = 0; i < 255; i++)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }

        for (size_t i = 255; i > 0; i--)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }

        if (display_write(display, 0, 0, &buf_desc, omar) != 0)
        {
            LOG_ERR("Failed to write to display");
            return;
        }
        for (size_t i = 0; i < 255; i++)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }

        for (size_t i = 255; i > 0; i--)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }
        
        if (display_write(display, 0, 0, &buf_desc, ibbe) != 0)
        {
            LOG_ERR("Failed to write to display");
            return;
        }
        for (size_t i = 0; i < 255; i++)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }

        for (size_t i = 255; i > 0; i--)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }
        
        if (display_write(display, 0, 0, &buf_desc, omar_julia) != 0)
        {
            LOG_ERR("Failed to write to display");
            return;
        }
        
        for (size_t i = 0; i < 255; i++)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }

        for (size_t i = 255; i > 0; i--)
        {
            display_set_contrast(display, i);
            k_msleep(ms_sleep);
        }
        
        if (display_write(display, 0, 0, &buf_desc, josef) != 0)
        {
            LOG_ERR("Failed to write to display");
            return;
        }

    }

    
}
    