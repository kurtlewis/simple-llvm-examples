#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/LLVMContext.h"

using namespace llvm;

Module* makeLLVMMOdule();

int main(int argc, char**argv) {
  Module * Mod = makeLLVMMOdule();
  verifyModule(*Mod, &errs());

  legacy::PassManager PM;
  PM.add(createPrintModulePass(outs()));
  PM.run(*Mod);

  delete Mod;
  return 0;
}

Module * makeLLVMMOdule() {
  Module * mod = new Module("gcd", getGlobalContext());
  LLVMContext &context = mod->getContext();

  Constant * c = mod->getOrInsertFunction("gcd",
                                          IntegerType::getInt32Ty(context),
                                          IntegerType::getInt32Ty(context),
                                          IntegerType::getInt32Ty(context),
                                          NULL);

  Function * gcd = cast<Function>(c);
  gcd->setCallingConv(CallingConv::C);

  // Add arguments to a function
  Function::arg_iterator args = gcd->arg_begin();
  Value * x = args++;
  x->setName("x");
  Value * y = args++;
  y->setName("y");

  // Blocks correspond to nodes in "tree" of program execution
  // Uses LLVM's automatic naming
  BasicBlock * entry = BasicBlock::Create(getGlobalContext(), "entry", gcd);
  BasicBlock * ret = BasicBlock::Create(getGlobalContext(), "return", gcd);
  BasicBlock * cond_false = BasicBlock::Create(getGlobalContext(), "cond_false", gcd);
  BasicBlock * cond_true = BasicBlock::Create(getGlobalContext(), "cond_true", gcd);
  BasicBlock * cond_false_2 = BasicBlock::Create(getGlobalContext(), "cond_false", gcd);

  // Code Generation starts with "builder" 
  IRBuilder<> builder(entry);
  Value * xEqualsY = builder.CreateICmpEQ(x, y, "tmp");
  builder.CreateCondBr(xEqualsY, ret, cond_false);

  // Instead of creating new IRBuilder for each block, we can retarget our existing one
  // This saves on construction and memory allocation costs
  builder.SetInsertPoint(ret);
  builder.CreateRet(x);

  // cond_false is a more interesting block
  builder.SetInsertPoint(cond_false);
  Value * xLessThanY = builder.CreateICmpULT(x, y, "tmp");
  builder.CreateCondBr(xLessThanY, cond_true, cond_false_2);

  // Concerned with CreateCall and LLVM-3.8

  // Last two blocks are similar, they both contian recursive calls albeit w/ dif. params
  // A vector is used to hold args. for a call instruction
  builder.SetInsertPoint(cond_true);
  Value * yMinusX = builder.CreateSub(y, x, "tmp");
  std::vector<Value *> args1;
  args1.push_back(x);
  args1.push_back(yMinusX);
  Value * recur_1 = builder.CreateCall(gcd, args1.begin(), args1.end(), "tmp");
  builder.CreateRet(recur_1);

  builder.SetInsertPoint(cond_false_2);
  Value * xMinusY = builder.CreateSub(x, y, "tmp");
  std::vector<Value *> args2;
  args2.push_back(xMinusY);
  args2.push_back(y);
  Value * recur_2 = builder.CreateCall(gcd, args2.begin(), args2.end(), "tmp");
  builder.CreateRet(recur_2);

  return mod;
}