#!/usr/bin/env python3
#-*-coding:utf-8-*-
import argparse
import os
import sys
import time
import datetime
import re
import shutil
import fcntl

import io
import sys
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')
 

def throw_error(_error_msg):
    """对于不正规的输入或不符合条件的，抛出异常，退出程序"""
    raise Exception(_error_msg)


def main(argv):
    a = 0

if __name__ == '__main__':
    main(sys.argv)