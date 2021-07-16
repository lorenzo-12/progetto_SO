CC=gcc
CCOPTS=-std=gnu99
BINS=capture_camera capture_joystick

.phony: clean all

all: $(BINS)

capture_camera:	capture_camera.c
	$(CC) -$(CCOPTS) -o $@ $^  

capture_joystick:	capture_joystick.c
	$(CC) -$(CCOPTS) -o $@ $^  

clean:
	rm -rf *~ $(BINS) *.pgm

