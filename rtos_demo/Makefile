# Target name
TARGET = rtos-demo-stm32-bluepill

# # Build path
BUILD_DIR = build

all:
	make format \
	&& cd ${BUILD_DIR} && ninja && cd ..

cmake:
		cmake --no-warn-unused-cli \
		-DCMAKE_TOOLCHAIN_FILE:FILEPATH=armgcc-toolchain.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
		-DCMAKE_BUILD_TYPE:STRING=Debug \
		-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-gcc-11.2.0 \
		-Bbuild \
		-GNinja

flash:
	openocd -f interface/stlink-dap.cfg -f target/stm32f1x.cfg -c "program ${BUILD_DIR}/${TARGET}.elf verify reset exit"

format:
	clang-format -i -style=LLVM Core/Src/*.c Core/Inc/*.h 

clean:
	-rm -fR ${BUILD_DIR}

ser:
	sudo minicom -D /dev/ttyUSB0 -b 115200
