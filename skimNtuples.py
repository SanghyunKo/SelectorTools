#!/usr/bin/env python
import ROOT
import argparse
import os
import sys
from Utilities.python import ApplySelection

def getComLineArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--selection", type=str,
                        required=True, help="Name of selection, which is" 
                        " mapped to a cuts json via Cuts/definitions.json")
    parser.add_argument("-t", "--trigger", type=str, default="",
                        choices=["DoubleEG", "DoubleMuon", "MuonEG", ""],
                        help="Name of trigger to select in data")
    parser.add_argument("-f", "--filelist", type=str,
                        required=True, help="List of input file names "
                        "to be processed (separated by commas)")
    parser.add_argument("-a", "--analysis", type=str,
                        required=True, help="Analysis name, used"
                        " in selection the cut json")
    parser.add_argument("-o", "--output_file_name", type=str,
                        required=True, help="Name of output file")
    return vars(parser.parse_args())
def writeNtupleToFile(output_file, tree, state, cut_string):
    state_dir = output_file.mkdir(state)
    state_dir.cd()
    save_tree = tree.CopyTree(cut_string)
    print "save_tree has %i entries" % save_tree.GetEntries()
    save_tree.Write()
    # Remove AutoSaved trees
    output_file.Purge()
    ROOT.gROOT.cd()
    del save_tree
def writeMetaTreeToFile(output_file, metaTree):
    output_file.cd()
    meta_dir = output_file.mkdir("metaInfo")
    meta_dir.cd()
    save_mt = metaTree.CopyTree("")
    save_mt.Write()
def skimNtuple(selection, analysis, trigger, filelist, output_file_name):
    current_path = os.getcwd()
    os.chdir(sys.path[0])
    ROOT.gROOT.SetBatch(True)
    output_file = ROOT.TFile(output_file_name, "RECREATE")
    ROOT.gROOT.cd()
    with open(filelist) as input_file:
        input_files = [('root://cmsxrootd.hep.wisc.edu/' + i.strip()) \
            if "store" in i[:6] else i.strip() for i in input_file.readlines()]
    metaTree = ROOT.TChain("metaInfo")
    for file_path in input_files:
        metaTree.Add(file_path)
    for state in ["eee", "eem", "emm", "mmm"]:
        tree = ROOT.TChain("%s/ntuple" % state)
        for file_path in input_files:
            print file_path
            tree.Add(file_path)
            print tree
            print "Now the tree has %i entries" % tree.GetEntries()
            cut_string = ApplySelection.buildCutString(state, selection, analysis, trigger).getString()
            print "Cut string is %s " % cut_string
            ApplySelection.setAliases(tree, state, "Cuts/aliases.json")
        writeNtupleToFile(output_file, tree, state, cut_string)
    writeMetaTreeToFile(output_file, metaTree)
    os.chdir(current_path)

def main():
    args = getComLineArgs()
    skimNtuple(args['selection'], args['analysis'], args['trigger'], args['filelist'], args['output_file_name'])
if __name__ == "__main__":
    main()