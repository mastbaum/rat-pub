{
name: "GEO",
index: "world",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "", // world volume has no mother
type: "box",
size: [20000.0, 20000.0, 20000.0], // mm, half-length
material: "rock",
invisible: 1,
}

{
name: "GEO",
index: "hall",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "world",
type: "box",
size: [2250.0, 2250.0, 5810.0],
position: [500.0, 1000.0, 4300.0],
material: "air",
color: [0.9, 0.9, 1.0, 0.1],
}

{
name: "GEO",
index: "upper_deck",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [2245.0, 2245.0, 150.0],
position: [0.0, 0.0, 2750.0],
material: "stainless_steel",
color: [0.5, 0.5, 0.5, 0.5],
drawstyle: "wireframe",
}

{
name: "GEO",
index: "lower_deck",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [2245.0, 2245.0, 150.0],
position: [0.0, 0.0, -1067.0],
material: "stainless_steel",
color: [0.5, 0.5, 0.5, 0.5],
drawstyle: "wireframe",
}

{
name: "GEO",
index: "upper_stairs",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [500.0, 1700.0, 100.0],
position: [1600.0, 0.0, 750.0],
rotation: [70.0, 0.0, 0.0],
material: "stainless_steel",
color: [0.5, 0.5, 0.5, 0.5],
drawstyle: "wireframe",
}

{
name: "GEO",
index: "lower_stairs",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [500.0, 2250.0, 100.0],
position: [1600.0, 250.0, -3500.0],
rotation: [70.0, 0.0, 0.0],
material: "stainless_steel",
color: [0.5, 0.5, 0.5, 0.5],
drawstyle: "wireframe",
}

{
name: "GEO",
index: "vessel",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
type: "box",
size: [1500.0, 750.0, 1500.0],
position: [-500.0, -1000.0, -4300.0],
material: "stainless_steel",
color: [0.5, 0.5, 0.5, 0.1],
}

{
name: "GEO",
index: "liner",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "vessel",
type: "box",
size: [1499.0, 749.0, 1499.0],
material: "acrylic_black",
invisible: 1,
}

{
name: "GEO",
index: "target",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "liner",
type: "box",
size: [1498.0, 748.0, 1498.0],
material: "water",
color: [0.0, 0.0, 1.0, 0.1],
}

{ 
name: "GEO", 
index: "pmts", 
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "target", 
type: "pmtarray", 
pmt_type: "r1408", 
pmt_detector_type: "idpmt",
sensitive_detector: "/mydet/pmt/inner", 
efficiency_correction: 1.027,  
pos_table: "PMTINFO", 
orientation: "manual",
} 

{
name: "GEO",
index: "muon_veto_vessel",
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "hall",
material: "stainless_steel",
type: "box",
size: [1500.0, 200.0, 1500.0, ],
position: [-500.0, -2000.0, -4300.0],
invisible: 1,
}

{
name: "GEO",
index: "muon_veto",
valid_begin: [0, 0], 
valid_end: [0, 0], 
mother: "muon_veto_vessel",
material: "acrylic_uvt",
//sensitive_detector: "/mydet/veto/genericchamber",
type: "box",
size: [1498.0, 198.0, 1498.0, ],
color: [1.0, 0.0, 0.0, 0.2],
}

{
name: "GEO",
index: "mrd_vessel",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "hall",
material: "stainless_steel",
type: "box",
size: [1255.0, 630.0, 1255.0],
position: [-500.0, 400.0, -4300.0],
invisible: 1,
}

{
name: "GEO",
index: "mrd_scintillator",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_vessel",
material: "scintillator",
type: "box",
//sensitive_detector: "/mydet/veto/genericchamber",
size: [1250.0, 625.0, 1250.0],
color: [0.0, 1.0, 0.0, 0.2],
}

{
name: "GEO",
index: "mrd_plank_0",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, -525.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_1",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, -430.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_2",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, -335.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_3",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, -239.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_4",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, -143.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_5",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, -48.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_11",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, 525.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_10",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, 430.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_9",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, 335.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_8",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, 239.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_7",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, 143.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

{
name: "GEO",
index: "mrd_plank_6",
valid_begin: [0, 0],
valid_end: [0, 0],
mother: "mrd_scintillator",
material: "stainless_steel",
size: [1250.0, 25.0, 1250.0],
position: [0.0, 48.0, 0.0],
type: "box",
color: [0.2, 0.2, 0.2, 0.1],
}

