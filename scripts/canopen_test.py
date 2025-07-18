import canopen
import time
import logging

logging.basicConfig(level=logging.DEBUG)

# Start with creating a network representing one CAN bus
network = canopen.Network()

network.connect(interface='gs_usb', channel=0, bitrate=125000)

# This will attempt to read an SDO from nodes 1 - 127
network.scanner.search()
# We may need to wait a short while here to allow all nodes to respond
time.sleep(2)
for node_id in network.scanner.nodes:
    print(f"Found node {node_id}!")

# network.sync.stop()
network.disconnect()