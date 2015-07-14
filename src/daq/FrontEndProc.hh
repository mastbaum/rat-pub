/**
 * @class RAT::FrontEndProc
 * @brief Front-end electronics simulation
 *
 * Here we simulate the action of the front end electronics, simulating the
 * charge spectrum and clustering hits on individual PMTs. We do the
 * clustering depending upon a sampling window, so that a given MCPMT can have
 * several samples corresponding to a single detected event.  The output is
 * kept in the data structure in MCHit objects and the samples in an array
 * of MCSamples within MCHits.
 *
 * For adjustable parameters see DAQ.ratdb.
 */

#ifndef __RAT_FrontEndProc__
#define __RAT_FrontEndProc__

#include <vector>
#include <RAT/Processor.hh>
#include <RAT/DB.hh>

namespace RAT {

namespace DS {
  class Root;
}

class FrontEndProc : public Processor {
public:
  FrontEndProc();
  virtual ~FrontEndProc() {}

  virtual Processor::Result DSEvent(DS::Root* ds);

protected:
  // Integration time in ns
  double fSamplingTime;

  // Single-hit discriminator threshold in pe
  float fHitThreshold;

  // Width of a PMT pulse in ns
  float fPulseWidth;

  // Width of noise in pe
  float fNoiseAmpl;

  // Time before discriminator fires that sampling gate opens
  double fGDelay;
};

}  // namespace RAT

#endif  // __RAT_FrontEndProc__

