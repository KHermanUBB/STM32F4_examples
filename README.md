# Zephyr Example Application

This repository contains a Zephyr example application. The main purpose of this
repository is to serve as a reference on how to structure Zephyr based
applications. Some of the features demonstrated in this example are:

- Basic [Zephyr application][app_dev] skeleton
- [Zephyr workspace applications][workspace_app]
- [West T2 topology][west_t2]
- [Custom boards][board_porting]
- Custom [devicetree bindings][bindings]
- Out-of-tree [drivers][drivers]
- Out-of-tree libraries
- Example CI configuration (using Github Actions)
- Custom [west extension][west_ext]

This repository is versioned together with the [Zephyr main tree][zephyr]. This
means that every time that Zephyr is tagged, this repository is tagged as well
with the same version number, and the [manifest](west.yml) entry for `zephyr`
will point to the corresponding Zephyr tag. For example, `example-application`
v2.6.0 will point to Zephyr v2.6.0. Note that the `main` branch will always
point to the development branch of Zephyr, also `main`.

[app_dev]: https://docs.zephyrproject.org/latest/develop/application/index.html
[workspace_app]: https://docs.zephyrproject.org/latest/develop/application/index.html#zephyr-workspace-app
[west_t2]: https://docs.zephyrproject.org/latest/develop/west/workspaces.html#west-t2
[board_porting]: https://docs.zephyrproject.org/latest/guides/porting/board_porting.html
[bindings]: https://docs.zephyrproject.org/latest/guides/dts/bindings.html
[drivers]: https://docs.zephyrproject.org/latest/reference/drivers/index.html
[zephyr]: https://github.com/zephyrproject-rtos/zephyr
[west_ext]: https://docs.zephyrproject.org/latest/develop/west/extensions.html

## Getting Started

Before getting started, make sure you have a proper Zephyr development
environment. You can follow the official
[Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html).

### Initialization

The first step is to initialize the workspace folder (``my-workspace``) where
the ``example-application`` and all Zephyr modules will be cloned. You can do
that by running:

```shell
# initialize my-workspace for the example-application (main branch)
west init -m https://github.com/zephyrproject-rtos/example-application --mr main my-workspace
# update Zephyr modules
cd my-workspace
west update
```
```shell
vi .west/config
change path to STM32F4_examples

```

### Build & Run

The application can be built by running:

```shell
cd STM32F4_example
west build -b stm32f4_disco app
```

```shell
west flash
```

### USART2
The USART2 is used as a Zephyr terminal on PA2-TX and PA3-RX. Baudrate 115200

### Test applications

Use symbolic link in app/src to point to the actual application ie. 

```shell
ln -s TestApplication.c main.c
```

### Renode

start renode 

```shell
i @renode/scripts/stm32f4_discovery.resc 
start
``` 

### HelloWorld.c example

Compile the applicationa and run renode

```shell
i @renode/scripts/stm32f4_discovery.resc 
start
``` 
observe the output 

### PressButton.c example

Compile the applicationa and run renode

```shell
i @renode/scripts/stm32f4_discovery.resc 
start
gpioPortA.UserButton PressAndRelease 
``` 

