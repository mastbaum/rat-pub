#include <GenericChamberHit.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4ios.hh>
#include <CLHEP/Units/SystemOfUnits.h>

namespace RAT {

G4Allocator<GenericChamberHit> GenericChamberHitAllocator;

GenericChamberHit::GenericChamberHit(G4int i, G4double t)
    : id(i), time(t), pLogV(NULL) {}


//GenericChamberHit::GenericChamberHit(const GenericChamberHit &rhs)
//    : G4VHit(), id(rhs.id), time(rhs.time), pos(rhs.pos),
//      rot(rhs.rot), pLogV(rhs.pLogV) {}


//const GenericChamberHit&
//GenericChamberHit::operator=(const GenericChamberHit &rhs) {
//  id = rhs.id;
//  time = rhs.time;
//  pos = rhs.pos;
//  rot = rhs.rot;
//  pLogV = rhs.pLogV;
//  return *this;
//}

void GenericChamberHit::Draw() {
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager) {
    G4Transform3D trans(rot.inverse(), pos);
    G4VisAttributes attribs;
    const G4VisAttributes* pVA = pLogV->GetVisAttributes();
    if (pVA) {
      attribs = *pVA;
    }
    G4Colour colour(0, 1, 1);
    attribs.SetColour(colour);
    attribs.SetForceSolid(true);
    pVVisManager->Draw(*pLogV, attribs, trans);
  }
}


void GenericChamberHit::Print() {
#ifdef G4DEBUG
  G4cout << "GenericChamber[" << id << "] "
         << time / CLHEP::ns << " (nsec)" << G4endl;
#endif
}

}  // namespace RAT

