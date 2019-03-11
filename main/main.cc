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
  Module* Mod = makeLLVMModule();

  verifyModule(*Mod, &errs());

  legacy::PassManager PM;
  PM.add(createPrintModulePass(outs()));
  PM.run(*Mod);

  delete Mod;
  return 0;
}



Module* makeLLVMModule() {
  // Module Construction
  Module* mod = new Module("test", getGlobalContext());
  LLVMContext &context = mod->getContext(); 

  Constant* c = mod->getOrInsertFunction("main",
  /*ret type*/                           IntegerType::getInt32Ty(context),
  /*varargs terminated with null*/       NULL);
    
  Function* main = cast<Function>(c);
  main->setCallingConv(CallingConv::C);


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

