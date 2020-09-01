#!/usr/bin/python3
# nst0022 2020-09-01 converted from Python2 to Python3

pattern='Aframax_tanker_%s.obj'

for (name, udelta) in [('Sky',0.125), ('Grey',0.5), ('Black', 0.625)]:
    infile =open(pattern % 'Blue', 'r', newline='')
    outfile=open(pattern % name, 'w')
    for line in infile:
        if line.startswith('VT'):
            c=line.split()
            if (c[7] in ['0.9063', '0.9688'] and c[8] in ['0.0313', '0.0938']):
                d=list(map(float, c[1:]))
                d[6] -= udelta
                outfile.write('VT\t%9.4f %9.4f %9.4f\t%6.3f %6.3f %6.3f\t%6.4f %6.4f\n' % tuple(d))
            else:
                outfile.write(line)
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
