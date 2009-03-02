/*************************************************************************
* Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
*                                                                        *
* Author: The ALICE Off-line Project.                                    *
* Contributors are mentioned in the code where appropriate.              *
*                                                                        *
* Permission to use, copy, modify and distribute this software and its   *
* documentation strictly for non-commercial purposes is hereby granted   *
* without fee, provided that the above copyright notice appears in all   *
* copies and that both the copyright notice and this permission notice   *
* appear in the supporting documentation. The authors make no claims     *
* about the suitability of this software for any purpose. It is          *
* provided "as is" without express or implied warranty.                  * 
**************************************************************************/

#define AliFlowAnalysisWithScalarProduct_cxx
 
#include "Riostream.h"  //needed as include
#include "TFile.h"      //needed as include
#include "TList.h"
#include "TMath.h"
#include "TProfile.h"
#include "TVector2.h"

class TH1F;

#include "AliFlowCommonConstants.h"    //needed as include
#include "AliFlowEventSimple.h"
#include "AliFlowTrackSimple.h"
#include "AliFlowCommonHist.h"
#include "AliFlowCommonHistResults.h"
#include "AliFlowAnalysisWithScalarProduct.h"

class AliFlowVector;

// AliFlowAnalysisWithScalarProduct:
// Description: 
// Maker to analyze Flow with the Scalar product method.
//
// author: N. van der Kolk (kolk@nikhef.nl)

ClassImp(AliFlowAnalysisWithScalarProduct)

  //-----------------------------------------------------------------------
 
 AliFlowAnalysisWithScalarProduct::AliFlowAnalysisWithScalarProduct():
   fEventNumber(0),
   fDebug(kFALSE),
   fHistList(NULL),
   fHistProUQetaRP(NULL),
   fHistProUQetaPOI(NULL),
   fHistProUQPtRP(NULL),
   fHistProUQPtPOI(NULL),
   fHistProVetaRP(NULL),
   fHistProVetaPOI(NULL),
   fHistProVPtRP(NULL),
   fHistProVPtPOI(NULL),
   fCommonHists(NULL),
   fCommonHistsRes(NULL)
{
  // Constructor.
  fHistList = new TList();
}
 //-----------------------------------------------------------------------


 AliFlowAnalysisWithScalarProduct::~AliFlowAnalysisWithScalarProduct() 
 {
   //destructor
   delete fHistList;
 }
 

//-----------------------------------------------------------------------

void AliFlowAnalysisWithScalarProduct::WriteHistograms(TString* outputFileName)
{
 //store the final results in output .root file

  TFile *output = new TFile(outputFileName->Data(),"RECREATE");
  output->WriteObject(fHistList, "cobjSP","SingleKey");
  delete output;
}

//-----------------------------------------------------------------------

void AliFlowAnalysisWithScalarProduct::WriteHistograms(TString outputFileName)
{
 //store the final results in output .root file

  TFile *output = new TFile(outputFileName.Data(),"RECREATE");
  output->WriteObject(fHistList, "cobjSP","SingleKey");
  delete output;
}

