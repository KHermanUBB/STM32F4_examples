# SENSORS

# GSM modem

### Modification in devicetree

Change UART2 by UART1

Add rng 

```jsx
&rng {
    status = "okay";
};
```

Comment i2c

```jsx
/*
&i2c2 {
        pinctrl-0 = <&i2c2_scl_pb10 &i2c2_sda_pb11>;
        pinctrl-names = "default";
        status = "okay";
        clock-frequency = <I2C_BITRATE_FAST>;

        vl53l0x@29 {
                compatible = "st,vl53l0x";
                reg = <0x29>;
                xshut-gpios = <&gpioc 6 GPIO_ACTIVE_HIGH>;
        };

        mpu6050@68 {
                compatible = "invensense,mpu6050";
                reg = <0x68>;
                status = "okay";
                int-gpios = <&gpioc 13 GPIO_ACTIVE_HIGH>;
        };

};
*/
```

### Modification prj.conf

Add corresponding support for the gsm modem example

```jsx
# UART support
CONFIG_SERIAL=y

## GSM modem support
CONFIG_MODEM=y
CONFIG_MODEM_GSM_PPP=y

## PPP networking support
CONFIG_NET_DRIVERS=y
CONFIG_NET_PPP=y
CONFIG_NET_L2_PPP=y
CONFIG_NET_NATIVE=y
CONFIG_NETWORKING=y

CONFIG_NET_L2_PPP_TIMEOUT=10000

## IPv4 enables PPP IPCP support
CONFIG_NET_IPV4=y
CONFIG_NET_IPV6=n

## Network management events
CONFIG_NET_CONNECTION_MANAGER=y

## Log buffers, modem and PPP
CONFIG_LOG=y
CONFIG_NET_LOG=y
#CONFIG_LOG_BUFFER_SIZE=16384
#CONFIG_MODEM_LOG_LEVEL_DBG=y
#CONFIG_NET_PPP_LOG_LEVEL_DBG=y
#CONFIG_NET_L2_PPP_LOG_LEVEL_DBG=y
#CONFIG_NET_MGMT_EVENT_LOG_LEVEL_DBG=y
#CONFIG_NET_CONNECTION_MANAGER_LOG_LEVEL_DBG=y

CONFIG_NET_SHELL=y
CONFIG_MODEM_SHELL=y

CONFIG_TEST_RANDOM_GENERATOR=y
#CONFIG_GSM_MUX=y
#CONFIG_UART_MUX=y
```

T**o compile the program you must do**

```jsx
west build -b stm32f4_disco app -- -DCONFIG_MODEM_GSM_APN=\"internet\" -DDTC_OVERLAY_FILE="boards/frdm_uart2_dts.overlay"
```