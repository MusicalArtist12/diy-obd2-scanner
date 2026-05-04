BOARD_FQDN=arduino:avr:uno
PORT=/dev/ttyUSB2

ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))


LIBS=${ROOT_DIR}arduino-mcp2515/,${ROOT_DIR}LCD1602/,${ROOT_DIR}include
CONFIG_DIR=${ROOT_DIR}data

EXTRA_ARGS=--config-dir ${CONFIG_DIR} -b ${BOARD_FQDN} -p ${PORT} --library ${LIBS}