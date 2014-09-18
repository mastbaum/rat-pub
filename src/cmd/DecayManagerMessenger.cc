#include <sstream>
#include <G4UIcommand.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithABool.hh>
#include <G4String.hh>
#include <GLG4StringUtil.hh>
#include <RAT/Log.hh>
#include <RAT/DecayManagerMessenger.hh>
#include <RAT/DecayManager.hh>

namespace RAT {

DecayManagerMessenger::DecayManagerMessenger(DecayManager* gen)
    : fGenerator(gen) {
  // Define commands in a /generator/decaymanager directory
  G4UIdirectory* dir = new G4UIdirectory("/generator/decaymanager/");
  dir->SetGuidance("Control the parameters of the Decay Manager");

  fSetCmd = new G4UIcommand("/generator/decaymanager/set", this);
  fSetCmd->SetGuidance("Set the radioactive load on a volume.");
  fSetCmd->SetGuidance("Usage: /generator/decaymanager/set volume:chain:activity");
  fSetCmd->SetParameter(new G4UIparameter("state1", 's', true));
  fSetCmd->SetParameter(new G4UIparameter("state2", 's', true));
  fSetCmd->SetParameter(new G4UIparameter("state3", 's', true));
}

DecayManagerMessenger::~DecayManagerMessenger(){
  delete fSetCmd;
}

void DecayManagerMessenger::SetNewValue(G4UIcommand* command,
                                        G4String newValues) {
  if (command == fSetCmd) {
    G4String state = util_strip_default(newValues);
    std::vector<std::string> parts = util_split(state, ":");
    Log::Assert(parts.size() == 3, "DecayManagerMessenger: Invalid command");

    std::string volname = parts[0];
    std::string chain = parts[1];

    std::vector<std::string> activityParts = util_split(parts[2], " ");
    Log::Assert(activityParts.size() < 3,
                "DecayManagerMessenger: Invalid command");
    std::stringstream sact;
    sact.str(activityParts[0]);
    double activity;
    sact >> activity;

    if (activityParts.size() == 2) {
      // TODO: Check that the units are really valid
      std::string activityUnit = activityParts[1];
      if (activityUnit.find("Ci") != std::string::npos) {
        activity *= 3.7e10;
      }
      if (activityUnit.find("m") != std::string::npos) {
        activity *= 1e-3;
      }
      else if (activityUnit.find("u") != std::string::npos) {
        activity *= 1e-6;
      }
      else if (activityUnit.find("n") != std::string::npos) {
        activity *= 1e-9;
      }
      else if (activityUnit.find("k") != std::string::npos) {
        activity *= 1e3;
      }
      else {
        Log::Die("DecayManagerMessenger: Invalid activity units");
      }
    }

    fGenerator->SetComponentLoad(volname, chain, activity);
  }
  else {
    Log::Die("DecayManagerMessenger: Invalid command");
  }
}

G4String DecayManagerMessenger::GetCurrentValue(G4UIcommand*) {
  return G4String("");
}

}  // namespace RAT

