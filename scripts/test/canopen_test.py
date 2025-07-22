import canopen
import time
import logging
import os

os.system('sudo ip link set can0 up type can bitrate 125000')

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

network = canopen.Network()
network.connect(interface='socketcan', channel='can0', bitrate=125000)

node = canopen.RemoteNode(21, './DS301_profile.eds')
network.add_node(node)

# node.sdo['Producer heartbeat time'].raw = 1000
# node.sdo['Target position'].raw = -1.0

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

network.sync.start(0.01)
# node.tpdo.read()
# node.rpdo.read()

# node.tpdo[1].clear()
# node.tpdo[1].add_variable('Target position')
# node.tpdo[1].trans_type = 254
# node.tpdo[1].event_timer = 10
# node.tpdo[1].enabled = True
# node.tpdo[1].save()

# node.rpdo[1].transmit()

node.rpdo.read()

# print(f'{node.tpdo=}')
# print(f'{node.rpdo=}')

angle = 0.0

try:
    while True:
        # node.sdo['Target position'].raw = angle
        angle += 0.01
        node.rpdo[1]['Target position'].raw = angle
        node.rpdo[1].transmit()
        time.sleep(0.01)
        # time.sleep(2)

except KeyboardInterrupt:
    print("\nAborted by user")
except Exception as e:
    logging.error(f"Error: {e}")
finally:
    print("Disconnecting from CAN bus...")
    if network.bus:
        network.sync.stop()
        network.disconnect()
    print("Disconnected")
