//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb  3 11:12:05 2017 by ROOT version 6.06/01
// from TTree ntuple/ntuple
// found on file: /data/kelong/DibosonAnalysisData/3LooseLeptons/2017-02-03-wz3lnu-powheg-WZxsec2016-3LooseLeptons-v1/skim-ntuplize_1.root
//////////////////////////////////////////////////////////

#ifndef FakeRateSelectorEEE_h
#define FakeRateSelectorEEE_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>

// Headers needed by this particular selector
#include <vector>
//#include "Analysis/WZAnalysis/interface/SelectorBase.h"

class FakeRateSelectorEEE : public TSelector {
public :
  TTreeReader    fReader;  //!the tree reader
  TTree       *fChain = 0;  //!pointer to the analyzed TTree or TChain
  const char* name_;
    TH2D* passingTight2D_;
    TH1D* passingTight1DPt_;
    TH1D* passingTight1DEta_;
    TH2D* passingLoose2D_;
    TH1D* passingLoose1DPt_;
    TH1D* passingLoose1DEta_;
    TList *currentHistDir_{nullptr};
    TTreeReaderValue<Float_t> type1_pfMETEt = {fReader, "type1_pfMETEt"};
    TTreeReaderValue<UInt_t> nWWLooseElec = {fReader, "nWWLooseElec"};
    TTreeReaderValue<UInt_t> nWZLooseMuon = {fReader, "nWZLooseMuon"};
    TTreeReaderValue<Float_t> e1PVDXY = {fReader, "e1PVDXY"};
    TTreeReaderValue<Float_t> e1PVDZ = {fReader, "e1PVDZ"};
//    TTreeReaderValue<Bool_t> e1IsCBVIDLoose = {fReader, "e1IsCBVIDLoose"};
//    TTreeReaderValue<Bool_t> e1IsCBVIDMedium = {fReader, "e1IsCBVIDMedium"};
    TTreeReaderValue<Bool_t> e1IsCBVIDTight = {fReader, "e1IsCBVIDTight"};
    TTreeReaderValue<Bool_t> e1IsEB = {fReader, "e1IsEB"};
    TTreeReaderValue<Float_t> e2PVDXY = {fReader, "e2PVDXY"};
    TTreeReaderValue<Float_t> e2PVDZ = {fReader, "e2PVDZ"};
    TTreeReaderValue<Bool_t> e2IsCBVIDTight = {fReader, "e2IsCBVIDTight"};
    TTreeReaderValue<Bool_t> e2IsEB = {fReader, "e2IsEB"};
    TTreeReaderValue<Float_t> e3Eta = {fReader, "e3Eta"};
    TTreeReaderValue<Float_t> e3PVDXY = {fReader, "e3PVDXY"};
    TTreeReaderValue<Float_t> e3PVDZ = {fReader, "e3PVDZ"};
    TTreeReaderValue<Float_t> e3Pt = {fReader, "e3Pt"};
    TTreeReaderValue<Bool_t> e3IsCBVIDTight = {fReader, "e3IsCBVIDTight"};
    TTreeReaderValue<Bool_t> e3IsEB = {fReader, "e3IsEB"};

    FakeRateSelectorEEE(TTree * /*tree*/ =0) { }
    FakeRateSelectorEEE(const char* name, TTree * /*tree*/ =0) : name_(name) { }
    virtual ~FakeRateSelectorEEE() { }
//    virtual void   SetupNewDirectory() override;
    virtual Bool_t Process(Long64_t entry) override;
    virtual void   Begin(TTree *tree) override;
    virtual void   SlaveBegin(TTree *tree) override;
    virtual void   Init(TTree *tree) override;
    virtual Bool_t Notify() override;
    virtual void   SlaveTerminate() override;
    virtual void   Terminate() override;


    ClassDefOverride(FakeRateSelectorEEE,0);
};

#endif