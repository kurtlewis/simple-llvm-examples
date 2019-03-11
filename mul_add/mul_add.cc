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

  // verify the module doesn't have errors. If it does, send them to stderr
  verifyModule(*Mod, &errs());

  // create a legacy PassManager and give it a pass for outputting IR
  // to stdout, then tell it to run against our module
  legacy::PassManager PM;
  PM.add(createPrintModulePass(outs()));
  PM.run(*Mod);

  // clean up
  delete Mod;
  return 0;
}



Module* makeLLVMModule() {
  // Module Construction
  Module* mod = new Module("test", getGlobalContext());

  // get module local context for variables
  LLVMContext &context = mod->getContext(); 

  // create a new function, it's a constant because functions aren't mutable
  // define our three args and return type
  Constant* c = mod->getOrInsertFunction("mul_add",
  /*ret type*/                           IntegerType::getInt32Ty(context),
  /*args*/                               IntegerType::getInt32Ty(context),
                                         IntegerType::getInt32Ty(context),
                                         IntegerType::getInt32Ty(context),
  /*varargs terminated with null*/       NULL);
    
  // cast constant return type to a function
  Function* mul_add = cast<Function>(c);
  // tell the function it'll have the calling conventions of a C program
  mul_add->setCallingConv(CallingConv::C);

  // iterate over the arguments to our functions previously typed
  // and give them names 
  Function::arg_iterator args = mul_add->arg_begin();
  Value* x = &*args++;
  x->setName("x");
  Value* y = &*args++;
  y->setName("y");
  Value* z = &*args++;
  z->setName("z");

  // create a block called "entry"
  BasicBlock* block = BasicBlock::Create(getGlobalContext(), "entry", mul_add);
  IRBuilder<> builder(block);

  // do our x * y and store it in a variable called "tmp"
  Value* tmp = builder.CreateBinOp(Instruction::Mul,
                                     x, y, "tmp");

  // do our tmp + z and store it in tmp2
  Value* tmp2 = builder.CreateBinOp(Instruction::Add,
                                        tmp, z, "tmp2");

  // return tmp2
  builder.CreateRet(tmp2);
        
  return mod;
}

