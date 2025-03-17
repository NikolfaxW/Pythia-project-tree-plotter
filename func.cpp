//
// Created by nikol on 11/25/2024.
//

#include "func.h"

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
#include <vector>

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

void DrawHistogramFromTreeD0PT(std::string path, std::string outName, std::string treename) {
    gStyle->SetOptStat(0);

    std::string variable = "D_0_pT";
    std::string selection = "";

    std::string variable1 = "jet_pT";
    std::string selection1 = "";

    bool doRootSave = false;

    TFile *file = TFile::Open(path.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename.c_str());
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }

    Float_t left_border = 0;
    Float_t right_border = 17;


    TH1F *histogram = new TH1F("histogram", "p_{T,D^{0}}, p_{T,jet}, no cut", 100, left_border, right_border);
    TH1F *histogram1 = new TH1F("histogram1", "p_{T,D^{0}}, p_{T,jet}, no cut", 100, left_border, right_border);



    // create histogram with filname as title, nbinsx bins, min and max values of variable - can be changed
    tree->Project("histogram", variable.c_str(), selection.c_str());
    tree->Project("histogram1", variable1.c_str(), selection.c_str());

    // 4250 x 3300 pixels for full page histograms?
    // 2075 x 1650 pixels for half page histograms?
    // 1037 x 825 pixels for quarter page histograms?
    // 800 x 600 is basic size

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

//    canvas->SetLogx(); //set x axis to log scales
    canvas->SetLogy();

//    histogram->Scale(1.0 / histogram->Integral());
//    histogram1->Scale(1.0 / histogram1->Integral());
    std::cout << histogram->Integral() << " " << histogram1->Integral() << std::endl;

    histogram1->SetLineColor(kRed);


    histogram->Draw("same");
    histogram1->Draw("same");


    TLegend *legend = new TLegend(0.7, 0.6, 0.85, 0.85); // Position: x1, y1, x2, y2
//    legend->SetHeader("Legend Title", "C");            // Optional title (centered)
    legend->SetEntrySeparation(1);
//    legend->SetMargin(1);
    legend->AddEntry(histogram, "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram, "Pythia8", "");         // "l" means line
    legend->AddEntry(histogram, "8*10^{5}D^{0} found", "");
    legend->AddEntry(histogram, "p_{T,D^{0}}", "l");
    legend->AddEntry(histogram1, "p_{T,jet}", "l");
    // Customize legend appearance (optional)

    legend->SetTextSize(0.03);   // Text size
    legend->SetFillStyle(0);  // Transparent background
    legend->SetFillColor(0);  // No fill color
    legend->SetLineColor(0);  // Optional: Remove border lines
    legend->SetBorderSize(0); // Optional: Remove border altogether

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = outName + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = outName + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete histogram1;
    delete canvas;
    file->Close();
}

bool CheckLeafForRepetitions(std::string path_to_tree, std::string tree_name,
                             std::string variable_name){
    TFile *file = TFile::Open(path_to_tree.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path_to_tree << std::endl;
        delete file;
        return false;
    }
    TTree *tree = (TTree *) file->Get(tree_name.c_str());
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << tree_name << " from file" << std::endl;
        file->Close();
        return false;
    }
    std::vector<Int_t> values;

    Int_t value;
    tree->SetBranchAddress(variable_name.c_str(), &value);  // Replace with your branch name
    long long int nEntries = tree->GetEntries();
    for (long long int i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        auto temp = std::find(values.begin(), values.end(),value);
        if(temp != values.end()){
            std::cerr << "Error: Found repetition of value " << value << " in leaf " << variable_name << std::endl;
            file->Close();
            return false;
        }
        values.push_back(value);
    }
    file->Close();
    return true;
}

