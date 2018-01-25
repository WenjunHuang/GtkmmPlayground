//
// Created by rick on 2018/1/24.
//
#include "catch.hpp"
#include "BuildApplication.h"

TEST_CASE("build_app","[gtkmm]"){
    auto application = BuildApplication::create();
    application->run();
}
