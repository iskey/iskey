CC= gcc

CFLAGS:= -L/usr/local/lib/ -I/usr/local/include/ -lev
CFLAGS:= $(CFLAGS) -g
CFLAGS:= $(CFLAGS) `pkg-config --libs --cflags glib-2.0`

TARGET_C=$(wildcard *.c)
TARGET_O=$(patsubst %.c,%.o,$(TARGET_C))
#TARGET=$(subst .c,,$(TARGET_C))
TARGET=$(patsubst %.c,%,$(TARGET_C))

all: rtsp_server

rtsp_server:$(TARGET_O)
	$(CC) -o $@ $^ $(CFLAGS)

$(TARGET_O):%.o:%.c
	$(CC) -c $< $(CFLAGS)
	
.PHONY : clean
clean:
	@rm -fvr $(TARGET_O)
	@rm -fvr rtsp_server
