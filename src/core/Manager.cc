#include <cstdlib>
#include <RAT/Manager.hh>
#include <RAT/ProcBlock.hh>
#include <RAT/Gsim.hh>
#include <GLG4PhysicsList.hh>
#include <G4RunManager.hh>

#ifdef G4VIS_USE
#include <GLG4VisManager.hh>
#endif

namespace RAT {

Manager::Manager() {
  mainBlock = NULL;
  Init();
}

Manager::Manager(ProcBlock* theMainBlock) {
  mainBlock = theMainBlock;
  Init();
}

void Manager::Init() {
  theRunManager = new G4RunManager;
  
  // Particle transport and interactions.  Note that this has to be
  // created outside of Gsim, since the physics list must be
  // initialized before the user tracking action.
  theRunManager->SetUserInitialization(new GLG4PhysicsList);

  ratGsim = new Gsim(mainBlock);
  
#ifdef G4VIS_USE
  theVisManager = new GLG4VisManager();
  theVisManager->Initialize();
#endif
}

Manager::~Manager() {
  delete ratGsim;

#ifdef G4VIS_USE
  delete theVisManager;
#endif
}

} // namespace RAT