//-----------------------------------------------------------------------
void AliFlowAnalysisWithScalarProduct::Init() {

  //Define all histograms
  cout<<"---Analysis with the Scalar Product Method--- Init"<<endl;

  Int_t iNbinsPt   = AliFlowCommonConstants::GetNbinsPt();
  Double_t dPtMin  = AliFlowCommonConstants::GetPtMin();	     
  Double_t dPtMax  = AliFlowCommonConstants::GetPtMax();
  Int_t iNbinsEta  = AliFlowCommonConstants::GetNbinsEta();
  Double_t dEtaMin = AliFlowCommonConstants::GetEtaMin();	     
  Double_t dEtaMax = AliFlowCommonConstants::GetEtaMax();

  fHistProUQetaRP = new TProfile("Flow_UQetaRP_SP","Flow_UQetaRP_SP",iNbinsEta,dEtaMin,dEtaMax);
  fHistProUQetaRP->SetXTitle("{eta}");
  fHistProUQetaRP->SetYTitle("<uQ>");
  fHistList->Add(fHistProUQetaRP);

  fHistProUQetaPOI = new TProfile("Flow_UQetaPOI_SP","Flow_UQetaPOI_SP",iNbinsEta,dEtaMin,dEtaMax);
  fHistProUQetaPOI->SetXTitle("{eta}");
  fHistProUQetaPOI->SetYTitle("<uQ>");
  fHistList->Add(fHistProUQetaPOI);

  fHistProUQPtRP = new TProfile("Flow_UQPtRP_SP","Flow_UQPtRP_SP",iNbinsPt,dPtMin,dPtMax);
  fHistProUQPtRP->SetXTitle("p_t (GeV)");
  fHistProUQPtRP->SetYTitle("<uQ>");
  fHistList->Add(fHistProUQPtRP);

  fHistProUQPtPOI = new TProfile("Flow_UQPtPOI_SP","Flow_UQPtPOI_SP",iNbinsPt,dPtMin,dPtMax);
  fHistProUQPtPOI->SetXTitle("p_t (GeV)");
  fHistProUQPtPOI->SetYTitle("<uQ>");
  fHistList->Add(fHistProUQPtPOI);

  fHistProVetaRP = new TProfile("Flow_VetaRP_SP","Flow_VetaRP_SP",iNbinsEta,dEtaMin,dEtaMax);
  fHistProVetaRP->SetXTitle("{eta}");
  fHistProVetaRP->SetYTitle("v_{2}");
  fHistList->Add(fHistProVetaRP);

  fHistProVetaPOI = new TProfile("Flow_VetaPOI_SP","Flow_VetaPOI_SP",iNbinsEta,dEtaMin,dEtaMax);
  fHistProVetaPOI->SetXTitle("{eta}");
  fHistProVetaPOI->SetYTitle("v_{2}");
  fHistList->Add(fHistProVetaPOI);

  fHistProVPtRP = new TProfile("Flow_VPtRP_SP","Flow_VPtRP_SP",iNbinsPt,dPtMin,dPtMax);
  fHistProVPtRP->SetXTitle("p_t (GeV)");
  fHistProVPtRP->SetYTitle("v_{2}");
  fHistList->Add(fHistProVPtRP);

  fHistProVPtPOI = new TProfile("Flow_VPtPOI_SP","Flow_VPtPOI_SP",iNbinsPt,dPtMin,dPtMax);
  fHistProVPtPOI->SetXTitle("p_t (GeV)");
  fHistProVPtPOI->SetYTitle("v_{2}");
  fHistList->Add(fHistProVPtPOI);

  fCommonHists = new AliFlowCommonHist("AliFlowCommonHistSP");
  fHistList->Add(fCommonHists);
  fCommonHistsRes = new AliFlowCommonHistResults("AliFlowCommonHistResultsSP");
  fHistList->Add(fCommonHistsRes);  

  fEventNumber = 0;  //set number of events to zero    
}

//-----------------------------------------------------------------------
 
void AliFlowAnalysisWithScalarProduct::Make(AliFlowEventSimple* anEvent) {

  //Fill histogram
  if (anEvent) {

    //fill control histograms     
    fCommonHists->FillControlHistograms(anEvent);
         
    //get the Q vector from the FlowEvent
    AliFlowVector vQ = anEvent->GetQ();
    //get Q vectors for the subevents
    AliFlowVector vQa = anEvent->GetQsub(-0.9,0.);  //Random subevents?
    AliFlowVector vQb = anEvent->GetQsub(0.,0.9);
    //CHECK THIS!
    Double_t dQaQb = vQa*vQb; //CHECK this!
    dQaQb = 2*TMath::Sqrt(dQaQb);
                
    //loop over the tracks of the event
    AliFlowTrackSimple*   pTrack = NULL; 
    Int_t iNumberOfTracks = anEvent->NumberOfTracks(); 
    for (Int_t i=0;i<iNumberOfTracks;i++) 
      {
	pTrack = anEvent->GetTrack(i) ; 
	if (pTrack){
	  Double_t dPhi = pTrack->Phi();
	  //calculate vU
	  TVector2 vU;
	  Double_t dUX = TMath::Cos(2*dPhi);
	  Double_t dUY = TMath::Sin(2*dPhi);
	  vU.Set(dUX,dUY);
	  Double_t dModulus = vU.Mod();
	  if (dModulus!=0.) vU.Set(dUX/dModulus,dUY/dModulus);  // make length 1
	  else cerr<<"dModulus is zero!"<<endl;

	  TVector2 vQm = vQ;
	  //subtrackt particle from the flowvector if used to define it
	  if (pTrack->UseForIntegratedFlow()) {
	    Double_t dQmX = vQm.X() - dUX;
	    Double_t dQmY = vQm.Y() - dUY;
	    vQm.Set(dQmX,dQmY);
	  }

	  //dUQ = scalar product of vU and vQm
	  Double_t dUQ = vU * vQm;
	  Double_t dV = 0.;
	  if (dQaQb != 0.) {dV = dUQ/dQaQb;}
	  Double_t dPt = pTrack->Pt();
	  Double_t dEta = pTrack->Eta();
	  //fill the profile histograms
	  if (pTrack->UseForIntegratedFlow()) {
	    fHistProUQetaRP -> Fill(dEta,dUQ);
	    fHistProUQPtRP -> Fill(dPt,dUQ);
	    fHistProVetaRP -> Fill(dEta,dV);
	    fHistProVPtRP -> Fill(dPt,dV);
	  }
	  if (pTrack->UseForDifferentialFlow()) {
	    fHistProUQetaPOI -> Fill(dEta,dUQ);
	    fHistProUQPtPOI -> Fill(dPt,dUQ);
	    fHistProVetaPOI -> Fill(dEta,dV);
	    fHistProVPtPOI -> Fill(dPt,dV);
	  }  
	}//track selected
      }//loop over tracks
	 
    fEventNumber++;
    //    cout<<"@@@@@ "<<fEventNumber<<" events processed"<<endl;
  }
}

  //--------------------------------------------------------------------    
