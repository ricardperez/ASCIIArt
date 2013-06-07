CC=g++
LIBS=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_ml

all:
	python prepare.py
	$(CC) $(LIBS) -o ASCIIArt *.cpp
	rm *.cpp
	rm *.h

clear:
	rm *.cpp
	rm *.h
	
copy:
	python prepare.py
	
compile:
	$(CC) $(LIBS) -o ASCIIArt *.cpp