import tkinter as tk
import serial
import threading
import time
import queue

class DaminGUI:
    def __init__(self, root, command_queue):
        self.root = root
        self.command_queue = command_queue

        self.root.title("Stepper Motor Control")
        self.root.geometry("400x400")
        self.root.configure(bg="#800000")

        self.connection_status = tk.Label(self.root, text="Arduino Not Connected", fg="red")
        self.connection_status.pack()

        self.create_buttons()

    def create_buttons(self):
        cw_button = tk.Button(self.root, text="CW", command=self.send_cw_command)
        cw_button.pack()

        ccw_button = tk.Button(self.root, text="CCW", command=self.send_ccw_command)
        ccw_button.pack()

        stop_button = tk.Button(self.root, text="Stop", command=self.send_stop_command)
        stop_button.pack()

        blink_button = tk.Button(self.root, text="Blink", command=self.send_blink_command)
        blink_button.pack()

    def send_cw_command(self):
        self.command_queue.put("CW")

    def send_ccw_command(self):
        self.command_queue.put("CCW")

    def send_stop_command(self):
        self.command_queue.put("STOP")

    def send_blink_command(self):
        self.command_queue.put("BLINK")

def control_motor(command_queue, blink_event):
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        gui.connection_status.pack_forget()
    except serial.SerialException:
        ser = None

    while True:
        if ser:
            try:
                command = command_queue.get(timeout=0.1)
                ser.write(command.encode())
                print(f"Sent command: {command}")
                time.sleep(0.1)

                if command == "BLINK":
                    blink_event.set()  # Set the blink event when BLINK command is received
            except queue.Empty:
                pass
        else:
            print("Arduino not connected")

def blink_led(blink_event):
    while True:
        if blink_event.is_set():
            # Blink the LED here (you need to implement this part)
            print("LED Blinking")
            time.sleep(0.5)  # Adjust the blink interval as needed
            blink_event.clear()  # Clear the blink event

if __name__ == "__main__":
    command_queue = queue.Queue()
    blink_event = threading.Event()  # Create an event for LED blinking

    root = tk.Tk()
    gui = DaminGUI(root, command_queue)

    motor_thread = threading.Thread(target=control_motor, args=(command_queue, blink_event))
    blink_thread = threading.Thread(target=blink_led, args=(blink_event,))

    motor_thread.start()
    blink_thread.start()

    root.mainloop()
