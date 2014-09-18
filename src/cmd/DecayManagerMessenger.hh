/**
 * @class RAT::DecayManagerMessenger
 * @author A. Mastbaum <mastbaum@hep.upenn.edu>
 *
 * @brief Handle command-line options to the DecayManager generator.
 */

#ifndef __RAT_DecayManagerMessenger__
#define __RAT_DecayManagerMessenger__

#include <G4UImessenger.hh>
#include <G4String.hh>

class G4UIcommand;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

namespace RAT {

class DecayManager;

class DecayManagerMessenger: public G4UImessenger {
public:
  DecayManagerMessenger(DecayManager*);
  ~DecayManagerMessenger();
  
  void SetNewValue(G4UIcommand* command, G4String newValues);
  G4String GetCurrentValue(G4UIcommand* command);
  
private:
  DecayManager* fGenerator;
  G4UIcommand* fSetCmd;
};

}  // namespace RAT

#endif  // __RAT_DecayManagerMessenger__

