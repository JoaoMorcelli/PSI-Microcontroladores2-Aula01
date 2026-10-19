#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MAIOR 500
#define SLEEP_TIME_MENOR 200
#define SLEEP_TIME_MEDIO 300

#define STACK_SIZE 1024
#define PRIORITY 0

// Define o LED usando Device Tree
#define LED2_NODE DT_ALIAS(led2)
#define LED1_NODE DT_ALIAS(led1)

static const struct gpio_dt_spec ledVermelho = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

static const struct gpio_dt_spec ledAzul = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

void threadLedAzul(void *arg1, void *arg2, void *arg3) {
    while (1) {
        int retAzul;

        retAzul = gpio_pin_configure_dt(&ledAzul, GPIO_OUTPUT_ACTIVE);
        gpio_pin_set_dt(&ledAzul, 0);

        k_msleep(SLEEP_TIME_MAIOR);
        gpio_pin_toggle_dt(&ledAzul);
        k_msleep(SLEEP_TIME_MENOR);
        gpio_pin_toggle_dt(&ledAzul);
        k_msleep(SLEEP_TIME_MEDIO);
        gpio_pin_toggle_dt(&ledAzul);       
        k_msleep(SLEEP_TIME_MENOR);
        gpio_pin_toggle_dt(&ledAzul); 
    }
}

void threadLedVermelho(void *arg1, void *arg2, void *arg3) {
    while (1) {
        int retVermelho;

        retVermelho = gpio_pin_configure_dt(&ledVermelho, GPIO_OUTPUT_ACTIVE);
        gpio_pin_set_dt(&ledVermelho, 0);

        k_msleep(SLEEP_TIME_MAIOR);
        k_msleep(SLEEP_TIME_MENOR);
        k_msleep(SLEEP_TIME_MEDIO);
        gpio_pin_toggle_dt(&ledVermelho);
        k_msleep(SLEEP_TIME_MENOR);
        gpio_pin_toggle_dt(&ledVermelho);

    }
}

K_THREAD_DEFINE(threadAzul, STACK_SIZE, threadLedAzul,
                NULL, NULL, NULL,
                PRIORITY, 0, 0);

K_THREAD_DEFINE(threadVermelho, STACK_SIZE, threadLedVermelho,
                NULL, NULL, NULL,
                PRIORITY, 0, 0);
