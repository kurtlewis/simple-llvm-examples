LLVM = `llvm-config --cxxflags --ldflags --libs --system-libs`

llvm-main: main.cc
	g++ -o $@ $^ $(LLVM)

main: llvm-main
	./llvm-main > main.ll
	llc main.ll -o main.s
	g++ main.s -o $@

clean:
	rm llvm-main main.ll main.s main

