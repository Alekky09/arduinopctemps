import time
import serial
import wmi

w = wmi.WMI(namespace="root\OpenHardwareMonitor")
cpu = 0
gpu = 0

# Put your COM port here
port = "COM5"
arduino = serial.Serial(port, 9600, timeout=1)

while True:
    hw_infos = w.Sensor()
    
    if hw_infos:
        for sensor in hw_infos:

            if sensor.SensorType == "Temperature":
                if sensor.Name == "GPU Core":                    
                    gpu = ("G%dP" % sensor.Value)

                elif sensor.Name == "CPU Package":                    
                    cpu = ("C%dS" % sensor.Value)
        
        arduino.write(gpu.encode() + cpu.encode())
        # print(gpu.encode() + cpu.encode())
        time.sleep(0.5)

    else:
        arduino.write("ErrorS".encode())        
        # print("Error".encode())
        time.sleep(2)
