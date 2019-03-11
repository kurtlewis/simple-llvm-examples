#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

Module* makeLLVMModule();

int main(int argc, char**argv) {
  // Generate the module using our function
  Module* Mod = makeLLVMModule();

  // check the module for errors, if they are found, send them to stderr
  verifyModule(*Mod, &errs());

  // Build a legacy PassManager and tell it to do a pass where it prints
  // the memory-structure as IR to standard out
  // then run the PassManager on our module
  legacy::PassManager PM;
  PM.add(createPrintModulePass(outs()));
  PM.run(*Mod);

  // clean up and return
  delete Mod;
  return 0;
}



Module* makeLLVMModule() {
  // Module Construction
  Module* mod = new Module("test", getGlobalContext());

  // get local context for module
  LLVMContext &context = mod->getContext(); 

  // define function. It returns a constant because functions are not variable,
  // and always of a consistent type
  Constant* c = mod->getOrInsertFunction("main",
  /*ret type*/                           IntegerType::getInt32Ty(context),
  /*varargs terminated with null*/       NULL);
    
  // make a function object from the constant return value
  Function* main = cast<Function>(c);
  // Tell the function it'll have the calling conventions of a C program
  // makes it compatible with C
  main->setCallingConv(CallingConv::C);


  // define our block and call it entry (label)
  BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", main);
  IRBuilder<> builder(block);

  // Create Arbitrary precision integer 
  APInt num(32, 15, true);
  // use that integer to make a constant
  Constant* val = ConstantInt::getIntegerValue(IntegerType::getInt32Ty(context),
                                               num);
  // return the constant value
  builder.CreateRet(val);
        
  return mod;
}

