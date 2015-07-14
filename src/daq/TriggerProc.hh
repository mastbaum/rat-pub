/**
 * @class RAT::TriggerProc
 * @brief A semi-generic simulation of an analog trigger system
 *
 * Each detected photoelectrons contributes a fixed-width square pulse to
 * an analog trigger sum waveform, and the amplitude of this waveform (with
 * Gaussian noise added) is compared to a threshold in number of hits (Nhit).
 *
 * When the trigger fires, one or more new event (EV) objects are created in
 * the data structure, depending on the timing of the hits and the length
 * of the event window.
 *
 * The length of the trigger window, width of the trigger pulses, and the
 * Nhit threshold are adjustable via parameters in the DAQ table;
 * see DAQ.ratdb.
 */ 

#ifndef __RAT_TriggerProc__
#define __RAT_TriggerProc__

#include <RAT/Processor.hh>

namespace RAT {

class TriggerProc : public Processor {
public:
  TriggerProc();
  virtual ~TriggerProc() {}

  virtual Processor::Result DSEvent(DS::Root* ds);

protected:
  // Triggered event counter
  int fEventCount;

  // Lockout time until next possible trigger.
  double fTrigLockout;

  // Width of square (NHIT) trigger pulses
  double fNHITPulseWidth;

  // Trigger threshold in NHITs
  float fNThreshold;
};

}  // namespace RAT

#endif  // __RAT_TriggerProc__

