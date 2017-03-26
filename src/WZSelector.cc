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
        "ZMass; M_{ll} [GeV]; Events;", 15, 0, 150);
    massHist_= new TH1D(("Mass_"+channel_).c_str(),
        "Mass; M_{3l} [GeV]; Events / 30 GeV;", 14, 100, 520);
    mjjHist_= new TH1D(("mjj_"+channel_).c_str(),
        "mjj; m_{jj} [GeV]; Events / 50 GeV;", 15, 0, 1500);
    dEtajjHist_= new TH1D(("dEtajj_"+channel_).c_str(),
        "dEtajj; #Delta#eta(j_{1}, j_{2}); Events;", 12, 0, 6);
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
    dEtajjHist_->SetDirectory(0);
    l1PtHist_->SetDirectory(0);
    l2PtHist_->SetDirectory(0);
    l3PtHist_->SetDirectory(0);
    histDir_->Add(nvtxHist_);
    histDir_->Add(zmassHist_);
    histDir_->Add(massHist_);
    histDir_->Add(mjjHist_);
    histDir_->Add(dEtajjHist_);
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
    if (isMC_) {
        b_genWeight->GetEntry(entry);
        b_nTruePU->GetEntry(entry);
    }
    else 
        genWeight = 1;
    b_Zmass->GetEntry(entry);
    b_Mass->GetEntry(entry);
    b_nvtx->GetEntry(entry);
    b_mjj->GetEntry(entry);
    b_type1_pfMETEt->GetEntry(entry);
    b_nCBVIDVetoElec->GetEntry(entry);
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
    b_jetPt->GetEntry(entry);
    b_jetEta->GetEntry(entry);
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
        if (isMC_) {
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
        if (isMC_) {
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
        if (isMC_) {
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
        if (isMC_) {
            genWeight *= mIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
    }
    //if (type1_pfMETEt < 30)
    //    return true;
    //if (Mass < 100)
    //    return true;
    //if (l1Pt < 25 || l2Pt < 15)
    //    return true;
    //if (Zmass > 116.1876 || Zmass < 76.1876)
    //    return true;
    if (nWZLooseMuon + nCBVIDVetoElec > 3)
        return true;
    if (!(zlep1IsTight() && zlep2IsTight() && wlepIsTight()))
        return true;
    float dEtajj = 0;
    if (jetEta->size() >= 2)
        dEtajj = std::abs(jetEta->at(0) - jetEta->at(1));
    //if (dEtajj < 2.5 || mjj < 500)
    //if (!(dEtajj > 2.5 || mjj > 500))
    //    return true;
    zmassHist_->Fill(Zmass, genWeight);
    nvtxHist_->Fill(nvtx, genWeight);
    l1PtHist_->Fill(l1Pt, genWeight);
    l2PtHist_->Fill(l2Pt, genWeight);
    l3PtHist_->Fill(l3Pt, genWeight);
    mjjHist_->Fill(mjj, genWeight*(isMC_ || mjj < 500));
    if (dEtajj > 0)
        dEtajjHist_->Fill(dEtajj, genWeight*(isMC_ || dEtajj < 2.5));
    massHist_->Fill(Mass, genWeight*(isMC_ || Mass < 400));
    return true;
}

bool WZSelector::zlep1IsTight() {
    if (channel_ == "eem" || channel_ == "eee") {
        return l1IsTight;
    }
    else 
        return m1RelPFIsoDBR04 < 0.15;
}

bool WZSelector::zlep2IsTight() {
    if (channel_ == "eem" || channel_ == "eee") {
        return l2IsTight;
    }
    else 
        return m2RelPFIsoDBR04 < 0.15;
}

bool WZSelector::wlepIsTight() {
    if (channel_ == "emm" || channel_ == "eee") {
        return l3IsTight;
    }
    else 
        return m3RelPFIsoDBR04 < 0.15;
}

//void WZSelector::getQGCWeightOffset() {
//    return 446;
//}
//void WZSelector::getQGCNames(std::string sample_name) {
//    std::map<std::string, std::vector<std::string> weightNames;
//    weightNames["wzjj-aqgcft"] = {
//        "wzjj-aqgcft__ft0-0_ft1-0_ft2-m6"
//        "wzjj-aqgcft__ft0-m4_ft1-0_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-0_ft2-3"
//        "wzjj-aqgcft__ft0-m8_ft1-0_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-0_ft2-m3"
//        "wzjj-aqgcft__ft0-0_ft1-0_ft2-6"
//        "wzjj-aqgcft__ft0-8_ft1-0_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-4_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-2_ft2-0"
//        "wzjj-aqgcft__ft0-4_ft1-0_ft2-0"
//        "wzjj-aqgcft__ft0-m6_ft1-0_ft2-0"
//        "wzjj-aqgcft__ft0-6_ft1-0_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-0_ft2-12"
//        "wzjj-aqgcft__ft0-0_ft1-m2_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-m4_ft2-0"
//        "wzjj-aqgcft__sm"
//        "wzjj-aqgcft__ft0-0_ft1-8_ft2-0"
//        "wzjj-aqgcft__ft0-0_ft1-0_ft2-m12"
//        "wzjj-aqgcft__ft0-0_ft1-m8_ft2-0"
//    };
//}

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
