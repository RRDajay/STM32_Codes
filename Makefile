# Target name
TARGET = i2c_master_write_demo
EXAMPLES = Examples

# # Build path
BUILD_DIR = build

all:
	cd ${BUILD_DIR} && ninja && cd ..

cmake:
		cmake --no-warn-unused-cli \
		-DCMAKE_TOOLCHAIN_FILE:FILEPATH=armgcc-toolchain.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
		-DCMAKE_BUILD_TYPE:STRING=Debug \
		-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-gcc-11.2.0 \
		-Bbuild \
		-GNinja

flash:
	openocd -f interface/stlink-dap.cfg -f target/stm32f1x.cfg -c "program ${BUILD_DIR}/${EXAMPLES}/${TARGET}/${TARGET}.elf verify reset exit"

format:
	find Examples/ -iname *.h -o -iname *.c | xargs clang-format -i -style=WebKit && \
	find Core -iname *.h -o -iname *.c | xargs clang-format -i -style=WebKit

clean:
	-rm -fR ${BUILD_DIR}

ser:
	sudo minicom -D /dev/ttyUSB0 -b 115200
