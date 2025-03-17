#include "func.h"


int main() {
//    DrawHistogramFromTreeD0PT("../source/D0.root", "../results/D0", "T");

    bool repetitions = CheckLeafForRepetitions("../../Pythia-project-tree-creator/results/d0.root", "infT", "seed"),
    repetitionsJets = CheckLeafForRepetitions("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "infT", "seed"),
    doDrawD0 = true,
    doDrawJets = true,
    doIntegralNorm = true;
    if(repetitions){
        std::cout << "Repetitions were not found for D0" << std::endl;
    } else {
        std::cout << "Repetitions were found for D0" << std::endl;
    }
    if(repetitionsJets){
        std::cout << "Repetitions were not found for inclusive-jets" << std::endl;
    } else {
        std::cout << "Repetitions were found for inclusive-jets" << std::endl;
    }



    if (doDrawD0 && repetitions) {

        std::string variable_array[2];
        variable_array[0] = "D_0_pT";
        variable_array[1] = "jet_pT";
        std::string selection_array[2];
        selection_array[0] = "";
        selection_array[1] = "";
        std::string variable_names[2];
        variable_names[0] = "p_{T,D^{0}}";
        variable_names[1] = "p_{T,jet}";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root", "../results/D0", "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, false, true, 0, 17,
                                  "p_{T,D^{0}}, p_{T,jet}, no cut", "p_{T}, GeV",
                                  "Number of entries");
        if(doIntegralNorm)DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root", "../results/D0(integral norm)",
                                  "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, true, true, 0, 17,
                                  "p_{T,D^{0}}, p_{T,jet}, no cut", "p_{T}, GeV",
                                  "Number of entries");
        selection_array[0] = "D_0_pT > 1";
        selection_array[1] = "D_0_pT > 1";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root", "../results/D01", "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, false, true, 0, 17,
                                  "p_{T,D^{0}} > 1 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        if(doIntegralNorm)DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root", "../results/D01(integral norm)",
                                  "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, true, true, 0, 17,
                                  "p_{T,D^{0}} > 1 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        selection_array[0] = "D_0_pT > 5";
        selection_array[1] = "D_0_pT > 5";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root", "../results/D05", "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, false, true, 0, 17,
                                  "p_{T,D^{0}} > 5 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        if(doIntegralNorm)DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root", "../results/D05(integral norm)",
                                  "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, true, true, 0, 17,
                                  "p_{T,D^{0}} > 5 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        std::string variable_array_angs[4];
        variable_array_angs[0] = "l11";
        variable_array_angs[1] = "l11";
        variable_array_angs[2] = "l11";
        variable_array_angs[3] = "l11";
        std::string selection_array_angs[4];
        selection_array_angs[0] = "";
        selection_array_angs[1] = "D_0_pT > 1";
        selection_array_angs[2] = "D_0_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "D_0_pT > 5 && jet_pT > 5";
        std::string variable_names_angs[4];
        variable_names_angs[0] = "#lambda^{1}_{1}";
        variable_names_angs[1] = "#lambda^{1}_{1}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{1}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{1}, p_{T,D^{0}} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/l11", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        1,
                                        "#lambda^{1}_{1}", "#lambda^{1}_{1}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/l11(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        1,
                                        "#lambda^{1}_{1}", "#lambda^{1}_{1}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l105";
        variable_array_angs[1] = "l105";
        variable_array_angs[2] = "l105";
        variable_array_angs[3] = "l105";
        variable_names_angs[0] = "#lambda^{1}_{0.5}";
        variable_names_angs[1] = "#lambda^{1}_{0.5}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{0.5}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{0.5}, p_{T,D^{0}} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/l105", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        1,
                                        "#lambda^{1}_{0.5}", "#lambda^{1}_{0.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/l105(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        1,
                                        "#lambda^{1}_{0.5}", "#lambda^{1}_{0.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l115";
        variable_array_angs[1] = "l115";
        variable_array_angs[2] = "l115";
        variable_array_angs[3] = "l115";
        variable_names_angs[0] = "#lambda^{1}_{1.5}";
        variable_names_angs[1] = "#lambda^{1}_{1.5}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{1.5}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{1.5}, p_{T,D^{0}} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/l115", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        1,
                                        "#lambda^{1}_{1.5}", "#lambda^{1}_{1.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/l115(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        1,
                                        "#lambda^{1}_{1.5}", "#lambda^{1}_{1.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l12";
        variable_array_angs[1] = "l12";
        variable_array_angs[2] = "l12";
        variable_array_angs[3] = "l12";
        variable_names_angs[0] = "#lambda^{1}_{2}";
        variable_names_angs[1] = "#lambda^{1}_{2}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{2}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{2}, p_{T,D^{0}} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/l12", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        1.6,
                                        "#lambda^{1}_{2}", "#lambda^{1}_{2}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/l12(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        1.6,
                                        "#lambda^{1}_{2}", "#lambda^{1}_{2}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l13";
        variable_array_angs[1] = "l13";
        variable_array_angs[2] = "l13";
        variable_array_angs[3] = "l13";
        variable_names_angs[0] = "#lambda^{1}_{3}";
        variable_names_angs[1] = "#lambda^{1}_{3}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{3}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{3}, p_{T,D^{0}} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/l13", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        6,
                                        "#lambda^{1}_{3}", "#lambda^{1}_{3}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/l13(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        6,
                                        "#lambda^{1}_{3}", "#lambda^{1}_{3}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l20";
        variable_array_angs[1] = "l20";
        variable_array_angs[2] = "l20";
        variable_array_angs[3] = "l20";
        variable_names_angs[0] = "#lambda^{2}_{0}";
        variable_names_angs[1] = "#lambda^{2}_{0}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "#lambda^{2}_{0}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{2}_{0}, p_{T,D^{0}} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/l20", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        1,
                                        "#lambda^{2}_{0}", "#lambda^{1}_{3}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/l20(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        1,
                                        "#lambda^{2}_{0}", "#lambda^{2}_{0}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "z_val";
        variable_array_angs[1] = "z_val";
        variable_array_angs[2] = "z_val";
        variable_array_angs[3] = "z_val";
        variable_names_angs[0] = "z_{value}";
        variable_names_angs[1] = "z_{value}, p_{T,D^{0}} > 1 GeV";
        variable_names_angs[2] = "z_{value}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "z_{value}, p_{T,D^{0}} > 1 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root", "../results/zval", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, true, 0,
                                        1,
                                        "z_{value}", "z_{value}",
                                        "Number of entries", 0.5, 0.2, 0.84, 0.5);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator/results/d0.root",
                                        "../results/zval(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, true, 0,
                                        1,
                                        "z_{value}", "z_{value}",
                                        "Number of entries", 0.5, 0.2, 0.84, 0.5);

        std::string variable_array_infT[1];
        variable_array_infT[0] = "n";
        std::string selection_array_infT[1];
        selection_array_infT[0] = "";
        std::string variable_names_infT[1];
        variable_names_infT[0] = "Number of events per 100k D^{0} found";

        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root",
                                  "../results/number_of_events_per_100k", "infT",
                                  variable_array_infT, selection_array_infT, variable_names_infT,
                                  1, false, false, false, true, 82000000,
                                  92000000, "Number of events per 100k D^{0} found", " n of events",
                                  "repetitions");

        variable_array[0] = "tcs";
        selection_array[0] = "";
        variable_names[0] = "Total crossection";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root",
                                  "../results/total crossection", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, true, 0,
                                  35, "Total event crossections", "crossection",
                                  " ");
        variable_array[0] = "tcsf";
        variable_names[0] = "Total crossection fraction";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root",
                                  "../results/total crossection fraction", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, true, 0,
                                  0.013, "Total event crossections devided by the event mass", "crossection",
                                  " ");
        variable_array[0] = "cs";
        variable_names[0] = "D^{0} crossection";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root",
                                  "../results/D0 crossection", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, true, 0,
                                  300000, "D0 crossections", "crossection",
                                  " ");
        variable_array[0] = "csf";
        variable_names[0] = "D^{0} crossection fraction";
        DrawHistogramFromTree("../../Pythia-project-tree-creator/results/d0.root",
                                  "../results/D0 crossection devided by the event mass", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, true, 0,
                                  4000, "D^{0} crossections devided by the event mass", "crossection",
                                  " ");
    }

    if (doDrawJets && repetitionsJets){
        std::string variable_array[2];
        variable_array[0] = "lead_pT";
        variable_array[1] = "jet_pT";
        std::string selection_array[2];
        selection_array[0] = "";
        selection_array[1] = "";
        std::string variable_names[2];
        variable_names[0] = "p_{T,leading}";
        variable_names[1] = "p_{T,jet}";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/lead0", "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, false, false, 0, 15,
                                  "p_{T,lead}, p_{T,jet}, no cut", "p_{T}, GeV",
                                  "Number of entries");
        if(doIntegralNorm)DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/lead0(integral norm)",
                                  "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, true, false, 0, 15,
                                  "p_{T,lead}, p_{T,jet}, no cut", "p_{T}, GeV",
                                  "Number of entries");
        selection_array[0] = "lead_pT > 1";
        selection_array[1] = "lead_pT > 1";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/lead01", "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, false, false, 0, 15,
                                  "p_{T,lead} > 1 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        if(doIntegralNorm)DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/lead01(integral norm)",
                                  "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, true, false, 0, 15,
                                  "p_{T,lead} > 1 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        selection_array[0] = "lead_pT > 5";
        selection_array[1] = "lead_pT > 5";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/lead05", "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, false, false, 0, 15,
                                  "p_{T,lead} > 5 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");
        if(doIntegralNorm)DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/lead05(integral norm)",
                                  "angT",
                                  variable_array, selection_array, variable_names, 2, false, true, true, false, 0, 15,
                                  "p_{T,lead} > 5 GeV, p_{T,jet} is any", "p_{T}, GeV",
                                  "Number of entries");

        std::string variable_array_angs[4];
        variable_array_angs[0] = "l11";
        variable_array_angs[1] = "l11";
        variable_array_angs[2] = "l11";
        variable_array_angs[3] = "l11";
        std::string selection_array_angs[4];
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        std::string variable_names_angs[4];
        variable_names_angs[0] = "#lambda^{1}_{1}";
        variable_names_angs[1] = "#lambda^{1}_{1}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{1}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{1}, p_{T,lead} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/leadl11", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        1,
                                        "#lambda^{1}_{1}", "#lambda^{1}_{1}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/leadl11(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        1,
                                        "#lambda^{1}_{1}", "#lambda^{1}_{1}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l105";
        variable_array_angs[1] = "l105";
        variable_array_angs[2] = "l105";
        variable_array_angs[3] = "l105";
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        variable_names_angs[0] = "#lambda^{1}_{0.5}";
        variable_names_angs[1] = "#lambda^{1}_{0.5}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{0.5}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{0.5}, p_{T,lead} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/jetsl105", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        1,
                                        "#lambda^{1}_{0.5}", "#lambda^{1}_{0.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                        "../results/jetsl105(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        1,
                                        "#lambda^{1}_{0.5}", "#lambda^{1}_{0.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l115";
        variable_array_angs[1] = "l115";
        variable_array_angs[2] = "l115";
        variable_array_angs[3] = "l115";
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        variable_names_angs[0] = "#lambda^{1}_{1.5}";
        variable_names_angs[1] = "#lambda^{1}_{1.5}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{1.5}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{1.5}, p_{T,lead} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/jetsl115", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        1,
                                        "#lambda^{1}_{1.5}", "#lambda^{1}_{1.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                        "../results/jetsl115(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        1,
                                        "#lambda^{1}_{1.5}", "#lambda^{1}_{1.5}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l12";
        variable_array_angs[1] = "l12";
        variable_array_angs[2] = "l12";
        variable_array_angs[3] = "l12";
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        variable_names_angs[0] = "#lambda^{1}_{2}";
        variable_names_angs[1] = "#lambda^{1}_{2}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{2}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{2}, p_{T,lead} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/jetsl12", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        1.6,
                                        "#lambda^{1}_{2}", "#lambda^{1}_{2}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                        "../results/jetsl12(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        1.6,
                                        "#lambda^{1}_{2}", "#lambda^{1}_{2}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l13";
        variable_array_angs[1] = "l13";
        variable_array_angs[2] = "l13";
        variable_array_angs[3] = "l13";
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        variable_names_angs[0] = "#lambda^{1}_{3}";
        variable_names_angs[1] = "#lambda^{1}_{3}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "#lambda^{1}_{3}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{1}_{3}, p_{T,lead} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/jetsl13", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        6,
                                        "#lambda^{1}_{3}", "#lambda^{1}_{3}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                        "../results/jetsl13(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        6,
                                        "#lambda^{1}_{3}", "#lambda^{1}_{3}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "l20";
        variable_array_angs[1] = "l20";
        variable_array_angs[2] = "l20";
        variable_array_angs[3] = "l20";
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        variable_names_angs[0] = "#lambda^{2}_{0}";
        variable_names_angs[1] = "#lambda^{2}_{0}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "#lambda^{2}_{0}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "#lambda^{2}_{0}, p_{T,lead} > 5 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/jetsl20", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        1,
                                        "#lambda^{2}_{0}", "#lambda^{1}_{3}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                        "../results/jetsl20(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        1,
                                        "#lambda^{2}_{0}", "#lambda^{2}_{0}",
                                        "Number of entries", 0.54, 0.57, 0.84, 0.87);
        variable_array_angs[0] = "z_val";
        variable_array_angs[1] = "z_val";
        variable_array_angs[2] = "z_val";
        variable_array_angs[3] = "z_val";
        selection_array_angs[0] = "";
        selection_array_angs[1] = "lead_pT > 1";
        selection_array_angs[2] = "lead_pT > 1 && jet_pT > 5";
        selection_array_angs[3] = "lead_pT > 5 && jet_pT > 5";
        variable_names_angs[0] = "z_{value}";
        variable_names_angs[1] = "z_{value}, p_{T,lead} > 1 GeV";
        variable_names_angs[2] = "z_{value}, p_{T,lead} > 1 GeV, p_{T,jet} > 5 GeV";
        variable_names_angs[3] = "z_{value}, p_{T,;lead} > 1 GeV, p_{T,jet} > 5 GeV";
        DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root", "../results/jetsZval", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        false, false, 0,
                                        1,
                                        "z_{value}", "z_{value}",
                                        "Number of entries", 0.5, 0.2, 0.84, 0.5);
        if(doIntegralNorm)DrawHistogramFromTreeSetLeg("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                        "../results/jetsZval(integral norm)", "angT",
                                        variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true,
                                        true, false, 0,
                                        1,
                                        "z_{value}", "z_{value}",
                                        "Number of entries", 0.5, 0.2, 0.84, 0.5);
        std::string variable_array_infT[1];
        variable_array_infT[0] = "n";
        std::string selection_array_infT[1];
        selection_array_infT[0] = "";
        std::string variable_names_infT[1];
        variable_names_infT[0] = "Number of events per 100k jets found";

        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                  "../results/number_of_events_per_100k_jets", "infT",
                                  variable_array_infT, selection_array_infT, variable_names_infT,
                                  1, false, false, false, false, 14300,
                                  14500, "Number of events per 100k jets found", " n of events",
                                  "repetitions");

        variable_array[0] = "tcs";
        selection_array[0] = "";
        variable_names[0] = "Total crossection";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                  "../results/jets total crossection", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, false, 0,
                                  60, "Total event crossections", "crossection",
                                  " ");
        variable_array[0] = "tcsf";
        variable_names[0] = "Total crossection fraction";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                  "../results/total crossection fraction", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, false, 0,
                                  30, "Total event crossections devided by the event mass", "crossection",
                                  " ");
        variable_array[0] = "cs";
        variable_names[0] = "leading jet particle crossection";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                  "../results/leading jet particle crossection", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, false, 0,
                                  470000, "leading jet parrticle crossections", "crossection",
                                  " ");
        variable_array[0] = "csf";
        variable_names[0] = "leading jet particle crossection fraction";
        DrawHistogramFromTree("../../Pythia-project-tree-creator-inclusive-jets-/results/jets.root",
                                  "../results/leading jet particle crossection devided by the event mass", "angT",
                                  variable_array, selection_array, variable_names,
                                  1, false, true, false, false, 0,
                                  450000, "leading jet parrticle crossections devided by the event mass", "crossection",
                                  " ");
    }
    return 0;
}
