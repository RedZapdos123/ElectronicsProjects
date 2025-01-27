from machine import Pin
import time

#Onboard LED and sensor pin setup with an in-built pull down resistor for stablity of the signal
sensorPin = Pin(15, Pin.IN, Pin.PULL_DOWN)
led = Pin(25, Pin.OUT)

#Pulse counters
pulseCount = 0
lastPulseTime = 0

#The function to count pulses
def pulseDetected(pin):
    global pulseCount, lastPulseTime
    
    #The current time in miliseconds
    currentTime = time.ticks_ms()
    
    #Buffer avoid multiple counts for the same pulse
    if time.ticks_diff(currentTime, lastPulseTime) > 100:
        pulseCount += 1
        lastPulseTime = currentTime

#The interupt function
sensorPin.irq(trigger=Pin.IRQ_RISING, handler=pulseDetected)

#Measuring the pulses' and printing the count on the serial monitor
try:
    while True:
        led.value(1)
        print("Measuring heart rate for 10 seconds...")

        #Measure heart rate for 10 seconds, and print the heart rate
        for second in range(1, 11):
            startTime = time.ticks_ms()
            startPulse = pulseCount

            #Count pulses for 1 second
            while time.ticks_diff(time.ticks_ms(), startTime) < 1000:
                time.sleep(0.01)

            #Calculate and display the heart rate for each second
            beats = pulseCount - startPulse
            heartRate = beats * 60 
            print(f"Second {second}: {heartRate} BPM")

        led.value(0)
        print("Measurement complete. Waiting before next session...\n")

        #Five seconds cooldown period.
        time.sleep(5)

#Error handling
except KeyboardInterrupt:
    print('Stopped.')
    led.value(0)
