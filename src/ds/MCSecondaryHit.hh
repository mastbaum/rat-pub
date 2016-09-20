/**
 * @class DS::MCSecondaryHit
 * Data Structure: Particle interaction recorded in a secondary detector
 *
 * @author Stan Seibert <sseibert@hep.upenn.edu>
 *
 * Useful for recording energy deposition in a secondary detector (say, in
 * a calibration source) that will not be fully simulated and output in
 * the standard EV data stream.
 */ 

#ifndef __RAT_DS_MCSecondaryHit__
#define __RAT_DS_MCSecondaryHit__

#include <TObject.h>
#include <TVector3.h>

namespace RAT {
  namespace DS {

class MCSecondaryHit : public TObject {
public:
  MCSecondaryHit() {}
  virtual ~MCSecondaryHit() {}

  /** Incident particle type as defined in MCParticle::pdgcode. */
  virtual int GetPDGCode() const { return pdgcode; }
  virtual void SetPDGCode(int _pdgcode) { pdgcode = _pdgcode; }

  /** Time of hit (ns). */
  virtual double GetTime() const { return time; }
  virtual void SetTime(double _time) { time = _time; }

  /** Location of hit (mm). */
  virtual const TVector3 &GetPosition() const { return pos; }
  virtual void SetPosition(const TVector3 &_pos) { pos = _pos; }

  /** Energy deposited (MeV). */
  virtual double GetEdep() const { return edep; }
  virtual void SetEdep(double _edep) { edep = _edep; }

  /** ID number of hit volume */
  virtual int GetVolID() const { return volID; }
  virtual void SetVolID(int _volID) { volID = _volID; }

  /** Name of detector volume in which this hit took place. */
  /** this may not be unique if detectors are replicated in geometry */
  virtual std::string GetVolume() const { return volume; }
  virtual void SetVolume(const std::string &_hit_volume) {
    volume = _hit_volume;
  }
    
  ClassDef(MCSecondaryHit, 1)

protected:
  int pdgcode;
  double time;
  TVector3 pos;
  double edep;
  int volID;
  std::string volume;
};

  }  // namespace DS
}  // namespace RAT

#endif  // __RAT_DS_MCSecondaryHit__

