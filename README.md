<!-- TOC -->

- [CXX](#cxx)
    - [General](#general)
    - [Thread](#thread)
    - [Smart Pointer](#smart-pointer)
    - [Regular Expression](#regular-expression)
    - [FILE I/O](#file-io)
    - [Random Numbers](#random-numbers)
    - [Atomic library](#atomic-library)
    - [Containers](#containers)
    - [Fold expression](#fold-expression)
    - [Design pattern](#design-pattern)
        - [Behavioural](#behavioural)
        - [Creational](#creational)
        - [Structural](#structural)
- [License](#license)

<!-- /TOC -->

# CXX
Simple test apps using C++11/14/17/20.
For C++17 support, use gcc-8 `(g++ (Ubuntu 8.2.0-1ubuntu2~18.04) 8.2.0)`
  - For installation on Ubuntu 18.04 LTS `sudo apt install gcc-8`

## General
- [nullptr](general/nullptr.cc)
- [Data type overflow](general/type_overflow.cc)
- [Elapsed time](general/elapsed_time.cc)
- [Timer with callback](general/cc_timer.cc)
- [Erase/Remove idiom](general/erase_remove.cc)
- [Show type of an object](general/print_type.cc)
- [Iterator implementation -- simple collection class](general/iterator_1.cc)
- [Iterator implementation -- begin and end funcs](general/iterator_2.cc)
- [Iterator implementation -- read iterator](general/iterator_3.cc)
- [Print date & time](general/print_time.cc)
- [String utilities](general/string_utils.cc)

## Thread
- [Create a thread simple/pass parameter/lambda](thread/01-thread.cc)
- [Thread with managing functions](thread/02-thread.cc)
- [Thread with affinity](thread/03-thread.cc)
- [Simple mutex](thread/20-thread.cc)
- [Recursive mutex](thread/21-thread.cc)
- [Lock guard](thread/22-thread.cc)
- [Shared mutex](thread/23-thread.cc)
- [Shared lock](thread/24-thread.cc)
- [Scoped lock](thread/25-thread.cc)
- [Unique lock](thread/26-thread.cc)
- [Conditional variable](thread/30-thread.cc)
- [ASync](thread/60-thread.cc)
- [Packaged task](thread/61-thread.cc)
- [Future/Promise](thread/62-thread.cc)
- [Shared future](thread/63-thread.cc)
- [ASync with std::vector<std::future<void>>](thread/64-thread.cc)
- [ASync with std::vector<std::future<int>>](thread/65-thread.cc)

## Smart Pointer
- [auto_ptr](smart_pointers/01-pointer.cc)
- [unique_ptr](smart_pointers/02-pointer.cc)
- [shared_ptr](smart_pointers/03-pointer.cc)
- [weak_ptr](smart_pointers/04-pointer.cc)

## Regular Expression
- [Match an expression](regex/01-regex.cc)
- [Search an expression](regex/02-regex.cc)
- [Search an expression using interators](regex/03-regex.cc)
- [Replace an expression](regex/04-regex.cc)

## FILE I/O
- [Current & Temp directories and sizes](filesystem/01-fs_test.cc)
- [Evaluation of a path](filesystem/02-fs_test.cc)
- [Directory iterator](filesystem/03-fs_test.cc)
- [Directory watcher](filesystem/04-fs_test.cc)

## Random Numbers
- [Different distribution usage](random/01-random.cc)
- [Different engine usage](random/02-random.cc)
- [Mersenne twister](random/03-random.cc)
- [discrete_distribution](random/04-random.cc)
- [piecewise_constant_distribution](random/05-random.cc)
- [piecewise_linear_distribution](random/06-random.cc)

## Atomic library
- [std::atomic<bool>](atomic/01-atomic.cc)
- [std::atomic_flag / Spinlock](atomic/02-atomic.cc)
- [std::atomic_uint64_t with exchange](atomic/03-atomic.cc)
- [std::atomic with POD](atomic/04-atomic.cc)
- [std::atomic with shared ptr](atomic/05-atomic.cc)

## Containers
- [std::stack usage](containers/01-containers.cc)
- [std::queue usage](containers/02-containers.cc)
- [std::priority_queue usage](containers/03-containers.cc)
- [std::map usage](containers/04-containers.cc)
- [std::multimap usage](containers/05-containers.cc)
- [std::unordered_map, std::unordered_multimap usage](containers/06-containers.cc)

## Fold expression
- [Simple fold expression](fold/01-fold.cc)
- [Fold expression with associativity](fold/02-fold.cc)
- [Misc usage](fold/03-fold.cc)

## Design pattern
### Behavioural
- [Chain of responsiblity](design_pattern/behavioural/chain_of_resp.cc)
- [Command](design_pattern/behavioural/command.cc)
- [Iterator](design_pattern/behavioural/iterator.cc)
- [Mediator](design_pattern/behavioural/mediator.cc)
- [Memento](design_pattern/behavioural/memento.cc)
- [Observer](design_pattern/behavioural/observer.cc)
- [State](design_pattern/behavioural/state.cc)
- [Strategy](design_pattern/behavioural/strategy.cc)
- [Template Method](design_pattern/behavioural/template_method.cc)
- [Visitor](design_pattern/behavioural/visitor.cc)

### Creational
- [Abstract Factory - 1](design_pattern/creational/abstract_factory_v1.cc)
- [Abstract Factory - 2](design_pattern/creational/abstract_factory_v2.cc)
- [Builder](design_pattern/creational/builder.cc)
- [Prototype](design_pattern/creational/prototype.cc)
- [Singleton](design_pattern/creational/singleton.cc)

### Structural
- [Adapter](design_pattern/structural/adapter.cc)
- [Bridge](design_pattern/structural/bridge.cc)
- [Composite](design_pattern/structural/composite.cc)
- [Decorator](design_pattern/structural/decorator.cc)
- [Facade](design_pattern/structural/facade.cc)
- [Flyweight](design_pattern/structural/flyweight.cc)
- [Proxy](design_pattern/structural/proxy.cc)

# License
[MIT](LICENSE)
