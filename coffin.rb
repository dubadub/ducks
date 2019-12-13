require "null_logger"

class Coffin
  class Driver

    COMMANDS = {
      volume_up: {
        on: "d".freeze,
        off: "c".freeze,
      },
      volume_down: {
        on: "f".freeze,
        off: "e".freeze,
      },
      power: {
        on: "b",
        off: "a",
      },
      usb: {
        on: "h".freeze,
        off: "g".freeze,
      },
    }

    PRESS_DELAY = 0.5

    def initialize(serial, logger = NullLogger.new)
      @serial = serial
      @logger = logger
    end

    def down(button)
      @logger.debug("down #{button}")
      fail unless COMMANDS[button]

      dispatch(COMMANDS[button][:on])
    end

    def up(button)
      @logger.debug("up #{button}")
      fail unless COMMANDS[button]

      dispatch(COMMANDS[button][:off])
    end

    def press(button)
      down(button)
      sleep PRESS_DELAY
      up(button)
    end

    def hold(button, time)
      fail unless COMMANDS[button]

      down(button)
      sleep time
      up(button)
    end

    private

    def dispatch(command)
      @logger.debug("Dispatching command to serial: '#{command}'")

      @serial.write(command)
    end
  end

end
