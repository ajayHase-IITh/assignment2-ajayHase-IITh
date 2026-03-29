ifdef CROSS_COMPILE
$(info  CROSS_COMPILE is defined)
CC :=  $(CROSS_COMPILE)gcc
else
$(info CROSS_COMPILE not defined use native build platform)
CC := gcc
endif

CFLAGS := -Wall -Wextra -Werror
TARGET := writer
SRCS   := writer.c
OBJS   := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
