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

void PrintTreeNames(const char *filename) {
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    TIter next(file->GetListOfKeys());
    TKey *key;
    while ((key = (TKey *) next())) {
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
                             std::string variable_name) {
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
        auto temp = std::find(values.begin(), values.end(), value);
        if (temp != values.end()) {
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
                           int size, bool doRootSave, bool do_setLogY, bool do_integral_norm, bool d0,
                           Double_t left_border,
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

    TH1F **histogram = new TH1F *[size];
    std::string temp;
    for (int i = 0; i < size; ++i) {
        temp = "histogram" + std::to_string(i + 1);
        histogram[i] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    }
    histogram[0]->SetStats(0);
    for (int i = 0; i < size; ++i)
        tree->Project(histogram[i]->GetName(), variable_array[i].c_str(), selection_array[i].c_str());
    if (do_setLogY) {
        canvas->SetLogy();
    }

    for (int i = 0; i < size; ++i) {
        histogram[i]->SetLineColor(i + 1);
    }
    if (do_integral_norm) {
        for (int i = 0; i < size; ++i) {
            histogram[i]->Scale(1.0 / histogram[i]->Integral());
        }
    }

    for (int i = 0; i < size; ++i) {
        histogram[i]->GetXaxis()->SetTitle(x_axis_name.c_str());
        histogram[i]->GetYaxis()->SetTitle(y_axis_name.c_str());
        histogram[i]->Draw("same");
    }
    TLegend *legend = new TLegend(0.7, 0.6, 0.85, 0.85); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(histogram[0], "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram[0], "Pythia8", "");         // "l" means line
    if (d0) legend->AddEntry(histogram[0], "1.2*10^{6}D^{0} found", "");
    else legend->AddEntry(histogram[0], "1.2*10^{6}jets found", "");
    for (int i = 0; i < size; ++i) {
        legend->AddEntry(histogram[i], variable_names[i].c_str(), "l");
    }

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    if (doRootSave) {
        temp = output_file_name + ".root";
        canvas->SaveAs(temp.c_str());
    }
    temp = output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());


    for (int i = 0; i < size; ++i) {
        delete histogram[i];
    }
    delete[] histogram;
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

    TH1F **histogram = new TH1F *[size];
    std::string temp;
    for (int i = 0; i < size; ++i) {
        temp = "histogram" + std::to_string(i + 1);
        histogram[i] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    }
    histogram[0]->SetStats(0);
    for (int i = 0; i < size; ++i)
        tree->Project(histogram[i]->GetName(), variable_array[i].c_str(), selection_array[i].c_str());
    if (do_setLogY) {
        canvas->SetLogy();
    }
    for (int i = 0; i < size; ++i) {
        histogram[i]->SetLineColor(i + 1);
    }
    if (do_integral_norm) {
        for (int i = 0; i < size; ++i) {
            histogram[i]->Scale(1.0 / histogram[i]->Integral());
        }
    }
    for (int i = 0; i < size; ++i) {
        histogram[i]->GetXaxis()->SetTitle(x_axis_name.c_str());
        histogram[i]->GetYaxis()->SetTitle(y_axis_name.c_str());
        histogram[i]->Draw("same");
    }
    TLegend *legend = new TLegend(x1, y1, x2, y2); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(histogram[0], "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram[0], "Pythia8", "");         // "l" means line
    if (d0) legend->AddEntry(histogram[0], "1.2*10^{6}D^{0} found", "");
    else legend->AddEntry(histogram[0], "1.2*10^{6}jets found", "");
    for (int i = 0; i < size; ++i) {
        legend->AddEntry(histogram[i], variable_names[i].c_str(), "l");
    }

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    if (doRootSave) {
        temp = output_file_name + ".root";
        canvas->SaveAs(temp.c_str());
    }
    temp = output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());


    for (int i = 0; i < size; ++i) {
        delete histogram[i];
    }
    delete[] histogram;
    delete canvas;
    file->Close();
}

void DrawHistogramFromTreeNoCutsTwoInputs(std::string path_to_tree_first, std::string path_to_tree_second,
                                          std::string output_file_name, std::string tree_name1, std::string tree_name2,
                                          std::string *variable_array, std::string *selection_array,
                                          std::string *variable_names,
                                          int size, bool doRootSave, bool do_setLogY, bool do_integral_norm, bool d0,
                                          Double_t left_border,
                                          Double_t right_border, std::string title, std::string x_axis_name,
                                          std::string y_axis_name) {
    TFile *file1 = TFile::Open(path_to_tree_first.c_str());
    TFile *file2 = TFile::Open(path_to_tree_second.c_str());
    if (!file1 || file1->IsZombie()) {
        std::cerr << "Error: Unable to open file1 " << path_to_tree_first << std::endl;
        return;
    }
    if (!file2 || file2->IsZombie()) {
        std::cerr << "Error: Unable to open file2 " << path_to_tree_second << std::endl;
        return;
    }
    TTree *tree1 = (TTree *) file1->Get(tree_name1.c_str());
    TTree *tree2 = (TTree *) file2->Get(tree_name2.c_str());

    if (!tree1) {
        std::cerr << "Error: Unable to retrieve tree1 " << tree_name1 << " from file1" << std::endl;
        file1->Close();
        return;
    }

    if (!tree2) {
        std::cerr << "Error: Unable to retrieve tree2 " << tree_name2 << " from file2" << std::endl;
        file1->Close();
        return;
    }


    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels
    TH1F **histogram = new TH1F *[2];
    std::string temp;
    temp = "histogram00";
    histogram[0] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    temp = "histogram11";
    histogram[1] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    histogram[0]->SetStats(0);
    tree1->Project(histogram[0]->GetName(), variable_array[0].c_str(), selection_array[0].c_str());
    tree2->Project(histogram[1]->GetName(), variable_array[1].c_str(), selection_array[1].c_str());

    if (do_setLogY) {
        canvas->SetLogy();
    }
    histogram[0]->SetLineColor(0);
    histogram[1]->SetLineColor(1);


    if (do_integral_norm) {
        histogram[0]->Scale(1.0 / histogram[0]->Integral());
        histogram[1]->Scale(1.0 / histogram[1]->Integral());
    }

    histogram[0]->GetXaxis()->SetTitle(x_axis_name.c_str());
    histogram[0]->GetYaxis()->SetTitle(y_axis_name.c_str());
    histogram[0]->Draw("same");


    histogram[1]->GetXaxis()->SetTitle(x_axis_name.c_str());
    histogram[1]->GetYaxis()->SetTitle(y_axis_name.c_str());
    histogram[1]->Draw("same");

    TLegend *legend = new TLegend(0.7, 0.6, 0.85, 0.85); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(histogram[0], "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram[0], "Pythia8", "");         // "l" means line
    legend->AddEntry(histogram[0], "1.2*10^{6}D^{0} jets found", "");
    legend->AddEntry(histogram[0], "1.2*10^{6}jets found", "");
    legend->AddEntry(histogram[0], variable_names[0].c_str(), "l");
    legend->AddEntry(histogram[1], variable_names[1].c_str(), "l");

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    if (doRootSave) {
        temp = output_file_name + ".root";
        canvas->SaveAs(temp.c_str());
    }

    temp = output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());

    delete histogram[0];
    delete histogram[1];
    delete[] histogram;
    delete canvas;
    file1->Close();
    file2->Close();
}

void
DrawHistogramsFromTreeNoCutsTwoInputs(std::string path_to_tree_d0, std::string path_to_tree_jets, std::string title,
                                      Double_t left_border, Double_t right_border, std::string variable,
                                      std::string output_file_name, bool doRootSave, bool do_setLogY,
                                      bool do_integral_norm, std::string x_axis_name, std::string y_axis_name) {
    TFile *file_d0 = TFile::Open(path_to_tree_d0.c_str()),
            *file_jets = TFile::Open(path_to_tree_jets.c_str());
    if (!file_d0 || file_d0->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path_to_tree_d0 << std::endl;
        return;
    }
    if (!file_jets || file_jets->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path_to_tree_jets << std::endl;
        return;
    }

    TTree *tree_d0 = (TTree *) file_d0->Get("angT"),
            *tree_jets = (TTree *) file_jets->Get("angT");
    if (!tree_d0) {
        std::cerr << "Error: Unable to retrieve tree " << "d0 tree" << " from file" << std::endl;
        file_d0->Close();
        return;
    }
    if (!tree_jets) {
        std::cerr << "Error: Unable to retrieve tree " << "jets tree" << " from file" << std::endl;
        file_jets->Close();
        return;
    }

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels
    std::string temp = "histogram_d0";
    TH1F histogram_d0(temp.c_str(), title.c_str(), 102, left_border, right_border);
    temp = "histogram_jets";
    TH1F histogram_jets(temp.c_str(), title.c_str(), 102, left_border, right_border);

    histogram_d0.SetStats(0);
    histogram_jets.SetStats(0);

    tree_d0->Project(histogram_d0.GetName(), variable.c_str(), "D_0_pT > 5");
    tree_jets->Project(histogram_jets.GetName(), variable.c_str(), "");

    if (do_setLogY) {
        canvas->SetLogy();
    }

    histogram_d0.SetLineColor(kBlue);
    histogram_jets.SetLineColor(kRed);

    if (do_integral_norm) {
        histogram_d0.Scale(1.0 / histogram_d0.Integral());
        histogram_jets.Scale(1.0 / histogram_jets.Integral());

    }

    histogram_d0.GetXaxis()->SetTitle(x_axis_name.c_str());
    histogram_d0.GetYaxis()->SetTitle(y_axis_name.c_str());
    histogram_d0.Draw("same");

    histogram_jets.GetXaxis()->SetTitle(x_axis_name.c_str());
    histogram_jets.GetYaxis()->SetTitle(y_axis_name.c_str());
    histogram_jets.Draw("same");

    TLegend *legend = new TLegend(0.7, 0.6, 0.85, 0.85); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(&histogram_d0, "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(&histogram_d0, "Pythia8", "");         // "l" means line
    legend->AddEntry(&histogram_d0, "1.2*10^{6}D^{0} found", "");
    legend->AddEntry(&histogram_d0, "1.2*10^{6}jets found", "");
    temp = x_axis_name + " D^{0} jets";
    legend->AddEntry(&histogram_d0, temp.c_str(), "l");
    temp = x_axis_name + " jets";
    legend->AddEntry(&histogram_jets, temp.c_str(), "l");

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    if (doRootSave) {
        temp = output_file_name + ".root";
        canvas->SaveAs(temp.c_str());
    }
    temp = output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());

    delete canvas;
    file_d0->Close();
    file_jets->Close();
    delete file_d0;
    delete file_jets;
}

void plotAngularityWithCut(std::string path_to_tree_d0, std::string title, Double_t left_border, Double_t right_border, std::string cut, std::string output_file_name){
    TFile *file_d0 = TFile::Open(path_to_tree_d0.c_str());
    if (!file_d0 || file_d0->IsZombie()) {
        std::cerr << "Error: Unable to open file " << path_to_tree_d0 << std::endl;
        return;
    }
    TTree *tree_d0 = (TTree *) file_d0->Get("angT");
    if (!tree_d0) {
        std::cerr << "Error: Unable to retrieve tree " << "d0 tree" << " from file" << std::endl;
        file_d0->Close();
        return;
    }
    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels
    canvas->SetTitle("title.c_str()");
    std::string temp;
    TH1F ** histogram = new TH1F*[6];
    for(int i = 0; i < 6; ++i){
        temp =  "histogram_d0 " + std::to_string(i);
        histogram[i] = new TH1F(temp.c_str(), title.c_str(), 102, left_border, right_border);
    }
    for(int i = 0; i < 6; ++i)
        histogram[i]->SetStats(0);


    tree_d0->Project(histogram[0]->GetName(), "l105", cut.c_str());
    tree_d0->Project(histogram[1]->GetName(), "l11", cut.c_str());
    tree_d0->Project(histogram[2]->GetName(), "l115", cut.c_str());
    tree_d0->Project(histogram[3]->GetName(), "l12", cut.c_str());
    tree_d0->Project(histogram[4]->GetName(), "l13", cut.c_str());
    tree_d0->Project(histogram[5]->GetName(), "l20", cut.c_str());


    canvas->SetLogy();
    temp = "Number of entries";
    for(int i = 0; i < 6; ++i){
        histogram[i]->SetLineColor(i+1);
        histogram[i]->Scale(1.0 / histogram[i]->Integral());
        histogram[i]->GetYaxis()->SetTitle(temp.c_str());
        histogram[i]->Draw("same");
    }

    TLegend *legend = new TLegend(0.7, 0.40, 0.85, 0.85); // Position: x1, y1, x2, y2
    legend->SetEntrySeparation(1);
    legend->AddEntry(histogram[0], "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram[0], "Pythia8", "");         // "l" means line
    legend->AddEntry(histogram[0], "1.2*10^{6}D^{0} found", "");
    legend->AddEntry(histogram[0], "1.2*10^{6}jets found", "");
    temp =  "#lambda^{1}_{0.5}";
    legend->AddEntry(histogram[0], temp.c_str(), "l");
    temp =  "#lambda^{1}_{1}";
    legend->AddEntry(histogram[1], temp.c_str(), "l");
    temp =  "#lambda^{1}_{1.5}";
    legend->AddEntry(histogram[2], temp.c_str(), "l");
    temp =  "#lambda^{1}_{2}";
    legend->AddEntry(histogram[3], temp.c_str(), "l");
    temp =  "#lambda^{1}_{3}";
    legend->AddEntry(histogram[4], temp.c_str(), "l");
    temp =  "#lambda^{2}_{0}";
    legend->AddEntry(histogram[5], temp.c_str(), "l");

    legend->SetTextSize(0.03);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetBorderSize(0);

    legend->Draw();

    temp = "../results/" + output_file_name + ".pdf";
    canvas->SaveAs(temp.c_str());

    delete canvas;
    file_d0->Close();
    delete file_d0;
    delete [] histogram;

}