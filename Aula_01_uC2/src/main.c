#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MAIOR 500
#define SLEEP_TIME_MENOR 200
#define SLEEP_TIME_MEDIO 300

// Define o LED usando Device Tree
#define LED2_NODE DT_ALIAS(led2)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
static const struct gpio_dt_spec ledVermelho = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec ledAzul = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

int main(void)
{
    int retAzul; int retVermelho;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&ledAzul)) {
        printk("Error: LED device %s is not ready\n", ledAzul.port->name);
        return 0;
    }

    // Configura o pino como saída
    retAzul = gpio_pin_configure_dt(&ledAzul, GPIO_OUTPUT_ACTIVE);
    retVermelho = gpio_pin_configure_dt(&ledVermelho, GPIO_OUTPUT_ACTIVE);

    if (retAzul < 0) {
        printk("Error %d: failed to configure LED pin\n", retAzul);
        return 0;
    }

    gpio_pin_set_dt(&ledVermelho, 0);
    gpio_pin_set_dt(&ledAzul, 0);

    while (1) {
        //Toggle do LED usando a nova API
        //gpio_pin_toggle_dt(&ledAzul);
        k_msleep(SLEEP_TIME_MAIOR);
        gpio_pin_toggle_dt(&ledAzul);
        k_msleep(SLEEP_TIME_MENOR);
        gpio_pin_toggle_dt(&ledAzul);
        k_msleep(SLEEP_TIME_MEDIO);
        gpio_pin_toggle_dt(&ledAzul);
        gpio_pin_toggle_dt(&ledVermelho);
        k_msleep(SLEEP_TIME_MENOR);
        gpio_pin_toggle_dt(&ledAzul);
        gpio_pin_toggle_dt(&ledVermelho);
    }
    return 0;
}