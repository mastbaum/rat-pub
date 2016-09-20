#ifndef __RAT_GenericChamber__
#define __RAT_GenericChamber__

#include <G4VSensitiveDetector.hh>
#include <RAT/GenericChamberHit.hh>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

namespace RAT {

class GenericChamber : public G4VSensitiveDetector {
  
public:
  GenericChamber(G4String name);
  virtual ~GenericChamber() {}
  
  virtual void Initialize(G4HCofThisEvent* _HCE);
  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
  virtual void EndOfEvent(G4HCofThisEvent*) {}

  std::vector<float> hit_x;  //!< Hit x coordinates
  std::vector<float> hit_y;  //!< Hit y coordinates
  std::vector<float> hit_z;  //!< Hit z coordinates
  std::vector<double> hit_E;  //!< Hit energy deposited
  std::vector<float> hit_time;  //!< Hit times
  std::vector<int> hit_uid;  //!< Chamber unique ID code
  std::vector<int> hit_pdg;  //!< Hit particle PDG code
  std::vector<std::string> hit_volume;  //!< Name of hit volume

private:
  int lastEventID;
  int lastTrackID;
    
  GenericChamberHitsCollection* hitsCollection;
  G4int HCID;
  G4HCofThisEvent* HCE;
};

}  // namespace RAT

#endif  // __RAT_GenericChamber__

