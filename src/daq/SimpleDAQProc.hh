/**
 * @class RAT::SimpleDAQProc
 * @brief A simplistic DAQ simulation
 *
 * This simple simulation assumes only tubes hit by a photon register
 * a hit, and that every MC event corresponds to one triggered event
 * The time of the PMT hit is that of the first photon.
 */

#ifndef __RAT_SimpleDAQProc__
#define __RAT_SimpleDAQProc__

#include <RAT/Processor.hh>

namespace RAT {

class SimpleDAQProc : public Processor {
public:
  SimpleDAQProc();
  virtual ~SimpleDAQProc() { };
  virtual Processor::Result DSEvent(DS::Root *ds);

protected:
  int fEventCounter;
  std::vector<double> fSPECharge;
};

}  // namespace RAT

#endif  // __RAT_SimpleDAQProc__

