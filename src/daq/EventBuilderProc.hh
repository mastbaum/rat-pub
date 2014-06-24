/**
 * @class RAT::EventBuilderProc
 * @brief Map MC truth hit information to detected hit information
 */

#ifndef __RAT_EventBuilderProc__
#define __RAT_EventBuilderProc__

#include <RAT/Processor.hh>

namespace RAT {

namespace DS {
  class Root;
}

class EventBuilderProc : public Processor {
public:
  EventBuilderProc();
  virtual ~EventBuilderProc() {}

  virtual Processor::Result DSEvent(DS::Root* ds);

  virtual double DigitizeT(double hitTime, double stopTime);

  virtual float DigitizeQ(float hitCharge);

protected:
  // Delay of global trigger back to front end
  double fTriggerDelay;

  // Width of trigger gate within which to collect hits
  double fTriggerGate;
};

}  // namespace RAT

#endif  // __RAT_EventBuilderProc__

