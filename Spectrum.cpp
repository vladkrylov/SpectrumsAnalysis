/*
 * Spectrum.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: vlad
 */

#include "Spectrum.h"
#include "TMath.h"
#include "TString.h"
#include "TAxis.h"

Spectrum::Spectrum() {
	// TODO Auto-generated constructor stub

}

Spectrum::Spectrum(int spectrumTime, string sp_data)
{
	spectrum_time = spectrumTime;
	Init(sp_data);
}

Spectrum::~Spectrum() {
	delete[] c;
	delete[] legend;
	delete[] gr;
	delete[] ftot;

	if (nop > 0) {
		for (int i = 0; i < nop; ++i) {
			delete[] fpart[i];
		}
		delete[] fpart;
	}
	delete[] params;
}

void Spectrum::Test()
{
	cout << numberOfPoints << endl;
}

void Spectrum::Init(string yd)
{
	nop = 0;

	Fill(yd);

	size_t xs = x.size();
	size_t ys = y.size();

	numberOfPoints = Min(xs, ys);
	gr = new TGraph(numberOfPoints, &(x[0]), &(y[0]));
}

void Spectrum::FillX(string xdata)
{
	double a;
	ifstream in;

	in.open(xdata.c_str());
	while (in >> a) {
		x.push_back(a);
	}
	in.close();
	in.clear();
}

void Spectrum::FillY(string ydata)
{
	double a;
	ifstream in;

	in.open(ydata.c_str());
	while (in >> a) {
		y.push_back(a);
	}
	in.close();
	in.clear();
}

void Spectrum::Fill(string data)
{
	double a, b;
	ifstream in;

	in.open(data.c_str());
	while (in >> a >> b) {
		x.push_back(a);
		y.push_back(b);
	}
	in.close();
	in.clear();
}

size_t Spectrum::Min(size_t a, size_t b)
{
	if (a < b)
		return a;
	else
		return b;
}

void Spectrum::Write()
{
	name = "Time = " + string(Form("%d", spectrum_time)) + " hours";

	c = new TCanvas(name.c_str(),name.c_str(),800,600);
	legend = new TLegend(.75,.80,.95,.95);

//	gr->SetTitle(name.c_str());
	gr->SetTitle("");
	gr->GetXaxis()->SetTitle("Wavelength, nm");
	gr->GetYaxis()->SetTitle("Amplitude, arbitrary units");
	gr->Draw("AC");
	legend->AddEntry(gr, "Experimental data", "L");
	legend->AddEntry(ftot, "Summary fit", "L");

	int dataToLegend = 0;
	string writeToLegend;
	for (int i = 0; i < nop; ++i) {
		fpart[i]->SetLineColor(3+i);
		fpart[i]->SetLineStyle(2);
		fpart[i]->Draw("ACsame");

		dataToLegend = fpart[i]->GetParameter(1);
		writeToLegend = string(Form("%i", dataToLegend)) + " nm";
		legend->AddEntry(fpart[i], writeToLegend.c_str(), "L");
	}
	legend->Draw();

	c->Write();
}

void Spectrum::WriteToPDF(string pdfname, char mode)
{
	string pdfBookmarkName = "Title:" + name;
	if (mode == 'o') {
		pdfname += "(";
	} else if (mode == 'f') {
		pdfname += ")";
	}
	c->Print(pdfname.c_str(), pdfBookmarkName.c_str());
}

void Spectrum::Fit(MathModel* model)
{
	nop = model->GetNumberOfPeaks();
	double f_min = x[0];
	double f_max = x[numberOfPoints-1];
	ftot = new TF1("ftot",model->GetModel(),f_min,f_max);
	fpart = new TF1*[nop];
	for (int i = 0; i < nop; ++i) {
		fpart[i] = new TF1("fpart", "gaus", f_min, f_max);
	}
	params = new double[3*nop];

	for (int i = 0; i < nop; ++i) {
		ftot->SetParLimits(3*i,   model->GetMinAmp(i),   model->GetMaxAmp(i));
		ftot->SetParLimits(3*i+1, model->GetMinMean(i),  model->GetMaxMean(i));
		ftot->SetParLimits(3*i+2, model->GetMinSigma(i), model->GetMaxSigma(i));
	}

//	ftot->SetRange(4004,6000);
	ftot->SetParameters(model->GetInitParameters());
	for (int i = 0; i < 10; ++i) {
		gr->Fit("ftot","qbR");
	}

	ftot->GetParameters(params);
	for (int i = 0; i < nop; ++i) {
		fpart[i]->SetParameters(&params[3*i]);
	}

	fullArea = 0;
	for (int i = 0; i < nop; ++i) {
		fullArea += GetArea(i);
	}

//	cout << area << endl;
}

double Spectrum::GetAmp(int peakId)
{
	return ftot->GetParameter(3*peakId);
}

double Spectrum::GetMean(int peakId)
{
	return ftot->GetParameter(3*peakId+1);
}

double Spectrum::GetArea(int peakId)
{
	return ftot->GetParameter(3*peakId) * TMath::Sqrt(2*TMath::Pi()) * (ftot->GetParameter(3*peakId+2));
}

double Spectrum::GetPartialArea(int peakId)
{
	return GetArea(peakId) / fullArea;
}
