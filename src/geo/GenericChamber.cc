#include <RAT/GenericChamber.hh>
#include <RAT/GenericChamberHit.hh>
#include <G4RunManager.hh>
#include <G4Run.hh>
#include <G4HCofThisEvent.hh>
#include <G4TouchableHistory.hh>
#include <G4Track.hh>
#include <G4Step.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>
#include <G4UImanager.hh>
#include <G4UIcommand.hh>
#include <G4UnitsTable.hh>

namespace RAT {

GenericChamber::GenericChamber(G4String name) : G4VSensitiveDetector(name) {
  G4String HCname = "genericchamberColl";
  collectionName.insert(HCname);
  HCID = -1;
}


void GenericChamber::Initialize(G4HCofThisEvent* _HCE) {  
#ifdef G4DEBUG
  G4cout << "GenericChamber::Initialize start." << G4endl;
#endif

  hitsCollection = \
    new GenericChamberHitsCollection(SensitiveDetectorName, collectionName[0]);

#ifdef G4DEBUG
  G4cout << "GenericChamber::Initialize hit collection address is "
         << hitsCollection << G4endl;
#endif

  if (HCID < 0) {
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  }


#ifdef G4DEBUG
  G4cout << "GenericChamber::Initialize hit collection ID = "
         << HCID << G4endl;
#endif

  _HCE->AddHitsCollection(HCID, hitsCollection);
  
  // Store pointer to hit collection
  HCE = _HCE;

  // Initialize the data members used to store information for the RAT Event

  // Empty the hit information vectors
  hit_x.clear();
  hit_y.clear();
  hit_z.clear();
  hit_E.clear();
  hit_time.clear();
  hit_uid.clear();
  hit_pdg.clear();
  hit_volume.clear();

  lastTrackID = lastEventID = -1;

#ifdef G4DEBUG
  G4cout << "GenericChamber::Initialize end." << G4endl;
#endif
}


G4bool GenericChamber::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
  // Don't store optical photons!
  if (aStep->GetTrack()->GetDefinition()->GetParticleName() == "opticalphoton")
    return true;

#ifdef G4DEBUG
    G4cout << "GenericChamber::ProcessHits start" << G4endl;
    G4cout << "GenericChamber::ProcessHits getting energy deposited" << G4endl;
#endif

  G4double edep = aStep->GetTotalEnergyDeposit();

#ifdef G4DEBUG
  G4cout << " Energy deposited: " << edep << G4endl;
#endif

  G4Track* aTrack = aStep->GetTrack();
  G4ParticleDefinition* part = aTrack->GetDefinition();
  int pdg = part->GetPDGEncoding();

#ifdef G4DEBUG
  G4cout << " Track information: " << G4endl
         << "   G4Track Pointer: " << aTrack  << G4endl
         << "   Particle Definition Pointer: " << part << G4endl
         << "   Particle PDG Encoding: " << pdg << G4endl;
#endif

#ifdef G4DEBUG
  G4cout << "GenericChamber::ProcessHits getting global time." << G4endl;
#endif

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();

  G4TouchableHistory* theTouchable = \
    (G4TouchableHistory*)(preStepPoint->GetTouchable());

  // Get the copy number of this element. This may not be unique,
  // if the mother is also a replica and occurs more than once.
  G4int copyNo = theTouchable->GetVolume()->GetCopyNo();

  // Get the mother copy number, and offset it by 1000. This will help
  // form the basis of the chamber ID.
  G4int motherCopyNo = (theTouchable->GetVolume(1)->GetCopyNo()) + 1000;
  G4int uid = motherCopyNo + copyNo; // Unique identifier of chamber

  // Construct a unique identifier for this copy
  G4int ivol = 0;
  G4int idOffset = 1;
  uid = 0;
  
#ifdef G4DEBUG
  G4cout << "History level: " << theTouchable->GetHistoryDepth() << G4endl;
#endif

  while (ivol < theTouchable->GetHistoryDepth()) {
#ifdef G4DEBUG
    G4cout << " * volume layer level = " << ivol << G4endl;
#endif
    uid += theTouchable->GetVolume(ivol)->GetCopyNo() * idOffset;
    idOffset *= 100;
    ivol++;
  }

  G4ThreeVector worldPos = preStepPoint->GetPosition();

#ifdef G4DEBUG
  G4Material* m = preStepPoint->GetMaterial();
  G4String mname = m->GetName();
  G4double d = m->GetDensity();
  G4String f = m->GetChemicalFormula();
  G4double dl = aStep->GetStepLength();