void AliFlowAnalysisWithScalarProduct::Finish() {
   
  //fill the commonhist results and calculate integrated flow
  if (fDebug) cout<<"AliFlowAnalysisWithScalarProduct::Finish()"<<endl;

  cout<<"*************************************"<<endl;
  cout<<"*************************************"<<endl;
  cout<<"      Integrated flow from           "<<endl;
  cout<<"         Scalar product              "<<endl;
  cout<<endl;

  //copy content of profile into TH1D and fill the AliFlowCommonHistResults
  Int_t iNbinsPt  = AliFlowCommonConstants::GetNbinsPt();
  Int_t iNbinsEta = AliFlowCommonConstants::GetNbinsEta();

  //v as a function of eta for RP selection
  for(Int_t b=0;b<iNbinsEta;b++) {
    Double_t dv2pro  = fHistProVetaRP->GetBinContent(b);
    Double_t dv2err  = fHistProVetaRP->GetBinError(b); //copy error for now
    //fill TH1D
    fCommonHistsRes->FillDifferentialFlowEtaRP(b, dv2pro, dv2err); 
  } //loop over bins b
    
  //v as a function of eta for POI selection
  for(Int_t b=0;b<iNbinsEta;b++) {
    Double_t dv2pro  = fHistProVetaPOI->GetBinContent(b);
    Double_t dv2err  = fHistProVetaPOI->GetBinError(b); //copy error for now
    //fill TH1D
    fCommonHistsRes->FillDifferentialFlowEtaPOI(b, dv2pro, dv2err); 
  } //loop over bins b
    
  //v as a function of Pt for RP selection
  TH1F* fHistPtInt = fCommonHists->GetHistPtInt(); //for calculating integrated flow
  Double_t dVRP = 0.;
  Double_t dSum = 0.;
  Double_t dErrV =0.;

  for(Int_t b=0;b<iNbinsPt;b++) {
    Double_t dv2pro  = fHistProVPtRP->GetBinContent(b);
    Double_t dv2err  = fHistProVPtRP->GetBinError(b); //copy error for now
    //fill TH1D
    fCommonHistsRes->FillDifferentialFlowPtRP(b, dv2pro, dv2err);
    //calculate integrated flow for RP selection
    if (fHistPtInt){
      Double_t dYieldPt = fHistPtInt->GetBinContent(b);
      dVRP += dv2pro*dYieldPt;
      dSum +=dYieldPt;
      dErrV += dYieldPt*dYieldPt*dv2err*dv2err;
    } else { cout<<"fHistPtDiff is NULL"<<endl; }
  } //loop over bins b

  if (dSum != 0.) {
    dVRP /= dSum; //the pt distribution should be normalised
    dErrV /= (dSum*dSum);
    dErrV = TMath::Sqrt(dErrV);
  }
  fCommonHistsRes->FillIntegratedFlowRP(dVRP,dErrV);

  cout<<"dV(RP) = "<<dVRP<<" +- "<<dErrV<<endl;
       
  //v as a function of Pt for POI selection 
  TH1F* fHistPtDiff = fCommonHists->GetHistPtDiff(); //for calculating integrated flow
  Double_t dVPOI = 0.;
  dSum = 0.;
  dErrV =0.;
  
  for(Int_t b=0;b<iNbinsPt;b++) {
    Double_t dv2pro = fHistProVPtPOI->GetBinContent(b);
    Double_t dv2err = fHistProVPtPOI->GetBinError(b); //copy error for now
    //fill TH1D
    fCommonHistsRes->FillDifferentialFlowPtPOI(b, dv2pro, dv2err); 

    //calculate integrated flow for POI selection
    if (fHistPtDiff){
      Double_t dYieldPt = fHistPtDiff->GetBinContent(b);
      dVPOI += dv2pro*dYieldPt;
      dSum +=dYieldPt;
      dErrV += dYieldPt*dYieldPt*dv2err*dv2err;
    } else { cout<<"fHistPtDiff is NULL"<<endl; }
  } //loop over bins b

  if (dSum != 0.) {
    dVPOI /= dSum; //the pt distribution should be normalised
    dErrV /= (dSum*dSum);
    dErrV = TMath::Sqrt(dErrV);
  }
  fCommonHistsRes->FillIntegratedFlowPOI(dVPOI,dErrV);

  cout<<"dV(POI) = "<<dVPOI<<" +- "<<dErrV<<endl;
  cout<<endl;
  cout<<"*************************************"<<endl;
  cout<<"*************************************"<<endl;   	  

  //cout<<".....finished"<<endl;
 }


