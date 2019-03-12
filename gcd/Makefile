LLVM = `llvm-config --cxxflags --ldflags --libs --system-libs`

gcd: gcd.cc
	g++ -o $@ $^ $(LLVM)

clean:
	rm gcd

