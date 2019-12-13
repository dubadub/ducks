require_relative "./coffin"
require "serialport"
require "logger"


serial = SerialPort.new "/dev/cu.usbmodem14101", 9600
# serial = STDOUT
driver = Coffin::Driver.new(serial, Logger.new(STDOUT))

sleep 3

# driver.up(:power)
# sleep 4
# driver.down(:power)

driver.press(:power)
# driver.hold(:volume_up, 5)

serial.close
