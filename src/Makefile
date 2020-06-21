
.PHONY: module
module:
	c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` testcompression.cpp -o testcompression`python3-config --extension-suffix`

.PHONY: clean
clean:
	rm -frd *.so *.cdt

.PHONY: test
test:
	pytest
