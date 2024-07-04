CC = gcc
CFLAGS = -O3
TARGET = gwc
SRCS = gwc.c
OBJS = $(SRCS:.c=.o)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build ran SUccessfully"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Clean ran Successfully"

.PHONY: all clean

