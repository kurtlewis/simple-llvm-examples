LLVM = `llvm-config --cxxflags --ldflags --libs --system-libs`

mul_add: mul_add.cc
	g++ -o $@ $^ $(LLVM)

clean:
	rm mul_add

