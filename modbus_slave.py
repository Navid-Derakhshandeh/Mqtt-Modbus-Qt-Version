from pyModbusTCP.server import ModbusServer
import time

# Create Modbus TCP server
server = ModbusServer("localhost", 1502, no_block=True)

try:
    print("Starting Modbus TCP server...")
    server.start()

    # Initialize 8 holding registers (addresses 0–7)
    server.data_bank.set_holding_registers(0, [0]*8)
    print("Server is running. Press Ctrl+C to stop.")

    last_value = None

    while True:
        # Read holding register 8
        values = server.data_bank.get_holding_registers(8, 1)
        if values:
            current_value = values[0]
            if current_value != last_value:
                print(f"Register 8 = {current_value}")
                last_value = current_value

        time.sleep(0.2)

except KeyboardInterrupt:
    print("Stopping server...")
    server.stop()

