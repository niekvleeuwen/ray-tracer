# this makefile can be used to easily compile the project.

SRCS = main.cpp
CFLAGS = -Wall -g
LIBS = . 
TARGET = ray-tracer

all: $(SRCS)
	@echo Installing the ray tracer..
	g++ $(CFLAGS) $(SRCS) -I $(LIBS)-o $(TARGET)
	@echo Running program..
	./$(TARGET)
	convert image.ppm image.png
	rm image.ppm
	@echo Done!
clean: 
	@echo Removing the executable..
	rm $(TARGET)