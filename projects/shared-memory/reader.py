import mmap

file = "/tmp/shared-memory-file"

with open(file, "r+b") as f:
    mm = mmap.mmap(f.fileno(), 0)
    print mm.readline()
    mm.close()