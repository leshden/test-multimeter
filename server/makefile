CC = gcc
LIBS = -lstdc++
OBJFILES = server.o local_socket.o multimeter_device.o transit_hub.o multimeter_channel.o
TARGET = server

all : $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES) $(LIBS)

clean:
	rm -f $(OBJFILES) $(TARGET)
