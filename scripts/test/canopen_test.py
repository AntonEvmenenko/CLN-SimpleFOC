import canopen
import time
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

network = canopen.Network()
# network.connect(interface='socketcan', channel='can0', bitrate=125000)
network.connect(interface='gs_usb', channel=0, bitrate=125000)

node = canopen.RemoteNode(21, None)
network.add_node(node)

# node.sdo['Producer heartbeat time'].raw = 1000

print(f"Initial NMT state: {node.nmt.state}")

# logger.info("Scanning...")
# network.scanner.search()
# time.sleep(2)
# found_nodes = list(network.scanner.nodes)
# logger.info(f"Found nodes: {found_nodes}")

def on_heartbeat(state: int):
    state_str = canopen.nmt.NMT_STATES.get(state, f'UNKNOWN ({state})')
    print(f"Received heartbeat. Currrent state: {state_str}")

node.nmt.add_heartbeat_callback(on_heartbeat)

try:
    while True:
        time.sleep(2)

except KeyboardInterrupt:
    print("\nAborted by user")
except Exception as e:
    logging.error(f"Error: {e}")
finally:
    print("Disconnecting from CAN bus...")
    if network.bus:
        network.disconnect()
    print("Disconnected")