  G4cout << "Hit material name " << mname << G4endl;
  G4cout << "density           " << d << G4endl;
  G4cout << "formula           " << f << G4endl;
  G4cout << "edep " << G4BestUnit(edep,"Energy") << G4endl;
  G4cout << "dl " << G4BestUnit(dl,"Length") << G4endl;
  G4cout << "pid " << pdg << G4endl;
  G4cout << "Position "
         << G4BestUnit(worldPos.x(), "Length") << " "
         << G4BestUnit(worldPos.y(), "Length") << " "
         << G4BestUnit(worldPos.z(), "Length") << " " << G4endl;
  G4cout << " " << G4endl;
#endif
  
  G4double hitTime = preStepPoint->GetGlobalTime();

  // Check if this chamber already has a hit
#ifdef G4DEBUG
  G4cout << "GenericChamber::ProcessHits checking for an existing hit "
         << "in this element." << G4endl;
#endif

  G4int ix = -1;

#ifdef G4DEBUG
  G4cout << "GenericChamber::ProcessHits hit collection address is "
         << hitsCollection << G4endl;
  G4cout << "GenericChamber: Hit ID = " << uid
         << " and position: " << worldPos << G4endl;
#endif

  int eventID = \
    G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEvent();

  int trackID = aStep->GetTrack()->GetTrackID();
  
  // Get volume name of hit as well 
  // Note that this volume name may not be unique
  G4String vol = theTouchable->GetVolume()->GetName();

  if (lastEventID != eventID || lastTrackID != trackID) {
      // Fill the hit information
      hit_x.push_back(worldPos.x());
      hit_y.push_back(worldPos.y());
      hit_z.push_back(worldPos.z());
      hit_E.push_back(edep);
      hit_time.push_back(hitTime);
      hit_uid.push_back(uid);
      hit_pdg.push_back(pdg);
      hit_volume.push_back(vol);
      lastEventID = eventID;
      lastTrackID = trackID;
  }
  
  if (hitsCollection == NULL) {
#ifdef G4DEBUG
    G4cout << "GenericChamber::ProcessHits hit collection null. "
           << "Reloading from HCofEThisEvent." << G4endl;
#endif
    if (HCE) {
      hitsCollection = (GenericChamberHitsCollection*)(HCE->GetHC(HCID));
#ifdef G4DEBUG
      G4cout << "GenericChamber::ProcessHits * hit collection address is "
         << hitsCollection
         << G4endl;
#endif
    }
    else {
#ifdef G4DEBUG
      G4cout << "GenericChamber::ProcessHits (E) HCofEThisEvent "
             << "pointer is NULL!" << G4endl;
#endif
    }
  }
  
  if (hitsCollection) {
    for (int i=0; i<hitsCollection->entries(); i++) {
#ifdef G4DEBUG
      G4cout << " * this hit ID is " << (*hitsCollection)[i]->GetID()
             << G4endl;
#endif
      if ((*hitsCollection)[i]->GetID() == uid) {
        ix = i;
        break;
      }
    }

    // Take the earlier time
    if (ix>=0) {
#ifdef G4DEBUG
      G4cout << "GenericChamber::ProcessHits use existing earlier "
             << "time for hit." << G4endl;
#endif

      if ((*hitsCollection)[ix]->GetTime() > hitTime) {
        (*hitsCollection)[ix]->SetTime(hitTime);
      }
    }
    else {
      // Create a new hit and set it to the collection
#ifdef G4DEBUG
      G4cout << "GenericChamber::ProcessHits creating a new hit." << G4endl;
#endif
      GenericChamberHit* aHit = new GenericChamberHit(uid, hitTime);
      G4VPhysicalVolume* thePhysical = theTouchable->GetVolume();
      aHit->SetLogV(thePhysical->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit->SetRot(aTrans.NetRotation());
      aHit->SetPos(aTrans.NetTranslation());
      hitsCollection->insert(aHit);
      aHit->Print();
      aHit->Draw();

#ifdef G4DEBUG
      G4cout << "  * Drawing Hit " << uid << G4endl;
#endif
    }
  }

#ifdef G4DEBUG
  G4cout << "GenericChamber::ProcessHits end." << G4endl;
#endif

  return true;
}

}  // namespace RAT

