/**
 * @class RAT::Manager
 * @author William Seligman
 *
 * Set up the G4RunManager environment, before initializing the
 * main RAT simulation in RAT.
 */

#ifndef __RAT_Manager__
#define __RAT_Manager__

class G4RunManager;

#ifdef G4VIS_USE
class G4VisManager;
#endif

namespace RAT {

class Gsim;
class ProcBlock;

class Manager {
public:
  Manager();
  Manager(ProcBlock* theMainBlock);
  virtual ~Manager();

protected:
  void Init();

private:
  G4RunManager* theRunManager;  ///< The G4 simulation process manager
  ProcBlock* mainBlock;  ///< The processor execution manager
  Gsim* ratGsim;  ///< The simulation manager

#ifdef G4VIS_USE
  G4VisManager* theVisManager;  ///< Visualization manager, if enabled
#endif
};

} // namespace RAT

#endif  // __RAT_Manager__

