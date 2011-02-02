
import subprocess
import os
import time
import sys

#compile = 'javac -cp src src/usrbincrash.java'

run     = sys.argv[1]
testdir = sys.argv[2] + '/'

if (not os.path.exists(run)):
    sys.stderr.write('File ' + run + ' is not exist\n')
    sys.exit(1)

if (not os.path.exists(run)):
    sys.stderr.write('Directory ' + testdir + ' is not exist\n')
    sys.exit(1)

names = {}
for filename in os.listdir(testdir):
    basename, extension = filename.split('.')	
    names[basename] = 1

#sys.stdout.write('Compilation...')
#starttime = time.time()
#res = subprocess.Popen(compile, stdout=subprocess.PIPE)
#result = res.stdout.read()
#sys.stdout.write(str(time.time() - starttime)+' sec.\n')

print 'Testing...'
files = names.keys()
files.sort()

total_time = 0

index = 1
for file in files:

    infilename  = testdir + file + ".in"	
    outfilename = testdir + file + ".out"	

    sys.stdout.write(str(index)+". ")
    sys.stdout.write(infilename)

    starttime = time.time()
    res = subprocess.Popen([run, infilename], stdout=subprocess.PIPE)	
    result = res.stdout.read().strip().replace( "\n", "" ) 	
    execution_time = time.time() - starttime
    total_time += execution_time	

    check_result = open(outfilename, 'r').readline().strip().replace( "\n", "" ) 

    sys.stdout.write(' Result = ' + str(result) + ' ')
    sys.stdout.write(' (')
    sys.stdout.write(str(execution_time))
    sys.stdout.write(' sec.)\n')
    if (result != check_result):
        sys.stdout.write("\n")
        print '======= ERROR ==============='
        print 'Result:', result, 'Right result:', check_result
        print '======= ERROR ==============='
        print
    index += 1	

print '======================================================='
print 'Done in (sec): ', total_time




