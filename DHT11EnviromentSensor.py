#This micropython program is compatible with DHT11. and DHT22 senors
#for reading and displaying the enviromental temperature and realative humidity.

import machine
import utime
import dht

#Initializing the pins for input and output

#The sensor pin setup with in-built pull-up resistor setup.
sensorPin = machine.Pin(15, machine.Pin.IN, machine.Pin.PULL_UP)
dhtSensor = dht.DHT11(sensorPin)

#Onboard led setup
led = machine.Pin(25, machine.Pin.OUT)

#Sensor stabilization time
utime.sleep(2)

#The function to read and display the data related to temperature and humidity.
def readAndDisplay():
    try:
        dhtSensor.measure()
        temperature = dhtSensor.temperature()
        humidity = dhtSensor.humidity()
        
        print("Temperature: {}\u00b0C".format(temperature))
        print("Humidity: {}%".format(humidity))
        
        if (temperature > 0) or (humidity > 0):
            led.value(1)
        else:
            led.value(0)
        
        utime.sleep(2)
        
    except Exception as e:
        print("Failed to read from DHT11 sensor:", e)
        led.value(0)

#Infinitely reads and displays the data until interrupted.
while True:
    thisReadAndDisplay()
