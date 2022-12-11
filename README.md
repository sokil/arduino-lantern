# Lantern

Lantern, controlled by move and lighting level

## Hardware

### Motion Sensor HC-SR501

Mote info at: 
* https://arduinogetstarted.com/tutorials/arduino-motion-sensor

## Troubleshooting
If you get error `[upload] could not open port /dev/ttyACM0: [Errno 13] Permission denied: '/dev/ttyACM0'` error, try:

```
sudo usermod -a -G tty {YOUR_USER_NAME}
sudo chmod a+rw /dev/ttyACM0
```
