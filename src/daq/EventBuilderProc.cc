#include <algorithm>
#include <cmath>
#include <vector>
#include <RAT/DB.hh>
#include <RAT/Log.hh>
#include <RAT/TimeUtil.hh>
#include <RAT/TriggerPulse.hh>
#include <RAT/TriggerSum.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/MCHit.hh>
#include <RAT/DS/MCSample.hh>
#include <RAT/DS/MCHit.hh>
#include <G4ThreeVector.hh>
#include <RAT/EventBuilderProc.hh>

namespace RAT {

inline bool Cmp_MCHit_TimeAscending(DS::MCHit& a, DS::MCHit& b) {
  return a.GetMCSample(0)->GetHitTime() < b.GetMCSample(0)->GetHitTime();
}


EventBuilderProc::EventBuilderProc() : Processor("eventbuilder") {
  DBLinkPtr ldaq = DB::Get()->GetLink("DAQ");

  info << dformat(" Trigger Delay : %5.2f ns\n", fTriggerDelay)
       << dformat(" Trigger Gate  : %5.2f ns\n", fTriggerGate);
}


Processor::Result EventBuilderProc::DSEvent(DS::Root* ds) {
  Log::Assert(ds->ExistMC(), "EventBuilderProc: No MC information found.");

  // First sort the MCHits
  ds->GetMC()->SortMCHit(Cmp_MCHit_TimeAscending);

  // Now loop over all triggers, collecting hits and samples
  for (int iev=0; iev<ds->GetEVCount(); iev++) {
    DS::EV* ev = ds->GetEV(iev);
    ev->SetTotalCharge(0);
    TTimeStamp triggerStopTime = AddNanoseconds(ev->GetUTC(), fTriggerDelay);

    if (ds->GetMC()->GetMCHitCount() == 0) {
      continue;
    }

    // Loop over hits. firstSampleTime tells us the time of the first sample
    // in a given MCHit.
    TTimeStamp firstSampleTime =
      AddNanoseconds(ev->GetUTC(),
                     ds->GetMC()->GetMCHit(0)->GetMCSample(0)->GetHitTime());
    int ihit = 0;
    while (ihit < ds->GetMC()->GetMCHitCount() &&
           firstSampleTime < triggerStopTime) {
      DS::MCHit* hit = ds->GetMC()->GetMCHit(ihit);

      // Advance through samples on this hit until we find the first one 
      // (if any) that is after the last trigger lockout time.
      TTimeStamp nextSampleTime;
      int imcsample = 0;
      while (imcsample < hit->GetMCSampleCount()) {
        DS::MCSample* mcsample = hit->GetMCSample(imcsample);

        // If sample is inside gate, create a PMT data object and fill the
        // time and charge samples, as well as PMT information..
        nextSampleTime = AddNanoseconds(ev->GetUTC(), mcsample->GetHitTime());

        if ((triggerStopTime - nextSampleTime) < fTriggerGate &&
             nextSampleTime < triggerStopTime) {
          DS::PMT* pmt = ev->AddNewPMT();
          pmt->SetID(hit->GetPMTID());

          // Loop over the rest of the MC samples, filling PMT data samples
          // until we run out of the trigger gate.
          while (imcsample < hit->GetMCSampleCount() &&
                 TimeDifference(
                   triggerStopTime,
                   AddNanoseconds(ev->GetUTC(),
                                  hit->GetMCSample(imcsample)->GetHitTime())) > 0) {
            DS::Sample* sample = pmt->AddNewSample();
            double mctime = mcsample->GetHitTime();
            double mccharge = mcsample->GetCharge();
            sample->SetTime(DigitizeT(mctime, triggerStopTime));
            sample->SetCharge(DigitizeQ(mccharge));
            ev->SetTotalCharge(ev->GetTotalCharge() + sample->GetCharge());
          }
        }
      }

      if (ihit < ds->GetMC()->GetMCHitCount()) {
        firstSampleTime = hit->GetMCSample(0)->GetHitTime();
      }
    }
  }

  return OK;
}

// Eventually this will have to return a 12-bit integer,
// in ADC or TDC counts
double EventBuilderProc::DigitizeT(double hitTime, double stopTime) {
  return stopTime - hitTime;
}


// Eventually this will have to return a 12-bit integer,
// in ADC counts
float EventBuilderProc::DigitizeQ(float hitCharge) {
  return hitCharge;
}

}  // namespace RAT

