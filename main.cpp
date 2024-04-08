#include "Pythia8/Pythia.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH2D.h"
#include "TMath.h"
#include "TMarker.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTree.h"
#include "TFile.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "TKey.h"
#include "TLegend.h"

#include <iostream>



void DrawHistogramFromTree(const char* filename, const char* treename, const char* variable, const char* selection = "") {
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree*)file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }

    TH1F *histogram = new TH1F("histogram", "Histogram of pT", 100, tree->GetMinimum(variable), tree->GetMaximum(variable));

    tree->Project("histogram", variable, selection);
    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 hight 600 pixels
    histogram->Draw();
    histogram->GetXaxis()->SetTitle("pT [MeV]");
    histogram->GetYaxis()->SetTitle("N");



    canvas->SaveAs("histogram.pdf");



    delete histogram;
    delete canvas;
    file->Close();
}

void PrintTreeNames(const char* filename) {
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    TIter next(file->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
        TObject *obj = key->ReadObj();
        if (obj->IsA()->InheritsFrom("TTree")) {
            std::cout << "Found tree: " << obj->GetName() << std::endl;
        }
    }

    file->Close();
}


int main() {
    DrawHistogramFromTree("Jet_tree.root", "T", "pT");
//    PrintTreeNames("Jet_tree.root");

    return 0;
}
