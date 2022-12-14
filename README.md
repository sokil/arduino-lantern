# Lantern

Lantern, controlled by move and lighting level

## Hardware

### Motion Sensor HC-SR501

Mote info at: 
* https://arduinogetstarted.com/tutorials/arduino-motion-sensor

## Troubleshooting

### Arduino Uno

If you get error `[upload] could not open port /dev/ttyACM0: [Errno 13] Permission denied: '/dev/ttyACM0'` error, try:

```
sudo usermod -a -G tty {YOUR_USER_NAME}
sudo chmod a+rw /dev/ttyACM0
```

### Arduino Nano

Arduino Nano uses USB chip CH340G. 

Check that driver present in system:

```
$ lsmod | grep -i ch34
ch341                  24576  0
usbserial              57344  1 ch341
```

In Ubuntu 22.10 driver conflicts with `brltty` package. Log of `dmesg`:

```
[226233.187200] usb 3-2: new full-speed USB device number 22 using xhci_hcd
[226233.339999] usb 3-2: New USB device found, idVendor=1a86, idProduct=7523, bcdDevice= 2.54
[226233.340010] usb 3-2: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[226233.340014] usb 3-2: Product: USB2.0-Ser!
[226233.342955] ch341 3-2:1.0: ch341-uart converter detected
[226233.343770] ch341-uart ttyUSB0: break control not supported, using simulated break
[226233.343913] usb 3-2: ch341-uart converter now attached to ttyUSB0
[226233.917868] input: BRLTTY 6.5 Linux Screen Driver Keyboard as /devices/virtual/input/input142
[226233.919386] usb 3-2: usbfs: interface 0 claimed by ch341 while 'brltty' sets config #1
[226233.919930] ch341-uart ttyUSB0: ch341-uart converter now disconnected from ttyUSB0
[226233.920091] ch341 3-2:1.0: device disconnected
```

Just remote this package:

```
sudo apt purge brltty
```

If you get error 

```
*** [upload] could not open port /dev/ttyUSB0: [Errno 13] Permission denied: '/dev/ttyUSB0'
```

set rights to it:

```
sudo chmod a+rw /dev/ttyUSB0
```
