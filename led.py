import time
import curses
import smbus
import time

bus = smbus.SMBus(1)


address = 0x04
prevcommand = 0
def main(stdscr):
	stdscr.nodelay(1)
	while True:
		command = stdscr.getch()
		if command != -1:
			stdscr.addstr(str(command) + ' ')
			if( command == 260):
				command = 1
			if( command == 261):
				command = 2
			writeNumber(command)
			stdscr.refresh()
			stdscr.move(0,0)
			readNumber()

def writeNumber(value):
	bus.write_byte(address,value)
	return -1

def readNumber():
	number = bus.read_byte(address)
	return number

if __name__ == '__main__':
	curses.wrapper(main)
