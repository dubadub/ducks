require "rubyserial"

class Coffin
  class Driver

    COMMANDS = {
      volume_up: {
        on: "a".freeze,
        off: "b".freeze,
      },
      volume_down: {
        on: "c".freeze,
        off: "d".freeze,
      },
      power: {
        on: "e".freeze,
        off: "f".freeze,
      },
      usb: {
        on: "g".freeze,
        off: "h".freeze,
      },
    }

    PRESS_DELAY = 1

    def initialize(serial)
      @serial = serial
    end

    def down(button)
      fail unless COMMANDS[button]

      dispatch(COMMANDS[button][:on])
    end

    def up(button)
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
      @serial.write(command)
    end
  end

end
