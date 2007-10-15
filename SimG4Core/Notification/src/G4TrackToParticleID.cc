#include "SimG4Core/Notification/interface/G4TrackToParticleID.h"

#include "G4Track.hh"

G4TrackToParticleID::G4TrackToParticleID()
{
    theInternalMap["deuteron"] = -100;
    theInternalMap["alpha"] = -102;
    theInternalMap["triton"] = -101;
    theInternalMap["He3"] = -104;
}

int G4TrackToParticleID::particleID(const G4Track * g4trk)
{
    int particleID_ = g4trk->GetDefinition()->GetPDGEncoding();
    if ( particleID_ > 1000000000 ) {
      //std::cout << "G4TrackToParticleID ion code = " << particleID_ << std::endl;
      particleID_ = theInternalMap[g4trk->GetDefinition()->GetParticleName()];
      //std::cout << "G4TrackToParticleID light nucleus code = " << particleID_ << std::endl;
    }
    if (particleID_ != 0) return particleID_;
    return -99;
}

G4TrackToParticleID::~G4TrackToParticleID() { theInternalMap.clear(); }
