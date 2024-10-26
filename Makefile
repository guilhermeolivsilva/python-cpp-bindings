all:
	c++ -O3 -Wall -shared -std=c++14 -undefined dynamic_lookup \
		`python3 -m pybind11 --includes` cpp_example.cpp -o cpp_example`python3-config --extension-suffix` \
		$(python3-config --ldflags)

clean:
	rm -rf *.so