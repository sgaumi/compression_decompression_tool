
.PHONY: module
module:
	c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` testcompression.cpp -o testcompression`python3-config --extension-suffix`

.PHONY: clean
clean:
	rm -frd *.so *.cdt
	rm -frd ../file_test/all*
	echo "aaaaaaaaaa" >> ../file_test/alla.txt
	echo "bbbbbbbbbb" >> ../file_test/allb.txt
	echo "cccccccccc" >> ../file_test/allc.txt

.PHONY: test
test:
	cd ../script_test && python3 -m pytest -v -s
