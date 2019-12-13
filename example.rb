require_relative "./coffin"

serial = Serial.new "/dev/cu.usbmodem144201", 9600
# serial = STDOUT
driver = Coffin::Driver.new(serial)

driver.down(:power)
sleep 1
driver.up(:power)

driver.press(:power)
driver.hold(:power, 5)
