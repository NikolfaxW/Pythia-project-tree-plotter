#include <iostream>
#include <string>

#include "TCanvas.h"
#include "TH2D.h"
#include "TMarker.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TTree.h"
#include "TFile.h"
#include "TKey.h"
#include "TLegend.h"

//! USE LOG SCALE FOR Y AXIS(JUST FOR PT destribution)



void DrawHistogramFromTree(const std::string path, const std::string filename, const char *treename, const char *variable, const char *selection = "") {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    save_path.append(variable);
    save_path.append(", ");
    save_path.append(filename);
    save_path.append(".pdf");
    TFile *file = TFile::Open( fullpath.c_str());
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

    Float_t left_border = tree->GetMinimum(variable);
    Float_t right_border = tree->GetMaximum(variable);

    TH1F *histogram = new TH1F("histogram", variable, 100, left_border , right_border);
    // create histogram with filname as title, nbinsx bins, min and max values of variable - can be changed
    tree->Project("histogram", variable, selection);
    // 4250 x 3300 pixels for full page histograms?
    // 2075 x 1650 pixels for half page histograms?
    // 1037 x 825 pixels for quarter page histograms?
    // 800 x 600 is basic size

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 4250, 3300); //width = 800 height 600 pixels
    histogram->Draw();



    histogram->GetXaxis()->SetTitle("pT [GeV/c]");
    histogram->GetYaxis()->SetTitle("N, number of jets");

    canvas->SaveAs(save_path.c_str());



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
    std::string path = "../../Pythia-project-tree-creator/results/";
    std::string filename = "jet tree, cut [D_0 n =10000, 1+ GeV]";
    DrawHistogramFromTree(path, filename, "T", "z_val", 0);

    return 0;
}
