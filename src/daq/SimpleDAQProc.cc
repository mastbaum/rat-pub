#include <vector>
#include <RAT/DB.hh>
#include <RAT/Log.hh>
#include <RAT/SimpleDAQProc.hh>

namespace RAT {

SimpleDAQProc::SimpleDAQProc() : Processor("simpledaq") {
  fEventCounter = 0;
}

Processor::Result SimpleDAQProc::DSEvent(DS::Root *ds) {
  DS::MC *mc = ds->GetMC();

  // If there is already a EV branch present, remove it, otherwise we'll
  // have multiple detector events in this physics event.
  if (ds->ExistEV()) {
    warn << "SimpleDAQProc: Deleting pre-existing EV data" << newline;
    ds->PruneEV();
  }
  DS::EV *ev = ds->AddNewEV();
  
  ev->SetID(fEventCounter);
  fEventCounter++;

  double totalQ = 0;
  for (int imcpmt=0; imcpmt<mc->GetPMTCount(); imcpmt++) {
    DS::MCPMT* mcpmt = mc->GetPMT(imcpmt);
    int pmtID = mcpmt->GetID();

    if (mcpmt->GetMCPhotonCount() > 0) {
      // Need at least one photon to trigger
      DS::PMT* pmt = ev->AddNewPMT();
      pmt->SetID(pmtID);

      // Create one sample, hit time is determined by first hit,
      // "infinite" charge integration time
      // WARNING: gets multiphoton effect right, but not walk correction

      double time = mcpmt->GetMCPhoton(0)->GetFrontEndTime();
      double charge = 0;

      for (int i=0; i < mcpmt->GetMCPhotonCount(); i++)  {
        charge += mcpmt->GetMCPhoton(i)->GetCharge();
      }

      totalQ += charge;

      DS::Sample* sample = pmt->AddNewSample();
      sample->SetCharge(charge);
      sample->SetTime(time);
    }
  }

  return Processor::OK;
}

} // namespace RAT

