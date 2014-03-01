#include "Spectrum.h"
#include "SpectrumAnalysis.h"

#include "TFile.h"
#include <stdlib.h>
#include "vector"

int main(int argc, char** argv)
{
	SpectrumAnalysis *Session = new SpectrumAnalysis("config");
	Session->Analyze();

	return 0;
}
