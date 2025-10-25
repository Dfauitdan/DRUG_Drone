import serial
import keyboard

# Replace 'COM4' with the correct port for your Arduino Uno
ser = serial.Serial('COM4', 9600)

def send_command():
    ser.write(b'R')

keyboard.add_hotkey('r', send_command)

print("Press 'R' to send command")
keyboard.wait('esc')  # Press ESC to exit
