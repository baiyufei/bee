import mmap
import fcntl

file = "/tmp/shared-memory-file-123"

with open(file, "r+b") as f:
    mm = mmap.mmap(f.fileno(), 0)
    print 'wait lock'
    fcntl.flock(f, fcntl.LOCK_EX)
    print 'get lock'
    print mm.readline()
    fcntl.flock(f, fcntl.LOCK_UN)
    mm.close()