import glob
import os
def mklist(ind, listname, outf, outfph):
    d = "{}/{}/".format(os.getcwd(), ind)
    flist = glob.glob("{}*/**/*.[ch]pp".format(d), recursive=True) + glob.glob("{}*.[ch]pp".format(d))
    flist = [x.replace("\\", "/") for x in flist]
    phlist = []
    for fname in flist:
        with open(fname, 'r') as f:
            if "//PRIVATE" not in f.readline():
                phlist.append(fname)
            else:
                print("Private header: " + fname)

    with open(d+outf, 'w') as f:
        f.write("set(\n\t{}_SOURCE_LIST".format(listname))
        for fname in flist:
            f.write("\n\t${CURDIR}"+fname[fname.index(ind) + len(ind):])
        f.write("\n)")
    with open(d+outfph, 'w') as f:
        f.write("set(\n\t{}_PUBLIC_HEADERS".format(listname))
        for fname in phlist:
            f.write("\n\t${CURDIR}"+fname[fname.index(ind) + len(ind):])
        f.write("\n)")


print("Generating framework file list...")
mklist("src/Framework", "DEVA_FRAMEWORK", "SourceList.cmake", "PublicHeaders.cmake")
print("Generating engine file list...")
mklist("src/Engine", "DEVA_ENGINE", "SourceList.cmake", "PublicHeaders.cmake")
