#!/bin/bash
''':'


exec python2 "$0" "$@"

exit 0

':'''

import sys

f = open(sys.argv[1], "rb")
 
try:
	while True:
		bytes = f.read(1)
		if bytes == "":
			break;
		print "%02X " % ord(bytes[0])
 
except IOError:
	pass
finally:
	f.close()
