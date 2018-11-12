#coding:utf-8

import fcntl
import time

fp = open('./l','r')
print('wait to lock')
fcntl.flock(fp, fcntl.LOCK_EX)
print('get lock')
time.sleep(20)
fcntl.flock(fp, fcntl.LOCK_UN)
print('unlock')
fp.close()
