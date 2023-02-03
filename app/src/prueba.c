/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <zephyr/sys/printk.h>
#include <mpu6050.h>


void main(void)
{
	const struct device *const mpu6050 = DEVICE_DT_GET_ONE(invensense_mpu6050);
	const struct device *const vl53l0x = DEVICE_DT_GET_ONE(st_vl53l0x);

	struct sensor_value value;
        int ret;
	
	if (!device_is_ready(mpu6050)) {
		printf("Device %s is not ready\n", mpu6050->name);
	}

	if (!device_is_ready(vl53l0x)) {
                printk("sensor: device not ready.\n");
        }

#ifdef CONFIG_MPU6050_TRIGGER
	trigger = (struct sensor_trigger) {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ALL,
	};
	if (sensor_trigger_set(mpu6050, &trigger,
			       handle_mpu6050_drdy) < 0) {
		printf("Cannot configure trigger\n");
		return;
	}
	printk("Configured for triggered sampling.\n");
#endif

	while (!IS_ENABLED(CONFIG_MPU6050_TRIGGER)) {
		int rc = process_mpu6050(mpu6050);
		
		ret = sensor_sample_fetch(vl53l0x);
		if (ret) {
                        printk("sensor_sample_fetch failed ret %d\n", ret);
                        return;
                }
		ret = sensor_channel_get(vl53l0x, SENSOR_CHAN_PROX, &value);
		
		printk("prox is %d\n", value.val1);
		ret = sensor_channel_get(vl53l0x,
                                         SENSOR_CHAN_DISTANCE,
                                         &value);
		printf("distance is %.3fm\n", sensor_value_to_double(&value));

                k_sleep(K_MSEC(1000));
        


		if (rc != 0) {
			break;
		}
		k_sleep(K_SECONDS(2));
	}

	/* triggered runs with its own thread after exit */
}
