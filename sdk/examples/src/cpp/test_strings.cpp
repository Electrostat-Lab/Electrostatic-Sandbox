#include <string>
#include <iostream>
#include <concepts>

/**
 *
 */
namespace test {
    class string_testing {
        public:
            /**
             * @brief Constructor.
             * Memory allocation should
             * occur here and initialization
             * of the program flow.
             */
            string_testing();

            constexpr string_testing(test::string_testing&& src): string_testing() {

            }
            constexpr string_testing(const test::string_testing& src): string_testing() {

            }

            constexpr test::string_testing& operator=(const test::string_testing&): string_testing() {
                return reinterpret_cast<string_testing&>(*this);
            }

        constexpr test::string_testing& operator=(const test::string_testing&&): string_testing() {
            return reinterpret_cast<string_testing&>(*this);
        }

            /**
             * @brief Destructor.
             * A destructor does not take an argument,
             * and a class can have only one destructor.
             * <p>
             * Destructors are called implicitly when an automatic variable goes out of scope,
             * an object on the free store is deleted, etc.
             * Only in very rare circumstances does the user need to call a
             * destructor explicitly.
             */
            ~string_testing();
//            string_testing& operator=(const test::string_testing& src) {
//                std::cout << "sdsd";
//                return reinterpret_cast<string_testing&>(*this);
//            }
//            string_testing& operator=(test::string_testing&& src) {
//                std::cout << "sdsd";
//                return reinterpret_cast<string_testing&>(*this);
//            }

            void print();

    private:

    };
}

test::string_testing::string_testing() {
    // invoked by the user or the API
    // initialization should take place in this phase
    // heap memory allocation (either static or dynamic)
    // shall be invoked here only, and no other places
    // should leak resources!
    // the complement of the constructor is the destructor
    // and it operates to release the system resources
    // that are acquired here! See the destructor comments.

    // a constructor shall initialize private members and native
    // resources. These are also known as "invariants".
    // Invariants:
    std::cout << "Constructor Called\n";
}

test::string_testing::~string_testing() {
    // invoked autonomously on automatically allocated variables.
    // dispatched implicitly when a free() or delete() operation
    // is invoked on a pointer (virtual memory address) for an
    // allocated object of this construct.
    // A destructor is the logical complement of the constructor
    // that is, it's designed to release system resources acquired
    // during the object construction phase.
    std::cout << "Destructor Called\n";
}

void test_auto_construction() {
    // static stack automatic allocation
    test::string_testing tester{};
    // stack automatic release
}

//void test_construction_leaks() {
//    // static heap allocation
//    test::string_testing *tester = (test::string_testing *) malloc(sizeof (test::string_testing));
//
//    tester->string_testing();
//    // leaking tester object ...
//}

void test_construction_leaks_fix() {
    // C++ static heap manual allocation
    test::string_testing *tester = new test::string_testing();
    // manually release resources
    delete(tester);
}

test::string_testing& get(test::string_testing& s) {
    return s;
}

int main() {
    // print C++ version

//    std::string test = {"hello world\n"};
//    std::string test1 = "hello world111\n";
//    test = test1;
    std::cout << test1;
//    std::cout << test;
    test::string_testing test0;
    test::string_testing test1 {};
    test0 = get(test1);


//    test_auto_construction();
//    int po(2);
//    test_construction_leaks();
    // examples for manipulating C++ string algorithms
    return 0;
}