void DrawHistogramFromTree(std::string path_to_tree, std::string output_file_name, std::string tree_name,
                           std::string *variable_array, std::string *selection_array, std::string *variable_names,
                           int size, bool doRootSave, bool do_setLogY, bool do_integral_norm, bool d0, Double_t left_border,
                           Double_t right_border, std::string title, std::string x_axis_name,
                           std::string y_axis_name) {
    TFile *file = TFile::Open(path_to_tree.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path_to_tree << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(tree_name.c_str());
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << tree_name << " from file" << std::endl;
        file->Close();
        return;
    }
    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

    TH1F **histogram = new TH1F*[size];
    std::string temp;
    for(int i = 0; i < size; ++i){
        temp = "histogram" + std::to_string(i + 1);
        histogram[i] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    }
    histogram[0]->SetStats(0);
    for(int i = 0; i < size; ++i)
        tree->Project(histogram[i]->GetName(), variable_array[i].c_str(), selection_array[i].c_str());
    if(do_setLogY){
        canvas->SetLogy();
    }

    for(int i = 0; i < size; ++i){
        histogram[i]->SetLineColor(i + 1);
    }
    if(do_integral_norm){
        for(int i = 0; i < size; ++i){
            histogram[i]->Scale(1.0 / histogram[i]->Integral());
        }
    }

    for(int i = 0; i < size; ++i){
        histogram[i]->GetXaxis()->SetTitle(x_axis_name.c_str());
        histogram[i]->GetYaxis()->SetTitle(y_axis_name.c_str());
        histogram[i]->Draw("same");
    }
    TLegend *legend = new TLegend(0.7, 0.6, 0.85, 0.85); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(histogram[0], "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram[0], "Pythia8", "");         // "l" means line
    if(d0) legend->AddEntry(histogram[0], "1.2*10^{6}D^{0} found", "");
    else legend->AddEntry(histogram[0], "1.2*10^{6}jets found", "");
    for(int i = 0; i < size; ++i){
        legend->AddEntry(histogram[i], variable_names[i].c_str(), "l");
    }

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    if(doRootSave){
        temp = output_file_name + ".root";
        canvas->SaveAs(temp.c_str());
    }
    temp = output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());


    for(int i = 0; i < size; ++i){
        delete histogram[i];
    }
    delete [] histogram;
    delete canvas;
    file->Close();

}

void DrawHistogramFromTreeSetLeg(std::string path_to_tree, std::string output_file_name, std::string tree_name,
                                 std::string *variable_array, std::string *selection_array,
                                 std::string *variable_names, int size, bool doRootSave, bool do_setLogY,
                                 bool do_integral_norm, bool d0, Double_t left_border, Double_t right_border,
                                 std::string title, std::string x_axis_name, std::string y_axis_name, double x1,
                                 double y1, double x2, double y2) {
    TFile *file = TFile::Open(path_to_tree.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path_to_tree << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(tree_name.c_str());
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << tree_name << " from file" << std::endl;
        file->Close();
        return;
    }
    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

    TH1F **histogram = new TH1F*[size];
    std::string temp;
    for(int i = 0; i < size; ++i){
        temp = "histogram" + std::to_string(i + 1);
        histogram[i] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    }
    histogram[0]->SetStats(0);
    for(int i = 0; i < size; ++i)
        tree->Project(histogram[i]->GetName(), variable_array[i].c_str(), selection_array[i].c_str());
    if(do_setLogY){
        canvas->SetLogy();
    }
    for(int i = 0; i < size; ++i){
        histogram[i]->SetLineColor(i + 1);
    }
    if(do_integral_norm){
        for(int i = 0; i < size; ++i){
            histogram[i]->Scale(1.0 / histogram[i]->Integral());
        }
    }
    for(int i = 0; i < size; ++i){
        histogram[i]->GetXaxis()->SetTitle(x_axis_name.c_str());
        histogram[i]->GetYaxis()->SetTitle(y_axis_name.c_str());
        histogram[i]->Draw("same");
    }
    TLegend *legend = new TLegend(x1, y1, x2, y2); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(histogram[0], "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram[0], "Pythia8", "");         // "l" means line
    if(d0) legend->AddEntry(histogram[0], "1.2*10^{6}D^{0} found", "");
    else legend->AddEntry(histogram[0], "1.2*10^{6}jets found", "");
    for(int i = 0; i < size; ++i){
        legend->AddEntry(histogram[i], variable_names[i].c_str(), "l");
    }

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    if(doRootSave){
        temp = output_file_name + ".root";
        canvas->SaveAs(temp.c_str());
    }
    temp = output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());


    for(int i = 0; i < size; ++i){
        delete histogram[i];
    }
    delete [] histogram;
    delete canvas;
    file->Close();
}
