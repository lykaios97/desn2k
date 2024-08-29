import serial
import time

def send_time(serial_port, interval=1):
    try:
        ser = serial.Serial(serial_port, 38400)  # Adjust the baud rate as necessary
        time.sleep(2)  # wait for the serial connection to initialize

        while True:
            current_time = time.localtime()
            time_str = time.strftime("%H%M%S%d%m%y", current_time)
            
            print(f"Sending time: {time_str}")
            ser.write(time_str.encode())
            time.sleep(interval)  # Wait for the specified interval before sending the next time
    except serial.SerialException as e:
        print(f"Error opening serial port {serial_port}: {e}")
    except KeyboardInterrupt:
        print("Stopping time sending.")
    finally:
        ser.close()

if __name__ == "__main__":
    send_time('/dev/tty.usbmodem113103', interval=1)