# A temperature sensor program made for DS18B20 and Raspberry Pi Pico 2.

import machine
import onewire
import ds18x20
import time

#Initializing the pins
dataPin = machine.Pin(15)

#Onboard LED pin as an output
led = machine.Pin(25, machine.Pin.OUT)

#Creating the OneWire and DS18X20 variables for operationality
ow = onewire.OneWire(dataPin)
ds = ds18x20.DS18X20(ow)

#Scan for DS18B20 device(s)
devices = ds.scan()


if not devices:
    print("No DS18B20 device found.")
else:
    print(f"Found {len(devices)} DS18B20 device(s): {devices}")

#Reading the temperature, multiple times
def readTemperature():
    while True:
        #Converting the temperature to Celsius from electric readings
        ds.convert_temp()
        time.sleep_ms(750)
        
        #Printing the readings
        for device in devices:
            temp = ds.read_temp(device)
            if temp is None:
                print("Error reading temperature!")
                led.off()
            else:
                print(f"Temperature: {temp:.2f} °C")
                led.on()
        
        #Reads every two seconds
        time.sleep(2)
        led.off()

if devices:
    readTemperature()
