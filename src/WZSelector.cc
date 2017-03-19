#define WZSelector_cxx
// The class definition in WZSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following se                                              WZSelector.C")
// root> T->Process("WZSelector.C","some options")
// root> T->Process("WZSelector.C+")
//


#include "Analysis/WZAnalysis/interface/WZSelector.h"
#include <TStyle.h>

void WZSelector::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void WZSelector::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).
    if (GetInputList() != nullptr) {
        TNamed* name = (TNamed *) GetInputList()->FindObject("name");
        TNamed* chan = (TNamed *) GetInputList()->FindObject("channel");
        if (name != nullptr) {
            name_ = name->GetTitle();
        }
        if (chan != nullptr) {
            channel_ = chan->GetTitle();
        }
    }
    pileupSF_ = (ScaleFactor *) GetInputList()->FindObject("pileupSF");
    if (pileupSF_ == nullptr ) 
        Abort("Must pass pileup weights SF");
    eIdSF_ = (ScaleFactor *) GetInputList()->FindObject("electronTightIdSF");
    if (eIdSF_ == nullptr ) 
        Abort("Must pass electron ID SF");
    mIdSF_ = (ScaleFactor *) GetInputList()->FindObject("muonTightIdSF");
    if (mIdSF_ == nullptr ) 
        Abort("Must pass muon ID SF");
    mIsoSF_ = (ScaleFactor *) GetInputList()->FindObject("muonIsoSF");
    if (mIsoSF_ == nullptr ) 
        Abort("Must pass muon Iso SF");

    histDir_ = new TList();
    histDir_->SetName(name_.c_str());
    fOutput->Add(histDir_);
    nvtxHist_= new TH1D(("nvtx_"+channel_).c_str(),
        "nvtx; Number of Vertices; Events;", 60, 0, 60);
    zmassHist_= new TH1D(("ZMass_"+channel_).c_str(),
        "ZMass; M_{ll} [GeV]; Events;", 15, 76, 106);
    massHist_= new TH1D(("Mass_"+channel_).c_str(),
        "Mass; M_{3l} [GeV]; Events / 40 GeV;", 11, 100, 540);
    mjjHist_= new TH1D(("mjj_"+channel_).c_str(),
        "mjj; m_{jj} [GeV]; Events / 50 GeV;", 10, 100, 600);
    l1PtHist_= new TH1D(("Zlep1_Pt_"+channel_).c_str(),
        "l1Pt; p_{T} leading Z lepton [GeV]; Events / 15 GeV;", 10, 25, 175);
    l2PtHist_= new TH1D(("Zlep2_Pt_"+channel_).c_str(),
        "l2Pt; p_{T} trailing Z lepton [GeV]; Events / 10 GeV;", 12, 15, 135);
    l3PtHist_= new TH1D(("Wlep_Pt_"+channel_).c_str(),
        "l2Pt; p_{T} W lepton [GeV]; Events / 10 GeV;", 10, 20, 220);
    nvtxHist_->SetDirectory(0);
    zmassHist_->SetDirectory(0);
    massHist_->SetDirectory(0);
    mjjHist_->SetDirectory(0);
    l1PtHist_->SetDirectory(0);
    l2PtHist_->SetDirectory(0);
    l3PtHist_->SetDirectory(0);
    histDir_->Add(nvtxHist_);
    histDir_->Add(zmassHist_);
    histDir_->Add(massHist_);
    histDir_->Add(mjjHist_);
    histDir_->Add(l1PtHist_);
    histDir_->Add(l2PtHist_);
    histDir_->Add(l3PtHist_);
    TString option = GetOption();
}

