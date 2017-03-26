// The class definition in WZSelectorBase.h has been generated automatically
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
// To use this file, try the following se                                              WZSelectorBase.C")
// root> T->Process("WZSelectorBase.C","some options")
// root> T->Process("WZSelectorBase.C+")
//


#include "Analysis/WZAnalysis/interface/WZSelectorBase.h"
#include <TStyle.h>

void WZSelectorBase::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void WZSelectorBase::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).
    TString option = GetOption();

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
    std::cout << "Processing " << name_ << std::endl;
    AddObject<TH2D>(passingTight2D_, ("passingTight2D_"+channel_).c_str(), "Tight leptons; p_{T} [GeV]", 
        4, 10, 50, 3, 0, 2.5);
    //passingTight1DPt_->SetDirectory(0);
    //histDir_->Add(passingTight1DPt_);
    //passingTight1DEta_ = new TH1D( (std::string("passingTight1DEta_")+channel_).c_str(), 
    //    "Tight leptons; #eta; Events", 3, 0, 2.5);
    //passingTight1DEta_->SetDirectory(0);
    //histDir_->Add(passingTight1DEta_);
    //passingLoose2D_ = new TH2D((std::string("passingLoose2D_")+channel_).c_str(), 
    //    "Leptons passing tight failing loose; p_{T} [GeV]; Eta", 4, 10, 50, 3, 0, 2.5);
    //passingLoose2D_->SetDirectory(0);
    //histDir_->Add(passingLoose2D_);
    //
    //passingLoose1DPt_ = new TH1D((std::string("passingLoose1DPt_")+channel_).c_str(), 
    //    "Loose leptons; p_{T} [GeV]; Events", 4, 10, 50);
    //passingLoose1DPt_->SetDirectory(0);
    //histDir_->Add(passingLoose1DPt_);
    //
    //passingLoose1DEta_ = new TH1D((std::string("passingLoose1DEta_")+channel_).c_str(), 
    //    "Loose leptons; #eta; Events", 3, 0, 2.5);
    //passingLoose1DEta_->SetDirectory(0);
    //histDir_->Add(passingLoose1DEta_);
    currentHistDir_ = dynamic_cast<TList*>(fOutput->FindObject(name_.c_str()));
    if ( currentHistDir_ == nullptr ) {
        currentHistDir_ = new TList();
        currentHistDir_->SetName(name_.c_str());
        fOutput->Add(currentHistDir_);
        // Watch for something that I hope never happens,
        size_t existingObjectPtrsSize = allObjects_.size();
        if ( existingObjectPtrsSize > 0 && allObjects_.size() != existingObjectPtrsSize ) {
            Abort(Form("WZSelectorBase: Size of allObjects has changed!: %lu to %lu", existingObjectPtrsSize, allObjects_.size()));
        }
    }
    UpdateDirectory();

}
void WZSelectorBase::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the reader is initialized.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).
    if (!tree) return;
    fChain = tree;
    if (name_.find("data") == std::string::npos){
        fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    }
    fChain->SetBranchAddress("type1_pfMETEt", &type1_pfMETEt, &b_type1_pfMETEt);
    fChain->SetBranchAddress("nCBVIDVetoElec", &nCBVIDVetoElec, &b_nCBVIDVetoElec);
    fChain->SetBranchAddress("nWZLooseMuon", &nWZLooseMuon, &b_nWZLooseMuon);

    if (channel_ == "eee") {
        fChain->SetBranchAddress("e1_e2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("e1IsCBVIDTight", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("e2IsCBVIDTight", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("e3IsCBVIDTight", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("e1IsEB", &e1IsEB, &b_e1IsEB);
        fChain->SetBranchAddress("e2IsEB", &e2IsEB, &b_e2IsEB);
        fChain->SetBranchAddress("e3IsEB", &e3IsEB, &b_e3IsEB);
        fChain->SetBranchAddress("e1PVDXY", &e1PVDXY, &b_e1PVDXY);
        fChain->SetBranchAddress("e2PVDXY", &e2PVDXY, &b_e2PVDXY);
        fChain->SetBranchAddress("e3PVDXY", &e3PVDXY, &b_e3PVDXY);
        fChain->SetBranchAddress("e1PVDZ", &e1PVDZ, &b_e1PVDZ);
        fChain->SetBranchAddress("e2PVDZ", &e2PVDZ, &b_e2PVDZ);
        fChain->SetBranchAddress("e3PVDZ", &e3PVDZ, &b_e3PVDZ);
        
        fChain->SetBranchAddress("e1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("e2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("e3Pt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("e3Eta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("e3MtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else if (channel_ == "eem") { 
        fChain->SetBranchAddress("e1_e2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("e1IsCBVIDTight", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("e2IsCBVIDTight", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("e1IsEB", &e1IsEB, &b_e1IsEB);
        fChain->SetBranchAddress("e2IsEB", &e2IsEB, &b_e2IsEB);
        fChain->SetBranchAddress("e1PVDXY", &e1PVDXY, &b_e1PVDXY);
        fChain->SetBranchAddress("e2PVDXY", &e2PVDXY, &b_e2PVDXY);
        fChain->SetBranchAddress("e1PVDZ", &e1PVDZ, &b_e1PVDZ);
        fChain->SetBranchAddress("e2PVDZ", &e2PVDZ, &b_e2PVDZ);
        
        fChain->SetBranchAddress("mIsMedium", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("mRelPFIsoDBR04", &m3RelPFIsoDBR04, &b_m3RelPFIsoDBR04);
        fChain->SetBranchAddress("e1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("e2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("mPt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("mEta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("mMtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else if (channel_ == "emm") { 
        fChain->SetBranchAddress("m1_m2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("eIsCBVIDTight", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("eIsEB", &e3IsEB, &b_e3IsEB);
        fChain->SetBranchAddress("ePVDXY", &e3PVDXY, &b_e3PVDXY);
        fChain->SetBranchAddress("ePVDZ", &e3PVDZ, &b_e3PVDZ);
        fChain->SetBranchAddress("m1IsMedium", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("m1RelPFIsoDBR04", &m1RelPFIsoDBR04, &b_m1RelPFIsoDBR04);
        fChain->SetBranchAddress("m2IsMedium", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("m2RelPFIsoDBR04", &m2RelPFIsoDBR04, &b_m2RelPFIsoDBR04);
        fChain->SetBranchAddress("m1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("m2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("ePt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("eEta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("eMtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else if (channel_ == "mmm") { 
        fChain->SetBranchAddress("m1_m2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("m1IsMedium", &l1IsTight, &b_l1IsTight);
        fChain->SetBranchAddress("m1RelPFIsoDBR04", &m1RelPFIsoDBR04, &b_m1RelPFIsoDBR04);
        fChain->SetBranchAddress("m2IsMedium", &l2IsTight, &b_l2IsTight);
        fChain->SetBranchAddress("m2RelPFIsoDBR04", &m2RelPFIsoDBR04, &b_m2RelPFIsoDBR04);
        fChain->SetBranchAddress("m3IsMedium", &l3IsTight, &b_l3IsTight);
        fChain->SetBranchAddress("m3RelPFIsoDBR04", &m3RelPFIsoDBR04, &b_m3RelPFIsoDBR04);
        fChain->SetBranchAddress("m1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("m2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("m3Pt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("m3Eta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("m3MtToMET", &l3MtToMET, &b_l3MtToMET);
    }
    else
        throw std::invalid_argument("Invalid channel choice!");
}

Bool_t WZSelectorBase::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}



Bool_t WZSelectorBase::Process(Long64_t entry)
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

    if (name_.find("data") == std::string::npos)
        b_genWeight->GetEntry(entry);
    else 
        genWeight = 1;
    b_Zmass->GetEntry(entry);
    b_type1_pfMETEt->GetEntry(entry);
    b_nCBVIDVetoElec->GetEntry(entry);
    b_nWZLooseMuon->GetEntry(entry);
    b_l1IsTight->GetEntry(entry);
    b_l2IsTight->GetEntry(entry);
    b_l3IsTight->GetEntry(entry);
    b_l3Eta->GetEntry(entry);
    b_l1Pt->GetEntry(entry);
    b_l2Pt->GetEntry(entry);
    b_l3Pt->GetEntry(entry);
    b_l3MtToMET->GetEntry(entry);
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
    }
    else if (channel_ == "eem") {
        b_e1IsEB->GetEntry(entry);
        b_e2IsEB->GetEntry(entry);
        b_e1PVDXY->GetEntry(entry);
        b_e2PVDXY->GetEntry(entry);
        b_e1PVDZ->GetEntry(entry);
        b_e2PVDZ->GetEntry(entry);
        b_m3RelPFIsoDBR04->GetEntry(entry);
    }
    else if (channel_ == "emm") {
        b_e3IsEB->GetEntry(entry);
        b_e3PVDXY->GetEntry(entry);
        b_e3PVDZ->GetEntry(entry);
        b_m1RelPFIsoDBR04->GetEntry(entry);
        b_m2RelPFIsoDBR04->GetEntry(entry);
    }
    else if (channel_ == "mmm") {
        b_m1RelPFIsoDBR04->GetEntry(entry);
        b_m2RelPFIsoDBR04->GetEntry(entry);
        b_m3RelPFIsoDBR04->GetEntry(entry);
    }
    //    return true;
    if (l1Pt < 25 || l2Pt < 15)
        return true;
    if (Zmass > 111.1876 || Zmass < 81.1876)
        return true;
    if (type1_pfMETEt > 30)
        return true;
    if (l3MtToMET > 30)
        return true;
    if (!tightZLeptons())
        return true;
    passingLoose2D_->Fill(l3Pt, std::abs(l3Eta), genWeight);
    passingLoose1DPt_->Fill(l3Pt, genWeight);
    passingLoose1DEta_->Fill(std::abs(l3Eta), genWeight);
    if (lepton3IsTight()) {
        passingTight2D_->Fill(l3Pt, std::abs(l3Eta), genWeight);
        passingTight1DPt_->Fill(l3Pt, genWeight);
        passingTight1DEta_->Fill(std::abs(l3Eta), genWeight);
    }
    return kTRUE;
}

bool WZSelectorBase::tightZLeptons() {
    if (channel_ == "eem" || channel_ == "eee") {
        return l1IsTight && l2IsTight; 
    }
    else 
        return m1RelPFIsoDBR04 < 0.15 && m2RelPFIsoDBR04 < 0.15;
}

bool WZSelectorBase::lepton3IsTight() {
    if (channel_ == "eee" || channel_ == "emm") {
        return l3IsTight;
    }
    else if (channel_ == "mmm" || channel_ == "eem") {
        return m3RelPFIsoDBR04 < 0.15;
    }
    else
        return false;
}

void WZSelectorBase::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    //ratio2D_ = dynamic_cast<TH2D*>(passingTight2D_->Clone());
    //ratio2D_->Divide(passingLoose2D_);
    //ratio2D_->SetName((std::string("ratio2D_") + channel_).c_str());
    //ratio2D_->SetTitle("Ratio tight/loose");
    //ratio2D_->SetDirectory(0);
    //histDir_->Add(ratio2D_);

    //ratio1DPt_ = dynamic_cast<TH1D*>(passingTight1DPt_->Clone());
    //ratio1DPt_->Divide(passingLoose1DPt_);
    //ratio1DPt_->SetName((std::string("ratio1DPt_") + channel_).c_str());
    //ratio1DPt_->SetTitle("Ratio tight/loose");
    //ratio1DPt_->SetDirectory(0);
    //histDir_->Add(ratio1DPt_);

    //ratio1DEta_ = dynamic_cast<TH1D*>(passingTight1DEta_->Clone());
    //ratio1DEta_->Divide(passingLoose1DEta_);
    //ratio1DEta_->SetName((std::string("ratio1DEta_") + channel_).c_str());
    //ratio1DEta_->SetTitle("Ratio tight/loose");
    //ratio1DEta_->SetDirectory(0);
    //histDir_->Add(ratio1DEta_);

}
    
void WZSelectorBase::SlaveTerminate()
{
}
void WZSelectorBase::UpdateDirectory()
{
  for(TNamed** objPtrPtr : allObjects_) {
    if ( *objPtrPtr == nullptr ) Abort("WZSelectorBase: Call to UpdateObject but existing pointer is null");
    *objPtrPtr = (TNamed *) currentHistDir_->FindObject((*objPtrPtr)->GetName());
    if ( *objPtrPtr == nullptr ) Abort("WZSelectorBase: Call to UpdateObject but current directory has no instance");
  }
}
