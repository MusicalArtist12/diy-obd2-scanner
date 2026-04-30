BOARD_FQDN=arduino:avr:uno
PORT=/dev/ttyUSB0

default: compile

compile:
	arduino-cli compile --library ./arduino-mcp2515/ -e -u -b ${BOARD_FQDN} -p ${PORT} --config-dir ./data -v

.PHONY: monitor
monitor:
	arduino-cli monitor  --config-dir ./data -p ${PORT} --config 115200

check_preprocess:
	arduino-cli compile --library ./arduino-mcp2515/ -e -u -b ${BOARD_FQDN} -p ${PORT} --config-dir ./data --preprocess
