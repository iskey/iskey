CC= gcc

CFLAGS:=

TARGET_C=$(wildcard *.c)
#TARGET_O=$(subst .c,.o,$(TARGET_C))
#TARGET=$(subst .c,,$(TARGET_C))
TARGET=$(patsubst %.c,%,$(TARGET_C))

all: $(TARGET)

$(TARGET):%:%.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY : clean
clean:
	@rm -fvr $(TARGET)