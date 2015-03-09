// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <TestMessage.h>
#include <TestCase.h>
#include <Exception.h>

using namespace RTF;

TestCase::TestCase(std::string name)
    : RTF::Test(name),
    successful(true),
    result(NULL)
{
}

TestCase::~TestCase() {

}

bool TestCase::succeeded() {
    return successful;
}

TestResult* TestCase::getResult() {
    return result;
}

bool TestCase::setup() {
    return true;
}


void TestCase::tearDown() { }


void TestCase::run(TestResult &rsl) {
    this->result = &rsl;
    // call setup/run/tearDown
    try {
        result->startTest(this);
        if (!setup()) {
            result->addError(this, RTF::TestMessage("setup() failed!"));
            successful = false;
            return;
        }
        run();
        tearDown();
        result->endTest(this);
    }
    catch(RTF::TestFailureException& e) {
        successful = false;
        result->addFailure(this, e.message());
    }
    catch(RTF::TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(std::exception& e) {
        successful = false;
        result->addError(this, RTF::TestMessage(e.what()));
    }
}
