#ifndef __RAT_GenericChamberHit__
#define __RAT_GenericChamberHit__

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>
#include <G4LogicalVolume.hh>
#include <G4Transform3D.hh>
#include <G4RotationMatrix.hh>

namespace RAT {

class GenericChamberHit : public G4VHit {
public:
    GenericChamberHit(int i, double t);
    virtual ~GenericChamberHit() {}

    //GenericChamberHit(const GenericChamberHit &rhs);
    //const GenericChamberHit& operator=(const GenericChamberHit &rhs);
    //int operator==(const GenericChamberHit &rhs) const { return 0; }

    inline void *operator new(size_t);
    inline void operator delete(void* aHit);

    void Draw();
    void Print();

private:
    G4int id;
    G4double time;
    G4ThreeVector pos;
    G4RotationMatrix rot;
    const G4LogicalVolume* pLogV;

public:
    inline G4int GetID() const { return id; }
    inline G4double GetTime() const { return time; }
    inline void SetTime(G4double val) { time = val; }
    inline void SetPos(G4ThreeVector xyz) { pos = xyz; }
    inline G4ThreeVector GetPos() const { return pos; }
    inline void SetRot(G4RotationMatrix rmat) { rot = rmat; }
    inline G4RotationMatrix GetRot() const { return rot; }
    inline void SetLogV(G4LogicalVolume* val) { pLogV = val; }
    inline const G4LogicalVolume* GetLogV() const { return pLogV; }
};


typedef G4THitsCollection<GenericChamberHit> GenericChamberHitsCollection;


extern G4Allocator<GenericChamberHit> GenericChamberHitAllocator;


inline void* GenericChamberHit::operator new(size_t) {
  void* aHit;
  aHit = (void*) GenericChamberHitAllocator.MallocSingle();
  return aHit;
}


inline void GenericChamberHit::operator delete(void* aHit) {
  GenericChamberHitAllocator.FreeSingle((GenericChamberHit*) aHit);
}

}  // namespace RAT

#endif  // __RAT_GenericChamber__

