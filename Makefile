Target  = test_spectrum
Sources = Spectrum.cpp SpectrumAnalysis.cpp MathModel.cpp main.cpp
Objects = Spectrum.o SpectrumAnalysis.o MathModel.o

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

all:$(Target)

test_spectrum: main.cpp $(Objects)
	g++ -o $@ main.cpp $(Objects) $(ROOTFLAGS) $(ROOTLIBS)

Spectrum.o: Spectrum.cpp Spectrum.h
	g++ -o $@ Spectrum.cpp -c $(ROOTFLAGS)

SpectrumAnalysis.o: SpectrumAnalysis.cpp SpectrumAnalysis.h
	g++ -o $@ SpectrumAnalysis.cpp -c $(ROOTFLAGS)

MathModel.o: MathModel.cpp MathModel.h
	g++ -o $@ MathModel.cpp -c $(ROOTFLAGS)

clean:
	rm -f $(Objects) $(Target)
	@echo "Sector clear!"