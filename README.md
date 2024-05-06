<!-- TOC -->

- [CXX](#cxx)
    - [General](#general)
    - [Chrono](#chrono)
    - [Thread](#thread)
    - [Smart Pointer](#smart-pointer)
    - [Regular Expression](#regular-expression)
    - [FILE I/O](#file-io)
    - [Random Numbers](#random-numbers)
    - [Atomic library](#atomic-library)
    - [Containers](#containers)
    - [Fold expression](#fold-expression)
    - [Misc](#misc)
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
- [Erase/Remove idiom](general/erase_remove.cc)
- [Show type of an object](general/print_type.cc)
- [Iterator implementation -- simple collection class](general/iterator_1.cc)
- [Iterator implementation -- begin and end funcs](general/iterator_2.cc)
- [Iterator implementation -- read iterator](general/iterator_3.cc)
- [String utilities](general/string_utils.cc)
- [variant](general/variant.cc)
- [Bitset usage](general/bitset-01.cc)
- [std::bitset + bit algo usage](general/bitset-02.cc)
- [Structure bindings](general/structure_bindings.cc)
- [Tuple usage](general/tuple-01.cc)
- [algorithm](general/algorithm.cc)
- [algorithm @ `copy`](general/algorithm_copy.cc)
- [algorithm @ heap - 01](general/algorithm_heap_01.cc)
- [algorithm @ heap - 02](general/algorithm_heap_02.cc)
- [algorithm @ heap - 03](general/algorithm_heap_03.cc)
- [algorithm @ heap - 04](general/algorithm_heap_04.cc)
- [Type traits usage - 01](general/type_traits-01.cc)
- [Type traits usage - 02](general/type_traits-02.cc)
- [Type traits usage - 03](general/type_traits-03.cc)
- [Type traits usage - 04](general/type_traits-04.cc)

## Chrono
- [Calculate elapsed time](chrono/01-chrono.cc)
- [Calculate elapsed time using a generic func](chrono/02-chrono.cc)
- [Print date & time](chrono/03-chrono.cc)
- [Timer functionality with callback](chrono/04-chrono.cc)
- [Manipulate different clocks](chrono/05-chrono.cc)
- [Number of days between two dates](chrono/05-chrono.cc)
- [Determine the day of the week from a date](chrono/06-chrono.cc)
- [Day of the week](chrono/07-chrono.cc)
- [Calendar of a month](chrono/08-chrono.cc)

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
- [std::multimap & std::multiset usage](containers/05-containers.cc)
- [std::unordered_map, std::unordered_multimap usage](containers/06-containers.cc)
- [std::unordered_map with enum class](containers/07-containers.cc)
- [std::unordered_map with custom hash or structure](containers/08-containers.cc)
- [Find a pair in std::vector](containers/09-containers.cc)
- [std::unordered_map access by index](containers/10-containers.cc)
- [Container usage of reserve, size and capacity](containers/11-containers.cc)
- [Remove an element from the container](containers/12-containers.cc)

## Fold expression
- [Simple fold expression](fold/01-fold.cc)
- [Fold expression with associativity](fold/02-fold.cc)
- [Misc usage](fold/03-fold.cc)

## Misc
- [Generate all possible combinations](misc/01-misc.cc)
- [Map a value of one range to another range](misc/02-misc.cc)
- [General lookup table compile time](misc/03-misc.cc)
- [String tokenization](misc/04-misc.cc)

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
