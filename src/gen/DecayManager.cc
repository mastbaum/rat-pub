#include <string_utilities.hpp>
#include <G4Event.hh>
#include <Randomize.hh>
#include <RAT/DecayManager.hh>
#include <RAT/DecayManagerMessenger.hh>
#include <RAT/DetectorConstruction.hh>
#include <RAT/DetectorComponent.hh>
#include <RAT/Log.hh>
#include <RAT/GLG4TimeGen.hh>

namespace RAT {

DecayManager::DecayManager() : state("default"), fTimeGenerator(0) {
  fMessenger = new DecayManagerMessenger(this);
  fTimeGenerator = new GLG4TimeGen_Poisson();
  SetState(state);
}


DecayManager::~DecayManager() {
  delete fTimeGenerator;
}


void DecayManager::GenerateEvent(G4Event *event) {
  // TODO: Draw events from a time-ordered series of decays drawn from
  // all DetectorComponents registered in DetectorConstruction.
}


void DecayManager::ResetTime(double offset) {
  nextTime = fTimeGenerator->GenerateEventTime() + offset;
}
 

void DecayManager::SetComponentLoad(std::string volumeName,
                                    std::string chain,
                                    double activity) {
  warn << "DecayManager: Setting load on component " << volumeName << ": "
       << activity << " Bq of " << chain << newline;

  DetectorConstruction* detector =
    DetectorConstruction::GetDetectorConstruction();

  DetectorComponent* component = detector->GetComponents()[volumeName];

  Log::Assert(component, dformat("DecayManager: Volume %s not found",
                                 volumeName.c_str()));

  warn << "Found the component " << volumeName
       << " at " << component << newline;

  // TODO: Set the activity in the DetectorComponent
}


void DecayManager::SetState(G4String state) {}


G4String DecayManager::GetState() const {
  return state;
}


void DecayManager::SetTimeState(G4String state) {
  if (fTimeGenerator) {
    fTimeGenerator->SetState(state);
  }
  else {
    warn << "DecayManager error: Cannot set time state, "
         << "no time generator selected" << newline;
  }
}


G4String DecayManager::GetTimeState() const {
  if (fTimeGenerator) {
    return fTimeGenerator->GetState();
  }
  else {
    warn << "DecayManager error: no time generator selected" << newline;
  }
  return G4String("");
}


void DecayManager::SetVertexState(G4String) {
    warn << "DecayManager error: Cannot set vertex state." << newline;
}


G4String DecayManager::GetVertexState() const {
  return G4String("DecayManager error: no vertex generator");
}


void DecayManager::SetPosState(G4String) {
  warn << "DecayManager error: Cannot set position state, "
       << "no position generator" << newline;
}


G4String DecayManager::GetPosState() const {
  return G4String("DecayManager error: no pos generator");
}

} // namespace RAT

