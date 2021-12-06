# SerowLang

The Serow language written for https://github.com/langjam/jam0002

This language embraces the Plan9 regular expressions along with the ability to pattern match abstract symbol trees and time itself in a simple lambda calculus based interpreter.

Sam reference card for regular expressions: http://sam.cat-v.org/cheatsheet/sam-refcard.pdf

## Basic Usage

This project requires a recent version of clang to be installed (developed on 13.0.0), see https://clang.llvm.org/
Testing requires a recent version of cunit to be installed (developed on 2.1.3-3), see http://cunit.sourceforge.net/

After you first check out this code make sure you run:

`make serow`

 * To run tests issue the following command:

`make test`

 * To clean up resources, make the project and run tests issue the following command:

`make clean all`

 * To run a script issue the following command, replacing the filename accordingly:

`./serow ./test/resources/01/main.slc`

 * To run a script issue the following command, replacing the filename accordingly:

`./serow ./test/resources/01/main.slc`

## Future Improvements

Bootstraping the compiler by writing it in Serow would be an interesting experiment as most of software is about moving data and transforming it into something else (hopefully by way of using readable patterns that are also easy to generate).

REPL for more interactive development might be possible, but it is certainly not a trivial task.  Those who dare to explore this feature have been warned...

Refining the time bending aspect of the code sounds wonderful, but if this feature becomes too powerful, it might break the space-time continuum.  The ultimate challenge would be if anyone can write anything useful with just this feature.

Constriants and goal oriented programming is something to be explored for future improvements to unit/integration testing, but dependent types should suffice for now since they satisfy the ultimate constraint, "That which can be proved must be proven; however, that which cannot be proven should be trusted but verified."
