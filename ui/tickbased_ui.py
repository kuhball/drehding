#!/usr/bin/env python3

# Simple UI to steer the `tickbased_ui` sketch

import time

import serial
import PySimpleGUI as sg

# Config
MAX_SKIP_TURNS = 10
HALL_PULSE_PER_TURN = 9  # see HALL_PULSE_PER_TURN setting in your sketch
SERIAL_PORT = '/dev/ttyACM1'  # see bottom right of Arduino IDE
SERIAL_PORT_BAUD = 9600 # see Serial.begin(SERIAL_PORT_BAUD) in your sketch

# Init connection to Arduino
arduino = serial.Serial(SERIAL_PORT, SERIAL_PORT_BAUD, timeout=.1)
time.sleep(1)  # give the connection a second to settle

# Functions
def mkslider(min, max, default, key):
    return sg.Slider(
        enable_events=True,
        range=(min, max),
        default_value=default,
        orientation='horizontal',
        key=key
    )


def mkled(id):
    return [
        [sg.Text(f"LED {id}")],
        [sg.Text(f"At which tick of the {HALL_PULSE_PER_TURN} rotation ticks to flash:")],
        [mkslider(0, HALL_PULSE_PER_TURN - 1, 0, f'led_{id}_pos')],
        [sg.Text("Rotations to skip after each flash:")],
        [mkslider(0, MAX_SKIP_TURNS, 0, f'led_{id}_cooldown')]
    ]


def main():
    layout = [
        [sg.Text("Controls for tickbased_ui sketch")],
        [sg.Text('_'*30)],
        [sg.Text("Motor speed")],
        [mkslider(0, 255, 40, 'motor_pulse_length')],
        [sg.Text('_'*30)],
        *mkled(1),
        [sg.Text('_'*30)],
        *mkled(2),
        [sg.Text('_'*30)],
        *mkled(3),
        [sg.Button("Close")]
    ]

    # Create the window
    window = sg.Window("Controls for tickbased_ui sketch", layout)

    # Create an event loop
    while True:
        event, values = window.read()
        # End program if user closes window or
        # presses the OK button
        if event == "Close" or event == sg.WIN_CLOSED:
            break

        msg = f'{event}:{int(values[event])}'
        arduino.write(str.encode(msg))
        print(f'Send: {msg}')

        while True:
            data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
            if data:
                print('data', data)
            else:
                break

    window.close()


if __name__ == "__main__":
    main()
