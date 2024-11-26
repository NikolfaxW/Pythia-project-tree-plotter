//
// Created by nikol on 11/25/2024.
//

#ifndef PYTHIA_PROJECT_TREE_PLOTTER_FUNC_H
#define PYTHIA_PROJECT_TREE_PLOTTER_FUNC_H

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

//! USE LOG SCALE FOR Y AXIS(JUST FOR PT destribution)

void DrawHistogramFromTreeD01(const std::string path, const std::string filename, const char *treename, const char *variable, const char *selection, const bool doRootSave);
void DrawHistogramFromTreeD05(const std::string path, const std::string filename, const char *treename, const char *variable, const char *selection, const bool doRootSave);
void DrawHistogramFromTreeD0(const std::string path, const std::string filename, const char *treename, const char *variable, const char *selection, const bool doRootSave);
void
DrawHistogramFromTreeL(const std::string path, const std::string filename, const char *treename, const char *variable,
                       Float_t left_border, Float_t right_border, std::string name, std::string addName,
                       const char *selection, const bool doRootSave);
void DrawHistogramFromTreeLLog(const std::string path, const std::string filename, const char *treename,
                               const char *variable, Float_t left_border, Float_t right_border, std::string name,
                               std::string addName, const char *selection, const bool doRootSave);
void DrawHistogramFromTreez(const std::string path, const std::string filename, const char *treename, const char *variable, Float_t left_border, Float_t right_border, std::string name,
                            const char *selection, const bool doRootSave);
void DrawHistogramFromTreezLog(const std::string path, const std::string filename, const char *treename,
                               const char *variable, Float_t left_border, Float_t right_border, std::string name,
                               std::string addName, const char *selection, const bool doRootSave);
#endif //PYTHIA_PROJECT_TREE_PLOTTER_FUNC_H
