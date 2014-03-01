/*
 * Spectrum.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: vlad
 */

#include "Spectrum.h"
#include "TMath.h"

Spectrum::Spectrum() {
	// TODO Auto-generated constructor stub

}

Spectrum::Spectrum(string xd, string yd)
{
	Init(xd, yd);
}

Spectrum::~Spectrum() {
	// TODO Auto-generated destructor stub
}

void Spectrum::Test()
{
	cout << numberOfPoints << endl;
}

void Spectrum::Init(string xd, string yd)
{
	FillX(xd);
	FillY(yd);

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

size_t Spectrum::Min(size_t a, size_t b)
{
	if (a < b)
		return a;
	else
		return b;
}

void Spectrum::Write()
{
	gr->Write();
}

void Spectrum::Fit(MathModel* model)
{
	double f_min = x[0];
	double f_max = x[numberOfPoints-1];
	ftot = new TF1("ftot",model->GetModel(),f_min,f_max);

	for (int i = 0; i < model->GetNumberOfPeaks(); ++i) {
		ftot->SetParLimits(3*i,   model->GetMinAmp(i),   model->GetMaxAmp(i));
		ftot->SetParLimits(3*i+1, model->GetMinMean(i),  model->GetMaxMean(i));
		ftot->SetParLimits(3*i+2, model->GetMinSigma(i), model->GetMaxSigma(i));
	}

//	ftot->SetRange(4004,6000);
	ftot->SetParameters(model->GetInitParameters());
	gr->Fit("ftot","qbR");

	Double_t area =  ftot->GetParameter(0) * TMath::Sqrt(2*TMath::Pi()) * (ftot->GetParameter(2));

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

