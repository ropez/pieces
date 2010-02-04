#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main(int argc, char** argv)
{
    CppUnit::TextTestRunner runner;
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();

    // Run all, or one specified test
    CppUnit::Test* test = registry.makeTest();
    if (argc > 1) {
        test = test->findTest(argv[1]);
    }
    runner.addTest(test);

    return runner.run() ? 0 : 1;
}
