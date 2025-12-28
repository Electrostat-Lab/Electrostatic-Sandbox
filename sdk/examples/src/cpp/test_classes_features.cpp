/**
 * @brief A short-listed tutorial for C++11/C++17/C++20 Classes, their features,
 * and some detailed software design conventions.
 *
 * <p>
 * This tutorial concludes the following list:
 * 1) Namespaces and scopes.
 * 2) Classes and their scopes.
 * 3) Class Instance Constructors.
 * 4) Class Members' Constructors.
 * 5) Explicit and Implicit Instance Construction.
 * 6) Destructors.
 * 7) Resource Acquisition Is Initialization (RAII) style of resource management.
 *
 * @copyright The Electrostatic-Sandbox SDK for distributed simulation.
 * @author pavl_g.
 */
#include <string>
#include <variant>
#include <iostream>
#include <typeinfo>

// Design around Resource Acquisition Is Initialization (RAII)
// Design around Constructor-Destructor pairs.
// Design Copy and Move Constructors.
// Define Memory Ownership semantics explicitly.
//

namespace object {
    class base {
    public:
        bool operator==(object::base& o2) noexcept {
            return this == &o2;
        }
        virtual ~base() { }
    };
}

namespace test {
    class string_testing: public object::base {
    public:
        /**
         * @brief Constructor.
         * Memory allocation should
         * occur here and initialization
         * of the program flow.
         */
        string_testing(char *string) noexcept;

        string_testing(test::string_testing&& src) noexcept {
            std::cout << "Move Constructor Invoked!" << std::endl;
        }

        string_testing(const test::string_testing& src) {
            std::cout << "Copy Constructor Invoked!" << std::endl;
        }

        test::string_testing& operator=(const test::string_testing& src) {
            // copy all elements from the src to [this]
            std::cout << "Copy Assignment Invoked!" << std::endl;
            return static_cast<string_testing&>(*this);
        }

        test::string_testing& operator=(const test::string_testing&& src) noexcept {
            // move all elements from the src to [this]
            std::cout << "Move Assignment Invoked!" << std::endl;
            return *this;
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

        const char *get_str() {
            return const_cast<const char *>(str);
        }

        void set_str(const char *string) {
            this->str = (char *) string;
        }

        void move(string_testing& dest, string_testing&& src) {
            dest.str = src.str;
            src.str = nullptr;
        }
    private:
        char *str;

    };
}

test::string_testing::string_testing(char *x) noexcept : str(x)  {
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
    test::string_testing tester{0};
    // stack automatic release
}

void test_construction_leaks_fix() {
    // C++ static heap manual allocation
    test::string_testing *tester = new test::string_testing(0);
    // manually release resources
    delete(tester);
}


namespace copy_utils {
    object::base& move(object::base& dest, object::base&& src) {
        if (src == dest) {
            return dest;
        }
        if (typeid(dest) == typeid(src)) {
            (dynamic_cast<test::string_testing&>(dest)).set_str((dynamic_cast<test::string_testing&>(src)).get_str());
        }
        return dest;
    }
}

int main() {
    // print C++ version
    const char *const x = "sds";

    test::string_testing test0 = {const_cast<char *>("Hello, World\n")};
    // construction by moving
    test::string_testing test1 = std::move(test0);
//    test::string_testing test1 = static_cast<typename std::remove_reference<test::string_testing>::type&&>(test0);

    // construction by copying
    test::string_testing test2 = test1;

    // move assignment
    test0 = std::move(test2);

    // copy assignment
    test2 = std::move(test1);

    return 0;
}