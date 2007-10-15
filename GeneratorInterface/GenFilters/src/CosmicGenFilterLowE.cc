// daniele.benedetti@cern.ch
// Filter to generate from CMSCGEN muon cosmics with Caprice energy spectrum only below 2 GeV


#include "GeneratorInterface/GenFilters/interface/CosmicGenFilterLowE.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"


#include <map>
#include <vector>

using namespace std;

CosmicGenFilterLowE::CosmicGenFilterLowE(const edm::ParameterSet& conf)
{
}

bool CosmicGenFilterLowE::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  
  edm::Handle<edm::HepMCProduct>HepMCEvt;
  iEvent.getByLabel("source","",HepMCEvt);
  const HepMC::GenEvent* MCEvt = HepMCEvt->GetEvent();
  
  double Ene = 0;
  
  for(HepMC::GenEvent::particle_const_iterator i=MCEvt->particles_begin(); i != MCEvt->particles_end();++i)
    {
      Ene = (*i)->momentum().e();
    }
  
  float r1;
  double prob;
  prob = RanGen2.Rndm();
  r1 = float(prob);
  float fpmax = 2565.;
  float fp;
  double ten = 10.0;
  float fp2gev = 1227.;  //...needed for the renormalization;
  
  
  if (Ene < 2) {
      
    fp =  97.303*(1.48*((pow(Ene,-1.5))* pow(ten,(1.189+0.9604*log10(Ene)-1.114*log10(Ene)*log10(Ene) +0.1775*log10(Ene)*log10(Ene)*log10(Ene)))));
    if (r1 < (fp/fpmax))  return true;
    else return false;
  }
  else {
    if ( r1 < (fp2gev/fpmax))  {
      return true;         
    }
    else return false;
  }
}

