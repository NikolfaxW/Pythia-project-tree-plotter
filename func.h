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

void PrintTreeNames(const char* filename);
void DrawHistogramFromTreeD0PT(std::string path, std::string outName, std::string treename); //reference function

void DrawHistogramFromTree(std::string path_to_tree, std::string output_file_name, std::string tree_name,
                           std::string *variable_array, std::string *selection_array, std::string *variable_names,
                           int size, bool doRootSave, bool do_setLogY, bool do_integral_norm, bool d0, Double_t left_border,
                           Double_t right_border, std::string title, std::string x_axis_name,
                           std::string y_axis_name);
void DrawHistogramFromTreeSetLeg(std::string path_to_tree, std::string output_file_name, std::string tree_name,
                                 std::string *variable_array, std::string *selection_array,
                                 std::string *variable_names, int size, bool doRootSave, bool do_setLogY,
                                 bool do_integral_norm, bool d0, Double_t left_border, Double_t right_border,
                                 std::string title, std::string x_axis_name, std::string y_axis_name, double x1,
                                 double y1, double x2, double y2);
bool CheckLeafForRepetitions(std::string path_to_tree, std::string tree_name,
                             std::string variable_name);

void DrawHistogramFromTreeNoCutsTwoInputs(std::string path_to_tree_first, std::string path_to_tree_second, std::string output_file_name, std::string tree_name1,std::string tree_name2,
                                          std::string *variable_array, std::string *selection_array, std::string *variable_names,
                                          int size, bool doRootSave, bool do_setLogY, bool do_integral_norm, bool d0, Double_t left_border,
                                          Double_t right_border, std::string title, std::string x_axis_name,
                                          std::string y_axis_name);

#endif //PYTHIA_PROJECT_TREE_PLOTTER_FUNC_H