Bool_t WZSelector::Process(Long64_t entry)
{
    // The Process() function is called for each entry in the tree (or possibly
    // keyed object in the case of PROOF) to be processed. The entry argument
    // specifies which entry in the currently loaded tree is to be processed.
    // When processing keyed objects with PROOF, the object is already loaded
    // and is available via the fObject pointer.
    //
    // This function should contain the \"body\" of the analysis. It can contain
    // simple or elaborate selection criteria, run algorithms on the data
    // of the event and typically fill histograms.
    //
    // The processing can be stopped by calling Abort().
    //
    // Use fStatus to set the return value of TTree::Process().
    //
    // The return value is currently not used.
    bool isMC = false;
    if (name_.find("data") == std::string::npos) {
        b_genWeight->GetEntry(entry);
        b_nTruePU->GetEntry(entry);
        isMC = true;
    }
    else 
        genWeight = 1;
    b_Zmass->GetEntry(entry);
    b_Mass->GetEntry(entry);
    b_nvtx->GetEntry(entry);
    b_mjj->GetEntry(entry);
    b_type1_pfMETEt->GetEntry(entry);
    b_nWWLooseElec->GetEntry(entry);
    b_nWZLooseMuon->GetEntry(entry);
    b_l1IsTight->GetEntry(entry);
    b_l2IsTight->GetEntry(entry);
    b_l3IsTight->GetEntry(entry);
    b_l1Eta->GetEntry(entry);
    b_l1Pt->GetEntry(entry);
    b_l2Eta->GetEntry(entry);
    b_l2Pt->GetEntry(entry);
    b_l3Eta->GetEntry(entry);
    b_l3Pt->GetEntry(entry);
    if (channel_ == "eee") {
        b_e1IsEB->GetEntry(entry);
        b_e2IsEB->GetEntry(entry);
        b_e3IsEB->GetEntry(entry);
        b_e1PVDXY->GetEntry(entry);
        b_e2PVDXY->GetEntry(entry);
        b_e3PVDXY->GetEntry(entry);
        b_e1PVDZ->GetEntry(entry);
        b_e2PVDZ->GetEntry(entry);
        b_e3PVDZ->GetEntry(entry);
        if (isMC) {
            genWeight *= eIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= eIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= eIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
    }
    else if (channel_ == "eem") {
        b_e1IsEB->GetEntry(entry);
        b_e2IsEB->GetEntry(entry);
        b_e1PVDXY->GetEntry(entry);
        b_e2PVDXY->GetEntry(entry);
        b_e1PVDZ->GetEntry(entry);
        b_e2PVDZ->GetEntry(entry);
        b_m3RelPFIsoDBR04->GetEntry(entry);
        if (isMC) {
            genWeight *= eIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= eIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
    }
    else if (channel_ == "emm") {
        b_e3IsEB->GetEntry(entry);
        b_e3PVDXY->GetEntry(entry);
        b_e3PVDZ->GetEntry(entry);
        b_m1RelPFIsoDBR04->GetEntry(entry);
        b_m2RelPFIsoDBR04->GetEntry(entry);
        if (isMC) {
            genWeight *= eIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
    }
    else if (channel_ == "mmm") {
        b_m1RelPFIsoDBR04->GetEntry(entry);
        b_m2RelPFIsoDBR04->GetEntry(entry);
        b_m3RelPFIsoDBR04->GetEntry(entry);
        if (isMC) {
            genWeight *= mIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
    }
    if (nWWLooseElec + nWZLooseMuon > 3)
        return true;
    if (l1Pt < 25 || l2Pt < 10)
        return true;
    //if (type1_pfMETEt < 30)
    //    return true;
    //if (Mass < 100)
    //    return true;
    //if (Zmass > 116.1876 || Zmass < 76.1876)
    //    return true;
    if (!(zlep1IsTight() && zlep2IsTight() && wlepIsTight()))
        return true;
    zmassHist_->Fill(Zmass, genWeight);
    nvtxHist_->Fill(nvtx, genWeight);
    l1PtHist_->Fill(l1Pt, genWeight);
    l2PtHist_->Fill(l2Pt, genWeight);
    l3PtHist_->Fill(l3Pt, genWeight);
    mjjHist_->Fill(mjj, genWeight*(isMC || mjj < 500));
    massHist_->Fill(Mass, genWeight*(isMC || Mass < 400));
    return true;
}

bool WZSelector::zlep1IsTight() {
    if (channel_ == "eem" || channel_ == "eee") {
        return (l1IsTight &&
            (e1IsEB ? e1PVDXY < 0.05 : e1PVDXY < 0.1) &&
            (e1IsEB ? e1PVDZ < 0.1 : e1PVDZ < 0.2));
    }
    else 
        return l1IsTight && (m1RelPFIsoDBR04 < 0.15);
}

bool WZSelector::zlep2IsTight() {
    if (channel_ == "eem" || channel_ == "eee") {
        return (l2IsTight &&
            (e2IsEB ? e2PVDXY < 0.05 : e2PVDXY < 0.1) &&
            (e2IsEB ? e2PVDZ < 0.1 : e2PVDZ < 0.2));
    }
    else 
        return l2IsTight && (m2RelPFIsoDBR04 < 0.15);
}

bool WZSelector::wlepIsTight() {
    if (channel_ == "emm" || channel_ == "eee") {
        return (l2IsTight &&
            (e3IsEB ? e3PVDXY < 0.05 : e3PVDXY < 0.1) &&
            (e3IsEB ? e3PVDZ < 0.1 : e3PVDZ < 0.2));
    }
    else 
        return l3IsTight && (m3RelPFIsoDBR04 < 0.15);
}

void WZSelector::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.

}

void WZSelector::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
}
