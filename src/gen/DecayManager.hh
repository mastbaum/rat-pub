/**
 * @class RAT::DecayManager
 * @author A. Mastbaum <mastbaum@hep.upenn.edu>
 *
 * @brief Specify event generation by putting a radioactive load on
 * detector components.
 *
 * This concept is ported from Baccarat.
 */

#ifndef __RAT_DecayManager__
#define __RAT_DecayManager__

#include <vector>
#include <G4String.hh>
#include <RAT/GLG4Gen.hh>

class G4Event;
class GLG4TimeGen;

namespace RAT {

class DecayManagerMessenger;

class DecayManager : public GLG4Gen {
public:
  DecayManager();
  virtual ~DecayManager();
  virtual void GenerateEvent(G4Event* event);
  virtual void ResetTime(double offset=0.0);
  virtual bool IsRepeatable() const { return true; };

  /** Add a radioactive load to a bulk volume. */
  virtual void SetComponentLoad(std::string volumeName,
                                std::string chain,
                                double activity);

  virtual void SetState(G4String state);
  virtual G4String GetState() const;
  
  virtual void SetTimeState(G4String state);
  virtual G4String GetTimeState() const;
  virtual void SetVertexState(G4String state);
  virtual G4String GetVertexState() const;
  virtual void SetPosState(G4String state);
  virtual G4String GetPosState() const;

protected:
  G4String state;
  DecayManagerMessenger* fMessenger;
  GLG4TimeGen* fTimeGenerator;
};

}  // namespace RAT

#endif  // __RAT_DecayManager__

