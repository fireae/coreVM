# The MIT License (MIT)
#
# Copyright (c) 2016 Yanzheng Li
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

"""
Validates the consistency and integrity of the IR assembler and disassembler
tools.
"""

import optparse
import os
import subprocess
import sys


## -----------------------------------------------------------------------------

class colors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

## -----------------------------------------------------------------------------

class Step(object):

    def __init__(self, args_string):
        self.cmdl_args = args_string.split(' ')

    def run(self):
        print subprocess.list2cmdline(self.cmdl_args)
        retcode = subprocess.call(self.cmdl_args)
        if retcode != 0:
            status = '{color}{status}{reset}'.format(
                color=colors.FAIL,
                status='ERROR',
                reset=colors.ENDC)

            print status

        return retcode

## -----------------------------------------------------------------------------

def run(opts):
    ir_dis_path = os.path.join(opts.build_dir, 'ir_dis')
    ir_asm_path = os.path.join(opts.build_dir, 'ir_asm')

    test_suites = (
        (
            'python tools/ir_gen.py --output sample.ir',
            '%s --input sample.ir --output sample.ir.txt' % ir_dis_path,
            '%s --input sample.ir.txt --output sample2.ir' % ir_asm_path,
            '%s --input sample2.ir --output sample2.ir.txt' % ir_dis_path,
            'diff sample.ir.txt sample2.ir.txt',
        ),
        (
            '%s --input src/ir/sample_ir.txt --output sample_ir.bin' % ir_asm_path,
            '%s --input sample_ir.bin --output sample_ir.txt' % ir_dis_path,
            'diff sample_ir.txt src/ir/sample_ir2.txt'
        )
    )

    for test_suite in test_suites:
        for cmd in test_suite:
            if Step(cmd).run() != 0:
                print status
                return False

    return True

## -----------------------------------------------------------------------------

def main():
    parser = optparse.OptionParser(
       usage='usage: %prog [options]',
       version='%prog v1.0') 

    parser.add_option(
        '-d',
        '--build_dir',
        action='store',
        dest='build_dir',
        default='',
        help='Build directory of IR tools'
    )

    opts, _ = parser.parse_args()

    print 'Running IR tools integrity checker...'
    if run(opts):
        print '{color}{status}{reset}'.format(
            color=colors.OKGREEN, status='PASS', reset=colors.ENDC)
    else:
        sys.exit(-1)

## -----------------------------------------------------------------------------

if __name__ == '__main__':
    main()
