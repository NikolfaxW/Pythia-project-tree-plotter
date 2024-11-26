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


void
DrawHistogramFromTreeD01(const std::string path, const std::string filename, const char *treename, const char *variable,
                         const char *selection = "", const bool doRootSave = false) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append(" ");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }

    Float_t left_border = 1;
    Float_t right_border = tree->GetMaximum(variable);


    TH1F *histogram = new TH1F("histogram", "p_{T,D^{0}} >= 1 GeV/c", 100, left_border, right_border);
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
    legend->AddEntry(histogram, "10^{6} events", "");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}

void
DrawHistogramFromTreeD05(const std::string path, const std::string filename, const char *treename, const char *variable,
                         const char *selection = "", const bool doRootSave = false) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append(" ");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }

    Float_t left_border = 5;
    Float_t right_border = tree->GetMaximum(variable);


    TH1F *histogram = new TH1F("histogram", "p_{T,D^{0}} >= 5 GeV/c", 100, left_border, right_border);
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
    legend->AddEntry(histogram, "10^{6} events", "");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}

void
DrawHistogramFromTreeD0(const std::string path, const std::string filename, const char *treename, const char *variable,
                        const char *selection = "", const bool doRootSave = false) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append(" ");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }

    Float_t left_border = tree->GetMinimum(variable);
    Float_t right_border = tree->GetMaximum(variable);


    TH1F *histogram = new TH1F("histogram", "p_{T,D^{0}}", 100, left_border, right_border);
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
    legend->AddEntry(histogram, "10^{6} events", "");
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
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}

void
DrawHistogramFromTreeL(const std::string path, const std::string filename, const char *treename, const char *variable,
                       Float_t left_border, Float_t right_border, std::string name, std::string addName,
                       const char *selection, const bool doRootSave) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append(" ");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }


    TH1F *histogram = new TH1F("histogram", (name+addName).c_str(), 100, left_border, right_border);
    // create histogram with filname as title, nbinsx bins, min and max values of variable - can be changed
    tree->Project("histogram", variable, selection);

    // 4250 x 3300 pixels for full page histograms?
    // 2075 x 1650 pixels for half page histograms?
    // 1037 x 825 pixels for quarter page histograms?
    // 800 x 600 is basic size

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

//    canvas->SetLogx(); //set x axis to log scales
//    canvas->SetLogy();


    histogram->Draw();


    TLegend *legend = new TLegend(0.7, 0.7, 0.85, 0.85); // Position: x1, y1, x2, y2
//    legend->SetHeader("Legend Title", "C");            // Optional title (centered)
    legend->SetEntrySeparation(1);
//    legend->SetMargin(1);
    legend->AddEntry(histogram, "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram, "Pythia8", "l");         // "l" means line
    legend->AddEntry(histogram, "10^{6} events", "");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
//    legend->AddEntry(histogram, selection, "");
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle(name.c_str());
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}

void DrawHistogramFromTreeLLog(const std::string path, const std::string filename, const char *treename,
                               const char *variable, Float_t left_border, Float_t right_border, std::string name,
                               std::string addName, const char *selection, const bool doRootSave) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append("(Log)");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }


    TH1F *histogram = new TH1F("histogram", (name + addName).c_str(), 100, left_border, right_border);
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
    legend->AddEntry(histogram, "10^{6} events", "");
//    legend->AddEntry(histogram, selection, "");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle(name.c_str());
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}

void
DrawHistogramFromTreez(const std::string path, const std::string filename, const char *treename, const char *variable,
                       Float_t left_border, Float_t right_border, std::string name,
                       const char *selection = "", const bool doRootSave = false) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append(" ");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }


    TH1F *histogram = new TH1F("histogram", name.c_str(), 100, left_border, right_border);
    // create histogram with filname as title, nbinsx bins, min and max values of variable - can be changed
    tree->Project("histogram", variable, selection);

    // 4250 x 3300 pixels for full page histograms?
    // 2075 x 1650 pixels for half page histograms?
    // 1037 x 825 pixels for quarter page histograms?
    // 800 x 600 is basic size

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600); //width = 800 height 600 pixels

//    canvas->SetLogx(); //set x axis to log scales
//    canvas->SetLogy();


    histogram->Draw();


    TLegend *legend = new TLegend(0.7, 0.12, 0.85, 0.37); // Position: x1, y1, x2, y2
//    legend->SetHeader("Legend Title", "C");            // Optional title (centered)
    legend->SetEntrySeparation(1);
//    legend->SetMargin(1);
    legend->AddEntry(histogram, "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram, "Pythia8", "l");         // "l" means line
    legend->AddEntry(histogram, "10^{6} events", "");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
//    legend->AddEntry(histogram, selection, "");
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle(name.c_str());
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}

void DrawHistogramFromTreezLog(const std::string path, const std::string filename, const char *treename,
                               const char *variable, Float_t left_border, Float_t right_border, std::string name,
                               std::string addName, const char *selection, const bool doRootSave) {
    std::string fullpath = path + filename + ".root", save_path = "../results/";
    gStyle->SetOptStat(0);
    save_path.append(variable);
    save_path.append("(Log)");
//    save_path.append(filename);
    save_path.append(selection);
//    save_path.append(".pdf");
    TFile *file = TFile::Open(fullpath.c_str());
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    TTree *tree = (TTree *) file->Get(treename);
    if (!tree) {
        std::cerr << "Error: Unable to retrieve tree " << treename << " from file" << std::endl;
        file->Close();
        return;
    }


    TH1F *histogram = new TH1F("histogram", (name + addName).c_str(), 100, left_border, right_border);
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


    TLegend *legend = new TLegend(0.7, 0.12, 0.85, 0.37); // Position: x1, y1, x2, y2
//    legend->SetHeader("Legend Title", "C");            // Optional title (centered)
    legend->SetEntrySeparation(1);
//    legend->SetMargin(1);
    legend->AddEntry(histogram, "#sqrt{S_{NN}} = 200 GeV", "");
    legend->AddEntry(histogram, "Pythia8", "l");         // "l" means line
    legend->AddEntry(histogram, "10^{6} events", "");
//    legend->AddEntry(histogram, selection, "");
    // Customize legend appearance (optional)
    legend->SetBorderSize(0);    // Border thickness (0 for no border)
    legend->SetTextSize(0.03);   // Text size
    legend->SetFillColor(kWhite); // Background color (kWhite = transparent)

    // Draw the legend
    legend->Draw();


    histogram->GetXaxis()->SetTitle(name.c_str());
    histogram->GetYaxis()->SetTitle("N, number of jets");

    std::string temp = save_path + ".pdf";
    canvas->SaveAs(temp.c_str());
    if (doRootSave) {
        temp = save_path + ".root";
        canvas->SaveAs(temp.c_str());
    }


    delete histogram;
    delete canvas;
    file->Close();
}