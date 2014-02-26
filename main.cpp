#include "Spectrum.h"
#include "SpectrumAnalysis.h"

#include "TFile.h"
#include <stdlib.h>
#include "vector"

int main(int argc, char** argv)
{
//	int numberOfSpectrums = 0;
//	std::vector<std::string> args(argv, argv+argc);
//	for (size_t i = 1; i < args.size() - 1; ++i) {
//		if (args[i] == "-nos") {
//			numberOfSpectrums = atoi(argv[i+1]);
//			break;
//		}
//	}
//	cout << numberOfSpectrums << endl;
	SpectrumAnalysis *Analysis = new SpectrumAnalysis("config");

//	Spectrum *f = new Spectrum();
//	f->Init("x.txt", "d1.txt");
////	f->Test();
//	f->Fit();
//
//	TFile *f_out = new TFile("nReport.root","RECREATE");
//	f->Write();
//	f_out->Close();

	return 0;
}
