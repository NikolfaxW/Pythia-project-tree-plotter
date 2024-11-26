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
#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TFile.h>

#include "func.h"



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



    TH1F *histogram = new TH1F("histogram", "P_{T,D^{0}}", 100, left_border , right_border);
    // create histogram with filname as title, nbinsx bins, min and max values of variable - can be changed
    tree->Project("histogram", variable, selection);

    // 4250 x 3300 pixels for full page histograms?
    // 2075 x 1650 pixels for half page histograms?
    // 1037 x 825 pixels for quarter page histograms?
    // 800 x 600 is basic size

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

//    canvas->SetLogx(); //set x axis to log scales
    canvas->SetLogy();


    histogram->Draw();


    TLegend *legend = new TLegend(0.7, 0.7, 0.85, 0.85); // Position: x1, y1, x2, y2
//    legend->SetHeader("Legend Title", "C");            // Optional title (centered)
    legend->SetEntrySeparation(1);
//    legend->SetMargin(1);
    legend->AddEntry(histogram, "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram, "Pythia8", "l");         // "l" means line
    legend->AddEntry(histogram, "10^{6} events","");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle("P_{T} [GeV/c]");
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
    std::string path = "../source/";
    std::string filename = "jet tree, cut [D_0 n =1000000, 1+ GeV]";
    DrawHistogramFromTreeD0(path, filename, "T", "D_0_pT", "", true);
    DrawHistogramFromTreeD01(path, filename, "T", "D_0_pT", "D_0_pT>=1", true);
    DrawHistogramFromTreeD05(path, filename, "T", "D_0_pT", "D_0_pT>=5", true);
    {
        DrawHistogramFromTreeL(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}", std::string(), "", true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}", std::string(), "", true);
        DrawHistogramFromTreeL(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}", std::string(), "", true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}", std::string(), "", true);
        DrawHistogramFromTreeL(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}", std::string(), "", true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}", std::string(), "", true);
        DrawHistogramFromTreeL(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}", std::string(), "", true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}", std::string(), "", true);
        DrawHistogramFromTreeL(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}", std::string(), "", true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}", std::string(), "", true);
        DrawHistogramFromTreeL(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}", std::string(), "", true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}", std::string(), "", true);
        DrawHistogramFromTreeL(path, filename, "T", "z_val", 0, 1, "z_{val}", std::string(), "", true);
        DrawHistogramFromTreezLog(path, filename, "T", "z_val", 0, 1, "z_{val}", "",
                                  "", true);

    }

    std::string selectionAng2 = "D_0_pT>=1";
    std::string addName2 = ", D^{0}_{P_{T}}#geq 1";
    {
        DrawHistogramFromTreeL(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}" , addName2,
                                  selectionAng2.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}" , addName2,
                                  selectionAng2.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}" , addName2,
                                  selectionAng2.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}" , addName2,
                                  selectionAng2.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}" , addName2,
                                  selectionAng2.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}" , addName2,
                                  selectionAng2.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "z_val", 0, 1, "z_{val}" , addName2,
                               selectionAng2.c_str(), true);
        DrawHistogramFromTreezLog(path, filename, "T", "z_val", 0, 1, "z_{val}", addName2,
                                  selectionAng2.c_str(), true);

    }
    std::string selectionAng3 = "D_0_pT>=1 && jet_pT >=5";
    std::string addName3 = ", D^{0}_{P_{T}}#geq 1 and P_{T,jet}#geq 5";
    {
        DrawHistogramFromTreeL(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}", addName3,
                                  selectionAng3.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}", addName3,
                                  selectionAng3.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}", addName3,
                                  selectionAng3.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}", addName3,
                                  selectionAng3.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}", addName3,
                                  selectionAng3.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}", addName3,
                                  selectionAng3.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "z_val", 0, 1, "z_{val}", addName3,
                               selectionAng3.c_str(), true);
        DrawHistogramFromTreezLog(path, filename, "T", "z_val", 0, 1, "z_{val}", addName3,
                                  selectionAng3.c_str(), true);

    }

    std::string selectionAng4 = "D_0_pT>=5";
    std::string addName4 = ", D^{0}_{P_{T}}#geq 5";
    {
        DrawHistogramFromTreeL(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l11", 0, 1, "#lambda^{1}_{1}", addName4,
                                  selectionAng4.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l105", 0, 1, "#lambda^{1}_{0.5}", addName4,
                                  selectionAng4.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l115", 0, 1, "#lambda^{1}_{1.5}", addName4,
                                  selectionAng4.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l12", 0, 1, "#lambda^{1}_{2}", addName4,
                                  selectionAng4.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l13", 0, 1, "#lambda^{1}_{3}", addName4,
                                  selectionAng4.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreeLLog(path, filename, "T", "l20", 0, 1, "#lambda^{2}_{0}", addName4,
                                  selectionAng4.c_str(), true);
        DrawHistogramFromTreeL(path, filename, "T", "z_val", 0, 1, "z_{val}", addName4,
                               selectionAng4.c_str(), true);
        DrawHistogramFromTreezLog(path, filename, "T", "z_val", 0, 1, "z_{val}", addName4,
                                  selectionAng4.c_str(), true);

    }

    return 0;
}
