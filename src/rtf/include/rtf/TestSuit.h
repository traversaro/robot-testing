// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTSUIT_H
#define _RTF_TESTSUIT_H

#include <rtf/rtf_config.h>
#include <rtf/Test.h>
#include <rtf/TestResult.h>
#include <rtf/TestMessage.h>
#include <rtf/FixtureManager.h>
#include <vector>

namespace RTF {
    class TestSuit;
}


/**
 * \ingroup key_class
 *
 * \brief The TestSuit holds a group of tests. When the \c run() method of a
 * TestSuit is called, it executes all its tests. A TestSuit can also has a FixtureManager.
 * In this case, it calls the \c setup() method of FixtureManager to setup any fixture which
 * is required for the tests before executing the tests. After running all the tests, the \c tearDown()
 * method of the FixtureManager is called to tear down the fixture.
 *
 * The \c fixtureCollapsed method is used by a fixture manager to inform the test suit
 * that the corresponding fixture has been collapsed. In this case, an exception is thrown
 * by the TestSuit and the remaining tests will not be executed any more.  This method can be
 * also overriden by a subclass if any specific action is required to be taken (such as retrying
 * to setup the fixture and runing the reamining tests) upon collapsing the fixture.
 *
 * Here's an example of using a TestSuit:
 * \include examples/simple_suit.cpp
 */
class RTF_API RTF::TestSuit : public RTF::Test, public RTF::FixtureEvents {

    typedef std::vector<RTF::Test*> TestContainer;
    typedef std::vector<RTF::Test*>::iterator TestIterator;
    typedef std::vector<RTF::FixtureManager*> FixtureContainer;
    typedef std::vector<RTF::FixtureManager*>::iterator FixtureIterator;

public:

    /**
     * TestSuit constructor
     * @param  name The TestSuit name
     */
    TestSuit(std::string name);

    /**
     *  TestSuit destructor
     */
    virtual ~TestSuit();

    /**
     * Adding a new test
     * @param test pointer to a Test object
     */
    void addTest(RTF::Test* test);

    /**
     * Remove a test
     * @param test pointer to a Test object
     */
    void removeTest(RTF::Test* test);

    /**
     * Clear the test list
     */
    void reset();

    /**
     * @brief addFixtureManager  add a fixture manager for
     * the current test suit.
     * @param manager an instance of FixtureManager
     */
    void addFixtureManager(RTF::FixtureManager* manager);

    /**
     * @brief fixtureCollapsed is called by a fixture manager
     *        (if it is already setup) to inform the test suit
     *        that the corresponding fixture has been collapsed.
     * @param reason An error message indicates the reason for
     *        collapsing the fixture.
     */
    virtual void fixtureCollapsed(RTF::TestMessage reason);

    /**
     * the main caller of a TestSuit inherited from Test Class.
     * @param result an instance of a TestResult
     * to collect the result of the test.
     */
    virtual void run(TestResult &result);

    /**
     * @brief interrupt interrupts the current test run
     */
    virtual void interrupt();

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    bool succeeded() const;

    /**
     * @brief getResult returns an instance of TestResult
     * if run(TestResult &result) has been already called
     * by a TestRunner
     * @return an instance of TestResult
     */
    RTF::TestResult* getResult();

protected:
    /**
     * @brief setup is called before the test run
     * @return true or false depending of the test initialization
     */
    virtual bool setup();

    /**
     * @brief tearDown is called after the test run
     */
    virtual void tearDown();

private:
    RTF::Test* current;
    RTF::TestResult* result;
    bool successful;
    bool fixtureOK;
    bool interrupted;
    RTF::TestMessage fixtureMesssage;
    FixtureContainer fixtureManagers;
    TestContainer tests;
};
#endif // _RTF_TESTSUIT_H
