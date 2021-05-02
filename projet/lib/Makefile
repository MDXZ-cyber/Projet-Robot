src=$(wildcard *.cpp)
OBJ = $(src:.cpp=.o)
MCU=atmega324pa

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr  -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall                                        

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

target = librairie.a
all: $(target)
librairie.a:$(OBJ)

	avr-ar -crs $(target) $(OBJ)

# De C++ a objet
%.o: %.cpp
	avr-g++ $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.d