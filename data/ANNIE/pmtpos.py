'''A script to generate totally made-up but plausible PMT locations for
ANNIE, written to a PMTINFO ratdb table.
'''

import numpy as np

header = '''{
name: "PMTINFO",
valid_begin: [0, 0],
valid_end: [0, 0],
'''

footer = '''}
'''

# Top array (78 PMTs)
ax = np.linspace(-1350, 1350, 13)
ay = np.linspace(-615, 615, 6)
pos = np.empty(shape=(len(ax)*len(ay), 2))
for i in range(len(ax)):
    for j in range(len(ay)):
        pos[len(ay)*i + j] = np.array((ax[i], ay[j]))

# Bottom array (21 PMTs)
ax = np.linspace(-1350, 1350, 7)
ay = np.linspace(-500, 500, 3)
posb = np.empty(shape=(len(ax)*len(ay), 2))
for i in range(len(ax)):
    for j in range(len(ay)):
        posb[len(ay)*i + j] = np.array((ax[i], ay[j]))

# Join 'em
dirz = np.hstack(([-1.0] * len(pos), [1.0] * len(posb)))
posz = np.hstack(([1250.0] * len(pos), [-1250.0] * len(posb)))
pos = np.vstack((pos, posb))

# Output to RATDB file
fmap = lambda x: '%1.1f' % x
imap = lambda x: '%i' % x
with open('PMTINFO.ratdb', 'w') as f:
    f.write(header)

    xs = 'x: [' + ', '.join(map(fmap, pos[:,0])) + '],\n'
    ys = 'y: [' + ', '.join(map(fmap, pos[:,1])) + '],\n'
    zs = 'z: [' + ', '.join(map(fmap, posz)) + '],\n'
    ts = 'type: [' + ', '.join(['1'] * len(pos)) + '],\n'

    dsx = 'dir_x: [' + ', '.join(['0.0'] * len(pos)) + '],\n'
    dsy = 'dir_y: [' + ', '.join(['0.0'] * len(pos)) + '],\n'
    dsz = 'dir_z: [' + ', '.join(map(fmap, dirz)) + '],\n'

    f.write(xs)
    f.write(ys)
    f.write(zs)
    f.write(dsx)
    f.write(dsy)
    f.write(dsz)
    f.write(ts)

    f.write(footer)

