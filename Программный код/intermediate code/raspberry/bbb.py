from time import sleep
import pydbus

DEVICE_ADDR = '7C:03:AB:B5:52:9C' #  device address


# DBus object paths
BLUEZ_SERVICE = 'org.bluez'
device_path = f"/org/bluez/hci0/dev_{DEVICE_ADDR.replace(':', '_')}"

# setup dbus
bus = pydbus.SystemBus()
device = bus.get(BLUEZ_SERVICE, device_path)

# Connect to device
device.Connect()
sleep(10)
device.Disconnect()