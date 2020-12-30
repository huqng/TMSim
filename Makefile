turing: main.cpp TM.h Transmission_function.h Tape.h
	g++ main.cpp -o turing
.PHONY:
clean:
	rm turing