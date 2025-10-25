import serial
import time
import keyboard

# Open serial port (Replace 'COM4' with the port your Arduino is connected to)
ser = serial.Serial('COM4', 9600, timeout=1)

# Wait for serial connection to be established
time.sleep(2)

# Initial values for drone control
throttle = 1500  # Start at midpoint (1000-2000)
yaw = 1500
pitch = 1500
roll = 1500
servo_toggled = False

def send_command(command_type, value):
    command = f"{command_type} {value}\n"
    ser.write(command.encode('utf-8'))
    print(f"Sent command: {command.strip()}")
    response = ser.readline().decode('utf-8').strip()
    print(f"Arduino response: {response}")

def toggle_servo():
    global servo_toggled
    servo_toggled = not servo_toggled
    command = "SERVO_TOGGLE\n"
    ser.write(command.encode('utf-8'))
    print(f"Sent command: {command.strip()}")
    response = ser.readline().decode('utf-8').strip()
    print(f"Arduino response: {response}")

try:
    print("Use W/S for throttle, A/D for yaw, I/K for pitch, J/L for roll, and R to toggle the servo.")
    while True:
        if keyboard.is_pressed('w'):
            throttle += 10
            if throttle > 2000:
                throttle = 2000
            send_command("THROTTLE", throttle)
            time.sleep(0.1)

        if keyboard.is_pressed('s'):
            throttle -= 10
            if throttle < 1000:
                throttle = 1000
            send_command("THROTTLE", throttle)
            time.sleep(0.1)

        if keyboard.is_pressed('a'):
            yaw -= 10
            if yaw < 1000:
                yaw = 1000
            send_command("YAW", yaw)
            time.sleep(0.1)

        if keyboard.is_pressed('d'):
            yaw += 10
            if yaw > 2000:
                yaw = 2000
            send_command("YAW", yaw)
            time.sleep(0.1)

        if keyboard.is_pressed('i'):
            pitch += 10
            if pitch > 2000:
                pitch = 2000
            send_command("PITCH", pitch)
            time.sleep(0.1)

        if keyboard.is_pressed('k'):
            pitch -= 10
            if pitch < 1000:
                pitch = 1000
            send_command("PITCH", pitch)
            time.sleep(0.1)

        if keyboard.is_pressed('j'):
            roll -= 10
            if roll < 1000:
                roll = 1000
            send_command("ROLL", roll)
            time.sleep(0.1)

        if keyboard.is_pressed('l'):
            roll += 10
            if roll > 2000:
                roll = 2000
            send_command("ROLL", roll)
            time.sleep(0.1)

        if keyboard.is_pressed('r'):
            toggle_servo()
            time.sleep(0.3)  # Debounce to prevent multiple toggles

except KeyboardInterrupt:
    print("Program terminated")

finally:
    ser.close()
