//
// Created by xxzyjy on 2018/1/14.
//

#include <iostream>
#include <catch.hpp>
#include "HelloWorld.h"
#include "TestFixture.h"

HelloWorld::HelloWorld() : _button("Hello World") {
  set_border_width(10);
  _button.signal_clicked().connect([]() {
    std::cout << "Hello World" << std::endl;
  });

  add(_button);
  _button.show();
}

TEST_CASE("hello_world","[gtkmm]"){
  HelloWorld helloworld;
  app->run(helloworld);
}
