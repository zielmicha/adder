#!/usr/bin/python
import subprocess
import os
import sys
import tempfile
import ctypes
import shutil
import re

adder_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

_makefile = open(os.path.join(adder_root, 'Makefile')).read()
object_files = re.search('OBJECTFILES=(.+)', _makefile).group(1).split()

def main():
    subprocess.check_call(['make', 'adder.a'], cwd=adder_root, stdout=open('/dev/null', 'w'))
    if len(sys.argv) > 1:
        test_names = sys.argv[1:]
    else:
        test_names = [ os.path.join(adder_root, 'tests', name)
                       for name in os.listdir(os.path.join(adder_root, 'tests'))
                       if name.startswith('test') and name.endswith('.c') ]
    print 'testing', ', '.join(test_names), '...'
    for test_name in test_names:
        test(test_name)

def test(path):
    test_do(path)

def test_do(path):
    CC =  ['gcc', '-I', adder_root, '-g']
    exe = path + '.so'
    subprocess.check_call(CC + [ os.path.join(adder_root, name) for name in object_files ] +
            [path, '-o', exe, '-fPIC', '-shared'])
    names = get_test_names(exe)
    dll = ctypes.CDLL(exe)
    for name in names:
        print '\t', name,
        func = getattr(dll, '_adder_testcase_' + name)
        pid = os.fork()
        if not pid:
            result = dll.adder_call_test(func)
            os._exit(0)
        else:
            pid, exit = os.wait()
            if exit == 256:
                print 'fail'
            elif exit != 0:
                print '- process exited with signal', exit
            else:
                print 'ok'

def get_test_names(exe):
    symbols_dump = subprocess.check_output(['objdump', '-t', exe])
    symbols_tests = [ match.group(1) for match in re.finditer(' _adder_testcase_(.+)', symbols_dump) ]
    return symbols_tests

if __name__ == '__main__':
    main()
