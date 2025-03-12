#include "func.h"






int main() {
//    DrawHistogramFromTreeD0PT("../source/D0.root", "../results/D0", "T");
    std::string variable_array[2];
    variable_array[0] = "D_0_pT";
    variable_array[1] = "jet_pT";
    std::string selection_array[2];
    selection_array[0] = "";
    selection_array[1] = "";
    std::string variable_names[2];
    variable_names[0] = "p_{T,D^{0}}";
    variable_names[1] = "p_{T,jet}";
    DrawHistogramFromTreeTest("../source/D0.root", "../results/D0", "angT",
                              variable_array, selection_array, variable_names, 2, false, true, false, 0, 17,
                              "p_{T,D^{0}}, p_{T,jet}, no cut", "p_{T}, GeV",
                              "Number of entries");
    DrawHistogramFromTreeTest("../source/D0.root", "../results/D0(integral norm)", "angT",
                              variable_array, selection_array, variable_names, 2, false, true, true, 0, 17,
                              "p_{T,D^{0}}, p_{T,jet}, no cut", "p_{T}, GeV",
                              "Number of entries");
    selection_array[0] = "D_0_pT > 1";
    selection_array[1] = "D_0_pT > 1";
    DrawHistogramFromTreeTest("../source/D0.root", "../results/D01", "angT",
                              variable_array, selection_array, variable_names, 2, false, true, false, 0, 17,
                              "p_{T,D^{0}} > 1 GeV, p_{T,jet} is any", "p_{T}, GeV",
                              "Number of entries");
    DrawHistogramFromTreeTest("../source/D0.root", "../results/D01(integral norm)", "angT",
                              variable_array, selection_array, variable_names, 2, false, true, true, 0, 17,
                              "p_{T,D^{0}} > 1 GeV, p_{T,jet} is any", "p_{T}, GeV",
                              "Number of entries");
    selection_array[0] = "D_0_pT > 5";
    selection_array[1] = "D_0_pT > 5";
    DrawHistogramFromTreeTest("../source/D0.root", "../results/D05", "angT",
                              variable_array, selection_array, variable_names, 2, false, true, false, 0, 17,
                              "p_{T,D^{0}} > 5 GeV, p_{T,jet} is any", "p_{T}, GeV",
                              "Number of entries");
    DrawHistogramFromTreeTest("../source/D0.root", "../results/D05(integral norm)", "angT",
                              variable_array, selection_array, variable_names, 2, false, true, true, 0, 17,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l11", "angT",
                              variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                              1,
                              "#lambda^{1}_{1}", "#lambda^{1}_{1}",
                              "Number of entries", 0.54, 0.57, 0.84, 0.87);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l11(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l105", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                                    1,
                                    "#lambda^{1}_{0.5}", "#lambda^{1}_{0.5}",
                                    "Number of entries", 0.54, 0.57, 0.84, 0.87);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l105(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l115", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                                    1,
                                    "#lambda^{1}_{1.5}", "#lambda^{1}_{1.5}",
                                    "Number of entries", 0.54, 0.57, 0.84, 0.87);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l115(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l12", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                                    1.6,
                                    "#lambda^{1}_{2}", "#lambda^{1}_{2}",
                                    "Number of entries", 0.54, 0.57, 0.84, 0.87);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l12(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l13", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                                    6,
                                    "#lambda^{1}_{3}", "#lambda^{1}_{3}",
                                    "Number of entries", 0.54, 0.57, 0.84, 0.87);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l13(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l20", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                                    1,
                                    "#lambda^{2}_{0}", "#lambda^{1}_{3}",
                                    "Number of entries", 0.54, 0.57, 0.84, 0.87);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/l20(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
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
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/zval", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, false, 0,
                                    1,
                                    "z_{value}", "z_{value}",
                                    "Number of entries", 0.5, 0.2, 0.84, 0.5);
    DrawHistogramFromTreeTestSetLeg("../source/D0.root", "../results/zval(integral norm)", "angT",
                                    variable_array_angs, selection_array_angs, variable_names_angs, 4, false, true, true, 0,
                                    1,
                                    "z_{value}", "z_{value}",
                                    "Number of entries", 0.5, 0.2, 0.84, 0.5);

    return 0;
}
