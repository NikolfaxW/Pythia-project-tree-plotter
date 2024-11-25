#include <iostream>
#include <string>
#include <algorithm>

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


#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TFile.h>

void superscript_example() {
    // Create a histogram
    TH1F *hist = new TH1F("hist", "Histogram with Superscript", 100, 0, 10);

    // Fill the histogram with random data
    for (int i = 0; i < 10000; ++i) {
        hist->Fill(gRandom->Gaus(5, 1));
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Canvas with Superscript", 800, 600);

    // Set the axis labels with superscripts
    hist->GetXaxis()->SetTitle("X axis label (units)^{2}");
    hist->GetYaxis()->SetTitle("Y axis label (units)^{2}");

    // Draw the histogram
    hist->Draw();

    // Save the canvas to a file
    canvas->SaveAs("histogram_with_superscript.png");

    // Clean up
    delete hist;
    delete canvas;
}

void DrawHistogramFromTree(const std::string path, const std::string filename, const char *treename, const char *variable, const char *selection = "", const bool doRootSave = false) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append(" ");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
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

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

//    canvas->SetLogx(); //set x axis to log scales



    histogram->Draw();


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Position: x1, y1, x2, y2
    legend->SetHeader("Legend Title", "C");            // Optional title (centered)
    legend->AddEntry(histogram, "Dataset 1", "l");         // "l" means line

    // Customize legend appearance (optional)
    legend->SetBorderSize(1);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle("pT [GeV/c]");
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if(doRootSave){
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }



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
//    std::string path = "../source/";
//    std::string filename = "jet tree, cut [D_0 n =1000000, 1+ GeV]";
//    PrintTreeNames((path + filename + ".root").c_str());
//    DrawHistogramFromTree(path, filename, "T", "D_0_pT", "", true);
    superscript_example();
    
    return 0;
}
